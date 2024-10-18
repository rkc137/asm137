#include <iostream>
#include <map>
#include <cstdint>

using byte = uint8_t;

/*
movi    0111 1111
add     1000 rrrr
sub     1001 rrrr
mul     1010 rrrr
div     1011 rrrr
in      1100 00rr
out     1100 01rr
*/

byte ucDataBlock[] = {
	// Offset 0x00000000 to 0x0000000B
	0xC4, 0xC5, 0xC6, 0xC7, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7
};

int main(int argc, char *argv[])
{
    byte a, b, c, d;
    std::map<byte, byte*> registers = {
        {0, &a},
        {1, &b},
        {2, &c},
        {3, &d}
    };
    for(auto &[k, v] : registers)
        *v = k + 10;
    
    for(auto &command : ucDataBlock)
    {
        if(command < 0x80)
            d = command;
        else if(command >= 0xC0)
        {
            printf("reg №%d: ", command & 3);
            
            byte &reg = *registers[command & 3];
            if(command >= 0xC4)
                printf("-%d-\n", reg);//out
            else if(command < 0xC4)
            {
                byte in;
                std::cin >> *(unsigned*)(&in);
                reg = in;
                // std::cin >> *(unsigned*)(&reg);// не работает
            }
        }
    }   
    return 0;
}

