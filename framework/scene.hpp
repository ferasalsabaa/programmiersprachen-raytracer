#ifndef SCENE_HPP
#define SCENE_HPP
#include"material.hpp"
#include"shape.hpp"
#include<memory>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<set>

struct Scene
{  std::string name_;
   std::map<std::string,std::shared_ptr<Material>> material_map;
   std::shared_ptr<Shape> shared_shape();
   
};
Scene open_sdf (std::string const& sdf_name);
std::shared_ptr<Material> find_map(std::string const& name,std::map<std::string,std::shared_ptr<Material>> const& material_map);
#endif