#include"file_parser.h"

void parser::getTokens(vector<string>& tokens ,string str){
    string space_delimiter = " ";
    size_t pos = 0;
    string token;
    while ((pos = str.find(space_delimiter)) != string::npos) {
        token = str.substr(0, pos);
        if(token != ""){
            tokens.push_back(token);}
        str.erase(0, pos + space_delimiter.length());
    }
    token = str.substr(0, pos);
    if(token != ""){
        tokens.push_back(token);
    }
    
}
parser::parser(string name){

    std::ifstream infile(name);
    string line;
            
    while (std::getline(infile, line))
    {
        // Trimming the "\r" character from the end of the line
        whole_file.push_back(line.find_last_not_of("\r") == string::npos
        ? "" : line.substr(0, line.find_last_not_of("\r")+1));
    }

    //TEMP
    pointLightList.push_back(PointLight(1, Vector3f(0, 0, 0), Vector3f(1000, 1000, 1000)));

    vector<string> tokens;
    int exit_key=0;
    int parse_mode=0;
    for(int i=0 ; i < whole_file.size() ; i++){


        if(whole_file[i] == ""){
            parse_mode = 0;
            continue;
        }
        else if(whole_file[i] == "#BackgroundColor"){
            parse_mode = 1;
            i++;
        }
        else if(whole_file[i] == "#MaxRecursionDepth"){
            parse_mode = 2;
            i++;
        }
        else if(whole_file[i] == "#ShadowRayEpsilon"){
            parse_mode = 3;
            i++;
        }
        else if(whole_file[i] == "#Camera"){
            parse_mode = 4;
            i++;
        }
        else if(whole_file[i] == "#Material"){
            parse_mode = 5;
            i++;
        }
        else if(whole_file[i] == "#AmbientLight"){
            parse_mode = 6;
            i++;
        }
        else if(whole_file[i] == "#PointLight"){
            parse_mode = 7;
            i++;
        }
        else if(whole_file[i] == "#VertexList"){
            parse_mode = 8;
            i++;
        }
        else if(whole_file[i] == "#Sphere"){
            parse_mode = 9;
            i++;
        }
        else if(whole_file[i] == "#Triangle"){
            parse_mode = 10;
            i++;
        }
        else if(whole_file[i] == "#Mesh"){
            parse_mode = 11;
            i++;
        }
        
        switch(parse_mode){
            case 1:
                getTokens(tokens, whole_file[i]);
                BackgroundColor = Vector3f(std::stof(tokens[0]), std::stof(tokens[1]), std::stof(tokens[2]));
                tokens.clear();
                break;
            
            case 2:
                 getTokens(tokens, whole_file[i]);
                 MaxRecursionDepth = std::stoi(tokens[0]);
                 tokens.clear();
                 break;

            case 3:
                getTokens(tokens, whole_file[i]);
                ShadowRayEpsilon = std::stof(tokens[0]);
                tokens.clear();
                break;
            case 4:
                getTokens(tokens, whole_file[i]);
                main_camera.setPosition(Vector3f(std::stof(tokens[0]),std::stof(tokens[1]),std::stof(tokens[2])));
                tokens.clear();
                i++;
                getTokens(tokens, whole_file[i]);
                main_camera.setGazeParameters(Vector3f(std::stof(tokens[0]),std::stof(tokens[1]),std::stof(tokens[2])));
                tokens.clear();
                i++;
                getTokens(tokens, whole_file[i]);
                main_camera.setUpParameters(Vector3f(std::stof(tokens[0]),std::stof(tokens[1]),std::stof(tokens[2])));
                tokens.clear();
                i++;
                getTokens(tokens, whole_file[i]);
                main_camera.setPlaneAttributes(std::stof(tokens[0]), std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
                tokens.clear();
                i++;
                getTokens(tokens, whole_file[i]);
                main_camera.setDistance(std::stof(tokens[0]));
                tokens.clear();
                i++;
                getTokens(tokens, whole_file[i]);
                main_camera.setResolution(Vector2i(std::stoi(tokens[0]) ,std::stoi(tokens[1])));
                tokens.clear();
                break;

            case 5:
                getTokens(tokens, whole_file[i]);
                i++;
                getTokens(tokens, whole_file[i]);
                i++;
                getTokens(tokens, whole_file[i]);
                i++;
                getTokens(tokens, whole_file[i]);
                i++;
                getTokens(tokens, whole_file[i]);
                i++;
                getTokens(tokens, whole_file[i]);
                materialList.push_back(Material(std::stoi(tokens[0]), 
                                               Vector3f(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])),
                                               Vector3f(std::stof(tokens[4]), std::stof(tokens[5]), std::stof(tokens[6])),
                                               Vector3f(std::stof(tokens[7]), std::stof(tokens[8]), std::stof(tokens[9])),
                                               std::stof(tokens[10]),
                                               Vector3f(std::stof(tokens[11]), std::stof(tokens[12]), std::stof(tokens[13]))));
                tokens.clear();
                break;

            
            case 6:
                getTokens(tokens, whole_file[i]);
                AmbientLight = Vector3f(std::stof(tokens[0]), std::stof(tokens[1]), std::stof(tokens[2]));
                tokens.clear();
                break;
            
            case 7:
                // TODO: Implement PointLight
                break;

            case 8:
                getTokens(tokens, whole_file[i]);
                    VertexList.push_back(Vector3f(std::stof(tokens[0]), std::stof(tokens[1]), std::stof(tokens[2])));
                    tokens.clear();
                    break;

              
            case 9:
                getTokens(tokens, whole_file[i]);
                i++;
                getTokens(tokens, whole_file[i]);
                i++;
                getTokens(tokens, whole_file[i]);
                i++;
                getTokens(tokens, whole_file[i]);
                sphereList.push_back(sphere(std::stoi(tokens[0]),
                                     std::stoi(tokens[1]),
                                     VertexList[std::stoi(tokens[2]) - 1],
                                     std::stof(tokens[3])));
                tokens.clear();
                break;

            case 10: 
                getTokens(tokens, whole_file[i]);
                i++;
                getTokens(tokens, whole_file[i]);
                i++;
                getTokens(tokens, whole_file[i]);
                triangleList.push_back(triangle(std::stoi(tokens[0]),
                                       std::stoi(tokens[1]),
                                       VertexList[std::stoi(tokens[2]) - 1],
                                       VertexList[std::stoi(tokens[3]) - 1],
                                       VertexList[std::stoi(tokens[4]) - 1]));
                tokens.clear();
                break;

            case 11:
                while(whole_file[i] != ""){
                    getTokens(tokens, whole_file[i]);
                    i++;
                }
                vector<triangle> temp;
                for(int j=2; j<tokens.size(); j+=3){
                    temp.push_back(triangle(j-2,
                                       std::stoi(tokens[1]),
                                       VertexList[std::stoi(tokens[j]) - 1],
                                       VertexList[std::stoi(tokens[j+1]) - 1],
                                       VertexList[std::stoi(tokens[j+2]) - 1]));
                }
                meshList.push_back(mesh(std::stoi(tokens[0]), std::stoi(tokens[1]), temp));
        }
    }      
}
 
void parser::print_file(){
    for(int i=0; i < whole_file.size(); i++ ){
        std::cout << whole_file[i] << std::endl;
    }
}

Camera parser::return_cam(){
    main_camera.calculate_vectors();
    return main_camera;
}