#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<vector<int>> state;
    int x, y;               // blank tile position
    string path;            // path of moves
    int depth;              // depth level
};

// Convert state to string (for visited checking)
string stateToString(vector<vector<int>>& state) {
    string s = "";
    for (auto &row : state)
        for (auto &val : row)
            s += to_string(val);
    return s;
}

// Print the board
void printState(vector<vector<int>>& state) {
    for (auto &row : state) {
        for (auto &val : row) cout << val << " ";
        cout << "\n";
    }
    cout << "--------\n";
}

// Depth Limited DFS
bool DFS(vector<vector<int>> start, vector<vector<int>> goal, int limit) {
    stack<Node> st;
    set<string> visited;

    Node root = {start, 0, 0, "", 0};

    // find blank position
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (start[i][j] == 0) {
                root.x = i;
                root.y = j;
            }

    st.push(root);
    visited.insert(stateToString(root.state));

    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};
    char dir[4] = {'U','D','L','R'};

    while (!st.empty()) {
        Node current = st.top(); st.pop();

        // Check goal
        if (current.state == goal) {
            cout << "Goal found with path: " << current.path<< "\n";
            return true;
        }

        // Apply depth limit
        if (current.depth >= limit) continue;

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
                Node next = current;
                swap(next.state[current.x][current.y], next.state[newX][newY]);
                next.x = newX;
                next.y = newY;
                next.path.push_back(dir[i]);
                next.depth = current.depth + 1;

                string key = stateToString(next.state);
                if (visited.find(key) == visited.end()) {
                    visited.insert(key);
                    st.push(next);
                }
            }
        }
    }
    return false;
}

int main() {
    vector<vector<int>> start = {
        {1,2,3},
        {4,5,6},
        {0,7,8}
    };

    vector<vector<int>> goal = {
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };

    int depthLimit = 20;  
    if (!DFS(start, goal, depthLimit)) {
        cout << "Goal not found within depth limit " << depthLimit << "\n";
    }

    return 0;
}
