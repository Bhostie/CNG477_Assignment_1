#ifndef MATERIAL_H
#define MATERIAL_H
#include <iostream>

#include"Eigen/Dense"

using Eigen::Vector3f;
using Eigen::Vector4f;
using Eigen::Vector2i;

/*
#Material: A material will be defined with ambient, diffuse, specular, and mirror reflectance 
values for each color channel in this homework.  
- In the first line under the tag, index of the material will be given.  
- In the second line under the tag, ambient reflectance will be given. It will be specified as 
three floating point numbers each between 0 and 1 representing R, G, and B channels, 
respectively.  
- In the third line under the tag, diffuse reflectance will be given. It will be specified as three 
floating point numbers each between 0 and 1 representing R, G, and B channels, 
respectively.  
- In the fourth line under the tag, specular reflectance will be given. It will be specified as 
three floating point numbers each between 0 and 1 representing R, G, and B channels, 
respectively.  
- In the fifth line under the tag, phong exponent for the specular reflectance will be given. It 
will be specified as a floating point number.  
- In the sixth line under the tag, mirror reflectance will be given. It will be specified as three 
floating point numbers each between 0 and 1 representing R, G, and B channels, 
respectively.  
- There may be multiple material tags each introducing another material. You can use 
material indexes to differentiate between them, same material index will not be defined for 
more than one material. 
*/

class Material{
    private:
        int index;
        Vector3f ambientColor;
        Vector3f diffuseColor;
        Vector3f specularColor;
        float phongExponent;
        Vector3f mirrorColor;
    public:
        Material(){}
        Material(int i, Vector3f a, Vector3f d, Vector3f s, float p, Vector3f m);
        Vector3f get_ambientColor();
        Vector3f get_diffuseColor();
        Vector3f get_specularColor();
        float get_phongExponent();
        Vector3f get_mirrorColor();
        int get_index();
};



#endif