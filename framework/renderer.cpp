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
                      filename_{"file"}, ppm_{width_, height_}, cam_{} {}

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Camera const& cam)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
  , cam_(cam)
{}

void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::shade(Shape const& shape, Ray const& ray, float t, std::vector<Light> const& light_vector, Light const& ambient){
  
  glm::vec3 position = ray.direction + ray.direction*t;
  glm::vec3 normal = glm::normalize(shape.get_normal(position));
  glm::vec3 vec_light = glm::normalize(light_vector[0].position_-position);

  Color ambient_col = ambient.intensity_ * (shape.material_->ka_);
  
  glm::vec3 reflection_vector = glm::normalize((2* glm::dot(normal, vec_light)*normal)-vec_light);
  glm::vec3 camera_vector = glm::normalize(ray.origin -position);
  float ref_vec = pow(glm::dot(reflection_vector,camera_vector),shape.material_->m_);
  Color reflect = (shape.material_->ks_) * std::max(ref_vec,(float)0);

  Color diffuse =  ((light_vector[0].intensity_ *  (shape.material_->kd_)) * glm::dot(normal,vec_light));
  Color end_product = diffuse + ambient_col + reflect;
  return end_product;
  
}

/*void Renderer::render_test(Scene const& scene){
for(int i=0;i<scene.objects.size();i++) {
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      Ray ray;
      ray.origin = glm::vec3{x,y,0};
      ray.direction = glm::vec3{0,0,-1.0};
      float distance=0;
      
        if(scene.objects[i]->intersect(ray,distance)==true){
         p.color = shade(*scene.objects[i], ray, distance, scene.lights, scene.ambient); 
        }else{
          p.color = Color(0.3,0.3,0.5);
        }
      write(p);
      }
      
    }
  }
  ppm_.save(filename_);  
}*/

 void Renderer::render(Scene const& scene){
   float distance = 0;
   bool intersect = false;
   for (unsigned y = 0; y < height_; ++y) {
     float sy= 1.0-y*1.0/height_;
     for (unsigned x = 0; x < width_; ++x) {
       float sx= x*1.0/width_;
       Pixel p(x,y);
       Ray ray= cam_.shoot_ray(sx,sy);
       float closest_distance = 100000;//infinity
       int object = -1; 
       for(int i=0;i<scene.objects.size();i++) {
         intersect = scene.objects[i]->intersect(ray,distance);
         if ((distance < closest_distance) && (intersect == true)) {
           closest_distance = distance;
           object = i;
         }
       }
         if(object != -1) {
           //p.color = Color(0.4,0.0,0.4);
           p.color = shade(*scene.objects[object], ray, distance, scene.lights, scene.ambient);
         } else {
           p.color = Color(0.0,0.0,0.4);
         }        
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