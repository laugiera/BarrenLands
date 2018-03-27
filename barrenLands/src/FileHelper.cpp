//
// Created by natshez on 24/11/2017.
//
#include "FileHelper.hpp"

std::string FileHelper::error_message = "Impossible to load file !";

/**
 * getContent
 * @param path  &std::string path of the file to open
 * @return std::vector<std::string> vector with all the strings separated by the char '|' in the file
 * \exception <std::runtime_error> { cannot open the given file }
 */
std::vector<std::string> FileHelper::getContent(const std::string &path){
    std::string row;
    std::vector<std::string> separatedValues;
    std::string token;

    std::ifstream fichier(path, std::ios::in);  //open file

    if(!fichier){
        throw std::runtime_error(FileHelper::error_message);
    }
    while(fichier.peek() != std::ifstream::traits_type::eof()){
        getline(fichier, row);
        std::istringstream ss(row);
        while(std::getline(ss, token, ';')) {
            separatedValues.push_back(token);
        }
    }
    fichier.close(); //close file
    return separatedValues;
}
/**
 * updateFile
 * @param path &std::string  path of the file to update
 * @param value &std::string    the new content of the file
 * \exception <std::runtime_error> { cannot open the given file }
 * This function erase the old content !
 */
void FileHelper::updateFile(const std::string &path, const std::string &value){
    std::ofstream fichier(path, std::ios::out);  //open file

    if(!fichier){
        throw std::runtime_error(FileHelper::error_message);
    }
    fichier << value << '\n';
    fichier.close(); //close file
}

int FileHelper::findLineWithWord(const std::string& firstWord){
        std::ifstream file(Tools::savePath.c_str(), std::ios::in);  //open file
        std::string line;
        if (!file){
            throw std::runtime_error(FileHelper::error_message);
        }
        unsigned int currentLine = 0;
        while (std::getline(file, line)) { // I changed this, see below
            currentLine++;
            if (lineStartsWith(line,firstWord) != std::string::npos) {
                std::cout << "found: " << firstWord << "line: " << currentLine << std::endl;
            }
        }
        file.close();
}

bool FileHelper::lineStartsWith(const std::string& s, const std::string& needle) {
    return needle.length() <= s.length()
           && std::equal(needle.begin(), needle.end(), s.begin());
}

