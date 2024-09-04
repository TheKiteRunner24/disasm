# A disassembler separated from Spike
Spike: https://github.com/riscv-software-src/riscv-isa-sim
## Get Started
```
cd disasm
mkdir build
cd build
cmake ..
make -j

./disasm ../insn.txt
```
## How to set ISA
change `DEFAULT_ISA` in `config.h`
```
#define DEFAULT_ISA "RV64IMAFDC"
```
