/* 
CNG 477 HW1 - K. Baris Gokmen - UNFINISHED
NOTE: Use "./main > output1.ppm" to create a .ppm file.
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


using Eigen::Vector3f;
using Eigen::Matrix3f;

void write_color(std::ostream &out, Vector3f pixel_color) {
    out << static_cast<int>(255 * pixel_color.x()) << ' '
        << static_cast<int>(255 * pixel_color.y()) << ' '
        << static_cast<int>(255 * pixel_color.z()) << '\n';
}

Vector3f ray_color(const ray& r,
                    vector<sphere>& sList,
                    vector<triangle>& tList,
                    vector<mesh>&mList,
                    vector<PointLight>&plList,
                    vector<Material>&materialList,
                    Vector3f background,
                    Vector3f ambientLight) {

    for(int i=0; i<sList.size(); i++){

        sphere s = sList[i];
        if (s.hit_check(r) == true){
        return s.get_color(plList,r, materialList[s.get_material_index() - 1], ambientLight);
        }
    }
    for(int i=0; i<tList.size(); i++){

        triangle t = tList[i];
        if (t.hit_check(r) == true){
        return Vector3f(1, 1, 1);
        }
    }
    for(int i=0; i<mList.size(); i++){

        mesh m = mList[i];
        if (m.hit_check(r) == true){
        return Vector3f(1, 1, 1);
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

    // Render 
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0 ; j < image_height ; j++) {
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
            myparser.AmbientLight
            ); 
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
