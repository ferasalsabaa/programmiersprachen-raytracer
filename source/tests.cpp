#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "Sphere.hpp"
#include<memory>
#include "box.hpp"
#include "light.hpp"
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/intersect.hpp>

TEST_CASE("testing_area_volum", "[area_volum]")
{
}

int main(int argc, char *argv[])
{
  


  return Catch::Session().run(argc, argv);
}

