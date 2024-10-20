#include <iostream>
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <ranges>
#include <vector>
#include <map>

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
    std::map<std::string, byte> instructions = {
        {"movi", 0x0},
        {"add", 0x80},
        {"sub", 0x90},
        {"mul", 0xA0},
        {"div", 0xB0},
        {"in", 0xC0},
        {"out", 0xC4}
    };

    std::map<std::string, byte> reg_names;
    for(int i = 0; i < 4; i++)
        reg_names[{char('a' + i)}] = byte(i);

    std::ifstream input{std::string(argv[1])};
    if(!input)
    {
        std::cerr << "file error" << std::endl;
        return 1;
    }

    std::vector<byte> commands;
    for(std::string line; std::getline(input, line);)
    {
        for(auto &c : line)
            c = std::tolower(c);
        
        auto words_view = line | std::views::split(' ');

        auto wit = words_view.begin();
        std::string cmd{(*wit).begin(), (*wit).end()};
        if(cmd[0] == '#')
            continue;

        wit++;
        switch(std::ranges::distance(words_view))
        {
        case 2:
        {
            auto dst = std::string{(*wit).begin(), (*wit).end()};
            if(cmd == "movi")
            {
                commands.push_back(std::stoi(dst));
                break;
            }
            commands.push_back(
                instructions[cmd] | reg_names[dst]
            );
            break;
        }
        case 3:
        {
            auto dst = std::string{(*wit).begin(), (*wit).end()};
            wit++;
            auto src = std::string{(*wit).begin(), (*wit).end()};
            commands.push_back(
                instructions[cmd] | 
                reg_names[dst] |
                reg_names[src]
            );
            break;
        }
        default:
            std::cerr << "error in " << line;
            return 1;
        }
    }
    std::ofstream output("a.exc", std::ios_base::binary);
    output.write((char*)(commands.data()), commands.size());
    return 0;
}