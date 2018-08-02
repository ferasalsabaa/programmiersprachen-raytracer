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



Color Renderer::shade(Shape const& shape, Ray const& ray, float t, int depth){
  Color end{0,0,0};
  glm::vec3 schnittpunkt = ray.origin + ray.direction*t;
  Color ambient_col = scene_.ambient_* (shape.material_->ka_);
   Color reflectedColor{0,0,0};

  for(int i = 0; i < scene_.lights.size(); ++i) {
      
      glm::vec3 normal = glm::normalize(shape.get_normal(schnittpunkt));
      glm::vec3 vec_light = glm::normalize(scene_.lights[i].position_ - schnittpunkt);
      Ray new_ray{schnittpunkt, vec_light};
      new_ray.origin += new_ray.direction * (float)0.001; //no self intersection

      
      bool intersect = false;
      float distance = 1;
      float intersect_value = 0;

      for(int j = 0; j<scene_.objects.size();++j){
        intersect = scene_.objects[j]->intersect(new_ray,distance);
        if (intersect == false) {
          intersect_value = 1;
        } else {
          intersect_value = 0;
        }
            glm::vec3 reflection_vector = glm::normalize((2* glm::dot(normal, vec_light)*normal)-vec_light);
            glm::vec3 camera_vector = glm::normalize(scene_.camera.origin_ -schnittpunkt);
            float ref_vec = std::max(glm::dot(reflection_vector,camera_vector),(float)0);
            Color reflect = (shape.material_->ks_) * pow(ref_vec,shape.material_->m_);

            Color diffuse =  (shape.material_->kd_) * std::max(glm::dot(normal,vec_light),(float)0);
            Color end_product = (scene_.lights[i].calculate_intensity() * (diffuse + reflect)) * intersect_value;
            end += end_product;
          }
      
      }

      //Reflection
      Color closest_reflection = shape.material_->ks_;
      if (depth > 0) {
        glm::vec3 V = ray.direction;
        glm::vec3 N = shape.get_normal(schnittpunkt);
        glm::vec3 reflection_vector = glm::normalize((2* glm::dot(N, V)*N)-V);

        Ray reflectionRay{schnittpunkt, reflection_vector};
        reflectionRay.origin+= reflectionRay.direction * (float)0.001;
        reflectedColor = raytrace(reflectionRay, depth-1);
        end += reflectedColor;
      }
    return (end + ambient_col)/(end + ambient_col + 1);
  }


Color Renderer::raytrace(Ray const& ray, int d) {
  int depth = d;
  Color end{0,0,0};
  float distance = 0;
  bool intersect = false;

  float closest_distance = 100000;//
  int object = -1; 
  for(int i=0;i< scene_.objects.size();i++) {
      intersect = scene_.objects[i]->intersect(ray,distance);
      if ((distance < closest_distance) && (intersect == true)) {
           closest_distance = distance;
           object = i;
      }
    }
    if(object != -1) {
        end = shade(*scene_.objects[object], ray, distance, depth);
      } else {
        end = Color(0.0,0.0,0.4);
      }      

    return end;

}

 void Renderer::render(){
  
   for (unsigned y = 0; y < height_; ++y) {
     for (unsigned x = 0; x < width_; ++x) {
       Pixel p(x,y);
       Ray ray= scene_.camera.shoot_ray(x,y, width_, height_);

       p.color = raytrace(ray,3);
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