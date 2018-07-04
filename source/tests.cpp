#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "Sphere.hpp"
#include "box.hpp"
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/intersect.hpp>

/*TEST_CASE("testing_area_volum", "[area_volum]")
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
}*/

int main(int argc, char *argv[])
{ /*std::cout<<"\n begin aufgabe 5.5  \n";
  glm::vec3 v_1(4.0f,10.0f,24.0f);
  glm::vec3 v_2(2.0f,8.0f,12.0f);
  Color c1{0.0,0.0,1.0};
  Sphere s11;
  Sphere s22(v_1,5,"sphere",c1);
  std::cout<<s11<<"\n";
  std::cout<<s22;
  Box b11;
  Box b22(v_1,v_2,"t1 ",c1);
  std::cout<<b11<<"\n";
  std::cout<<b22;
  std::cout<<"\n Ende aufgabe 5.5  \n";


Color red{255,0,0};
glm::vec3 position {0.0f,0.0f,0.0f};
std::cout<<"begin  5.8  "<<"\n";
Sphere* s1 = new Sphere{position,1.2f,"sphere0",red};
Shape*  s2 = new Sphere{position,1.2f,"sphere1",red};
s1->print(std::cout);
s2->print(std::cout);
delete s1;
delete s2;
std::cout<<"end  5.8"<<"\n";*/

  return Catch::Session().run(argc, argv);
}
/*
//5.6
TEST_CASE("intersect_ray_sphere" , "[intersect]")
{
// Ray
glm:: vec3 ray_origin{0.0f,0.0f,0.0f};
// ray direction has to be normalized !
// you can use :
//v = glm::normalize(some_vector)
glm::vec3 ray_direction {0.0f,0.0f,1.0f};
// Sphere
glm::vec3 sphere_center {0.0f,0.0f,5.0f};
float sphere_radius {1.0f};
float distance = 0.0f;
auto result = glm::intersectRaySphere(
ray_origin,ray_direction,
sphere_center,
sphere_radius * sphere_radius , // squared radius !!!
distance );
REQUIRE ( distance == Approx(4.0f));
//REQUIRE ( result == true);
}
//5.6
TEST_CASE("intersect_sphere","[intersect_sphere]")
{
  Ray ray;
  ray.origin=glm::vec3 {0.0,0.0,0.0};
  ray.direction=glm::vec3 {0.0,0.0,1.0};
  glm::vec3 sphere_center {0.0f,0.0f,5.0f};
  Ray ray1;
  float distance =0;
  ray1.origin=glm::vec3 {0.0,0.0,0.0};
  ray1.direction=glm::vec3 {0.0,0.0,-1.0};
  Sphere s1{sphere_center,1.0f};
  float d=0.0f;
  float d1=0.0f;
  bool result = s1.intersect(ray,d);
  bool result1 = s1.intersect(ray1,d1);
  REQUIRE ( result1 == false);
  REQUIRE ( result == true);
  REQUIRE ( d == Approx(4.0f));

}*/

//6.3
TEST_CASE("intersect_box","[intersect_box]")
{
  Ray ray;
  ray.origin=glm::vec3 {0.0,0.0,0.0};
  ray.direction=glm::vec3 {2.0,2.0,2.0};
  glm::vec3 min {1.0f,0.0f,0.0f};
  glm::vec3 max {6.0f,5.0f,5.0f};

  Ray ray1;
  ray1.origin=glm::vec3 {0.0,0.0,0.0};
  ray1.direction=glm::vec3 {2.0,3.0,1.0};
   glm::vec3 min1 {8.0f,-5.0f,0.0f};
 
  float distance =0;
  float distance1 =0;
  Box box1(max,min);
  Box box2(max,min1);


  bool result =  box1.intersect(ray,distance);
  bool result1 = box2.intersect(ray1,distance1);
  //bool result1 = s1.intersect(ray1,d1);
  //REQUIRE ( result1 == false);
  REQUIRE ( result == true);
  REQUIRE ( result1 == false);
  //REQUIRE ( distance == Approx(0.5f));

}
