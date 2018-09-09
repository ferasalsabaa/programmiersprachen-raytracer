#define CATCH_CONFIG_RUNNER
#include "shape.hpp"
#include<iostream>

Shape::Shape() : name_{""} , material_{}, world_transformation_{}, world_transformation_inv_{glm::inverse(world_transformation_)} {}

Shape::Shape(std::string const& name,std::shared_ptr<Material> const& material) : name_{name} , material_{material}, world_transformation_{}, world_transformation_inv_{glm::inverse(world_transformation_)} {}

Shape::Shape(std::string const& name,std::shared_ptr<Material> const& material, glm::mat4 world_transform) : name_{name} , material_{material}, world_transformation_{world_transform}, world_transformation_inv_{glm::inverse(world_transformation_)} {}

Shape::Shape(Shape const& shape1): name_{shape1.name_} , material_{shape1.material_}, world_transformation_{shape1.world_transformation_}, world_transformation_inv_{glm::inverse(world_transformation_)} {}

Shape::~Shape() {}


std::ostream& Shape::print(std::ostream& os) const {
   os << "\n name  : " <<name_<< "\n  ";
   return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
    s.print(os);
    return os;
}
std::shared_ptr<Material> Shape::get_material() const{
    return material_;
}
std::string Shape::get_name() const{
  return name_;
}

glm::mat4 Shape::world_transformation() const {
  return world_transformation_;
}

glm::mat4 Shape::world_transformation_inv() const {
  return world_transformation_inv_;
}

void Shape::world_transformation(glm::mat4 const& matrix) {
  world_transformation_ = matrix;
  world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::translate(glm::vec3 const& p) {
  glm::mat4 translateMat;
  translateMat[0] = glm::vec4 {1.0f, 0.0f, 0.0f, p.x};
  translateMat[1] = glm::vec4 {0.0f, 1.0f, 0.0f, p.y};
  translateMat[2] = glm::vec4 {0.0f, 0.0f, 1.0f, p.z};
  translateMat[3] = glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};

  world_transformation_  = translateMat * world_transformation_;
  world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::scale(glm::vec3 const& s) {
  glm::mat4 scale;
  scale[0] = glm::vec4 {s.x, 0.0f, 0.0f, 0.0f};
  scale[1] = glm::vec4 {0.0f, s.y, 0.0f, 0.0f};
  scale[2] = glm::vec4 {0.0f, 0.0f, s.z, 0.0f};
  scale[3] = glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};

  world_transformation_  = scale * world_transformation_ ;
  world_transformation_inv_ = glm::inverse(world_transformation_ );
}


void Shape::rotate_x(float phi) {
  glm::mat4 rotationMat;
  rotationMat[0] = glm::vec4 {1.0f, 0.0f, 0.0f, 0.0f};
  rotationMat[1] = glm::vec4 {0.0f, cos(phi), sin(phi), 0.0f};
  rotationMat[2] = glm::vec4 {0.0f, -sin(phi), cos(phi), 0.0f};
  rotationMat[3] = glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};
  world_transformation_ = rotationMat * world_transformation_ ;
  world_transformation_inv_ = glm::inverse(world_transformation_ );
}

void Shape::rotate_y(float phi) {
  glm::mat4 rotationMat;
  rotationMat[0] = glm::vec4 {cos(phi), 0.0f, -sin(phi), 0.0f};
  rotationMat[1] = glm::vec4 {0.0f, 1.0f, 0.0f, 0.0f};
  rotationMat[2] = glm::vec4 {sin(phi), 0.0f, cos(phi), 0.0f};
  rotationMat[3] = glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};

  world_transformation_ = rotationMat * world_transformation_ ;
  world_transformation_inv_ = glm::inverse(world_transformation_ );
}


void Shape::rotate_z(float phi) {
  glm::mat4 rotationMat;
  rotationMat[0] = glm::vec4 {cos(phi), sin(phi), 0.0f, 0.0f};
  rotationMat[1] = glm::vec4 {-sin(phi), cos(phi), 0.0f, 0.0f};
  rotationMat[2] = glm::vec4 {0.0f, 0.0f, 1.0f, 0.0f};
  rotationMat[3] = glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};

  world_transformation_ = rotationMat * world_transformation_ ;
  world_transformation_inv_ = glm::inverse(world_transformation_ );
}

