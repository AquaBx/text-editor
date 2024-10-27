//
// Created by tomch on 15/10/2024.
//

#ifndef TEXTEDITOR_DEBUG_H
#define TEXTEDITOR_DEBUG_H


#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

class Debug {
public :
    void static print(const std::string& texte){
        std::ofstream myfile;

        myfile.open("./debug/debug.txt", std::ios_base::app);
        time_t result = time(NULL);
        myfile << result;
        myfile << " : ";
        myfile << texte;
        myfile << "\n";
        myfile.close();
    }
};


#endif //TEXTEDITOR_DEBUG_H
