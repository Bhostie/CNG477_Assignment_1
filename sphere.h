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
        int get_material_index(){
            return material_index;
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
        Vector3f getHitPoint(const ray& r) {
            Vector3f oc = r.origin() - center;
            double a = r.direction().normalized().dot(r.direction().normalized());
            double b = oc.dot(r.direction().normalized()) * 2.0;
            double c = oc.dot(oc) - radius*radius;
            float discriminant = b*b - 4*a*c;
            float t = (-b - std::sqrt(discriminant)) / (2.0 * a);
            return r.origin() + r.direction() * t;
        }
        
        Vector3f get_normal(const Vector3f& p) const {
            return (p - center).normalized();
        }
        
        Vector3f get_color_with_lights(vector<PointLight>& plList, const ray& r, Material& material) {
            Vector3f hitPoint = getHitPoint(r);
            Vector3f normal = get_normal(hitPoint);
            Vector3f view = -r.direction();
            Vector3f ambientIntensity = Vector3f(0.1, 0.1, 0.1);
            Vector3f color = Vector3f(0, 0, 0);
            for (int i = 0; i < plList.size(); i++) {
                PointLight pl = plList[i];
                if (!pl.is_in_shadow(ray(hitPoint, pl.get_position() - hitPoint), pl.get_distance(hitPoint))) {
                    color += pl.get_color(hitPoint, normal, view, material, ambientIntensity);
                }
            }
            return color;
        }

};

#endif