//前向推理简单示例

#include <iostream>
#include <vector>
#include <string>
#include <set>

//规则格式：IF A AND B THEN C

struct Rule {
    std::vector<std::string> conditions;
    std::string conclusion;
};

bool ruleCanFire(const Rule& r, const std::set<std::string>& facts) {
    for (auto& c : r.conditions) {
        if (facts.find(c) == facts.end()) return false;
    }
    return true;
}

int main() {
    // 初始事实
    std::set<std::string> facts = {"A", "B"};

    // 规则库
    std::vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C"}, "D"}
    };

    bool newFactAdded = true;

    while (newFactAdded) {
        newFactAdded = false;
        for (auto& r : rules) {
            if (ruleCanFire(r, facts) &&
                facts.find(r.conclusion) == facts.end()) 
            {
                std::cout << "推理得到新事实: " << r.conclusion << "\n";
                facts.insert(r.conclusion);
                newFactAdded = true;
            }
        }
    }

    std::cout << "\n最终事实集合:\n";
    for (auto& f : facts) std::cout << f << " ";
    std::cout << "\n";
}
