#define CATCH_CONFIG_RUNNER

#include "box.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <vector>
#include <math.h>
#include <algorithm>

Box::Box() : maximum_{0.0f, 0.0f, 0.0f}, minimum_{0.0f, 0.0f, 0.0f}
{
}
Box::Box(glm::vec3 const &maximum, glm::vec3 const &minimum) : maximum_{maximum}, minimum_{minimum}
{
}
Box::Box(glm::vec3 const &maximum, glm::vec3 const &minimum, std::string const &name, std::shared_ptr<Material> const& material) 
: maximum_{maximum},
  minimum_{minimum},
  Shape(name, material)
{
}
glm::vec3 Box::get_maximum() const
{
    return maximum_;
}
glm::vec3 Box::get_minimum() const
{
    return minimum_;
}
float Box::area() const
{
    float length = get_maximum().x - get_minimum().x;
    float width = get_maximum().z - get_minimum().z;
    float hight = get_maximum().y - get_minimum().y;
    return 2 * (length * width + width * hight + hight * length);
}
float Box::volume() const
{
    float length = get_maximum().x - get_minimum().x;
    float width = get_maximum().z - get_minimum().z;
    float hight = get_maximum().y - get_minimum().y;
    return hight * length * width;
}
std::ostream &Box::print(std::ostream &os) const
{
    Shape::print(os);
    os << "\n max : " << maximum_.x << "," << maximum_.y << "," << maximum_.z << "\n"
       << " min : " << minimum_.x << "," << minimum_.y << "," << minimum_.z <<"\n material : "<< *material_<< "\n";
    return os;
}
bool Box::intersect(Ray const &ray, float &t) const
{
    /* if(ray.origin.x>maximum_.x && ray.origin.y>maximum_.y && ray.origin.z>maximum_.z &&ray.direction.x>ray.origin.x && ray.direction.y>ray.origin.y && ray.direction.z>ray.origin.z) //richtung recht und box links
     {
       return false;
     }
    else if(ray.origin.x<minimum_.x && ray.origin.y<minimum_.y && ray.origin.z<minimum_.z &&ray.direction.x<ray.origin.x && ray.direction.y<ray.origin.y && ray.direction.z<ray.origin.z) //richtung links und box recht
    {
        return false;
        
    }*/
    /*if(ray.origin.x<maximum_.x && ray.origin.y<maximum_.y && ray.origin.z<maximum_.z && ray.origin.x>minimum_.x && ray.origin.y>minimum_.y && ray.origin.z>minimum_.z)  //in box
    {
        return true;

    }*/

    std::cout << minimum_.x << "origin " << ray.origin.x << "dir " << ray.direction.x;
    if (ray.direction.x == 0 && ray.direction.y == 0 && ray.direction.z == 0)
    {
        std::cout << "diriction kann nicht 0,0,0 sein";
    }
    else
    {
        std::vector<float> distance_vector;
        float distance_x_min = (minimum_.x - ray.origin.x) / ray.direction.x;
        float distance_x_max = (maximum_.x - ray.origin.x) / ray.direction.x;
        distance_vector.push_back(distance_x_min);
        distance_vector.push_back(distance_x_max);

        float distance_y_min = (minimum_.y - ray.origin.y) / ray.direction.y;
        float distance_y_max = (maximum_.y - ray.origin.y) / ray.direction.y;
        distance_vector.push_back(distance_y_min);
        distance_vector.push_back(distance_y_max);

        float distance_z_min = (minimum_.z - ray.origin.z) / ray.direction.z;
        float distance_z_max = (maximum_.z - ray.origin.z) / ray.direction.z;
        distance_vector.push_back(distance_z_min);
        distance_vector.push_back(distance_z_max);

        std::sort(distance_vector.begin(), distance_vector.end());

        for (auto &i : distance_vector)
        {
            if (!std::isinf(i))
            {
                if (ray.direction.x == 0 && ray.direction.y == 0 && ray.direction.z == 0)
                {
                    std::cout << "diriction kann nicht 0,0,0 sein";
                }
                glm::vec3 schnitt_punkt = ray.origin + (i * ray.direction);

                if ((schnitt_punkt.x <= maximum_.x && schnitt_punkt.x >= minimum_.x) && (schnitt_punkt.y <= maximum_.y && schnitt_punkt.y >= minimum_.y) && (schnitt_punkt.z <= maximum_.z && schnitt_punkt.z >= minimum_.z))
                {
                    t = i;
                    // glm::vec3 vector_distance = schnitt_punkt - ray.origin;

                    // t = sqrt((vector_distance.x * vector_distance.x) + (vector_distance.y*vector_distance.y) + (vector_distance.z*vector_distance.z));
                    std::cout << "...$$$$$..." << t;
                    return true;
                }
            }
        }
    }
    return false;
}
