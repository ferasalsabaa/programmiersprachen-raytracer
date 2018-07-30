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
  Color ks(1.0,0.0,0.0);
  float m=10;
  Scene test2(open_sdf("scene"));

  std::shared_ptr<Material> m1(new Material(ka,kd,ks,m));

  Light light{"sun",{100,100,-10},{0,1,1},10};
  test.lights.push_back(light);
  test.material_map.insert(make_pair(m1->name_,m1));
  glm::vec3 min {1.0f,0.0f,-50.0f};
  glm::vec3 max {400.0f,200.0f,-50.0f};
  glm::vec3 position {200.0f,200.0f,-10.0f};
  float distance = 90;

  std::shared_ptr<Sphere> b1(new Sphere(position,distance,"sphere",m1));
  std::shared_ptr<Box> b2(new Box(max,min,"mm",m1));
  test.objects.push_back(b1);
  //test.objects.push_back(b2);
  Light ambient_l{"ambient",{0.1,0.1,0.1},{0.0,0.0,0.0},1};
  test.ambient = ambient_l;
  Camera cam{};

  Renderer renderer{image_width, image_height, filename, cam};
  renderer.render_test(test);
  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }


  return 0;
}