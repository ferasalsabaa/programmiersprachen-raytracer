#ifndef SCENE_HPP
#define SCENE_HPP
#include "material.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "Sphere.hpp"
#include "light.hpp"
#include "box.hpp"
#include "camera.hpp"

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>


struct Scene{ 
    
   std::string name_;
   Camera cam_;
   std::map<std::string,std::shared_ptr<Material>> material_map;
   std::vector<std::shared_ptr<Shape>> objects;
   std::vector<Light> lights;
   Light ambient();
   //Renderer rend();

};

Scene open_sdf (std::string const& sdf_name);
std::shared_ptr<Material> find_map(std::string const& name,std::map<std::string,std::shared_ptr<Material>> const& material_map);

#endif