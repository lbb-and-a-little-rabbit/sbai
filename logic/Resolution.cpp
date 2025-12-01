//归结推理示例（反证法）

#include <iostream>
#include <vector>
#include <set>
#include <string>

//（A v B) ^ (~A V C)->(B v C)

struct Clause {
    std::set<std::string> lits; // literals
};

bool isComplement(const std::string& a, const std::string& b) {
    return (a == "~" + b) || (b == "~" + a);
}

bool resolveClauses(const Clause& c1, const Clause& c2, Clause& resolvent) {
    int count = 0;
    std::string lit1, lit2;

    for (auto& a : c1.lits) {
        for (auto& b : c2.lits) {
            if (isComplement(a, b)) {
                count++;
                lit1 = a; lit2 = b;
            }
        }
    }
    if (count != 1) return false;

    resolvent = Clause();
    for (auto& a : c1.lits) if (a != lit1) resolvent.lits.insert(a);
    for (auto& b : c2.lits) if (b != lit2) resolvent.lits.insert(b);

    return true;
}

bool containsEmptyClause(const std::vector<Clause>& clauses) {
    for (auto& c : clauses) {
        if (c.lits.empty()) return true;
    }
    return false;
}

int main() {
    //证明(A∨B)∧(¬A)∧(¬B) 是不可满足的。

    std::vector<Clause> clauses = {
        {{"A", "B"}},    // A ∨ B
        {{"~A"}},        // ¬A
        {{"~B"}}         // ¬B
    };

    bool added = true;
    while (added) {
        added = false;
        std::vector<Clause> newClauses = clauses;

        for (size_t i = 0; i < clauses.size(); i++) {
            for (size_t j = i+1; j < clauses.size(); j++) {
                Clause res;
                if (resolveClauses(clauses[i], clauses[j], res)) {
                    if (res.lits.empty()) {
                        std::cout << "得到空子句，证明成立\n";
                        return 0;
                    }
                    newClauses.push_back(res);
                    added = true;
                }
            }
        }
        clauses = newClauses;
    }

    std::cout << "无法推出空子句，证明失败\n";
}
