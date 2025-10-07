#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

// Rule structure
struct Rule {
    vector<string> conditions;
    string conclusion;
};

// Check if all conditions of a rule are satisfied
bool isApplicable(const Rule& rule, const unordered_set<string>& facts) {
    for (const string& cond : rule.conditions)
        if (facts.find(cond) == facts.end())
            return false;
    return true;
}

// Forward chaining algorithm with trace
bool forwardChaining(vector<Rule>& rules, unordered_set<string>& facts, const string& goal, vector<string>& trace) {
    bool changed = true;

    while (changed) {
        changed = false;
        for (const Rule& rule : rules) {
            if (isApplicable(rule, facts) && facts.find(rule.conclusion) == facts.end()) {
                facts.insert(rule.conclusion);
                trace.push_back("Inferred: " + rule.conclusion + " using rule: if [ " +
                    [&]() {
                        string s;
                        for (const string& cond : rule.conditions) s += cond + " ";
                        return s;
                    }() + "] then " + rule.conclusion);
                changed = true;
                if (rule.conclusion == goal) return true;
            }
        }
    }

    return facts.find(goal) != facts.end();
}

int main() {
    // Initial facts
    unordered_set<string> facts = {"A", "B"};

    // Rules
    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C"}, "D"},
        {{"D"}, "E"},
        {{"E"}, "F"}
    };

    string goal = "F";
    vector<string> trace;

    cout << "Forward Chaining Inference\n";
    cout << "Initial facts: ";
    for (const string& f : facts) cout << f << " ";
    cout << "\nGoal to infer: '" << goal << "'\n\n";

    bool result = forwardChaining(rules, facts, goal, trace);

    // Print trace
    for (const string& step : trace)
        cout << step << endl;

    cout << "\nFinal Result: ";
    if (result)
        cout << "Goal '" << goal << "' was successfully inferred.\n";
    else
        cout << "Goal '" << goal << "' could NOT be inferred from the given facts and rules.\n";

    return 0;
}
