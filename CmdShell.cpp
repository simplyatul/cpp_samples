/*
 * run: g++ CmdShell.cpp
 * This program opens FIFO_FILE/named pipe file
 * And it reads on it
 * 
 * When external application writes in the  FIFO_FILE, the 
 * program reads the line and tokanize it using space as delim
 * 
 * Tokens can be then trated as instruction and program can
 * execute them as the the business logic
 * 
 */
#include <iostream>
#include <string>
#include "common.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <sstream>

#define FIFO_FILE   "/tmp/cmdshell"

class CmdShell {
private:
    CmdShell() {

    }
    int fifoExists() {
        struct stat statStruct;
        int result;
        return stat(FIFO_FILE, &statStruct);
    }
public:
    static CmdShell& getInst() {
        static CmdShell _instance;
        return _instance;
    }

    void initCmdShell() {
        if (0 == fifoExists()) {
            std::cout << "Fifo exists" << std::endl;

        } else {
            if ((mkfifo(FIFO_FILE, 0777)) != 0) {
                std::cout << "mkfifo fails. errno=" << errno << std::endl;
                return;
            }
            std::cout << "Fifo created" << std::endl;
        }
    }

    void executeCmd(std::vector<std::string> tokens) {
        if(tokens.empty()) {
            cout << "Empty Tokens" << endl;
            return;
        }
        if(tokens.size() >= 2 && tokens[0]=="list" && tokens[1]=="links") {
            cout << "Executing: list links" << endl;
        }
    }
    
    void runCmd() {
        std::ifstream rpipe;
        std::string line;
        while (true) {
            rpipe.open(FIFO_FILE, ios::in);
            getline(rpipe, line);
            std::cout << line << std::endl;
            std::vector < std::string > tokens;
            std::stringstream ss(line);
            std::string buf;
            while (ss >> buf) {
                tokens.push_back(buf);
            }
            std::cout << "Total Tokens: " << tokens.size() << endl;
            for (auto t : tokens) {
                std::cout << t << std::endl;
            }
            executeCmd(tokens);
            rpipe.close();
        }
    }
};

int main() {
    CmdShell::getInst().initCmdShell();
    CmdShell::getInst().runCmd();
    return 0;
}
