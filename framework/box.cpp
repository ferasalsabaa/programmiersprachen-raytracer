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
bool Box::intersect(Ray const &rayIn, float &t) const
{   
    Ray ray{rayIn};
    ray = ray.transform_ray(world_transformation_inv(), ray);
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
glm::vec3 Box::get_normal_box(int x) const{
switch(x){
		case 0: return glm::vec3{-1.0,0.0,0.0}; // -x
		case 1: return glm::vec3{0.0,-1.0,0.0}; // -y
		case 2: return glm::vec3{0.0,0.0,-1.0}; // -z
		case 3: return glm::vec3{1.0,0.0,0.0}; // +x-Plane
		case 4: return glm::vec3{0.0,1.0,0.0}; // +y-Plane
		case 5: return glm::vec3{0.0,0.0,1.0}; // +z-Plane
}
}
bool Box::intersect_box (Ray const& ray, float& t, glm::vec3& normal) const {
    bool intersect=false;
	float origin_x=ray.origin.x;
	float origin_y=ray.origin.y;
	float origin_z=ray.origin.z;
	float direction_x=ray.direction.x;
	float direction_y=ray.direction.y;
	float direction_z=ray.direction.z;
	
	float min_x,min_y,min_z;
    float max_x,max_y,max_z;

    float a = 1.0/direction_x;
	if(a>=0){
		min_x =(minimum_.x-origin_x)*a;
		max_x =(maximum_.x-origin_x)*a;
	}else{
		min_x=(maximum_.x-origin_x)*a;
		max_x=(minimum_.x-origin_x)*a;
	}
	float b = 1.0/direction_y;
	if(b>=0){
		min_y =(minimum_.y-origin_y)*b;
		max_y =(maximum_.y-origin_y)*b;
	}else{
		min_y=(maximum_.y-origin_y)*b;
		max_y=(minimum_.y-origin_y)*b;
	}
	float c= 1.0/direction_z;
	if(c>=0){
		min_z=(minimum_.z-origin_z)*c;
		max_z=(maximum_.z-origin_z)*c;
	}else{
		min_z=(maximum_.z-origin_z)*c;
		max_z=(minimum_.z-origin_z)*c;
}



    float biggest_t;// biggest_in_t zwischen min_x,min_y,min_z; in_T!!!
	float smallest_t; // smallest_out_t zwischen max_x,max_y,max_z; out_T!!!
	
	int plane_in,plane_out;
	if(min_x>min_y){
		biggest_t=min_x;
		plane_in=(a>=0.0)? 0:3;
	}else{
		biggest_t=min_y;
		plane_in=(b>=0.0)? 1:4;
	}
	if(min_z>biggest_t){
		biggest_t=min_z;
		plane_in=(c>=0.0)?2:5;
	}
	if(max_x<max_y){
		smallest_t=max_x;
		plane_out=(a>=0.0)?3:0;
	}else{
		smallest_t=max_y;
		plane_out=(b>=0.0)?4:1;
	}
	if(max_z<smallest_t){
		smallest_t=max_z;
		plane_out=(c>=0.0)?5:2;
	}
	intersect=biggest_t<smallest_t && smallest_t>10e-6;
	if(intersect==true ){ //hit
		if(biggest_t>10e-6){
			t=biggest_t;
			normal=get_normal_box(plane_in);
		}
		else{
			t=smallest_t;
			normal=get_normal_box(plane_out);
		}
	}
return intersect;




}

 intersection_shape Box::intersect_new (Ray const& rayIn,float & t) const{
     Ray ray{rayIn};
     ray = ray.transform_ray(world_transformation_inv(), ray);
     intersection_shape shape1{};
     glm::vec3 normal{0.0,0.0,0.0};
    if(intersect_box(ray,t,normal)==true){
        shape1.hit = true;
        shape1.distance = t;
        shape1.position=ray.origin + ray.direction*t;
        shape1.normal = normal;
        shape1.normal = glm::normalize(glm::vec3(glm::transpose(world_transformation_inv())*glm::vec4(shape1.normal, 0.0)));
        shape1.position = glm::vec3(world_transformation()*glm::vec4(shape1.position,1.0));

    }
    return shape1;
 }