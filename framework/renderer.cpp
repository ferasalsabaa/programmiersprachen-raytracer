// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

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

Color shade(Shape const& shape, Ray const& ray, float t, std::vector<Light> const& light_vector){
  glm::vec3 position = ray.direction + ray.direction*t;
  glm::vec3 normal = glm::normalize(position);
  glm::vec3 vec_light = light_vector[0].position_-position;
  float angle = glm::angle(normal,vec_light);
  Color intensity = (shape.material_->kd_) + (cos(angle)* float (light_vector[0].brightness_)) ;
}

void Renderer::render_test(Scene const& scene){
for(int i=0;i<scene.objects.size();i++) {
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      Ray ray;
      ray.origin = glm::vec3{x,y,0};
      ray.direction = glm::vec3{0,0,-1.0};
      float distance=0;
      
        if(scene.objects[i]->intersect(ray,distance)==true){
         // p.color = Color(0.0, 1.0, 1.0);
         p.color = shade(*scene.objects[i],ray,distance,scene.lights);
        }else{
          p.color = Color(0.0,1.0,0.0);
        }
      write(p);
      }
      
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

