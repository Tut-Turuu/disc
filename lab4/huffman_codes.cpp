#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>


struct Node {
    char c;
    int n;
    Node* right;
    Node* left;
};

void tree_traversal(Node* tree) {
    if (tree->right != nullptr) {
        tree_traversal(tree->right);
    }
    std::cout << tree->n << ' ';
    if (tree->left != nullptr) {
        tree_traversal(tree->left);
    }
}

void form_codes(std::map<char, std::string>& codes, Node* tree, std::string& code) {
    if (tree->right != nullptr) {
        code += '1';
        form_codes(codes, tree->right, code);
        code.pop_back();
    }
    if (tree->left != nullptr) {
        code += '0';
        form_codes(codes, tree->left, code);
        code.pop_back();
    }
    if ((tree->left == nullptr) && (tree->right == nullptr)) {
        codes.insert({tree->c, code});
    }

}

int find_min(std::vector<std::pair<int, Node*>> vec) {
    int min = 0x7fffffff;
    int res;
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i].first < min) {
            min = vec[i].first;
            res = i;
        }
    }
    return res;
}



int main() {

    std::string filename("text.txt");
    std::ifstream in;

    in.open(filename);

    std::map<char, int> dict;

    char cur;

    while (1) {

        in.read(&cur, 1);
        if (in.eof()) break;

        if (dict.find(cur) != dict.end()) {
            ++dict[cur];
        } else {
            dict.insert({cur, 1});
        }


    }
    in.close();


    std::cout << "chars frequency:\n";
    int chars_count = 0;
    for (auto i : dict) {
        std::cout << i.first << ": " << i.second << '\n';
        chars_count += i.second;
    }

    std::vector<std::pair<int, Node*>> nodes;
    Node* node;

    for (auto i : dict) {
        node = new Node;
        node->left = nullptr;
        node->right = nullptr;
        node->c = i.first;
        node->n = i.second;
        nodes.push_back({i.second, node});
    }
    // std::cout << nodes.size() << '\n';

    Node* new_node;

    int min;
 
    while (nodes.size() != 1) {
        new_node = new Node;
        new_node->n = 0;

        min = find_min(nodes);

        new_node->n += nodes[min].first;
        new_node->right = nodes[min].second;
        nodes.erase(nodes.begin() + min);

        min = find_min(nodes);

        new_node->left = nodes[min].second;
        new_node->n += nodes[min].first;
        nodes.erase(nodes.begin() + min);
        
        new_node->c = 0;
        nodes.push_back({new_node->n, new_node});

    }

    // for (auto i: nodes) {
    //     std::cout << i.first << '\n';
    // }


    // std::vector<std::pair<char, std::string>> codes;
    std::map<char, std::string> codes;


    Node* tree;
    // std::cout << nodes.size();
    for (auto i: nodes) {
        tree = i.second;
    }
    // tree_traversal(tree);

    std::string code;
    form_codes(codes, tree, code);

    // std::cout << codes.size();

    std::cout << "Huffman codes:\n";
    for (auto i: codes) {
        std::cout << (int)i.first << ": " << i.second << '\n';
    }
    

    int encoded_size = 0;
    for (auto i: dict) {
        encoded_size += i.second * codes[i.first].size();
    }

    std::cout << "encoded is " << encoded_size << " bits\n";
    std::cout << "chars count is " << chars_count << '\n';


    double shannon = 0;

    for (auto i: dict) {
        shannon -= (((double)i.second)/((double)chars_count)) * log(((double)i.second)/((double)chars_count)) / log(2);
    }

    std::cout << "shannon is " << shannon << '\n';


}