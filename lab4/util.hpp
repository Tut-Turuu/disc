#include <string>


void fill_zeros(std::string& str, int len) {

    // if (str.size() > len) {
    //     std::cout << "extreme fuck\n";
    //     std::cout.flush();
    // }
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

std::string bin(int n) {
    std::string str;
    while (n > 0) {
        str = std::to_string(n % 2) + str;
        n /= 2;
    }
    return str;
}

// void bin(std::string& str, int n) {
//     while (n > 0) {
//         str = std::to_string(n % 2) + str;
//         n /= 2;
//     }
//     return str;
// }


void print(const std::map<std::string, std::string>& map) {
    for (auto& i: map) {
        std::cout << i.first << ": " << i.second << '\n';
    }
}

void print(const std::unordered_map<std::string, std::string>& map) {
    for (auto& i: map) {
        std::cout << i.first << ": " << i.second << '\n';
    }
}