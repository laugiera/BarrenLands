//
// Created by Lou Landry on 08/12/2017.
//

#include "../include/Tools.hpp"


float Tools::windowWidth = 1200;
float Tools::windowHeight = 1000;
int Tools::nbSub = 100;
float Tools::scale = 10;
float Tools::width = 1;
float Tools::speed = 15;
float Tools::seaLevel = -5;
glm::mat4 Tools::projMatrix = glm::perspective(glm::radians(70.f), Tools::windowWidth/Tools::windowHeight, 0.1f, 2000.f);

/**
 * Take a string representation of a bool and converts it to bool
 * @param s string
 * @return bool or throws std::invalid_argument
 */
bool Tools::boolFromString(std::string s) {
    if (s == "0" || s == "false" || s == "FALSE") {
        return false;
    } else if (s == "1" || s == "true" || s== "TRUE") {
        return true;
    } else {
        throw std::invalid_argument(s + " -> input does not represent a bool");
    }
}

/**
 * Take a string representation of an int and converts it to int
 * @param s string
 * @return string or throws std::invalid_argument
 */
int Tools::intFromString(std::string s) {
    std::regex reg("[0-9]+$");
    if(!std::regex_match(s, reg)){
        throw std::invalid_argument(s+ " -> input does not represent an int");
    }
    return std::stoi(s);
}

/**
 * Puts a string to lower case
 * @param s string
 * @return string
 */
std::string Tools::toLowerCase(const std::string & s) {
    std::string new_string = s;
    std::transform(new_string.begin(), new_string.end(),new_string.begin(), ::tolower);
    return new_string;
}

/**
 * Puts a string to upper case
 * @param s string
 * @return string
 */
std::string Tools::toUpperCase(const std::string &s) {
    std::string new_string = s;
    std::transform(new_string.begin(), new_string.end(),new_string.begin(), ::toupper);
    return new_string;
}

/**
 * Removes all blank characters from a string and puts it to lower case for comparison purposes
 * @param s string
 * @return string
 */
std::string Tools::sanitizeInput(const std::string s) {
    std::string new_string = s;
    std::size_t pos = new_string.find(" ");
    while(pos != std::string::npos) {
        new_string.erase(pos,1);
        pos = new_string.find(" ");
    }
    return toLowerCase(new_string);
}


/**
 * Parse a string using a string as delimitor adn puts all substrings in a vector
 * @param _data string
 * @param delimitor string
 * @return vector<string>
 */
std::vector<std::string> Tools::stringToVector(std::string _data, std::string delimitor) {
    std::vector<std::string> content_vector;
    //put data string in c char *
    char * data = new char [_data.length()+1];
    std::strcpy (data, _data.c_str());
    //tokenize
    char * vector_element = strtok(data, delimitor.c_str());
    while(vector_element != NULL){
        content_vector.push_back(std::string(vector_element)); //push substring in vector
        vector_element = strtok(nullptr, delimitor.c_str());
    }
    return content_vector;
}

/**
 * Computes Parent Folder path of the file (or folder) designated by the passed path
 * @param filePath
 * @return
 */
std::string Tools::getFolderPath(const std::string & filePath) {
#ifdef _WIN32
    char pathSeparator = '\\';
#else
    char pathSeparator = '/';
#endif
    size_t pos = filePath.find_last_of(pathSeparator);
    return filePath.substr(0, pos); //return substring from beginning to last pathseparator
}

bool Tools::WaitForSeconds(double secondsToWait){

    clock_t startTime = clock(); //Start timer
    double secondsPassed;

    bool wait =true;
    while(wait)
    {
        secondsPassed = (clock() - startTime) / CLOCKS_PER_SEC;
        if(secondsPassed >= secondsToWait)
        {
            wait = false;
        }
    }
}

float  Tools::SquareDistance(glm::vec2 v1, glm::vec2 v2){ //check the square to avoid using roots
    return pow((v2.x-v2.x),2) - pow((v1.y-v1.y),2);
}

std::vector<std::string> Tools::load(std::string filePath) {
    std::ifstream file (filePath);
    std::string line;
    std::vector<std::string> fileContent;
    if(file.is_open()){
        while(std::getline(file, line) && !line.empty() && line!= " "  ){
            fileContent.push_back(line);
        }
        file.close();
    } else {
        throw std::runtime_error(filePath + " : File doesn't exist or could not be opened");
    }
    if(fileContent.empty()){
        throw std::runtime_error("File is empty");
    }
    return fileContent;
}






