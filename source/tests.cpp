#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Box.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "ray.hpp"

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


TEST_CASE("intersect_ray_sphere", "[intersect]") {
    // Ray
    glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
    // ray direction has to be normalized !
    // you can use:
    // v = glm::normalize(some_vector)
    glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};
    // Sphere
    glm::vec3 sphere_center{0.0f ,0.0f, 5.0f};
    float sphere_radius{1.0f};
    float distance = 0.0f;
    auto result = glm::intersectRaySphere(
      ray_origin , ray_direction ,
      sphere_center ,
      sphere_radius * sphere_radius, // squared radius !!!
      distance );
    REQUIRE(distance == Approx(4.0f));

    float distance = 0.0f;
    Sphere kugel(sphere_center, 1);
    Ray ray{ray_origin, ray_direction};
    auto result2 = kugel.intersect(ray, distance);
    REQUIRE(result == true);
    REQUIRE(distance == 4);
}

int main(int argc, char *argv[])
{
  glm::vec3 vec(1,2,3);
  glm::vec3 vec2(3,5,6);
  Color color(1,3,0);
  Sphere kugel(vec, 3, "kugeli", color);
  std::cout << kugel;

  Sphere kugel2;
  std::cout << kugel2;

  Box kiste;
  std::cout << kiste;

  Box kiste2(vec, vec2, "boxi", color);
  std::cout << kiste2;
  

  return Catch::Session().run(argc, argv);
}
