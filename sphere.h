#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector>

#include"Eigen/Dense"
#include "ray.h"
#include "pointlight.h"
#include "camera.h"
using Eigen::Vector3f;
using std::vector;

class sphere{
    private:
        int sphere_index;
        int material_index;
        Vector3f center;
        double radius;
    public:
        sphere(){}
        sphere(int si, int mi, Vector3f C, double R){
            sphere_index = si;
            material_index = mi;
            center = C;
            radius = R;
        }
        Vector3f getcenter(){
             return center;
        }
        double getradius(){
            return radius;
        }

        bool hit_check(const ray& r) {

            Vector3f oc = r.origin() - center;
            double a = r.direction().normalized().dot(r.direction().normalized());
            double b = oc.dot(r.direction().normalized()) * 2.0;
            double c = oc.dot(oc) - radius*radius;
            float discriminant = b*b - 4*a*c;
            //std::cerr << "\rdiscriminant:" << discriminant  << std::flush;
            return (discriminant > 0);
    
        }
        
        Vector3f get_normal(const Vector3f& p) const {
            return (p - center).normalized();
        }
        
        Vector3f get_color_with_lights(vector<PointLight>& plList) {
            Vector3f color(0, 0, 0);
            for (int i = 0; i < plList.size(); ++i) {
                PointLight pl = plList[i];
                Vector3f l = pl.get_position() - center; // Assuming center is the position of your sphere
                float s = l.norm() * l.norm(); // Apply inverse square law
                l = l.normalized();
                Vector3f normal = get_normal(pl.get_position()); // Assuming this returns the correct surface normal
                float m = l.dot(normal);
                if (m > 0) {
                    color += (pl.get_intensity() / s) * m;
                }
            }
            // make color vector values between 0 and 1
            color = color.cwiseMax(0).cwiseMin(1);
            return color;
}






};

#endif