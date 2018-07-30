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

  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
  Camera cam_;

  Renderer();
  Renderer(unsigned w, unsigned h, std::string const& file, Camera const& cam);

  void render();
  void render_test(Scene const& scene);
  void write(Pixel const& p);
  Color shade(Shape const& shape, Ray const& ray, float t, std::vector<Light> const& light_vector, Light const& ambient);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }



private:

};

#endif // #ifndef BUW_RENDERER_HPP
