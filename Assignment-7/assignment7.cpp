
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> subjects = {
        "DAA", "AIML", "SPM", "EAC", "MDM-3"
    };

    int n = subjects.size();
    vector<vector<int>> graph(n, vector<int>(n, 0));

    int m;
    cout << "Enter number of subject conflicts: ";
    cin >> m;

    cout << "Subject IDs:\n";
    for (int i = 0; i < n; i++)
        cout << i << " - " << subjects[i] << "\n";

    cout << "\nEnter conflicting subject pairs (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        if (u >= 0 && u < n && v >= 0 && v < n && u != v)
            graph[u][v] = graph[v][u] = 1;
    }

    // Greedy graph coloring
    vector<int> color(n, -1);

    for (int u = 0; u < n; u++) {
        vector<bool> used(n, false);

        for (int v = 0; v < n; v++)
            if (graph[u][v] && color[v] != -1)
                used[color[v]] = true;

        int c = 0;
        while (used[c])
            c++;

        color[u] = c;
    }

    // Room allocation
    int rooms, capacity;
    cout << "\nEnter number of rooms: ";
    cin >> rooms;

    cout << "Enter capacity of each room: ";
    cin >> capacity;

    vector<int> students(n);
    cout << "\nEnter student count for each subject:\n";

    for (int i = 0; i < n; i++) {
        cout << subjects[i] << ": ";
        cin >> students[i];
    }

    int slots = *max_element(color.begin(), color.end()) + 1;

    cout << "\n----- EXAM TIMETABLE -----\n";

    for (int s = 0; s < slots; s++) {
        cout << "\nTime Slot " << s + 1 << ":\n";

        int available = rooms * capacity;

        for (int i = 0; i < n; i++) {
            if (color[i] == s) {
                cout << subjects[i];

                if (students[i] <= available) {
                    cout << " - Allocated\n";
                    available -= students[i];
                } else {
                    cout << " - Insufficient rooms\n";
                }
            }
        }
    }

    cout << "\nTotal time slots required: " << slots << "\n";

    return 0;
}
