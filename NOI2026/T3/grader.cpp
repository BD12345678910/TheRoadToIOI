#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "pudding.h"

#define VERBOSE if(verbose) std::cout

bool verbose = false;


namespace grader {
    int target_tastiness;
    int query_count = 0, total_puddings = 0;
    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
    double f(int x) {
        return pow(0.7, std::max(0, x - 4));
    }
    double g(int x) {
        if (x <= 35) {
            return 1.0;
        }
        if (x <= 75) {
            return 1.35 - 0.01 * x;
        }
        if (x <= 235) {
            return 0.2 + pow((235 - x) / 1000.0, 0.5);
        }
        if (x <= 3000) {
            return 0.2 * pow(2, (235 - x) / 1500.0);
        }
        return 0.0;
    }

    int query_tastiness(std::vector<int> puddings) {

        query_count++;
        if(query_count > 15) {
            std::cerr << "Too many queries." << std::endl;
            return -1;
        }
        if(puddings.empty()) {
            std::cerr << "Empty query." << std::endl;
            return -1;
        }
        total_puddings += puddings.size();
        if(total_puddings > 3000) {
            std::cerr << "Too many total puddings." << std::endl;
            return -1;
        }
        VERBOSE << "Query " << query_count << ": Puddings = ";
        for(int i = 0; i < puddings.size(); i++) {
            VERBOSE << puddings[i];
            if(puddings[i] <= 0 or puddings[i] > 4500) {
                VERBOSE << "x";
            }
            VERBOSE << " ";
        }
        VERBOSE << std::endl;
        for(auto it: puddings) {
            if(it <= 0 or it > 4500) {
                std::cerr << "Invalid tastiness value: " << it << std::endl;
                return -1;
            }
        }
        puddings.push_back(target_tastiness);
        std::sort(puddings.begin(), puddings.end());
        VERBOSE << "Sorted puddings after mixing = ";
        for(int i = 0; i < puddings.size(); i++) {
            VERBOSE << puddings[i];
            if(puddings[i] == target_tastiness and (i == 0 or puddings[i - 1] != target_tastiness)) {
                VERBOSE << "*";
            }
            VERBOSE << " ";
        }
        VERBOSE << std::endl;
        VERBOSE << "GCDs after sorting = ";
        int result = 0;
        for (int i = 1; i < puddings.size(); i++) {
            result += gcd(puddings[i - 1], puddings[i]);
            VERBOSE << gcd(puddings[i - 1], puddings[i]) << " ";
            if(i < puddings.size() - 1) {
                VERBOSE << "+ ";
            }
            else if (puddings.size() > 2) VERBOSE << "= " << result;
        }
        VERBOSE << std::endl;
        VERBOSE << "-----------------------------" << std::endl;
        return result;
    }
    int main() {
        int t, W, id;
        std::cin >> id >> t >> W;
        init(id, t);
        bool correct = true;
        int max_query = 0, max_total_puddings = 0;
        for(int i = 1; i <= t; i++) {
            query_count = 0;
            total_puddings = 0;
            std::cin >> target_tastiness;
            int returned_tastiness = find_tastiness(id, W);
            if (returned_tastiness == target_tastiness) {
                VERBOSE << "Case #" << i << ": Correctly returned "<< target_tastiness << ", Queries = " << query_count << ", Total Puddings = " << total_puddings << std::endl;
            } else {
                VERBOSE << "Case #" << i << ": Wrong Answer (Expected " << target_tastiness << ", got " << returned_tastiness << ")" << std::endl;
                correct = false;
            }
            max_query = std::max(max_query, query_count);
            max_total_puddings = std::max(max_total_puddings, total_puddings);
            VERBOSE << "======================================" << std::endl;
        }
        if(!correct) {
            std::cout << "Wrong answer." << std::endl;
        } else {
            std::cout << "Correct!" << std::endl;
            std::cout << "Max queries used: " << max_query << std::endl;
            std::cout << "Max total puddings queried: " << max_total_puddings << std::endl;
            VERBOSE << "Score coefficient = " << f(max_query) << " * " << g(max_total_puddings) << " = " << f(max_query) * g(max_total_puddings) << std::endl;
        }
        return 0;
    }
}

int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; i++) {
        if(std::string(argv[i]) == "-v" or std::string(argv[i]) == "--verbose") {
            verbose = true;
        }
    }
    return grader::main();
}

int query_tastiness(std::vector<int> tastiness) {
    return grader::query_tastiness(tastiness);
}
