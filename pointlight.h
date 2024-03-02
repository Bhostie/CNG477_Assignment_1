#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Eigen/Dense"
#include "ray.h"
using Eigen::Vector3f;
using Eigen::Vector4f;
using Eigen::Vector2i;
/*
#PointLight: A point light will be defined with its position and intensity in this homework.  
- In the first line under the tag, index of the point light will be given.  
- In the second line under the tag, position of the light will be given as three floating point 
numbers corresponding to x, y, and z coordinates, respectively.  
- In the third line under the tagi intensity of the light will be given. It will consist of three 
floating point numbers for R, G, and B channels, respectively.  
- There may be multiple point lights in the scene. You have to take into account all of them 
while rendering. You can use their indexes to differentiate between them, same index will 
not be defined for more than one point light source.
*/


class PointLight{
    private:
        int index;
        Vector3f position;
        Vector3f intensity;
    public:
        PointLight(){}
        PointLight(int i, Vector3f pos, Vector3f inten){
            index = i;
            position = pos;
            intensity = inten;
        }
        Vector3f get_position(){
            return position;
        }
        Vector3f get_intensity(){
            return intensity;
        }
        int get_index(){
            return index;
        }
        Vector3f get_direction(Vector3f point){
            return (position - point).normalized();
        }
        float get_distance(Vector3f point){
            return (position - point).norm();
        }
        Vector3f get_color(Vector3f point, Vector3f normal, Vector3f view){
            Vector3f direction = get_direction(point);
            Vector3f reflection = (2 * normal.dot(direction) * normal - direction).normalized();
            float val = pow(reflection.dot(view), 10);
            Vector3f vec(val, val, val);
            return (intensity / (position - point).squaredNorm()) * normal.dot(direction) + vec;
        }
        bool is_in_shadow(const ray& r, float distance) {
            Vector3f l = position - r.origin();
            float t = l.norm();
            l = l.normalized();
            float s = l.dot(r.direction());
            if (s < 0) {
                return false;
            }
            if (t < 0) {
                return false;
            }
            if (t > distance) {
                return false;
            }
            return true;
        }
};

#endif