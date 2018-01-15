//
// Created by Lou Landry on 08/12/2017.
//

#ifndef INTERACTIVESTORY_TOOLS_HPP
#define INTERACTIVESTORY_TOOLS_HPP

#include <string>
#include <regex>
#include <vector>
#include <iostream>
#include <cstring>
#include <math.h>
#include "glm/vec2.hpp"

class Tools {
public:

    static float windowWidth;
    static float windowHeight;

//transforms a string bool (ex "true") into a bool, throws std::invalid_argument
static bool boolFromString(std::string s);

//transforms a string int (ex "3") into an int, throws std::invalid_argument
static int intFromString(std::string s);

//removes all blanks from an int and puts it in lower case for comparison purposes
static std::string sanitizeInput(std::string s);

//puts string in lower case
static std::string toLowerCase(const std::string & s);

//puts string in lower case
static std::string toUpperCase(const std::string & s);

//separate a string using a character as delimitor, puts all the substrings in a vector
static std::vector<std::string> stringToVector(std::string data, std::string delimitor);

static std::string getFolderPath(const std::string & filePath);

//waits for x seconds
static bool WaitForSeconds(double secondsToWait);

static float  SquareDistance(glm::vec2 v1, glm::vec2 v2);

};





#endif //INTERACTIVESTORY_TOOLS_HPP
