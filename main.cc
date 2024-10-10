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
        std::cerr << "Error opening file!" << std::endl;
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

        if (disasm == "unknown") {
            printf("invalid instruction\n");
        } else {
            printf("%s\n", disasm.c_str());
        }
    }
    delete disassembler;
    return 0;
}
#else
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <instruction_in_hex>" << std::endl;
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

    if (disasm == "unknown") {
        std::cout << "Invalid instruction" << std::endl;
    } else {
        std::cout << disasm << std::endl;
    }

    delete disassembler;
    return 0;
}
#endif