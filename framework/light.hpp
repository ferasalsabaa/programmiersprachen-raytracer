#ifndef light_HPP
#define light_HPP
#include "color.hpp"
#include <iostream>
#include <glm/vec3.hpp>

class Light {
public:
	Light():
		name_{"default"},
		position_{10.0f,20.0f,10.0f},
		color_{1.0f,1.0f,1.0f},
	    brightness_{2000.0f} {}
	    //isSchatten_{false} 

	Light(std::string const& name, glm::vec3 position, Color const& color, float brightness):
		name_{name},
		position_{position}, 
		color_{color},
		brightness_{brightness}{} 

	~Light(){}
	Color calculate_intensity() const {
		Color intensity {color_*brightness_} ;
		return intensity;
	}

	glm::vec3 get_position() const {
		return position_;
	}



private:
	std::string name_;
	glm::vec3 position_;
	Color color_;
	float brightness_;


};

#endif