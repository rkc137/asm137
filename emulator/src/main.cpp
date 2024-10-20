#include <iostream>
#include <fstream>
#include <array>
#include <cstdint>

using byte = uint8_t;

/*
movi    0iii iiii
add     1000 rrrr
sub     1001 rrrr
mul     1010 rrrr
div     1011 rrrr
in      1100 00rr
out     1100 01rr
*/

int main(int argc, char *argv[])
{
    std::array<byte, 4> registers;//a b c d
    for(int i = 0; i < registers.size(); i++)
        registers[i] = i;

    std::ifstream input(std::string(argv[1]), std::ios_base::binary);
    for(byte command; input.get(reinterpret_cast<char&>(command));)
    {
        if(command < 0x80)
            registers.back() = command;
        else if(command >= 0xC0)
        {            
            byte &reg = registers[command & 3];//last 2 bits
            if(command >= 0xC4)
                std::cout << static_cast<unsigned>(reg);//out
            else if(command < 0xC4)
            {
                unsigned in;
                std::cin >> in;
                reg = in & 0xFF;
            }
        }
        else
        {
            byte &dst = registers[(command >> 2) & 3];//pre last 2 bits
            byte &src = registers[command & 3];//last 2 bits

            switch((command >> 4) & 3) 
            {
            case 0://add
                dst += src;
                break;
            case 1://sub
                dst -= src;
                break;
            case 2://mul
                dst *= src;
                break;
            case 3://div
                dst /= src;
                break;
            default:
                std::terminate();
                break;
            }
        }
    }   
    return 0;
}

