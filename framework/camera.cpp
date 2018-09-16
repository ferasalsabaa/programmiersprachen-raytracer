#include "camera.hpp"
using namespace std;

   

    Camera::Camera() : name_{""}, aperture_{90}, origin_{0.0,10.0,10.0}, direction_{0.0,0.0,-1}, up_{0,1,0}, transform_cam_{}, transform_cam_inv_{glm::inverse(transform_cam_)} {}

    Camera::Camera(std::string const& name, float aperture, glm::vec3 origin, glm::vec3 direction, glm::vec3 up) :
     name_{name}, aperture_{aperture}, origin_ {origin}, direction_{direction}, up_{up}, transform_cam_{}, transform_cam_inv_{glm::inverse(transform_cam_)} {}

    Camera::~Camera(){}
    Ray Camera::shoot_ray(float x, float y, float width_, float height_) {
        glm::vec3 rayOrigin{0,0,0};
        glm::vec3 rayDirection = {(x-width_/2), (y-height_/2), -(width_/2)/tan(aperture_/2)}; 
        Ray cam_ray{rayOrigin,rayDirection};
        auto transform_cam = transform_camera();
        return cam_ray.transform_ray(transform_cam);
    }


     Ray Camera::shoot_ray1(float x, float y){
		glm::vec3 right=glm::cross(direction_,up_);
		glm::vec3 up=glm::cross(right,direction_); 
		float fovBereich=tan(aperture_*(M_PI*0.5f/180))*2;
		glm::vec3 r=right*( (x-0.5f)*fovBereich );
		glm::vec3 u=up*( (y-0.5f)*fovBereich );
		glm::vec3 tmp=direction_+r+u;
		Ray ray{origin_,glm::normalize(tmp)};

        transform_cam_ = transform_camera(); //check if i need to change transform_cam_ from camera or not

        Ray newRay;

        return newRay.transform_ray(transform_cam_, ray);

	}

    glm::vec3 Camera::get_origin() const{
        return origin_;
    }

    glm::mat4 Camera::transform_camera(){
        glm::vec3 e = origin_;
        glm::vec3 n = glm::normalize(direction_); //negative z-Achse
        glm::vec3 up = up_; //y-Achse 
 
        glm::vec3 u = glm::normalize(glm::cross(n, up)); //u steht senkrecht auch n und up
        glm::vec3 v = glm::normalize(glm::cross(u, n)); // stellt sicher, dass up senkrecht zu u und n ist

        glm::mat4 transformCam;
        transformCam[0] = glm::vec4 {u.x, v.x, n.x, e.x};
        transformCam[1] = glm::vec4 {u.y, v.y, n.y, e.y};
        transformCam[2] = glm::vec4 {u.z, v.z, n.z, e.z};
        transformCam[3] = glm::vec4 {0,0,0,1};

        return transformCam;
    }


    void Camera::translate(glm::vec3 const& p) {
        glm::mat4 transformCam;
        transformCam[0] = glm::vec4 {1.0f, 0.0f, 0.0f, p.x};
        transformCam[1] = glm::vec4 {0.0f, 1.0f, 0.0f, p.y};
        transformCam[2] = glm::vec4 {0.0f, 0.0f, 1.0f, p.z};
        transformCam[3] = glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};

        transform_cam_ = transformCam * transform_cam_;
        transform_cam_inv_ = glm::inverse(transform_cam_);
    }

    void Camera::rotate_x(float phi) {
        glm::mat4 transformCam;
        transformCam[0] = glm::vec4 {1.0f, 0.0f, 0.0f, 0.0f};
        transformCam[1] = glm::vec4 {0.0f, cos(phi), sin(phi), 0.0f};
        transformCam[2] = glm::vec4 {0.0f, -sin(phi), cos(phi), 0.0f};
        transformCam[3] = glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};

        transform_cam_ = transformCam * transform_cam_;
        transform_cam_inv_ = glm::inverse(transform_cam_);
    }

    void Camera::rotate_y(float phi) {
        glm::mat4 transformCam;
        transformCam[0] = glm::vec4 {cos(phi), 0.0f, -sin(phi), 0.0f};
        transformCam[1] = glm::vec4 {0.0f, 1.0f, 0.0f, 0.0f};
        transformCam[2] = glm::vec4 {sin(phi), 0.0f, cos(phi), 0.0f};
        transformCam[3] = glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};

        transform_cam_ = transformCam * transform_cam_;
        transform_cam_inv_ = glm::inverse(transform_cam_);
    }

    void Camera::rotate_z(float phi) {
        glm::mat4 transformCam;
        transformCam[0] = glm::vec4 {cos(phi), sin(phi), 0.0f, 0.0f};
        transformCam[1] = glm::vec4 {-sin(phi), cos(phi), 0.0f, 0.0f};
        transformCam[2] = glm::vec4 {0.0f, 0.0f, 1.0f, 0.0f};
        transformCam[3] = glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};

        transform_cam_ = transformCam * transform_cam_;
        transform_cam_inv_ = glm::inverse(transform_cam_);
    }

 