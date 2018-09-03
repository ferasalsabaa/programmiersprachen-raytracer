// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "shape.hpp"
#include <string>
#include <glm/glm.hpp>
#include <math.h>
#include <cmath>




class Renderer
{

public:

  Renderer();
  Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene);

  void render();
  void write(Pixel const& p);
  Color shade(Shape const& shape, Ray const& ray, float t, int depth);
  void render(Scene const& scene);
  Color raytrace(Ray const& ray, int d);
  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }


private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
  Scene scene_{};

};

#endif // #ifndef BUW_RENDERER_HPP
