#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// WINDOWS
#include <stdio.h>

using namespace std;


const string DATA_FILE = "data";

bool startsWith(string text, string beginning){
    if(text.size() > beginning.size()){
        bool good = true;
        for(int i = 0; i < beginning.size(); i++){
            if(beginning.at(i) != text.at(i)){
                good = false;
            }
        }
        return good;
    } else {
        return false;
    }
}

string trimBack(string text){
    if(text.size() > 0){
        if(text.at(text.size()-1) == ' ' || text.at(text.size()-1) == '\t' || text.at(text.size()-1) == '\n'){
            return trimBack(text.substr(0, text.size()-1));
        }
    } 
    return text;
}

string trimFront(string text){
    if(text.size() > 0){
        if(text.at(0) == ' ' || text.at(0) == '\t' || text.at(0) == '\n'){
            return trimFront(text.substr(1));
        }
    }
    return text;
}

string trim(string text){
    return trimBack(trimFront(text));
}

string readData(string key){
    ifstream inFile;
    inFile.open(DATA_FILE);

    string value = "NULL";
    if(inFile.good()){
        string line;
        while(!inFile.eof()){
            getline(inFile, line);
            if(line.size() > 0){
                size_t equalsPosition = line.find_first_of('=');
                if(line.substr(0, equalsPosition).compare(key) == 0){
                    value = line.substr(equalsPosition+1);
                    break;
                }
            }
        }
    }

    inFile.close();

    return value;
}

bool deleteData(string key){
    vector<string>* readValues = new vector<string>();

    ifstream inFile;
    inFile.open(DATA_FILE);

    bool deleted = false;

    if(inFile.good()){
        string line;
        while(!inFile.eof()){
            getline(inFile, line);
            if(line.size() > 0)
                readValues->push_back(line);
        }

        inFile.close();

        ofstream outFile;
        outFile.open(DATA_FILE, ofstream::out);

        if(outFile.good()){

            for(int i = 0; i < readValues->size(); i++){
                size_t equalsPosition = readValues->at(i).find_first_of('=');
                if(readValues->at(i).substr(0, equalsPosition).compare(key) == 0){
                    deleted = true;
                } else {
                    outFile << readValues->at(i) << endl;
                }
            }
        }

        outFile.close();

    } else {
        inFile.close();
    }

    delete readValues;

    return deleted;
}

void writeData(string key, string value){
    vector<string>* readValues = new vector<string>();

    ifstream inFile;
    inFile.open(DATA_FILE);

    if(inFile.good()){
        string line;
        while(!inFile.eof()){
            getline(inFile, line);
            if(line.size() > 0)
                readValues->push_back(line);
        }

        inFile.close();

        ofstream outFile;
        outFile.open(DATA_FILE, ofstream::out);

        if(outFile.good()){

            bool written = false;
            for(int i = 0; i < readValues->size(); i++){
                size_t equalsPosition = readValues->at(i).find_first_of('=');
                if(readValues->at(i).substr(0, equalsPosition).compare(key) == 0){
                    outFile << key << '=' << value << endl;
                    written = true;
                } else {
                    outFile << readValues->at(i) << endl;
                }
            }

            if(!written){
                outFile << key << '=' << value << endl;
            }
        }

        outFile.close();

    } else {
        inFile.close();
    }

    delete readValues;

}

vector<string> cmd(string command){
    // UNIX
    /*char buffer[128];
    vector<string> values;

    FILE* pipe = popen(command.c_str(), "r");

    if(pipe){
        while(!feof(pipe)){
            if(fgets(buffer, 128, pipe) != NULL){
                string feedback = buffer;
                if(feedback.at(feedback.size()-1) == '\n'){
                    feedback = feedback.substr(0, feedback.size()-1);
                }
                values.push_back(feedback);
            }
        }
    }

    pclose(pipe);

    return values;*/

    // WINDOWS
    char buffer[128];
    vector<string> values;
    
    FILE* pipe = 
        #ifdef _WIN32
            _popen(command.c_str(), "r");
        #else
            popen(command.c_str(), "r");
        #endif

    if(pipe){
        while(!feof(pipe)){
            if(fgets(buffer, 128, pipe) != NULL){
                string feedback = buffer;
                if(feedback.at(feedback.size()-1) == '\n'){
                    feedback = feedback.substr(0, feedback.size()-1);
                }
                values.push_back(feedback);
            }
        }
    }

    #ifdef _WIN32
        _pclose(pipe);
    #else
        pclose(pipe);
    #endif

    return values;
}

#endif