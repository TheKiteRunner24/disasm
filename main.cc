#include "config.h"
#include "isa_parser.h"
#include "disasm.h"
#include <iostream>
#include <string>
#include <fstream>

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
        uint64_t insn = strtoull(s.c_str(), &end, 16);
    
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
