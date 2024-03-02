#ifndef FILE_PARSER_H
#define FILE_PARSER_H

/* TO BE CONTINUED ! */
#include<iostream>
#include<string>
#include<vector>
#include<fstream>   // for std::ifstream
#include<sstream>   // for std::istringstream
#include"Eigen/Dense"

#include"sphere.h"
#include"sphere.h"
#include"file_parser.h"
#include"triangle.h"
#include"ray.h"
#include"camera.h"
#include"mesh.h"
#include"pointlight.h"

using Eigen::Vector3f;
using Eigen::Vector3i;
using Eigen::Vector4f;
using Eigen::Vector2i;
using std::vector;
using std::string;


/**
 * @class parser
 * @brief A class that represents a file parser.
 * 
 * The parser class is responsible for parsing a file and extracting relevant information from it.
 * It provides methods to retrieve various data such as camera settings, background color, material properties, etc.
 */
class parser{
    private:
        vector<string> whole_file;
        Camera main_camera;
        
        /**
         * @brief Splits a string into tokens based on a delimiter and stores them in a vector.
         * 
         * @param tokens The vector to store the tokens.
         * @param str The string to be split into tokens.
         */
        void getTokens(vector<string>& ,string);
       
    public:
        
        Vector3f BackgroundColor;
        int MaxRecursionDepth;
        float ShadowRayEpsilon;
        
        Vector3f AmbientLight;
        vector<Vector3f> VertexList;
        vector<sphere> sphereList;
        vector<triangle> triangleList;
        vector<mesh> meshList;
        vector<PointLight> pointLightList;

        parser(string name);
        void print_file();
        Camera return_cam();
        


};

#endif


