#include <bits.h>

#include <stdexcept>
#include <cmath>

namespace bits
{
    void inverter(void* ptr, uint64_t len, const std::vector<uint64_t>& to_invert)
    {
        if (!ptr)
            throw std::invalid_argument("Pointer to memory block is nullptr!");
        if (len == 0)
            throw std::invalid_argument("Length of memory block equals zero!");
        
        char* charptr = (char*) ptr;
        
        // Total number of bytes we work with (including incomplete)
        int numberOfBytes = std::ceil(len / 8.0);

        for (const auto& invert : to_invert)
        {
            if (invert >= len)
                throw std::invalid_argument("Number of bit to change is too big!");
            
            int byteNum = invert / 8;
            uint8_t mask = 1u << (7 - invert % 8);
            charptr[numberOfBytes-1-byteNum] ^= mask;
        }
    }
} // namespace bits