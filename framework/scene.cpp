#include "scene.hpp"
#include "renderer.hpp"
#include<memory>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include"material.hpp"

Scene open_sdf(std::string const& sdf_name)
{
    Scene scene;
    std::ifstream ifs;
    ifs.open(sdf_name);
    std::string line;

    while(std::getline(ifs,line))
    {
        std::stringstream line_stream(line);
        std::string word;
        line_stream >> word;
        if(word=="define")
        {
           line_stream>>word;
           if(word=="material") {
                std::shared_ptr<Material> material_ptr = std::make_shared<Material>();
                line_stream>> material_ptr->name_;
                line_stream >> material_ptr->ka_.r; 
                line_stream >> material_ptr->ka_.g; 
                line_stream >> material_ptr->ka_.b; 
                line_stream >> material_ptr->kd_.r; 
                line_stream >> material_ptr->kd_.g;
                line_stream >> material_ptr->kd_.b;
                line_stream >> material_ptr->ks_.r; 
                line_stream >> material_ptr->ks_.g;
                line_stream >> material_ptr->ks_.b;
                line_stream >> material_ptr->m_; 
                line_stream >> material_ptr->opacity_;
                line_stream >> material_ptr->refraction_index_; 
                scene.material_map.insert(make_pair(material_ptr->name_,material_ptr));
           }
           if(word=="shape"){ 
                  line_stream>>word;       
                  if(word=="sphere"){
                      line_stream >> word;
                      std::string name = word;
                      glm::vec3 center;   
                      line_stream >> center.x;
                      line_stream >> center.y;
                      line_stream >> center.z;
                      float radius;
                      line_stream >> radius;
                      line_stream >> word;
                      std::shared_ptr<Material> material_sphere  = find_map(word, scene.material_map);
                      std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(center, radius, name, material_sphere); 
                      scene.objects.push_back(sphere);

                } else if (word=="box") {
                    std::string name;
                    line_stream >> word;
                    name = word; 
                    glm::vec3 min;
                    glm::vec3 max;
                    line_stream >> min.x;
                    line_stream >> min.y;
                    line_stream >> min.z;
                    line_stream >> max.x;
                    line_stream >> max.y;
                    line_stream >> max.z;
                    line_stream >> word;
                    std::shared_ptr<Material> material_box  = find_map(word, scene.material_map);
                    std::shared_ptr<Box> box = std::make_shared<Box>(min, max, name, material_box);
                    scene.objects.push_back(box);
                }
                else if(word=="triangle") {
                    // std::string name;
                    // line_stream >> word;
                    // name = word;
                    // glm::vec3 a;
                    // glm::vec3 b;
                    // glm::vec3 c;
                    // line_stream >> a.x;
                    // line_stream >> a.y;
                    // line_stream >> a.z;
                    // line_stream >> b.x;
                    // line_stream >> b.y;
                    // line_stream >> b.z;
                    // line_stream >> c.x;
                    // line_stream >> c.y;
                    // line_stream >> c.z;
                    // line_stream >> word;
                    // std::shared_ptr<Material> material_triangle  = find_map(word, scene.material_map);
                    // std::shared_ptr<Triangle> triangle = std::make_shared<Triangle>(a,b,c,name,material_triangle);
                    // scene.objects.push_back(triangle);
                }     
           }
           if (word=="light") {
               std::string name;
               line_stream >> word;
               name = word;
               glm::vec3 position;
               Color color;
               float brightness;
               line_stream >> position.x;
               line_stream >> position.y;
               line_stream >> position.z;
               line_stream >> color.r;
               line_stream >> color.g;
               line_stream >> color.b;
               line_stream >> brightness;
               Light light(name,position,color,brightness);
               scene.lights.push_back(light);
           }
           if (word=="ambient") {
               Color ambient_col{0,0,0};
               line_stream >> ambient_col.r;
               line_stream >> ambient_col.g;
               line_stream >> ambient_col.b;
               scene.ambient_ = ambient_col;
 
           }
           if(word=="camera") {
               std::string name;
               line_stream >> word;
               name = word;
               float aperture;
               glm::vec3 origin;
               glm::vec3 direction;
               glm::vec3 up;
               line_stream >> aperture;
               line_stream >> origin.x;
               line_stream >> origin.y;
               line_stream >> origin.z;
               line_stream >> direction.x;
               line_stream >> direction.y;
               line_stream >> direction.z;
               line_stream >> up.x;
               line_stream >> up.y;
               line_stream >> up.z;
               Camera cam{name,aperture,origin,direction,up};
               scene.camera=cam;

           }
        }
         if(word=="render") {
               line_stream>>scene.width_;
               line_stream>>scene.height_;
               line_stream>>scene.name_;
         

         }
    }
    ifs.close();
    return scene;
}





std::shared_ptr<Material> find_map(std::string const& name,std::map<std::string,std::shared_ptr<Material>> const& material_map) {
    auto it = material_map.find(name);
    if(it != material_map.end())
    {
        return it->second;
    } else {
        return nullptr;
    }

}

Camera find_camera(std::string const& name, std::map<std::string, Camera> const& cameras) {
    auto it = cameras.find(name);
    if(it != cameras.end())
    {
        return it->second;
    } else {
        Camera cam{};
        std::cout << "no such camera. set default";
        return cam;
    }

}
