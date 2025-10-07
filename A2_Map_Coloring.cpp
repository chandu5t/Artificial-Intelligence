#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

vector<string> variables = {
    "WA", "NT", "SA", "Q", "NSW", "V", "T"
};

map<string, vector<string>> neighbors = {
    {"WA", {"NT", "SA"}},
    {"NT", {"WA", "SA", "Q"}},
    {"SA", {"WA", "NT", "Q", "NSW", "V"}},
    {"Q", {"NT", "SA", "NSW"}},
    {"NSW", {"SA", "Q", "V"}},
    {"V", {"SA", "NSW"}},
    {"T", {}}
};

vector<string> colors = {
    "Red", "Green", "Blue"
};

bool isConsistent(const string &var, const string &value, map<string, string> &assignment) {
    for (const string &neighbor : neighbors[var]) {
        if (assignment.find(neighbor) != assignment.end() && assignment[neighbor] == value) {
            return false;
        }
    }
    return true;
}

map<string, vector<string>> deepcopyDomain(const map<string, vector<string>> &domain) {
    map<string, vector<string>> copy;
    for (const auto &pair : domain) {
        copy[pair.first] = pair.second;
    }
    return copy;
}

bool forwardCheck(const string &var, const string &value,
                  map<string, vector<string>> &domain,
                  const map<string, string> &assignment) {
    for (const string &neighbor : neighbors[var]) {
        if (assignment.find(neighbor) == assignment.end()) {
            vector<string> &neighborDomain = domain[neighbor];
            neighborDomain.erase(remove(neighborDomain.begin(), neighborDomain.end(), value), neighborDomain.end());
            if (neighborDomain.empty()) {
                return false;
            }
        }
    }
    return true;
}

bool backtrack(map<string, string> &assignment, map<string, vector<string>> &domain) {
    if (assignment.size() == variables.size()) {
        return true;
    }

    // Select unassigned variable (first one for simplicity)
    string unassigned;
    for (const string &var : variables) {
        if (assignment.find(var) == assignment.end()) {
            unassigned = var;
            break;
        }
    }

    for (const string &value : domain[unassigned]) {
        if (isConsistent(unassigned, value, assignment)) {
            assignment[unassigned] = value;
            map<string, vector<string>> domainCopy = deepcopyDomain(domain);

            if (forwardCheck(unassigned, value, domain, assignment)) {
                if (backtrack(assignment, domain)) {
                    return true;
                }
            }

            domain = domainCopy;
            assignment.erase(unassigned);
        }
    }

    return false;
}

int main() {
    map<string, string> assignment;
    map<string, vector<string>> domain;

    for (const string &var : variables) {
        domain[var] = colors;
    }

    if (backtrack(assignment, domain)) {
        cout << "Solution Found!\n";
        for (const auto &pair : assignment) {
            cout << pair.first << " -> " << pair.second << endl;
        }
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
