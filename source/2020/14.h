//
// Created by Sven Anders Robbestad on 08/12/2020.
//

#include <numeric>
#include <unordered_set>
#include <regex>
#include <map>
#include <set>
#include <utility>
#include "../include/utils.h"
#include "../include/binaryToDecimal.h"

#ifndef AOC_14_H
#define AOC_14_H

namespace day14 {
using ull = unsigned long long;
    using Clock = std::chrono::high_resolution_clock;

    ull apply_mask(ull number, std::string mask) {
        auto dec = utils::toBinary(number);
        string rdec(dec.rbegin(), dec.rend());
        string rev_mask(mask.rbegin(), mask.rend());
        for (int n = 0; n < dec.length(); n++) {
            if (rev_mask[n] == 0) {
                rev_mask[n] = 0;
            } else if (rev_mask[n] == 'X') {
                auto num = rdec[n];
                rev_mask[n] = num;
            }
        }
        string temp_mask(rev_mask.rbegin(), rev_mask.rend());
        auto res_mask = regex_replace(temp_mask, (regex) "X", "0");
        return std::bitset<64>(res_mask).to_ullong();
    }

    ull apply_mask_bitshift(ull number, std::string mask) {
        ull zeros_mask = (1ULL << 37) - 1;
        ull ones_mask{};
        for (int i{}; i < mask.size(); ++i)
            if (mask[mask.size() - i - 1] == '1') ones_mask += 1ULL << i;
            else if (mask[mask.size() - i - 1] == '0') zeros_mask ^= 1ULL << i;

        return (number | ones_mask) & zeros_mask;
    }


    void part1(const string &label, const string &path) {
        auto t_read = Clock::now();
        std::string command, eq_string, value, mask;
        std::fstream f{path};
        std::map<ull, ull> memory, memory2;
        while (f >> command >> eq_string >> value) {
            if (command == "mask")
                mask = value;
            else {
                const auto memaddress{std::strtol(command.substr(4, command.size() - 5).c_str(), nullptr, 10)};
                memory[memaddress] = apply_mask(std::strtol(value.c_str(), nullptr, 10), mask);
            }
        }
        size_t read_time = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t_read).count();

        auto t1 = Clock::now();

        ull sum{};
        auto mem_sum = [](const auto &memory) {
            ull sum{};
            for (const auto &mem : memory)
                sum += mem.second;
            return sum;
        };

        sum = mem_sum(memory);

        auto t2 = Clock::now();
        size_t result_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        cout << label << ": "
             << sum
             << " (compute: "
             << result_time << " us)"
             << " (parse: "
             << read_time << " us)"
             << endl;
    }

}

#endif //AOC_14_H
