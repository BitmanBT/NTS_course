#include <iostream>
#include <bitset>

#include <bits.h>

int main()
{
    uint32_t x = 0b00011000;
    std::vector<uint64_t> to_invert1 = {27, 28};
    bits::inverter(&x, 32, to_invert1);
    std::cout << std::bitset<32>(x) << std::endl; // has to be 32 zeros

    uint8_t y = 0b00011000;
    std::vector<uint64_t> to_invert2 = {3, 4};
    bits::inverter(&y, 5, to_invert2);
    std::cout << std::bitset<8>(y) << std::endl; // has to be 8 zeros
}