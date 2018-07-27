// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include "ray.hpp"


Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
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

void Renderer::render_test(Scene const& scene){

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      Ray ray;
      ray.origin = glm::vec3{x,y,0};
      ray.direction = glm::vec3{0,0,1.0};
      float distance=0;
      if(scene.objects[0]->intersect(ray,distance)==true){
       p.color = Color(0.0, 1.0, 1.0);
      }else{
        p.color = Color(0.0,1.0,0.0);
      }
      write(p);
      
    }
  }
  ppm_.save(filename_);  
}

void Renderer::render(Scene const& scene) {
  Ray ray;
  float t = 1;
  std::shared_ptr<Shape> closest_o(scene.objects.front());
  float closest_t = closest_o->intersect(ray, t);
  closest_o = 0;
  for(int i = 0; i<=100; ++i) {
    for(int j = 0; j<= 100; ++j) {
      Pixel p(i,j);
      for (auto& object : scene.objects) {
        t = object->intersect(ray,t);
        if(t<closest_t) {
          closest_t = t;
          closest_o = object;
        }
      }
      if(closest_o != 0) {
     p.color = Color(0.0, 1.0, 0.0);
     write(p);
    } else {
     p.color = Color(0.0, 0.0, 1.0);
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

