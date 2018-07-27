#include"scene.hpp"
#include"Sphere.hpp"
#include"shape.hpp"
#include"light.hpp"
#include"box.hpp"
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
                  if(word=="sphere"){
                      std::shared_ptr<Shape> sphere = std::make_shared<Sphere>();
                      line_stream >> word;
                      sphere->set_name(word);    
        //            line_stream >> sphere -> mittelpunkt_.x_;
        //            line_stream >> sphere -> mittelpunkt_.y_;
        //            line_stream >> sphere -> mittelpunkt_.z_;
        //            line_stream >> sphere -> radius_;                 
        //        } else if (word=="box") {
        //            auto box = std::make_shared<Box>();
        //            line_stream >> box -> minimum_.x_;
        //            line_stream >> box -> minimum_.y_;
        //            line_stream >> box -> minimum_.z_;
        //            line_stream >> box -> maximum.x_;
        //            line_stream >> box -> maximum.y_;
        //            line_stream >> box -> maximum.z_;
        //        }
        //        line_stream >> shape -> material_.*name_;
        //    }
        //    if (word=="light") {
        //        auto light = std::make_shared<Light>();
        //        line_stream >> light -> name_;
        //        line_stream >> light -> position_.x_;
        //        line_stream >> light -> position_.y_;
        //        line_stream >> light -> position_.z_;
        //        line_stream >> light -> color_.r;
        //        line_stream >> light -> color_.g;
        //        line_stream >> light -> color_.b;
        //        line_stream >> light -> brightness_;
           }
        }

    }
    ifs.close();
    return scene;
}
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
