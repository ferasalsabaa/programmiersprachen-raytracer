// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include <algorithm>



Renderer::Renderer() : width_{480}, height_{320}, color_buffer_(width_*height_, Color(0.0, 0.0, 0.0)),
                      filename_{"file"}, ppm_{width_, height_}, scene_{} {}

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
  , scene_(scene)
{}

Color reflected_color_contribution(0.0, 0.0, 0.0);
Color Renderer::raytrace(Ray const& ray, int d) {
  Color end{0,0,0};
  float distance = 0;
  bool intersect = false;
  glm::vec3 schnittpunkt;
  glm::vec3 normal_inter;

  intersection_shape intersection_shape1;
  float closest_distance = 100000;//
  int object = -1; 

  //check if any of the objects are hit. Set the closest object to object
  for(int i=0;i< scene_.objects.size();++i) {
      intersection_shape1 = scene_.objects[i]->intersect_new(ray,distance);
      intersect = intersection_shape1.hit;
      if ((distance < closest_distance) && (intersect == true)) {
           closest_distance = distance;
           object = i;
           schnittpunkt = intersection_shape1.position;
           normal_inter = intersection_shape1.normal;
    }
   }
  //if an object is found 
  if(object != -1) {
    // glm::vec3 schnittpunkt = ray.origin + ray.direction*distance;
    // glm::vec3 normale = glm::normalize(scene_.objects[object]->get_normal(schnittpunkt)* glm::vec3{2.0f}+glm::vec3{1.0f}); //*glm::vec3{255.0f});
    // end= Color{normale.x, normale.y, normale.z};
      //necessary Colors
      Color diffuse_col{0,0,0}; //in place implementieren
      Color ambient_col{0,0,0};
      Color reflect_col{0,0,0};
      Color reflectedColor{0,0,0};
      Color refractedColor{0,0,0};

      //calculate the intersection point 
     // glm::vec3 schnittpunkt = ray.origin + ray.direction*distance;
      
      //calculate the influence of the ambient light on the object
      ambient_col = scene_.ambient_* (scene_.objects[object]->get_material()->ka_);
      
      
      //iterate through all lights
      for(int j = 0; j < scene_.lights.size(); ++j){
          
          //calculate normal, light vector and ray between
          glm::vec3 normal = glm::normalize(normal_inter);
          glm::vec3 vec_light = glm::normalize(scene_.lights[j].get_position() - schnittpunkt); 
          Ray new_ray{schnittpunkt, vec_light};
          new_ray.origin += new_ray.direction * (float)0.001; //no self intersection





          
          //check if any objects are between intersection point and light source
          bool intersect1 = false;
          float distance1 = 1;
          float intersect_value = 0;
          intersection_shape shape2;

          for(int k = 0; k<scene_.objects.size();++k){
            shape2 = scene_.objects[k]->intersect_new(new_ray,distance1);
            intersect1 = shape2.hit;
            if (intersect1 == false) {
              intersect_value = 1; //object didnt intersect1
            } else {
              intersect_value = 0;
            }

            //calculate reflection vector and camera vector
            glm::vec3 reflection_vector = glm::normalize((2* glm::dot(normal, vec_light)*normal)-vec_light);
            glm::vec3 camera_vector = glm::normalize(scene_.camera.get_origin() -schnittpunkt);
            float ref_vec = std::max(glm::dot(reflection_vector,camera_vector),(float)0);
            reflect_col = Color(0.0, 0.0, 0.0);//(scene_.objects[object]->get_material()->ks_) * pow(ref_vec,scene_.objects[object]->get_material()->m_); //* scene_.lights[j].calculate_intensity();
            
            //calculate diffuse color
            diffuse_col =  (scene_.objects[object]->get_material()->kd_) * std::max(glm::dot(normal,vec_light),(float)0);
            Color non_reflected_color_contribution = (scene_.lights[j].calculate_intensity() * (diffuse_col )) ;
            non_reflected_color_contribution += reflect_col * intersect_value; 
            
            // do we need real reflection? how strong?
            float perfect_reflection_weight = 0.2;

            ///////

            
            if(d > 0) {
                glm::vec3 V = ray.direction; //calculates the ray we come from
              // glm::vec3 V =  glm::normalize(schnittpunkt-scene_.camera.get_origin());
                //glm::vec3 normal = scene_.objects[object]->get_normal(schnittpunkt); 
              if( (scene_.objects[object]->get_material()->ks_.r > 0.5
                  || scene_.objects[object]->get_material()->ks_.g > 0.5
                  || scene_.objects[object]->get_material()->ks_.b > 0.5)) {           
                glm::vec3 reflection_vector = glm::reflect(V, normal_inter);//glm::normalize((2* (glm::dot(normal_inter, V))*normal_inter)-V);
                Ray reflectionRay{schnittpunkt, reflection_vector};
                reflectionRay.origin += reflectionRay.direction * (float)0.001; //avoid self intersection

                //recursive for three objects
                reflected_color_contribution = raytrace(reflectionRay, d-1);
                //end += reflectedColor; //reduces the brightness of the reflection a bit if i add *0.8?
                
              }else {
              perfect_reflection_weight = 0.0;
            }

            //add to final color
            end +=   non_reflected_color_contribution *  (1.0 - perfect_reflection_weight) +
                     reflected_color_contribution * (perfect_reflection_weight);
            
          }
      }

      //Reflection
        glm::vec3 V = ray.direction; //calculates the ray we come from

        //Check refraction
        int is_opaque = scene_.objects[object]->get_material()->opacity_; 
          if (is_opaque  && d > 0)
          {
            float q;
            float refraction_index = scene_.objects[object]->get_material()->refraction_index_;
            float angle = glm::dot(normal_inter, V);
            // we check if we are in or outside the material. Angle is positive or negative
            if (angle < 0) {
                angle=-angle; 
                q= 1/refraction_index ; //inverse refraction index
            } else {
              q=refraction_index;
              normal_inter =- normal_inter; //need to inverse the normal, go in object
            }

            float c2 = 1-q*q*(1-angle*angle);   //1 for the refration index of air, calculate the angle
            if (c2>0) {
              c2=sqrt(c2);
            } else {
              c2=0; // there is total internal reflection
            }

            glm::vec3 t = glm::normalize( q*V + (q*angle-c2)*normal_inter );   // calculate outgoing vector in new material with fresnel
            Ray refractionRay{schnittpunkt, t}; //create new ray from it
            refractionRay.origin+= refractionRay.direction* (float)0.001; //self intersection
    
            //refractedColor += raytrace(refractionRay, d-1); //do recursively
            end+=refractedColor;
        }
      }
       end = (end + ambient_col)/(end + ambient_col + 1);
      } else {
        end =scene_.ambient_;
      }      
  return end;
}

 void Renderer::render(){
  
   for (unsigned x = 0; x < height_; ++x) {
     for (unsigned y = 0; y < width_; ++y) {
       Pixel p(x,y);
       Ray ray= scene_.camera.shoot_ray(x,y, width_, height_);

       p.color = raytrace(ray,1);
       write(p);
       }
     }
   ppm_.save(filename_);  
}


void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}