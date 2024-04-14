#include <vector>
#include <cstdint>

namespace bits
{
    /**
     * Iverts chosen bytes.
     * 
     * @param ptr Pointer to the memory block.
     * @param len Length of the memory block.
     * @param to_invert Numbers of bits to invert (from 0 to len-1).
    */
    void inverter(void* ptr, uint64_t len, const std::vector<uint64_t>& to_invert);
} // namespace bits