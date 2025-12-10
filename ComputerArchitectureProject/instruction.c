#include "instruction.h"

DecodedInstruction instruction_decode(EncodedInstruction ins) {
    DecodedInstruction result;
    result.immediate = ins & 0xfff;
    ins >>= 12;
    result.rt = ins & 0xf;
    ins >>= 4;
    result.rs = ins & 0xf;
    ins >>= 4;
    result.rd = ins & 0xf;
    ins >>= 4;
    result.opcode = ins;
    return result;
}
