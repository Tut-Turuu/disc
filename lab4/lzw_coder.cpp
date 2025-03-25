#include <fstream>
#include <map>
#include <unordered_map>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>


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




void encode(std::string input_fn, std::string output_fn) {
    std::ifstream in;
    std::ofstream out;
    in.open(input_fn);
    out.open(output_fn);

    std::map<std::string, std::string> code_table; // <string, code>
    
    // start code table
    for (int i = 0; i < 32; ++i) {

        std::stringstream tmp;
        tmp << alphabet[i];
        code_table.insert({tmp.str(), std::to_string(i)});

        tmp.clear();
    }

    // for (auto i : code_table) {
    //     std::cout << i.first << ": " << i.second << '\n';
    // }

    // resuming the table 
}



int main() {
    // analyze("text.txt");
    encode("text.txt", "out.txt");
}