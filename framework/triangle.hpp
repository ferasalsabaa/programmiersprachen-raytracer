#ifndef triangle_HPP
#define triangle_HPP

#include"ray.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <math.h>

class Triangle : public shape
{
    public:
    Triangle();
    Treiangle(glm::vec3 a,glm::vec3 b,glm::vec3 c);
    private:
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;

};

#endif