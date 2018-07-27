#ifndef light_HPP
#define light_HPP
#include "color.hpp"
#include <iostream>
#include <glm/vec3.hpp>

class Light {
    public:
    Light(): name_{""},position_{0.0,0.0,0.0},color_{0.0,0.0,0.0},brightness_{0},intensity_{0.0,0.0,0.0}
    {}

    Light(std::string const& name,glm::vec3 const& position,Color const& color,unsigned int brightness):
    name_{name},position_{position},color_{color},brightness_{brightness} ,intensity_{calucate_intensity(color,brightness)}
    {}
    
    Color calucate_intensity(Color const& color, unsigned int brightness){
        Color intensity(color.r*brightness,color.g*brightness,color.b*brightness);
        return intensity;
    }

    ~Light();

    std::string name_;
    glm::vec3 position_;
    Color color_;
    unsigned int brightness_;
    Color intensity_;

    private:
   



};

#endif