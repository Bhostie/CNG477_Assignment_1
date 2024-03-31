#include "ray.h"
#include"material.h"

Material::Material(int i, Vector3f a, Vector3f d, Vector3f s, float p, Vector3f m){
    index = i;
    ambientColor = a;
    diffuseColor = d;
    specularColor = s;
    phongExponent = p;
    mirrorColor = m;
}
Vector3f Material::get_ambientColor(){
    return ambientColor;
}
Vector3f Material::get_diffuseColor(){
    return diffuseColor;
}
Vector3f Material::get_specularColor(){
    return specularColor;
}
float Material::get_phongExponent(){
    return phongExponent;
}
Vector3f Material::get_mirrorColor(){
    return mirrorColor;
}
int Material::get_index(){
    return index;
}
