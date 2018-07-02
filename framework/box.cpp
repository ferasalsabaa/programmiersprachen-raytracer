#define CATCH_CONFIG_RUNNER

#include "box.hpp"
#include<glm/glm.hpp>
#include<glm/gtx/intersect.hpp>

Box::Box() : maximum_{0.0f,0.0f,0.0f} , minimum_{0.0f,0.0f,0.0f}
{}
Box::Box(glm::vec3 const& maximum , glm::vec3 const& minimum) : maximum_{maximum} , minimum_{minimum}
{}
Box::Box(glm::vec3 const& maximum,glm::vec3 const& minimum,std::string const& name, Color const& box_color) : 
    maximum_{maximum} ,
    minimum_{minimum} , 
    Shape(name,box_color)
{}
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
  return 2*(length*width + width*hight + hight*length);
}
float Box::volume() const
{
    float length = get_maximum().x - get_minimum().x;
  float width = get_maximum().z - get_minimum().z;
  float hight = get_maximum().y - get_minimum().y;
  return hight*length*width;   
}
std::ostream& Box::print(std::ostream& os) const
{   Shape::print(os);
    os << "\n max x  "<<maximum_.x<<" max y "<<maximum_.y<<" maxinmum z"<<maximum_.z<<"\n"<<" min x"<<minimum_.x<<" min y"<<minimum_.y<<" min z"<<minimum_.z;
    return os;
}
bool Box::intersect(Ray const& ray,float & t) const
{
   bool test=false;
   if(ray.origin.x>minimum_.x && ray.origin.y>minimum_.y && ray.origin.z>minimum_.z &&ray.direction.x>ray.origin.x && ray.direction.y>ray.origin.y && ray.direction.z>ray.origin.z) //richtung recht und box links
     {
       test = false;
     }
    else if(ray.origin.x<minimum_.x && ray.origin.y<minimum_.y && ray.origin.z<minimum_.z &&ray.direction.x<ray.origin.x && ray.direction.y<ray.origin.y && ray.direction.z<ray.origin.z) //richtung links und box recht
    {
        test = false;
    }
    else if(ray.origin.x<maximum_.x && ray.origin.y<maximum_.y && ray.origin.z<maximum_.z && ray.origin.x>minimum_.x && ray.origin.y>minimum_.y && ray.origin.z>minimum_.z)  //in box
    {
        test = true;
    }
   else
   {
    glm::vec3 v = glm::normalize(ray.direction);
    
    float distance_x = (minimum_.x - ray.origin.x) / ray.direction.x;
    glm::vec3 schnitt_punkt_x = ray.origin + (distance_x*ray.direction);
    if((schnitt_punkt_x.y<=maximum_.y&&schnitt_punkt_x.y>=minimum_.y)&&(schnitt_punkt_x.z<=maximum_.z&&schnitt_punkt_x.z>=minimum_.z))
    {
        glm::vec3 vector_distance = schnitt_punkt_x - ray.origin;
        t = sqrt(vector_distance.x * vector_distance.x + vector_distance.y*vector_distance.y + vector_distance.z*vector_distance.z);
        test = true;
    }

    float distance_y = (minimum_.y - ray.origin.y) / ray.direction.y;
    glm::vec3 schnitt_punkt_y = ray.origin + (distance_y*ray.direction);
    if((schnitt_punkt_y.x<=maximum_.x&&schnitt_punkt_y.x>=minimum_.x)&&(schnitt_punkt_y.z<=maximum_.z&&schnitt_punkt_y.z>=minimum_.z))
    {
        glm::vec3 vector_distance = schnitt_punkt_y - ray.origin;
        t = sqrt(vector_distance.x * vector_distance.x + vector_distance.y*vector_distance.y + vector_distance.z*vector_distance.z);
        test=true;
    }

    float distance_z = (minimum_.z - ray.origin.z) / ray.direction.z;
    glm::vec3 schnitt_punkt_z = ray.origin + (distance_z*ray.direction);
    if((schnitt_punkt_z.y<=maximum_.y&&schnitt_punkt_z.y>=minimum_.y)&&(schnitt_punkt_z.x<=maximum_.x&&schnitt_punkt_z.x>=minimum_.x))
    {
        glm::vec3 vector_distance = schnitt_punkt_z - ray.origin;
        t = sqrt(vector_distance.x * vector_distance.x + vector_distance.y*vector_distance.y + vector_distance.z*vector_distance.z);
        test=true;
    }
}

    return test;
}
