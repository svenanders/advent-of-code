#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <map>
#include <unordered_map>
#include "../include/split.h"
#include "../include/parser.h"

using namespace std;

namespace day7b {
    struct Bag {
        Bag():nbs(0){}
        int nbs;
        std::string bagColor;
    };

    int num_bags(const Bag& key);

    std::map<std::string, std::vector<Bag>> m_Tree2;
    struct tree {
        string value;
        std::vector<tree> children;
    };

    void parse_input(const string &path) {
        parse_input_by_line(path, [&](const auto &line) {
            vector<string> bags;
            split(line, ' ', bags);

            for (int i = 4; i < bags.size(); i = i + 4) {
                Bag bag;
                bag.bagColor = bags[i + 1] + " " + bags[i + 2];
                bag.nbs = atoi(bags[i].c_str());
                m_Tree2[bags[0] + ' ' + bags[1]].push_back(bag);

            }
        });
    }

    int num_bags(const Bag& key) {
        int nb = 0;
        for (const auto& it : m_Tree2[key.bagColor]) {
            if (it.bagColor == "other bags.")
                return 0;
            nb += it.nbs + it.nbs * num_bags(it);
            //cout << key.bagColor << "  :" << nb << endl;
        }
        return nb;
    }

    int solve() {
        int result = 0;
        for (const auto& it : m_Tree2["shiny gold"]) {
            result += it.nbs + it.nbs * num_bags(it);
        }
        return result;
    }

}
