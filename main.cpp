/* 
CNG 477 HW1 - K. Baris Gokmen - UNFINISHED
NOTE: Use "./main input1.txt > output1.ppm" to create a .ppm file.     [FOR MAC]
NOTE: Use "main.exe input1.txt > output1.ppm" to create a .ppm file.     [FOR WINDOWS]
*/
#include <iostream>
#include <vector>
#include "Eigen/Dense"
#include "Eigen/LU"
#include "file_parser.h"
#include "sphere.h"
#include "triangle.h"
#include "mesh.h"
#include "ray.h"
#include "camera.h"
#include "pointlight.h"
#include "material.h"
#include "pointlight.h"
#include "material.h"


using Eigen::Vector3f;
using Eigen::Matrix3f;

void write_color(std::ostream &out, Vector3f pixel_color) {
    out << static_cast<int>(pixel_color.x()) << ' '
        << static_cast<int>(pixel_color.y()) << ' '
        << static_cast<int>(pixel_color.z()) << '\n';
}


/*This function will check if there are any object between hitpoint and the other point lights*/
bool check_shadow(Vector3f hitPoint, vector<PointLight>plList, vector<sphere>& sList, vector<triangle>& tList, vector<mesh>& mList, float ShadowRayEpsilon){
    for(int i=0; i<plList.size(); i++){
        PointLight pl = plList[i];
        Vector3f lightDir = pl.get_direction(hitPoint);
        Vector3f lightPos = pl.get_position();
        Vector3f shadowRayOrigin = hitPoint + lightDir * ShadowRayEpsilon;
        Vector3f shadowRayDirection = lightDir;
        ray shadowRay(hitPoint + shadowRayOrigin , shadowRayDirection);
        for(int j=0; j<sList.size(); j++){
            sphere s = sList[j];
            if(s.hit_check(shadowRay) == true && s.getHitPoint(shadowRay).norm() < lightPos.norm()){
                return true;
            }
        }
        for(int j=0; j<tList.size(); j++){
            triangle t = tList[j];
            if(t.hit_check(shadowRay) == true && t.getHitPoint(shadowRay).norm() < lightPos.norm()){
                return true;
            }
        }
        for(int j=0; j<mList.size(); j++){
            mesh m = mList[j];
            if(m.hit_check(shadowRay) == true && m.getHitPoint(shadowRay).norm() < lightPos.norm()){
                return true;
            }
        }
    }
    return false;
}


Vector3f ray_color(const ray& r,
                    vector<sphere>& sList,
                    vector<triangle>& tList,
                    vector<mesh>&mList,
                    vector<PointLight>&plList,
                    vector<Material>&materialList,
                    Vector3f background,
                    Vector3f ambientLight,
                    float ShadowRayEpsilon) {

    for(int i=0; i<sList.size(); i++){

        sphere s = sList[i];
        if (s.hit_check(r) == true){

            if(check_shadow(s.getHitPoint(r), plList, sList, tList, mList, ShadowRayEpsilon) == true){
                return s.get_ambient_color(materialList[s.get_material_index() - 1], ambientLight);
            }

        return s.get_color(plList,r, materialList[s.get_material_index() - 1], ambientLight);
        }
    }
    for(int i=0; i<tList.size(); i++){

        triangle t = tList[i];
        if (t.hit_check(r) == true){

            if(check_shadow(t.getHitPoint(r), plList, sList, tList, mList, ShadowRayEpsilon) == true){
                return t.get_ambient_color(materialList[t.get_material_index() - 1], ambientLight);
            }
        return t.get_color(plList,r, materialList[t.get_material_index() - 1], ambientLight);
        }
    }
    for(int i=0; i<mList.size(); i++){

        mesh m = mList[i];
        if (m.hit_check(r) == true){
            if(check_shadow(m.getHitPoint(r), plList, sList, tList, mList, ShadowRayEpsilon) == true){
                return m.get_ambient_color(materialList[m.get_material_index() - 1], ambientLight);
            }
        return m.get_color(plList,r, materialList[m.get_material_index() - 1], ambientLight);
        }
    }
    return background;
}



int main(int argc, char* argv[]) {


    // Error message for missing or extra arguments
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file\n";
        return 1;
    }
    // Getting inout file name from command line
    string str = argv[1];
    parser myparser(str);

    // Camera
    Camera cam = myparser.return_cam();
    int image_width = cam.getWidth();
    int image_height = cam.getHeight();

    std::ofstream outputFile("output.ppm");

    // Render 
    outputFile << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0 ; j < image_height ; j++) {
        std::cerr << "\rScanlines remaining: " << image_height - j << ' ' << std::flush;
        std::cerr << "\rScanlines remaining: " << image_height - j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            // Creating main ray
            ray r = cam.getRay(i,j);
            Vector3f pixel_color = ray_color(r, myparser.sphereList,
            myparser.triangleList,
            myparser.meshList,
            myparser.pointLightList,
            myparser.materialList,
            myparser.BackgroundColor,
            myparser.AmbientLight,
            myparser.ShadowRayEpsilon
            ); 
            
            write_color(outputFile, pixel_color);
            
        }
    }
    outputFile.close();

    std::cerr << "\nDone.\n";
}
