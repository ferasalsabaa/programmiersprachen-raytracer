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

                scene.material_map.insert(make_pair(material_ptr->name_,material_ptr));
           }
           if(word=="shape"){ 
                  line_stream>>word;       
                  if(word=="sphere"){
                      std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(); 
                      line_stream >> word;
                      sphere->set_name(word);      
                      line_stream >> sphere -> mittelpunkt_.x;
                      line_stream >> sphere -> mittelpunkt_.y;
                      line_stream >> sphere -> mittelpunkt_.z;
                      line_stream >> sphere -> radius_;
                      line_stream >> word;
                      sphere->material_ = find_map(word, scene.material_map);
                      scene.objects.push_back(sphere);

                } else if (word=="box") {
                    std::shared_ptr<Box> box = std::make_shared<Box>();
                    line_stream >> word;
                    box->set_name(word);  
                    line_stream >> box -> minimum_.x;
                    line_stream >> box -> minimum_.y;
                    line_stream >> box -> minimum_.z;
                    line_stream >> box -> maximum_.x;
                    line_stream >> box -> maximum_.y;
                    line_stream >> box -> maximum_.z;
                    box->material_ = find_map(word, scene.material_map);
                    scene.objects.push_back(box);
                }     
           }
           if (word=="light") {
               Light light{};
               line_stream >> light.name_;
               line_stream >> light.position_.x;
               line_stream >> light.position_.y;
               line_stream >> light.position_.z;
               line_stream >> light.color_.r;
               line_stream >> light.color_.g;
               line_stream >> light.color_.b;
               line_stream >> light.brightness_;
               scene.lights.push_back(light);
           }
           if(word=="camera") {
               Camera cam{};
               line_stream >> cam.name_;
               line_stream >> cam.aperture_;
               scene.cameras.insert(make_pair(cam.name_,cam));
           }
        }
         if(word=="render") {
             Renderer ren{};
             line_stream >> word;
             //find camera and add to renderer?
             line_stream >> ren.filename_;
             line_stream >> ren.width_;
             line_stream >> ren.height_;
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
