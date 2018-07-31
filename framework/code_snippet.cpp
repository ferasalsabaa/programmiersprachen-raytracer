//   Ray Renderer::shoot_ray(float x, float y){
// 		glm::vec3 right= glm::cross(cam_.direction_, cam_.up_); 
// 		glm::vec3 up= glm::cross(right,cam_.direction_); 
// 		float fovBereich=tan(cam_.aperture_*(M_PI*0.5f/180))*2;
// 		glm::vec3 r=right*( (x-0.5f)*fovBereich );
// 		glm::vec3 u=up*( (y-0.5f)*fovBereich );
// 		glm::vec3 tmp=cam_.direction_+r+u;
// 		return Ray{cam_.origin_,glm::normalize(tmp)};
// 	}


// int calculate_shadow(glm::vec3 position, vector<light> lights, ) {
//     int sum = 0;
//     for(int i = 0; i<lights.size(); i++) {
//         Ray ray();
//         ray.origin_{position};
//         ray.direction_{lights[0].position};
//         float distance = 10;
//          for(int i=0;i<scene.objects.size();i++) {
//               bool test =scene.objects[i]->intersect(ray,distance);
//          if((test=true) {
//             sum +=1;
//         }
//         return sum;
//     }
// }


// Color Renderer::shade(Shape const& shape, Ray const& ray, float t, std::vector<Light> const& light_vector, Color const& ambient, std::vector<std::shared_ptr<Shape>> objects){
//   Color end{0,0,0};

//   for(int i = 0; i < light_vector.size(); ++i) {

//       glm::vec3 position = ray.direction + ray.direction*t;
//       glm::vec3 normal = glm::normalize(shape.get_normal(position));
//       glm::vec3 vec_light = glm::normalize(light_vector[i].position_-position);

//       Color ambient_col = ambient * (shape.material_->ka_);
//       bool intersect = false;
//       float distance = 1;
//       float intersect_value = 0;

//       for(int j = 0; j<objects.size();++j){
//         intersect = objects[j]->intersect(ray,distance);
//         if (intersect == false) {
//           intersect_value = 1;
//         } else {
//           intersect_value = 0;
//         }
//             glm::vec3 reflection_vector = glm::normalize((2* glm::dot(normal, vec_light)*normal)-vec_light);
//             glm::vec3 camera_vector = glm::normalize(ray.origin -position);
//             float ref_vec = pow(glm::dot(reflection_vector,camera_vector),shape.material_->m_);
//             Color reflect = (shape.material_->ks_) * std::max(ref_vec,(float)0);

//             Color diffuse =  ((light_vector[0].intensity_ *  (shape.material_->kd_)) * glm::dot(normal,vec_light));
//             Color end_product = (diffuse + reflect) * intersect_value;
//             end += end_product;
//           }
      
//       }
      
//     return end;
//   }

