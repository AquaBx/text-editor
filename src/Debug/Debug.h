//
// Created by tomch on 15/10/2024.
//

#pragma once

#include <string>
#include <fstream>
#include <ctime>

class Debug
{
public :
    void static print(const std::string& texte)
    {
        std::ofstream myfile;

        myfile.open("./debug/debug.txt", std::ios_base::app);
        const time_t result = time(nullptr);
        myfile << result;
        myfile << " : ";
        myfile << texte;
        myfile << "\n";
        myfile.close();
    }
};


