#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include <color.hpp>

class Shape {

    public:
        Shape();
        Shape(std::string const& name, Color const& color);
        virtual double area() const=0;
        virtual double volume() const=0;
        virtual std::ostream& print(std::ostream& os) const;

    private:
        std::string name_;
        Color color_;

        
};

std::ostream& operator <<(std::ostream& os, Shape const& s);

#endif //Shape.hpp