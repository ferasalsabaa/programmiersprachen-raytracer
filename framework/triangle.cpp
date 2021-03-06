#include "triangle.hpp"

Triangle::Triangle() : Shape(), a_{0.0,0.0,0.0}, b_{0.0,0.0,0.0}, c_{0.0,0.0,0.0}
{}
Triangle::Triangle(glm::vec3 const& a,glm::vec3 const& b,glm::vec3 const& c,std::string const& name, std::shared_ptr<Material> const& material) :
  Shape(name,material),a_{a}, b_{b}, c_{c}
{}
Triangle::~Triangle(){}

bool Triangle::intersect (Ray const& ray,float & t) const {
  /*glm::vec3 position;
  bool res = glm::intersectRayTriangle(ray.origin, ray.direction,
  a_, b_, c_, position);
 t = position.t;
  return res;*/

glm::vec3 e1=b_-a_;
glm::vec3 e2=c_ -a_;
//set_ray(ray);


float u = glm::dot(ray.origin-a_,glm::cross(ray.direction,e2)) / 
          glm::dot(e1,glm::cross(ray.direction,e2));
          //set_u(uu);
float v = glm::dot(ray.direction,(glm::cross((ray.origin-a_),e1)) /
          glm::dot(e1,glm::cross(ray.direction,e2)));
float w = 1-u-v;
float distance = glm::dot(e2,glm::cross((ray.origin-a_),e1)) / glm::dot(e1,glm::cross(ray.direction,e2));

if(u<0 || u>1){
    return false;
}
if(v<0 || u+v>1){
    return false;
}
else{
    t = distance;
    return true;
}

}
glm::vec3 Triangle::get_normal(glm::vec3 const& schnittpunkt) const{
    return glm::normalize(glm::cross(a_-b_, a_-c_));
 /*   glm::vec3 normal;
    normal.x = (schnittpunkt.x - get_center().x);
    normal.y = (schnittpunkt.y - get_center().y);
    normal.z = (schnittpunkt.z - get_center().z);
    return normal;*/
    
}

 intersection_shape Triangle::intersect_new (Ray const& ray,float & t) const{
     intersection_shape shape1{};
    if(intersect(ray,t)==true){
        shape1.hit = true;
        shape1.distance = t;
        shape1.position=ray.origin + ray.direction*t;
        shape1.normal = get_normal(shape1.position);

    }
    return shape1;
 }


float Triangle::area() const{
    return 1;
}
float Triangle::volume()const{
    return 1;
}
glm::vec3 Triangle::get_center() const{
    glm::vec3((a_.x+b_.x+c_.x)/3,(a_.y+b_.y+c_.y)/3,(a_.z+b_.z+c_.z)/3);
}
std::ostream& Triangle::print(std::ostream& os) const{
    std::cout<<"ff";
}
float Triangle::get_radius() const{
    return 1;
}