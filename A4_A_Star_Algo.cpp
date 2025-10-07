#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<vector<int>> state;
    int g, h;
    Node* parent;

    Node(vector<vector<int>> s, int g, int h, Node* p=nullptr)
        : state(s), g(g), h(h), parent(p) {}
};

struct cmp {
    bool operator()(Node* a, Node* b) {
        return (a->g + a->h) > (b->g + b->h);
    }
};

// Goal state
vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};

// Manhattan distance heuristic
int heuristic(vector<vector<int>> &state) {
    int dist = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int val = state[i][j];
            if(val != 0) {
                int targetX = (val-1)/3;
                int targetY = (val-1)%3;
                dist += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return dist;
}

pair<int,int> findBlank(vector<vector<int>> &state) {
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(state[i][j] == 0) return {i,j};
        }
    }
    return {-1,-1};
}

bool isGoal(vector<vector<int>> &state) {
    return state == goal;
}

void printPath(Node* node) {
    if(node == nullptr) return;
    printPath(node->parent);
    for(auto &row : node->state) {
        for(int val : row) cout << val << " ";
        cout << endl;
    }
    cout << "----" << endl;
}

void AStar(vector<vector<int>> start) {
    priority_queue<Node*, vector<Node*>, cmp> pq;
    set<vector<vector<int>>> visited;

    Node* root = new Node(start, 0, heuristic(start));
    pq.push(root);

    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    while(!pq.empty()) {
        Node* cur = pq.top(); pq.pop();

        if(isGoal(cur->state)) {
            cout << "Solution found! Path:" << endl;
            printPath(cur);
            return;
        }

        visited.insert(cur->state);

        pair<int,int> blank = findBlank(cur->state);
        int x = blank.first, y = blank.second;

        for(int d=0; d<4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if(nx>=0 && nx<3 && ny>=0 && ny<3) {
                vector<vector<int>> newState = cur->state;
                swap(newState[x][y], newState[nx][ny]);

                if(visited.find(newState) == visited.end()) {
                    Node* next = new Node(newState, cur->g+1, heuristic(newState), cur);
                    pq.push(next);
                }
            }
        }
    }
    cout << "No solution found." << endl;
}

int main() {
    vector<vector<int>> start = {
        {1,2,3},
        {4,0,6},
        {7,5,8}
    };

    AStar(start);
    return 0;
}
