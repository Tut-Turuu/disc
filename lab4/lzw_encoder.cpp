#include <fstream>
#include <map>
#include <unordered_map>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <unistd.h>
#include "util.hpp"

char alphabet[] = "\n ',.;abcdefghijklmnopqrstuvwxyz";

void analyze(std::string filename) {
    std::ifstream in;

    in.open(filename);

    std::map<short, int> dict;

    char prev;
    char cur;
    short tmp1;
    short tmp2;

    in.read(&prev, 1);
    while (!in.eof()) {
        in.read(&cur, 1);

        ((char*)&tmp1)[0] = prev;
        ((char*)&tmp1)[1] = 0;

        ((char*)&tmp2)[0] = prev;
        ((char*)&tmp2)[1] = cur;

        if (dict.find(tmp1) != dict.end()) {
            ++dict[tmp1];
        } else {
            dict.insert({tmp1, 1});
        }

        if (dict.find(tmp2) != dict.end()) {
            ++dict[tmp2];
        } else {
            dict.insert({tmp2, 1});
        }
        prev = cur;
    }
    in.close();

    for (auto i : dict) {
        std::cout << (int)((char*)&i.first)[0] << ' ' << (int)((char*)&i.first)[1] << ": " << i.second << '\n';
    }

}



bool is_bin(const std::string& str) {
    for (auto i: str) {
        if (i != '0' && i != '1') return false;
    }
    return true;
}



void encode(std::string input_fn, std::string output_fn) {
    std::ifstream in;
    std::ofstream out;
    in.open(input_fn);
    out.open(output_fn);

    std::map<std::string, std::string> code_table; // <string of letters, binary code>
    
    // start code table
    for (int i = 0; i < 32; ++i) {

        std::stringstream tmp;
        tmp << alphabet[i];
        std::string code(bin(i));
        fill_zeros(code, 5);
        code_table.insert({tmp.str(), code});
        code.clear();
        tmp.clear();
    }
    // print(code_table);
    // exit(0);

    int border = 32;
    int code_sz = 5;

    // for (auto i : code_table) {
    //     std::cout << i.first << ": " << i.second << '\n';
    // }

    // resuming code table and start of encoding

    char tmp;
    std::string curr;
    char phantom = 0;

    while (1) {
        if (phantom != 0) {
            curr += phantom;
            phantom = 0;
        } else {
            in.read(&tmp, 1);
            if (in.eof()) break;
            curr += tmp;
        }
        if (code_table.find(curr) == code_table.end()) {
            phantom = curr[curr.size() - 1];
            curr.pop_back();

            out << code_table[curr];

            if (code_table.size() == border) {
    
                border *= 2;
                ++code_sz;
                for (auto& i: code_table) {
                    fill_zeros(std::get<1>(i), code_sz);
                }

            }
            
            curr += tmp;
            std::string code(bin(code_table.size()));
            fill_zeros(code, code_sz);
            code_table.insert({curr, code});

            curr.clear();

        }

    }

}



int main() {
    // analyze("text.txt");
    encode("text.txt", "out.txt");
}