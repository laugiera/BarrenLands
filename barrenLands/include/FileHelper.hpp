//
// Created by natshez on 24/11/2017.
//

#ifndef GAME_FILEHELPER_HPP_H
#define GAME_FILEHELPER_HPP_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Tools.hpp"

/**
 * \class <FileHelper>
 * Utils to manage files
 */
class FileHelper {
public :
    static std::vector<std::string> getContent(const std::string &path);
    static void updateFile(const std::string &path, const std::string &value);
    static int findLineWithWord(const std::string& firstWord);

private:
    static std::string error_message;
    static bool lineStartsWith(const std::string& s, const std::string& needle);
};

#endif //GAME_FILEHELPER_HPP_H
