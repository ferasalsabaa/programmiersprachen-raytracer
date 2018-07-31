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


// void Renderer::render_test2(Scene const& scene){
//   float distance = 0;
//   bool intersect = false;
//   for (unsigned y = 0; y < height_; ++y) {
//     float sy= 1.0-y*1.0/height_;
//     for (unsigned x = 0; x < width_; ++x) {
//       float sx= x*1.0/width_;
//       Pixel p(x,y);
//       Ray ray= cam_.shoot_ray(sx,sy);
//       float closest_distance = 100;
//       int object = 10000; 
//       for(int i=0;i<scene.objects.size();i++) {
//         intersect = scene.objects[i]->intersect(ray,distance);
//         if ((distance < closest_distance) && (intersect == true)) {
//           closest_distance = distance;
//           object = i;
//         }
//       }
//         if(object != 10000) {
//           //p.color = Color(0.4,0.0,0.4);
//           p.color = shade(*scene.objects[object], ray, distance, scene.lights, scene.ambient);
//         } else {
//           p.color = Color(0.0,0.0,0.4);
//         }        
//       write(p);
//       }
//     }
//   ppm_.save(filename_);  
// }


