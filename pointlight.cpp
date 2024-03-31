#include "pointlight.h"

PointLight::PointLight(int i, Vector3f pos, Vector3f inten){
            index = i;
            position = pos;
            intensity = inten;
}

Vector3f PointLight::get_position(){
    return position;
}
Vector3f PointLight::get_intensity(){
    return intensity;
}
int PointLight::get_index(){
    return index;
}
Vector3f PointLight::get_direction(Vector3f point){
    return (position - point).normalized();
}
float PointLight::get_distance(Vector3f point){
    return (position - point).norm();
}
Vector3f PointLight::get_color(Vector3f point, Vector3f normal, Vector3f view, Material material, Vector3f ambientIntensity){
    Vector3f lightDir = (position - point).normalized();
    Vector3f diffuseColor = material.get_diffuseColor();
    Vector3f ambientColor = material.get_ambientColor();
    Vector3f specularColor = material.get_specularColor();
    float phongExponent = material.get_phongExponent();
    Vector3f mirrorColor = material.get_mirrorColor();
    Vector3f lightIntensity = intensity;
    Vector3f ambient = ambientColor.cwiseProduct(ambientIntensity);
    float diff = max(0.0f, normal.dot(lightDir));
    Vector3f diffuse = diff * diffuseColor.cwiseProduct(lightIntensity);
    Vector3f reflectDir = (2.0f * normal.dot(lightDir) * normal - lightDir).normalized();
    float spec = max(0.0f, view.dot(reflectDir));
    Vector3f specular = pow(spec, phongExponent) * specularColor.cwiseProduct(lightIntensity);
    return ambient + diffuse + specular;
}





