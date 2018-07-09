#ifndef SCENE_HPP
#define SCENE_HPP
#include"material.hpp"
#include<memory>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<set>

struct Scene
{  std::string name_;
   std::vector<std::shared_ptr<Material>> material_vector;
   std::map<std::string,std::shared_ptr<Material>> material_map;
   std::set<std::shared_ptr<Material>> material_set;
};
Scene open_sdf (std::string const& sdf_name);
std::shared_ptr<Material> find_vector(std::string const& name,std::vector<std::shared_ptr<Material>> const& material_vector);
std::shared_ptr<Material> find_map(std::string const& name,std::map<std::string,std::shared_ptr<Material>> const& material_map);
std::shared_ptr<Material> find_set(std::string const& name,std::set<std::shared_ptr<Material>> const& material_set);
#endif