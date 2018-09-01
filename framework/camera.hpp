#ifndef camera_HPP
#define camera_HPP
#include <glm/vec3.hpp>
#include <iostream>
#include <glm/gtx/intersect.hpp>
#include <ray.hpp>

class Camera {

    public:
  

    Camera();
    Camera(std::string const& name, float aperture, glm::vec3 origin, glm::vec3 direction, glm::vec3 up);

    Ray shoot_ray(float x, float y, float width_, float height_) const;

    Ray shoot_ray1(float x, float y) const;

    glm::vec3 get_origin() const;

    // glm::mat4 transform_camera() const;
    // void translate(glm::vec3 const& p);
    // void rotate_x(float phi);
    // void rotate_y(float phi);
    // void rotate_z(float phi);


    private:
    std::string name_;
    float aperture_;
    glm::vec3 origin_;
    glm::vec3 direction_;
    glm::vec3 up_;
    // glm::mat4 transform_cam_;
    // glm::mat4 transform_cam_inv_;
    
};



#endif