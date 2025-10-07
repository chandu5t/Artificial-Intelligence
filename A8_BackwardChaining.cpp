#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

// Rule structure
struct Rule {
    vector<string> conditions;
    string conclusion;
};

// Recursive backward chaining with explanation
bool backwardChaining(const string& goal,
                      const vector<Rule>& rules,
                      const unordered_set<string>& facts,
                      unordered_set<string>& visited,
                      vector<string>& trace) {
    if (facts.find(goal) != facts.end()) {
        trace.push_back("Fact '" + goal + "' is known.");
        return true;
    }

    if (visited.find(goal) != visited.end()) {
        trace.push_back("Already visited '" + goal + "', skipping to avoid loop.");
        return false;
    }

    visited.insert(goal);
    trace.push_back("Trying to infer '" + goal + "'...");

    for (const Rule& rule : rules) {
        if (rule.conclusion == goal) {
            string conditionList;
            for (const string& cond : rule.conditions)
                conditionList += cond + " ";
            trace.push_back("Found rule: if [" + conditionList + "] then " + goal);

            bool allConditionsMet = true;
            for (const string& cond : rule.conditions) {
                if (!backwardChaining(cond, rules, facts, visited, trace)) {
                    trace.push_back("Cannot infer condition '" + cond + "' for rule leading to '" + goal + "'.");
                    allConditionsMet = false;
                    break;
                }
            }

            if (allConditionsMet) {
                trace.push_back("All conditions met. Inferred '" + goal + "'.");
                return true;
            }
        }
    }

    trace.push_back("No rule could infer '" + goal + "'.");
    return false;
}

int main() {
    // Known facts
    unordered_set<string> facts = {"A", "B"};

    // Inference rules
    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C"}, "D"},
        {{"D"}, "E"},
        {{"E"}, "F"}
    };

    string goal = "F";
    unordered_set<string> visited;
    vector<string> trace;

    cout << "Backward Chaining Inference\n";
    cout << "Known facts: ";
    for (const string& f : facts) cout << f << " ";
    cout << "\nGoal to infer: '" << goal << "'\n\n";

    bool result = backwardChaining(goal, rules, facts, visited, trace);

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
