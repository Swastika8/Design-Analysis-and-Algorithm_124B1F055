
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    double base, cost;
};

int main() {
    int S, M;
    cout << "Enter number of stages: ";
    cin >> S;

    vector<int> count(S), start(S);
    int N = 0;

    cout << "Enter nodes in each stage: ";
    for (int i = 0; i < S; i++) {
        cin >> count[i];
        start[i] = N;
        N += count[i];
    }

    vector<vector<Edge>> adj(N);
    vector<vector<int>> rev(N);

    cout << "Enter number of edges: ";
    cin >> M;

    cout << "Enter edges (u v cost):\n";
    for (int i = 0; i < M; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w, w});
        rev[v].push_back(u);
    }

    const double INF = 1e18;
    vector<double> dp(N, INF);
    vector<int> next(N, -1);

    for (int i = start[S - 1]; i < N; i++)
        dp[i] = 0;

    auto solve = [&](int u) {
        double best = INF;
        int bestNode = -1;

        for (auto e : adj[u]) {
            if (e.cost + dp[e.to] < best) {
                best = e.cost + dp[e.to];
                bestNode = e.to;
            }
        }

        dp[u] = best;
        next[u] = bestNode;
    };

    for (int s = S - 2; s >= 0; s--)
        for (int i = start[s]; i < start[s] + count[s]; i++)
            solve(i);

    cout << "\nMinimum costs:\n";
    for (int i = 0; i < count[0]; i++) {
        if (dp[i] == INF)
            cout << i << ": Unreachable\n";
        else
            cout << i << ": " << dp[i] << "\n";
    }

    int src;
    cout << "\nEnter source node (-1 to skip): ";
    cin >> src;

    if (src >= 0 && src < count[0]) {
        if (dp[src] == INF) {
            cout << "No path\n";
        } else {
            cout << "Path: ";
            for (int u = src; u != -1; u = next[u]) {
                cout << u;
                if (next[u] != -1) cout << " -> ";
            }
            cout << "\nCost: " << dp[src] << "\n";
        }
    }

    int Q;
    cout << "\nEnter number of updates: ";
    cin >> Q;

    while (Q--) {
        int u, v;
        double multiplier;

        cout << "Enter u v multiplier: ";
        cin >> u >> v >> multiplier;

        for (auto &e : adj[u])
            if (e.to == v)
                e.cost = e.base * multiplier;

        queue<int> q;
        q.push(u);

        while (!q.empty()) {
            int x = q.front();
            q.pop();

            double old = dp[x];
            int oldNext = next[x];
            solve(x);

            if (abs(old - dp[x]) > 1e-9 || oldNext != next[x])
                for (int p : rev[x])
                    q.push(p);
        }
    }

    cout << "\nUpdated minimum costs:\n";
    for (int i = 0; i < count[0]; i++) {
        if (dp[i] == INF)
            cout << i << ": Unreachable\n";
        else
            cout << i << ": " << dp[i] << "\n";
    }

    return 0;
}

