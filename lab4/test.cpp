#include <string>
#include <iostream>
#include <map>
#include <vector>

void fill_zeros(std::string& str, int len) {
    str.reserve(len);
    int delta = len - str.size();
    str.resize(len);
    for (int i = len - 1; i > delta-1; --i) {
        str[i] = str[i - delta];
    }
    for (int i = 0; i < delta; ++i) {
        str[i] = '0';
    }
}

int main() {

    std::vector<int> vec;

    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();

}