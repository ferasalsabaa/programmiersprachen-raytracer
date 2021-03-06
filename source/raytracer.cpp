#include <renderer.hpp>
#include "shape.hpp"
#include "Sphere.hpp"
#include <window.hpp>
#include "camera.hpp"
#include "box.hpp"
#include <glm/vec3.hpp>
//#include <GLFW/glfw3.h>
#include <thread>
#include <map>
#include <vector>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  unsigned const image_width = 500;
  unsigned const image_height = 500;
  std::string const filename = "./checkerboard.ppm";

  Scene test;
  test.name_ = "aa";
  Color ka(1.0,0.0,0.0);
  Color kd(1.0,0.0,0.0);
  Color ks(1.0,1.0,1.0);
  float m=5;
  Scene test2;
  test2 = open_sdf("scene2.sdf");

  std::shared_ptr<Material> m1(new Material(ka,kd,ks,m,1,1));

  Light light{"sun",{50,-30,-10},{0,0.5,0},50};
  test.lights.push_back(light);
  test.material_map.insert(make_pair(m1->name_,m1));
  glm::vec3 min {0.0f,10.0f,-20.0f};
  glm::vec3 max {10.0f,20.0f,-15.0f};
  glm::vec3 position {0.0f,10.0f,-20.0f};
  glm::vec3 position2 {-5.0f,5.0f,-40.0f};
  float distance = 10;
  float distance2 = 5;

  std::shared_ptr<Sphere> b1(new Sphere(position,distance,"sphere",m1));
  std::shared_ptr<Sphere> b2(new Sphere(position2,distance,"sphere2",m1));
  std::shared_ptr<Box> b3(new Box(max,min,"mm",m1));
 // test.objects.push_back(b1);
  test.objects.push_back(b3);
  Color ambient_l{0.8,0.8,0.8};
  test.ambient_ = ambient_l;
  Camera cam{};

  Renderer renderer{test2.width_, test2.height_, test2.file_name_, test2};
  renderer.render();
  Window window{{test2.width_, test2.width_,}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }


  return 0;
}