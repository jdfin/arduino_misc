#pragma once

#include <Arduino.h>


// extract, extract8:
// shift value down by 'lsb', then mask according to 'num_bits'

// insert, insert8:
//   input/output value 'reg'
//     clear 'num_bits' at position 'lsb'
//     or-in bits in 'val', masked and shifted up to 'lsb'


inline uint32_t extract(uint32_t value, int num_bits, int lsb)
{
    uint32_t mask = (1 << num_bits) - 1; // e.g. num_bits=5 -> 0x0000001f
    return (value >> lsb) & mask;
}


inline void insert(uint32_t& reg, uint32_t val, int num_bits, int lsb)
{
    uint32_t mask = (1 << num_bits) - 1;
    reg = (reg & ~(mask << lsb)) | ((val & mask) << lsb);
}


inline uint8_t extract8(uint8_t value, int num_bits, int lsb)
{
    uint8_t mask = (1 << num_bits) - 1;
    return (value >> lsb) & mask;
}


inline void insert8(uint8_t& reg, uint8_t val, int num_bits, int lsb)
{
    uint8_t mask = (1 << num_bits) - 1;
    reg = (reg & ~(mask << lsb)) | ((val & mask) << lsb);
}
