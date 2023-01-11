#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>

//Those define are for the working directory where main.cpp is stored
//So 'files' dir is located in the same folder with main.cpp
#define FILE_IN "files/in.txt"
#define FILE_OUT "files/out.txt"

#define CHECK_BIT(var, pos) ((var) & (1<<(pos)))

const std::map<std::string, char> CMD_TABLE{
        std::make_pair("XZ", 0b10101010),
        std::make_pair("YZ", 0b10101000),
        std::make_pair("X++", 0b01111110),
        std::make_pair("Y++", 0b11011100),
        std::make_pair("X--", 0b00111010),
        std::make_pair("Y--", 0b11001000),
        std::make_pair("ADD X", 0b00001010),
        std::make_pair("ADD Y", 0b00001000),
        std::make_pair("SUB X", 0b01001110), // X = X - Y
        std::make_pair("SUB Y", 0b00011100), // Y = Y - X
        std::make_pair("OR X", 0b01010110),
        std::make_pair("OR Y", 0b01010100),
        std::make_pair("AND X", 0b00000010),
        std::make_pair("AND Y", 0b00000000),
        std::make_pair("IMP X", 0b00010110),
        std::make_pair("IMP Y", 0b01000100),
        std::make_pair("OUT X", 0b00101011),
        std::make_pair("OUT Y", 0b10001001)
};

int X = 0, Y = 0;

std::ifstream infile;
std::ofstream outfile;

int readCommands();

void pass_line(const std::string &line);

void ALU_pass(bool zx, bool nx, bool zy, bool ny, bool f, bool nf, bool sf, bool of);

char ALU_process(bool zx, bool nx, bool zy, bool ny, bool f);

int main() {
    infile.open(FILE_IN);
    outfile.open(FILE_OUT);
    readCommands();
}

int readCommands() {
    //read file
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            if (line.empty())
                continue;
            if (line.at(0) == '#')
                continue;
            pass_line(line);
        }
        infile.close();
        outfile.close();
    } else
        return -1;

    return 0;
}

void pass_line(const std::string &line) {
    try {
        //translate mnemonics into bits
        char flags = CMD_TABLE.at(line);
        //bits to booleans
        ALU_pass(CHECK_BIT(flags, 7),
                 CHECK_BIT(flags, 6),
                 CHECK_BIT(flags, 5),
                 CHECK_BIT(flags, 4),
                 CHECK_BIT(flags, 3),
                 CHECK_BIT(flags, 2),
                 CHECK_BIT(flags, 1),
                 CHECK_BIT(flags, 0));
    } catch (const std::exception &ex) {
        std::cout << "Unknown command: " << line << std::endl;
    }
}

void ALU_pass(bool zx, bool nx, bool zy, bool ny, bool f, bool nf, bool sf, bool of) {
    if (sf) {
        X = (unsigned char) ALU_process(zx, nx, zy, ny, f);
        if (nf) X = ~X;
        if (of) outfile << "X=" << X << std::endl;
    } else {
        Y = (unsigned char) ALU_process(zx, nx, zy, ny, f);
        if (nf) Y = ~Y;
        if (of) outfile << "Y=" << Y << std::endl;
    }
}

//count result
char ALU_process(bool zx, bool nx, bool zy, bool ny, bool f) {
    int X1 = 0, Y1 = 0;
    if (!zx) X1 = X;
    if (nx) X1 = ~X1;
    if (!zy) Y1 = Y;
    if (ny) Y1 = ~Y1;
    return char(f ? X1 + Y1 : X1 & Y1);
}






