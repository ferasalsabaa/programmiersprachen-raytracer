#ifndef RAY_HPP
#define RAY_HPP
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

struct Ray
{
	Ray(): origin{0.0f,0.0f,0.0f},direction{1.0f,0.0f,0.0f}{}
	Ray(glm::vec3 const& origin_, glm::vec3 const& direction_) :
		origin{origin_},
		direction{ glm::normalize(direction_) } {}
		
	Ray(const Ray& r1): origin{r1.origin}, direction{r1.direction}
	{}


	Ray& transform_ray(glm::mat4 const& mat) {
		glm::vec4 a {origin, 1.0f}; //point w is 1
		glm::vec4 b {direction, 0.0f}; //vector w is 0
		glm::vec3 origin_ {mat * a};
		glm::vec3 direction_ {mat * b};

		return *this;
	}

	Ray transform_ray(glm::mat4 const& mat, Ray& ray) {
		return ray.transform_ray(mat);;
	}

	glm::vec3 origin= {0.0f,0.0f,0.0f};
	glm::vec3 direction = {0.0f,0.0f,-1.0f};

};

#endif