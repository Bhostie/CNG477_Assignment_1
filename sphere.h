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


        /* ITS NOT WORKING CORRECTLY */
        Vector3f get_color(vector<PointLight>& plList, const ray& r, Material& material, Vector3f ambientLight) {

            Vector3f hitPoint = getHitPoint(r);
            Vector3f normal = get_normal(hitPoint);
            Vector3f color = Vector3f(0, 0, 0); // color of the pixel
            Vector3f view = r.direction().normalized();
            Vector3f ambient = material.get_ambientColor().cwiseProduct(ambientLight);
            Vector3f diffuseColor = material.get_diffuseColor();
            Vector3f specularColor = material.get_specularColor();
            float phongExponent = material.get_phongExponent();
            Vector3f mirrorColor = material.get_mirrorColor();

            for (int i = 0; i < plList.size(); i++) {
                PointLight pl = plList[i];
                Vector3f lightDir = pl.get_direction(hitPoint);
                Vector3f lightIntensity = pl.get_intensity();
                float diff = std::max(0.0f, normal.dot(lightDir));
                Vector3f diffuse = diff * diffuseColor.cwiseProduct(lightIntensity);
                Vector3f reflectDir = (2.0f * normal.dot(lightDir) * normal - lightDir).normalized();
                float spec = std::pow(std::max(0.0f, view.dot(reflectDir)), phongExponent);
                Vector3f specular = spec * specularColor.cwiseProduct(lightIntensity);
                color += (diffuse + specular);
            }
            color += material.get_ambientColor().cwiseProduct(ambientLight);
            

            return color;
        }
        

};

#endif