#define CATCH_CONFIG_RUNNER

#include "Sphere.hpp"
#include "ray.hpp"
#include<math.h>
#include<glm/glm.hpp>
#include<glm/gtx/intersect.hpp>


Sphere::Sphere() : Shape() , mittelpunkt_{0.0f,0.0f,0.0f} , radius_{0.0f}{
    std::cout<<"sphere constructor 1"<<"\n";
    }

Sphere::Sphere(glm::vec3 const& mittelpunkt,float const& radius) : Shape(), mittelpunkt_{mittelpunkt} , radius_{radius} {
    std::cout<<"sphere constructor 2"<<"\n";
    }

Sphere::Sphere(glm::vec3 const& mittelpunkt,float const& radius,std::string const& name,std::shared_ptr<Material> const& material) : 
    mittelpunkt_{mittelpunkt} , radius_{radius}, Shape(name,material) {}

Sphere::~Sphere(){}


float Sphere::get_radius() const {
    return radius_;
}

glm::vec3 Sphere::get_mittelpunkt() const {
    return mittelpunkt_;
}

float Sphere::area() const {
  return 4 * pow(get_radius(),2) * M_PI;
}

float Sphere::volume() const {
  return (4.0f/3.0f) * M_PI * (pow(get_radius(),3));
}

std::ostream& Sphere::print(std::ostream& os) const {
    Shape::print(os);
    os<<"\n radius : "<<radius_<<"\n center : " <<"\n x "<<mittelpunkt_.x<<" y "<<mittelpunkt_.y<<" z "<<mittelpunkt_.z<<"\n";
    return os;
}

bool Sphere::intersect(Ray const& ray,float & distance) const {

glm::vec3 v = glm::normalize(ray.direction); //ohne ende
//auto a = ray.direction = {0.0f,0.0f,1.0f};

return glm::intersectRaySphere(
    ray.origin,v,
    mittelpunkt_,
    radius_ * radius_, // squared radius !!!   
    distance);
}

intersection_shape Sphere::intersect_new (Ray const& rayIn,float & t) const{
    Ray ray{rayIn};
    ray = ray.transform_ray(world_transformation_inv(), ray);
    intersection_shape shape1{};
    if(intersect(ray,t)==true){
        shape1.hit = true;
        shape1.distance = t;
        shape1.position = ray.origin + ray.direction*t;
        shape1.normal = glm::normalize(shape1.position - mittelpunkt_);
        shape1.normal = glm::normalize(glm::vec3(glm::transpose(world_transformation_inv())*glm::vec4(shape1.normal, 0.0))); //double inversion?
        shape1.position = glm::vec3(world_transformation()*glm::vec4(shape1.position,1.0)); //we can drop the w part, because it becomes irrelevant afterwards (just for position/direction)

    }
    else{
        shape1.hit = false;
    }
    return shape1;
}

glm::vec3 Sphere::get_center() const{
    return mittelpunkt_;
}

glm::vec3 Sphere::get_normal(glm::vec3 const& schnittpunkt) const{
    glm::vec3 normal;
    normal.x = (schnittpunkt.x - mittelpunkt_.x);
    normal.y = (schnittpunkt.y - mittelpunkt_.y);
    normal.z = (schnittpunkt.z - mittelpunkt_.z);
    return normal;
}


