#include "sphere.h"

sphere::sphere(int si, int mi, Vector3f C, double R){
    sphere_index = si;
    material_index = mi;
    center = C;
    radius = R;
}
Vector3f sphere::getcenter(){
     return center;
}
double sphere::getradius(){
    return radius;
}
int sphere::get_material_index(){
    return material_index;
}
bool sphere::hit_check(const ray& r){
    Vector3f oc = r.origin() - center;
    double a = r.direction().normalized().dot(r.direction().normalized());
    double b = oc.dot(r.direction().normalized()) * 2.0;
    double c = oc.dot(oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    //std::cerr << "\rdiscriminant:" << discriminant  << std::flush;
    return (discriminant > 0);
}
Vector3f sphere::getHitPoint(const ray& r) {
    Vector3f oc = r.origin() - center;
    double a = r.direction().normalized().dot(r.direction().normalized());
    double b = oc.dot(r.direction().normalized()) * 2.0;
    double c = oc.dot(oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    float t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    return r.origin() + r.direction() * t;
}
Vector3f sphere::get_normal(const Vector3f& p) const {
    return (p - center).normalized();
}

float sphere::getHitPointDistance(const ray& r){
    Vector3f oc = r.origin() - center;
    double a = r.direction().normalized().dot(r.direction().normalized());
    double b = oc.dot(r.direction().normalized()) * 2.0;
    double c = oc.dot(oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    float t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    return t;
}

Vector3f sphere::get_color(vector<PointLight>& plList, const ray& r, Material& material, Vector3f ambientLight){
    Vector3f hitPoint = getHitPoint(r);
    Vector3f normal = get_normal(hitPoint);
    Vector3f color = Vector3f(0, 0, 0); // color of the pixe
    // handling ambient light
    color += material.get_ambientColor().cwiseProduct(ambientLight);
    Vector3f view = r.direction().normalized();
    Vector3f ambient = material.get_ambientColor().cwiseProduct(ambientLight);
    Vector3f diffuseColor = material.get_diffuseColor();
    Vector3f specularColor = material.get_specularColor();
    float phongExponent = material.get_phongExponent();
    Vector3f mirrorColor = material.get_mirrorColor();
    for (int i = 0; i < plList.size(); i++) {
        PointLight pl = plList[i];
        // Direction of the light
        Vector3f lightDir = pl.get_direction(hitPoint);
        // Intensity of the light
        Vector3f lightIntensity = pl.get_intensity();
        // Distance between the light and the hit point
        float distance = pl.get_distance(hitPoint);
        // Diffuese color
        float diff = std::max(0.0f, normal.dot(lightDir));
        Vector3f diffuse = diff * diffuseColor.cwiseProduct(lightIntensity / (distance * distance));
        // Specular color
        Vector3f halfwayDir = (lightDir - view).normalized();
        float spec = std::pow(std::max(0.0f, normal.dot(halfwayDir)), phongExponent);
        Vector3f specular = spec * specularColor*255;
        // Adding diffuse and specular color to the pixel color
        color += (diffuse + specular);
    }

    return color;
}

Vector3f sphere::get_ambient_color(Material& material, Vector3f ambientLight){
    return material.get_ambientColor().cwiseProduct(ambientLight);
}