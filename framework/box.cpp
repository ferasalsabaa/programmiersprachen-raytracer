#define CATCH_CONFIG_RUNNER

#include "box.hpp"
#include <limits>

Box::Box() : minimum_{0.0f, 0.0f, 0.0f}, maximum_{1.0f, 1.0f, 1.0f} {}

Box::Box(glm::vec3 const& minimum, glm::vec3 const& maximum) : minimum_{minimum}, maximum_{maximum} {}

Box::Box(glm::vec3 const& minimum, glm::vec3 const& maximum, std::string const &name, std::shared_ptr<Material> const& material) 
: minimum_{minimum},
  maximum_{maximum},
  Shape(name, material)
{}

glm::vec3 Box::get_maximum() const
{
    return maximum_;
    std::cout<<"hollaaaaa";
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
    if (ray.direction.x == 0 && ray.direction.y == 0 && ray.direction.z == 0)
    {
        std::cout << "direction kann nicht 0,0,0 sein";
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

        for (auto i : distance_vector)
        {
            if (!std::isinf(i))
            {
               // if (ray.direction.x == 0 && ray.direction.y == 0 && ray.direction.z == 0)
               // {
               //     std::cout << "diriction kann nicht 0,0,0 sein";
               // }
                glm::vec3 schnitt_punkt = ray.origin + (i * ray.direction);

                if ((schnitt_punkt.x <= maximum_.x && schnitt_punkt.x >= minimum_.x) && (schnitt_punkt.y <= maximum_.y && schnitt_punkt.y >= minimum_.y) && (schnitt_punkt.z <= maximum_.z && schnitt_punkt.z >= minimum_.z))
                {
                    t = i;
                    return true;
                }
            }
        }
    }
    return false;
}

glm::vec3 Box::get_center() const{
    glm::vec3 center((minimum_.x+maximum_.x)/2,(minimum_.y+maximum_.y)/2,(minimum_.z+maximum_.z)/2);
    return center;
}
float Box::get_radius() const{
    return sqrt(((get_center().x-minimum_.x)*(get_center().x-minimum_.x)) +
      ((get_center().y-minimum_.y)*(get_center().y-minimum_.y)) +
       ((get_center().z-minimum_.z)*(get_center().z-minimum_.z)));
}

glm::vec3 Box::get_normal(glm::vec3 const& schnittpunkt) const{

 auto surface_pt = schnittpunkt; 
   if(surface_pt.x == Approx(minimum_.x)){
     return glm::vec3{-1.0,0.0,0.0};
   } if(surface_pt.y == Approx(minimum_.y)){
     return glm::vec3{0.0,-1.0,0.0};
   }
   if(surface_pt.z == Approx(minimum_.z)){
     return glm::vec3{0.0,0.0,-1.0};
   }
   if(surface_pt.x == Approx(maximum_.x)){
     return glm::vec3{1.0,0.0,0.0};
   }
   if(surface_pt.y == Approx(maximum_.y)){
     return glm::vec3{0.0,1.0,0.0};
   }
   if(surface_pt.z == Approx(maximum_.z)){
     return glm::vec3{0.0,0.0,1.0};
   }
}

 intersection_shape Box::intersect_new (Ray const& ray,float & t) const{
     intersection_shape shape1{};
    if(intersect(ray,t)==true){
        shape1.hit = true;
        shape1.distance = t;
        shape1.position=ray.origin + ray.direction*t;
        shape1.normal = get_normal(shape1.position);

    }
    return shape1;
 }