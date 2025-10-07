#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<vector<int>> state;
    vector<char> path;
};

vector<int> dx = {1, -1, 0, 0};
vector<int> dy = {0, 0, 1, -1};
vector<char> dir = {'D', 'U', 'R', 'L'};  // Down, Up, Right, Left

// Convert state to string for hashing
string stateToString(vector<vector<int>>& state) {
    string s = "";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            s += to_string(state[i][j]);
    return s;
}

// Find blank (0) position
pair<int,int> findBlank(vector<vector<int>>& state) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state[i][j] == 0)
                return {i, j};
        }
    }
    return {-1, -1}; // should never happen
}

bool isGoal(vector<vector<int>>& state) {
    vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};
    return state == goal;
}

void BFS(vector<vector<int>> start) {
    queue<Node> q;
    set<string> visited;

    Node root;
    root.state = start;
    q.push(root);
    visited.insert(stateToString(root.state));

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        if (isGoal(cur.state)) {
            cout << "Goal found! Path: ";
            for (char c : cur.path) cout << c << " ";
            cout << "\n";
            return;
        }

        pair<int,int> blank = findBlank(cur.state);
        int x = blank.first;
        int y = blank.second;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                Node next = cur;
                swap(next.state[x][y], next.state[nx][ny]);
                next.path.push_back(dir[d]);

                string key = stateToString(next.state);
                if (visited.find(key) == visited.end()) {
                    visited.insert(key);
                    q.push(next);
                }
            }
        }
    }
    cout << "No solution found.\n";
}

int main() {
    // Example start state (3 moves away from goal)
    vector<vector<int>> start = {
        {1,2,3},
        {4,5,6},
        {0,7,8}
    };

    BFS(start);
    return 0;
}
