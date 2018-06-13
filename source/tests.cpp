#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "Sphere.hpp"
#include "box.hpp"

TEST_CASE("testing_area_volum", "[area_volum]")
{
  glm::vec3 mittel(0.0f,0.0f,0.0f);
  Sphere s1;
  REQUIRE(0==s1.get_radius());
  REQUIRE(0==s1.get_mittel_punkt().x);
  Sphere s2(mittel,5);
  REQUIRE(5==s2.get_radius());
  REQUIRE(s2.area() == Approx(314.16).epsilon(0.001));
  REQUIRE(s2.volume()==Approx(523.598).epsilon(0.001));

  Box b1;
  REQUIRE(0==b1.get_maximum().x);
  REQUIRE(0==b1.get_maximum().y);
  REQUIRE(0==b1.get_maximum().z);
  REQUIRE(0==b1.get_minimum().x);
  REQUIRE(0==b1.get_minimum().y);
  REQUIRE(0==b1.area());
  REQUIRE(0==b1.volume());
  glm::vec3 max(4.0f,10.0f,24.0f);
  glm::vec3 min(2.0f,8.0f,12.0f);
  Box b2(max,min);
  REQUIRE(104==b2.area());
  REQUIRE(48==b2.volume());




}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
