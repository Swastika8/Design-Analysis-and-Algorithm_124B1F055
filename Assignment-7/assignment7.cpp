
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> subjects = {
        "DAA", "AIML", "SPM", "EAC", "MDM-3"
    };

    int n = subjects.size();
    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Subject IDs:\n";
    for (int i = 0; i < n; i++)
        cout << i << " - " << subjects[i] << "\n";

    int m;
    cout << "\nEnter number of conflicts: ";
    cin >> m;

    cout << "Enter conflicting subject pairs (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        if (u >= 0 && u < n && v >= 0 && v < n && u != v)
            graph[u][v] = graph[v][u] = 1;
    }

    // Greedy Graph Coloring
    vector<int> color(n, -1);

    for (int u = 0; u < n; u++) {
        vector<bool> used(n, false);

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && color[v] != -1)
                used[color[v]] = true;
        }

        int c = 0;
        while (c < n && used[c])
            c++;

        color[u] = c;
    }

    // Display Colors
    vector<string> colors = {
        "Red", "Green", "Blue", "Yellow", "Orange"
    };

    cout << "\n----- GRAPH COLORING RESULT -----\n";

    for (int i = 0; i < n; i++) {
        cout << subjects[i]
             << " -> " << colors[color[i]]
             << " (Slot " << color[i] + 1 << ")\n";
    }

    // Room Allocation
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

    cout << "\n----- FINAL EXAM TIMETABLE -----\n";

    for (int s = 0; s < slots; s++) {
        cout << "\nSlot " << s + 1
             << " (" << colors[s] << "):\n";

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

    cout << "\nTotal Colors Used: " << slots;
    cout << "\nTotal Exam Slots Required: " << slots << "\n";

    return 0;
}
