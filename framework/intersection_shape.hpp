#ifndef Intersection_shape_HPP
#define Intersection_shape_HPP
#include <glm/vec3.hpp>


struct intersection_shape{
	float distance;
	bool hit;
	glm::vec3 position; 
  glm::vec3 normal;
};

#endif