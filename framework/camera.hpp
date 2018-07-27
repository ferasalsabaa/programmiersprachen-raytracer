#ifndef camera_HPP
#define camera_HPP
#include <iostream>

class Camera {

    public:
    std::string name_;
    float aperture_;

    Camera() : name_{""}, aperture_{45} {}
    Camera(std::string const& name, float aperture) : name_{name}, aperture_{aperture} {}

    private:
    //

};



#endif