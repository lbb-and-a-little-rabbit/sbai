//后向推理示例

#include <iostream>
#include <vector>
#include <string>
#include <set>

//规则格式：IF A AND B THEN C

struct Rule {
    std::string conclusion;
    std::vector<std::string> conditions;
};

bool prove(const std::string& goal,
           const std::set<std::string>& facts,
           const std::vector<Rule>& rules,
           std::set<std::string>& visited)
{
    if (facts.find(goal) != facts.end()) return true; // 已知事实

    if (visited.find(goal) != visited.end()) return false; // 避免循环
    visited.insert(goal);

    for (const auto& r : rules) {
        if (r.conclusion == goal) {
            bool ok = true;
            for (auto& cond : r.conditions) {
                if (!prove(cond, facts, rules, visited))
                    ok = false;
            }
            if (ok) return true;
        }
    }
    return false;
}

int main() {
    std::set<std::string> facts = {"A", "B"};
    std::vector<Rule> rules = {
        {"C", {"A", "B"}},
        {"D", {"C"}}
    };

    std::string goal = "D";
    std::set<std::string> visited;

    if (prove(goal, facts, rules, visited))
        std::cout << "目标 " << goal << " 被证明成立\n";
    else
        std::cout << "无法证明目标 " << goal << "\n";
}
