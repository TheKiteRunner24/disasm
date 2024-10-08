#include "config.h"
#include "isa_parser.h"
#include "disasm.h"
#include <iostream>
#include <string>
#include <fstream>

#ifdef FILE_INPUT
int main(int argc, char* argv[]) {
    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error opening input file!" << std::endl;
        return 1;
    }
    std::ofstream outfile(argv[2]);
    if (!outfile) {
        std::cerr << "Error opening output file!" << std::endl;
        return 1;
    }

    isa_parser_t isa_parser(DEFAULT_ISA, DEFAULT_PRIV);
    disassembler_t* disassembler = new disassembler_t(&isa_parser);

    std::string s;
    while (std::getline(infile, s)) {
        char* end;
        uint64_t insn;
        if (strncmp(s.c_str(), "0x", 2) == 0) {
            // Hexadecimal input
            insn = strtoull(s.c_str(), &end, 16);
        } else {
            // Decimal input
            insn = strtoull(s.c_str(), &end, 10);
        }
    
        std::string disasm  = disassembler->disassemble(insn);

        outfile << disasm << std::endl;
    }
    delete disassembler;
    infile.close();
    outfile.close();
    return 0;
}
#else
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "instruction" << std::endl;
        return 1;
    }
    char* end;
    uint64_t insn;
    if (strncmp(argv[1], "0x", 2) == 0) {
        // Hexadecimal input
        insn = strtoull(argv[1], &end, 16);
    } else {
        // Decimal input
        insn = strtoull(argv[1], &end, 10);
    }

    isa_parser_t isa_parser(DEFAULT_ISA, DEFAULT_PRIV);
    disassembler_t* disassembler = new disassembler_t(&isa_parser);

    std::string disasm = disassembler->disassemble(insn);

    std::cout << disasm << std::endl;

    delete disassembler;
    return 0;
}
#endif