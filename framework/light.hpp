#ifndef light_HPP
#define light_HPP
#include "color.hpp"
#include <iostream>
#include <glm/vec3.hpp>

class Light {
    public:
    Light(): name_{""},position_{0.0,0.0,0.0},light_color_{0.0,0.0,0.0},brightness_{0},intensity_{0.0,0.0,0.0}
    {}

    Light(std::string name,glm::vec3 position,Color light_color,unsigned int brightness):
    name_{name},position_{position},light_color_{light_color},brightness_{brightness} ,intensity_{calucate_intensity(light_color,brightness)}
    {}
    
    Color calucate_intensity(Color light_color, unsigned int brightness){
        Color intensity(light_color.r*brightness,light_color.g*brightness,light_color.b*brightness);
        return intensity;
    }

    private:
    std::string name_;
    glm::vec3 position_;
    Color light_color_;
    unsigned int brightness_;
    Color intensity_;



};

#endif