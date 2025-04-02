#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <iostream>
#include <unistd.h>
#include "util.hpp"


char alphabet[] = "\n ',.;abcdefghijklmnopqrstuvwxyz";


void decode(std::string input_fn, std::string output_fn) {

    char buf[1024];

    std::ifstream in;
    std::ofstream out;
    in.open(input_fn);
    out.open(output_fn);

    std::map<std::string, std::string> rev_code_table; // <binary code, string of letters>

    for (int i = 0; i < 32; ++i) {

        std::stringstream tmp;
        tmp << alphabet[i];
        std::string code(bin(i));
        fill_zeros(code, 5);
        rev_code_table.insert({code, tmp.str()});
        code.clear();
        tmp.clear();
    }
    int i = 32;
    int border = 32;
    int code_sz = 5;

    std::string curr;
    std::string code;
    std::string prev_code;
    std::string new_str;
    std::string new_code;

    curr.reserve(50);
    code.reserve(50);
    new_code.reserve(50);
    new_str.reserve(50);
    prev_code.reserve(50);

    while (1) {

        in.read(buf, code_sz);
        if (in.eof()) break;
        code.assign(buf, code_sz);

        if (rev_code_table.find(code) != rev_code_table.end()) {
            curr = rev_code_table[code];
            prev_code = bin(i-1);
            fill_zeros(prev_code, code_sz);
            std::string* prev_str = &rev_code_table[prev_code];
            if ((*prev_str)[prev_str->size() - 1] == '@') {
                (*prev_str)[prev_str->size() - 1] = curr[0];
            }
            out << curr;

            if (i == border) {

    
                border *= 2;
                ++code_sz;
    
                std::map<std::string, std::string> new_code_table;
                for (auto& i: rev_code_table) {
                    std::string code(std::move(i.first));
                    std::string str(std::move(i.second));
    
                    fill_zeros(code, code_sz);
                    new_code_table.insert({std::move(code), std::move(str)});
                }
                rev_code_table = new_code_table;
                new_code_table.clear();
    
    
            }
            new_str = curr;
            new_str += '@';

            new_code = bin(i);
            fill_zeros(new_code, code_sz);
            rev_code_table.insert({new_code, new_str});
            ++i;

        } else {
            std::cout << "code: " << code << '\n';
            print(rev_code_table);
            out.flush();
            exit(-1);
        }
        curr.clear();
        code.clear();
        new_code.clear();
        new_str.clear();
        prev_code.clear();



    }
}



int main() {
    decode("out.txt", "decoded.txt");
}