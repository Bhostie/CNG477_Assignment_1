#ifndef CAMERA_H
#define CAMERA_H

#include "Eigen/Dense"
#include "ray.h"
using Eigen::Vector3f;
using Eigen::Vector4f;
using Eigen::Vector2i;

/*
#Camera: Parameters defining the camera will be given under this tag.  
- In the first line under the tag, position parameters of the camera will be given as three 
floating point numbers, specifying x, y, z coordinates, respectively.  
- In the second line under the tag, gaze parameters will be given. These will define the gaze 
vector which is the direction that the camera is looking at. Gaze parameters will consist of 
three floating point numbers specifying x, y, z values of the gaze vector.  
- In the third line under the tag, up parameters will be given. These will define the up vector 
of the camera. Up parameters will be three floating point numbers specifying x, y, z values of 
the up vector.  
- In the fourth line under the tag, near plane attributes will be listed. These will consist of 
four floating point numbers specifying left, right, bottom, and top parameters, respectively.  
- In the fifth line under the tag, near distance will be given. This value is the distance 
between the image plane and the camera. The value will consist of one floating point 
number.  
- In the sixth line under the tag, resolution of the output image will be given. These will 
consist of two integer values specifying the number of pixels in the width and height, 
respectively.  
- There will be only one of this tag in the scene file. 
*/

struct fourf{
    float left;
    float right;
    float bottom;
    float top;
};
typedef struct fourf fourf;

class Camera{
    private:
        Vector3f position;
        Vector3f gaze_parameters;
        Vector3f up_parameters;
        fourf plane_attributes;
        float near_distance;
        Vector2i resolution;

    public:
    Vector3f vxw;
    Vector3f m;
    Vector3f q;
    Camera(){}
    Camera(Vector3f pos, Vector3f gaze, Vector3f up, fourf plane, float near, Vector2i res){
        position = pos;
        gaze_parameters = gaze;
        up_parameters = up;
        plane_attributes = plane;
        near_distance = near;
        resolution = res;
        
        Vector3f temp1 = up_parameters.normalized().cross(gaze_parameters.normalized() * (-1));
        vxw = temp1.normalized();
        m = position + (gaze_parameters.normalized() * near_distance);
        q = m + vxw * plane.left + up_parameters.normalized() * plane.top;
    }
    void calculate_vectors(){
        Vector3f temp1 = up_parameters.normalized().cross(gaze_parameters.normalized() * (-1));
        vxw = temp1.normalized();
        m = position + (gaze_parameters.normalized() * near_distance);
        q = m + vxw * plane_attributes.left + up_parameters.normalized() * plane_attributes.top;
    }
    int getWidth(){
        return resolution.x();
    }
    int getHeight(){
        return resolution.y();
    }
    void setPosition(Vector3f input){
        position = input;
    }
    void setGazeParameters(Vector3f input){
        gaze_parameters = input;
    }
    void setUpParameters(Vector3f input){
        up_parameters = input;
    }
    void setPlaneAttributes(float i1, float i2, float i3, float i4){
        plane_attributes.left = i1;
        plane_attributes.right = i2;
        plane_attributes.bottom = i3;
        plane_attributes.top = i4;
    }
    void setDistance(float input){
        near_distance = input;
    }
    void setResolution(Vector2i input){
        resolution = input;
    }

    Vector3f getPosition(){
        return position;
    }
    Vector3f getGazeParameters(){
        return gaze_parameters;
    }
    Vector3f getUpParameters(){
        return up_parameters;
    }
    fourf getPlaneAttributes(){
        return plane_attributes;
    }
    float getDistance(){
        return near_distance;
    }
    Vector2i getResolution(){
        return resolution;
    }


    ray getRay(int row, int col) {
    float u = ((plane_attributes.right - plane_attributes.left) / getWidth()) * (row + 0.5);
    float v = ((plane_attributes.top - plane_attributes.bottom) / getHeight()) * (col + 0.5);

    // Calculate ray direction in camera space
    Vector3f ray_dir = (q + (vxw * u) - (up_parameters.normalized() * v) - position).normalized();

    ray_dir = ray_dir.x() * vxw + ray_dir.y() * up_parameters.normalized() + ray_dir.z() * (-gaze_parameters.normalized());

    // Create and return ray
    return ray(position, ray_dir);
}


    

};

#endif