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
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./checkerboard.ppm";

  Scene test;
  test.name_ = "aa";
  //Camera cam();
  //test.cam_(cam);
  Color ka(0.0,0.0,0.0);
  Color kd(0.0,0.0,0.0);
  Color ks(0.0,0.0,0.0);
  float m=50;
//Material m1(ka,kd,ks,m);
 std::shared_ptr<Material> m1(new Material(ka,kd,ks,m));
 //test.material_map.reserve(10);
 Light lampe{};
 test.lights.push_back(lampe);
 test.material_map.insert(make_pair(m1->name_,m1));
 glm::vec3 min {1.0f,0.0f,-50.0f};
 glm::vec3 max {400.0f,200.0f,-50.0f};
 glm::vec3 position {400.0f,300.0f,-700.0f};
 float distance = 90;

//std::shared_ptr<Box> b1(new Box(max,min,"dd",m1));
std::shared_ptr<Sphere> b1(new Sphere(position,distance,"sphere",m1));
std::shared_ptr<Box> b2(new Box(max,min,"mm",m1));
test.objects.reserve(10);
test.objects.push_back(b1);
test.objects.push_back(b2);

Camera cam{};

  Renderer renderer{image_width, image_height, filename, cam};

  //create separate thread to see updates of pixels while rendering
  //std::thread render_thread([&renderer]() {renderer.render();});

  //std::thread render_thread([&renderer]() {renderer.render_test(test);});
  renderer.render_test(test);

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  //"join" threads, i.e. synchronize main thread with render_thread
  //render_thread.join();
  return 0;
}
