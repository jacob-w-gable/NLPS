#ifndef NLPS_H
#define NLPS_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <vector>

#include "computer.h"
#include "person.h"
#include "helper_functions.h"

using namespace std;

class NLPS {
    private:
        string directory;
        vector<string>* files;
        vector<Person>* persons;
        vector<Computer>* computers;

        const char FILETYPE_LOWER[6] = ".nlps";
        const char FILETYPE_UPPER[6] = ".NLPS";

        void exploreDirectory(string directory){
            for(const auto& file : std::filesystem::directory_iterator(directory)){
                string path = file.path().string();
                if(file.is_directory()){
                    exploreDirectory(path);
                } else {
                    if(path.substr(path.size()-5).compare(FILETYPE_LOWER) == 0 || path.substr(path.size()-5).compare(FILETYPE_UPPER) == 0){
                        files->push_back(path);
                    }
                }                
            }
        }

        // TODO: 
        void processBlock(string block){
            cout << "{" << block << "}" << endl;
        }

        void readFile(string filename){
            ifstream inFile;
            inFile.open(filename);

            if(inFile.good()){

                // construct block segments of conversations
                string block = "";
                while(!inFile.eof()){

                    string line;
                    getline(inFile, line);
                    string trimmedLine = trim(line);

                    if(trimmedLine.size() > 0){
                        if(line.at(0) != ' ' && line.at(0) != '\t'){
                            if(block.size() > 0){
                                processBlock(block);
                            }
                            block = line;
                        } else {
                            block = block + '\n' + line;
                        }
                    }

                }

                if(block.size() > 0 && block.at(0) != ' ' && block.at(0) != '\t')
                    processBlock(block);
            }

            inFile.close();
        }

    public:
        NLPS(string directory){
            this->directory = directory;
            files = new vector<string>();

            exploreDirectory(directory);

            for(string file: *(files)){
                readFile(file);
            }
        }

        ~NLPS(){
            delete files;
        }
};


#endif