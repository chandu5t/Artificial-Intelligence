#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

// Represents a person in the family tree
struct Person {
    string name;
    vector<string> parents;
    vector<string> children;
};

// Knowledge Base: A map from a person's name to their Person object
map<string, Person> knowledge_base;

// Helper function to create a person if they don't exist
void ensurePersonExists(const string& name) {
    if (knowledge_base.find(name) == knowledge_base.end()) {
        knowledge_base[name] = Person{name, {}, {}};
    }
}

// --- Add Facts ---
// Adds a parent-child relationship to the knowledge base
void addParentChild(const string& parent_name, const string& child_name) {
    ensurePersonExists(parent_name);
    ensurePersonExists(child_name);

    // Add child to parent's children list
    knowledge_base[parent_name].children.push_back(child_name);

    // Add parent to child's parents list
    knowledge_base[child_name].parents.push_back(parent_name);
}

// --- Rules ---
// Rule 1: Get children of a given person
vector<string> getChildren(const string& name) {
    if (knowledge_base.count(name)) {
        return knowledge_base[name].children;
    }
    return {};
}

// Rule 2: Get siblings of a given person
vector<string> getSiblings(const string& name) {
    vector<string> siblings;
    set<string> sibling_set; // Use a set to avoid duplicates

    if (knowledge_base.count(name)) {
        // Find all children of the person's parents
        for (const string& parent_name : knowledge_base[name].parents) {
            for (const string& sibling_name : knowledge_base[parent_name].children) {
                // Add to set if not the person themselves
                if (sibling_name != name) {
                    sibling_set.insert(sibling_name);
                }
            }
        }
    }
    // Convert set to vector for returning
    siblings.assign(sibling_set.begin(), sibling_set.end());
    return siblings;
}

// Rule 3: Get grandchildren of a given person
vector<string> getGrandchildren(const string& name) {
    vector<string> grandchildren;
    if (knowledge_base.count(name)) {
        // Find all children
        for (const string& child_name : knowledge_base[name].children) {
            // Find all children of those children (grandchildren)
            for (const string& grandchild_name : knowledge_base[child_name].children) {
                grandchildren.push_back(grandchild_name);
            }
        }
    }
    return grandchildren;
}

// Rule 4: 'is' relation to check if person1 is a parent, child, or sibling of person2
void isRelation(const string& person1, const string& person2) {
    bool found = false;
    // Check if person1 is a child of person2
    if (find(knowledge_base[person2].children.begin(), knowledge_base[person2].children.end(), person1) != knowledge_base[person2].children.end()) {
        cout << person1 << " is a child of " << person2 << "." << endl;
        found = true;
    }
    // Check if person1 is a parent of person2
    if (find(knowledge_base[person2].parents.begin(), knowledge_base[person2].parents.end(), person1) != knowledge_base[person2].parents.end()) {
        cout << person1 << " is a parent of " << person2 << "." << endl;
        found = true;
    }
    // Check if person1 is a sibling of person2
    vector<string> siblings_of_p2 = getSiblings(person2);
    if (find(siblings_of_p2.begin(), siblings_of_p2.end(), person1) != siblings_of_p2.end()) {
        cout << person1 << " is a sibling of " << person2 << "." << endl;
        found = true;
    }

    if (!found) {
        cout << "No direct relation found between " << person1 << " and " << person2 << "." << endl;
    }
}

// --- Main ---
int main() {
    // FACTS
    addParentChild("Mohan", "Ram");
    addParentChild("Mohan", "Shyam");
    addParentChild("Mohan", "Gita");
    addParentChild("Sita", "Ram");
    addParentChild("Sita", "Shyam");
    addParentChild("Sita", "Gita");
    addParentChild("Shyam", "Anu");
    addParentChild("Shyam", "Raju");

    cout << "Family Tree Knowledge Base Parser\n";
    cout << "----------------------------------\n";

    cout << "Queries Supported:\n";
    cout << "1. children <name>\n";
    cout << "2. siblings <name>\n";
    cout << "3. grandchildren <name>\n";
    cout << "4. is <person1> <person2>\n";
    cout << "Type 'exit' to quit.\n\n";

    string query, name, name2;
    while (true) {
        cout << "Enter query: ";
        cin >> query;
        if (query == "exit") break;
        if (query == "is") {
            cin >> name >> name2;
            isRelation(name, name2);
        } else {
            cin >> name;
            if (query == "children") {
                vector<string> res = getChildren(name);
                if (res.empty()) cout << name << " has no children.\n";
                else {
                    cout << "Children of " << name << ": ";
                    for (const string& c : res) cout << c << " ";
                    cout << endl;
                }
            } else if (query == "siblings") {
                vector<string> res = getSiblings(name);
                if (res.empty()) cout << name << " has no siblings.\n";
                else {
                    cout << "Siblings of " << name << ": ";
                    for (const string& s : res) cout << s << " ";
                    cout << endl;
                }
            } else if (query == "grandchildren") {
                vector<string> res = getGrandchildren(name);
                if (res.empty()) cout << name << " has no grandchildren.\n";
                else {
                    cout << "Grandchildren of " << name << ": ";
                    for (const string& g : res) cout << g << " ";
                    cout << endl;
                }
            } else {
                cout << "Unknown query type!\n";
            }
        }
    }
    return 0;
}