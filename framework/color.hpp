// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>
#include <glm/vec3.hpp>

struct Color
{
  Color(float red, float green, float blue) : r(red), g(green), b(blue) {}
  Color() : r(0.0), g(0.0), b(0.0) {}

  friend std::ostream& operator<<(std::ostream& os, Color const& c){
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  Color& operator+=(Color const& other){
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other){
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

    Color& operator*=(Color const& other){
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
  }

     Color& operator/=(Color const& other){
    r /= other.r;
    g /= other.g;
    b /= other.b;
    return *this;
    
  }

  friend Color operator+(Color const& a, Color const& b){
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b){
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

friend Color operator*(Color const& a, float x) {
     auto tmp(a);
     tmp *= x;
    return tmp;
}


friend Color operator+(Color const& a, float x) {
    auto tmp(a);
    tmp.r = a.r+x;
    tmp.g = a.g+x;
    tmp.b = a.b+x;
    return tmp;
}

friend Color operator*(Color const& a, Color const& b){
  auto tmp(a);
  tmp *=b;
  return tmp;
}

friend Color operator/(Color const& a, Color const& b){
  auto tmp(a);
  tmp /=b;
  return tmp;
}


Color& operator/=(float other){
    r /= other;
    g /= other;
    b /= other;
    return *this;
  }

Color& operator*=(float other){
  r *= other;
  g *= other;
  b *= other;
  return *this;
}

  float r;
  float g;
  float b;
};

#endif //#define BUW_COLOR_HPP
