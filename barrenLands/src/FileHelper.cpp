//
// Created by natshez on 24/11/2017.
//
#include <include/NoiseManager.hpp>
#include "FileHelper.hpp"

std::string FileHelper::error_message = "Impossible to load file !";

/**
 * getContent
 * @param path  &std::string path of the file to open
 * @return std::vector<std::string> vector with all the strings separated by the char ';' in the file
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
 * @param value &std::string  the new content
 * @param  choosenSave  int the number of the line to update in the file
 * \exception <std::runtime_error> { cannot open the given file }
 * This function erase the old content !
 */
void FileHelper::updateFile(const std::vector<std::string>  &content, const std::string &path, const int & choosenSave){
    std::ifstream oldFile(path, std::ios::in);  //open old file
    if(!oldFile){
        throw std::runtime_error(FileHelper::error_message);
    }
    std::ofstream newFile("test", std::ios::out);  //create new file
    if(!newFile){
        throw std::runtime_error(FileHelper::error_message);
    }

    std::string line, newLine = "";

    const char* const delim = ";";
    std::ostringstream imploded; //parse the vector into a string with the delimiter ;
    std::copy(content.begin(), content.end(),
              std::ostream_iterator<std::string>(imploded, delim));
    newLine = imploded.str();

    unsigned int numberOfLines = 0, found = false;
    while (std::getline(oldFile, line)){
        if(numberOfLines == choosenSave){// when we found the line to update
            newFile << newLine <<'\n'; //we replace the content of the line
            found = true;
        }
        else {
            newFile << line <<'\n'; //meanwhile, we copy the old file's content into the new file
        }
        numberOfLines++;
    }
    if (!found){ //if the line to update was not found
        newFile << newLine <<'\n'; //we add the new content at the end of the file
    }
    oldFile.close();
    newFile.close();
    std::remove(path.c_str()); //we remove the old file
    std::rename("test", path.c_str()); //and replace it by the new one
}
/**
 * getContentOfLine()
 * return a vector of string exploded with the delimiter ;
 * @param firstWord of the line to return (it takes the first occurence of the word in the file)
 * @param filePath
 * @return std::vector<std::string> the content of the line if found, empty vector if not found
 * \exception <std::runtime_error> { cannot open the given file }
 */
std::vector<std::string>  FileHelper::getContentOfLine(const std::string& firstWord, const std::string & filePath){
    std::ifstream file(filePath.c_str(), std::ios::in);  //open file
    std::string line, token;
    std::vector<std::string> separatedValues;
    if (!file){
        throw std::runtime_error(FileHelper::error_message);
    }

    unsigned int currentLine = 0;
    int found = false;
    while ( !found && std::getline(file, line)) {
        std::istringstream ss(line);
        std::getline(ss, token, ';');
        if (lineStartsWith(token,firstWord) != false) {
            std::cout << "found: " << firstWord << "line: " << currentLine << std::endl;
            found = true;
        }
        currentLine++;
    }
    file.close();

    if(found){//parse the string into the vector using ; delimiter
        std::istringstream ss(line);
        while(std::getline(ss, token, ';')) {
            separatedValues.push_back(token);
        }
    }
    return separatedValues;
}
/**
 * lineStartsWith()
 * check if a given string begins with a given word
 * @param s std::string the string to check
 * @param needle std::string    the word to compare with
 * @return bool, true if s begins with needle
 */
bool FileHelper::lineStartsWith(const std::string& s, const std::string& needle) {
    return needle.length() <= s.length()
           && std::equal(needle.begin(), needle.end(), s.begin());
}
/**
 * getAllLineFirstWord()
 * return all the first words of all lines in the given file
 * @param filePath
 * @return std::vector<std::string>
 * \exception <std::runtime_error> { cannot open the given file }
 */
std::vector<std::string> FileHelper::getAllLineFirstWord(const std::string & filePath){
    std::ifstream file(filePath.c_str(), std::ios::in);  //open file
    std::string line, token;
    std::vector<std::string> separatedValues;
    if (!file){
        throw std::runtime_error(FileHelper::error_message);
    }
    while ( std::getline(file, line)) {
        std::istringstream ss(line);
        std::getline(ss, token, ';');
        separatedValues.push_back(token);
    }
    file.close();

    return separatedValues;
}

