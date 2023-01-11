#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>

//Those define are for the working directory where main.cpp is stored
//So 'files' dir is located in the same folder with main.cpp
#define FILE_IN "files/fibonacci.txt"
#define FILE_OUT "files/out.txt"

#define PAIR(name, val) std::make_pair(name, (Flags) char(val)),
#define CHECK_BIT(var, pos) ((var) & (1<<(pos)))

struct Flags {

    bool zx : 1;
    bool nx : 1;
    bool zy : 1;
    bool ny : 1;
    bool f : 1;
    bool nf : 1;
    bool sf : 1;
    bool of : 1;

    explicit Flags(char flags) {
        zx = CHECK_BIT(flags, 7);
        nx = CHECK_BIT(flags, 6);
        zy = CHECK_BIT(flags, 5);
        ny = CHECK_BIT(flags, 4);
        f  = CHECK_BIT(flags, 3);
        nf = CHECK_BIT(flags, 2);
        sf = CHECK_BIT(flags, 1);
        of = CHECK_BIT(flags, 0);
    }

};

const std::map<std::string, Flags> CMD_TABLE{
        PAIR("XZ",     0b10101010) PAIR("YZ",     0b10101000)
        PAIR("X++",    0b01111110) PAIR("Y++",    0b11011100)
        PAIR("X--",    0b00111010) PAIR("Y--",    0b11001000)
        PAIR("OR X",   0b01010110) PAIR("OR Y",   0b01010100)
        PAIR("AND X",  0b00000010) PAIR("AND Y",  0b00000000)
        PAIR("ADD X",  0b00001010) PAIR("ADD Y",  0b00001000)
        PAIR("SUB X",  0b01001110) PAIR("SUB Y",  0b00011100) // X = X - Y; Y = Y - X
        PAIR("SUB XS", 0b00011110) PAIR("SUB YS", 0b01001100) // X = Y - X; Y = X - Y
        PAIR("IMP X",  0b00010110) PAIR("IMP Y",  0b01000100)
        PAIR("OUT X",  0b00101011) PAIR("OUT Y",  0b10001001)
};

int X = 0, Y = 0;

std::ifstream infile;
std::ofstream outfile;

int readCommands();

void pass_line(const std::string &line);

void ALU_pass(Flags flags);

char ALU_process(Flags flags);

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
        Flags flags = CMD_TABLE.at(line);
        //send to ALU
        ALU_pass(flags);
    } catch (const std::exception &ex) {
        std::cout << "Unknown command: " << line << std::endl;
    }
}

int result;

void ALU_pass(Flags flags) {
    result = (unsigned char) ALU_process(flags);
    if (flags.nf) result = ~result;

    if (flags.sf) {
        X = result;
        if (flags.of) outfile << "X=" << X << std::endl;
    } else {
        Y = result;
        if (flags.of) outfile << "Y=" << Y << std::endl;
    }
}

//count result
char ALU_process(Flags flags) {
    int X1 = 0, Y1 = 0;
    if (!flags.zx) X1 = X;
    if (flags.nx) X1 = ~X1;
    if (!flags.zy) Y1 = Y;
    if (flags.ny) Y1 = ~Y1;
    return char(flags.f ? X1 + Y1 : X1 & Y1);
}






