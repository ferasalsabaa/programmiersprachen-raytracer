#include <glm/vec3.hpp>
#include "Shape.hpp"


class Sphere : public Shape {
 
    public:
        Sphere();
        Sphere(glm::vec3 const& vec3, double const& radius);
        Sphere(glm::vec3 const& vec3, double const& radius, std::string const& name, Color const& color);
        glm::vec3 get_center() const;
        double get_radius() const;
        double area() const override;
        double volume() const override;
        std::ostream& print(std::ostream& os) const override;

    private:                // private immer nach public - Konvention
        glm::vec3 center_;
        double radius_;
};
