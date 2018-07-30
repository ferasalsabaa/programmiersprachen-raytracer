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