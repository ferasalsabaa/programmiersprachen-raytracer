#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Box.hpp"

TEST_CASE("circle-normal_construct, getter") {
  Sphere kugel;
  REQUIRE(0 == kugel.get_radius());
  REQUIRE(0 == kugel.get_center().x);
  REQUIRE(0 == kugel.get_center().y);
}

TEST_CASE("circle-initalize, getter") {
  glm::vec3 vec(1,2,3);
  Sphere kugel(vec, 4);
  REQUIRE(4 == kugel.get_radius());
  REQUIRE(1 == kugel.get_center().x);
  REQUIRE(2 == kugel.get_center().y);
  REQUIRE(3 == kugel.get_center().z);
}

TEST_CASE("circle-area/volume, getter") {
  glm::vec3 vec(1,2,3);
  Sphere kugel(vec, 4);
  Sphere kugel2(vec, 6);
  REQUIRE(Approx(201.06).epsilon(0.1) == kugel.area());
  REQUIRE(Approx(452.34).epsilon(0.1) == kugel2.area());
  REQUIRE(Approx(286.09).epsilon(0.1) == kugel.volume());
  REQUIRE(Approx(904.78).epsilon(0.1) == kugel2.volume());
}

TEST_CASE("box-constructor") {
  Box kiste;
  REQUIRE(0 == kiste.get_min().x);
  REQUIRE(0 == kiste.get_min().y);
  REQUIRE(0 == kiste.get_min().z);
}

TEST_CASE("box-user-constructor") {
  glm::vec3 min(1,2,3);
  glm::vec3 max(4,5,6);
  Box kiste(min, max);
  REQUIRE(1 == kiste.get_min().x);
  REQUIRE(2 == kiste.get_min().y);
  REQUIRE(3 == kiste.get_min().z);
  REQUIRE(4 == kiste.get_max().x);
  REQUIRE(5 == kiste.get_max().y);
  REQUIRE(6 == kiste.get_max().z);
}

TEST_CASE("box-area/volume") {
  glm::vec3 min(1,2,3);
  glm::vec3 max(4,5,6);
  Box kiste(min, max);
  REQUIRE(54 == kiste.area());
  REQUIRE(27 == kiste.volume());
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
