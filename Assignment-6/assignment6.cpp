
#include <bits/stdc++.h>
using namespace std;

struct Item {
    int weight, value, priority;
    bool used = false;
};

int main() {
    int n, trucks;

    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);

    for (int i = 0; i < n; i++) {
        cout << "\nItem " << i + 1 << ":\n";
        cout << "Enter weight, utility, priority (1/0): ";
        cin >> items[i].weight >> items[i].value >> items[i].priority;
    }

    cout << "\nEnter number of trucks: ";
    cin >> trucks;

    for (int t = 1; t <= trucks; t++) {
        int W;
        cout << "\nEnter capacity of truck " << t << ": ";
        cin >> W;

        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

        // 0/1 Knapsack DP
        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= W; w++) {
                dp[i][w] = dp[i - 1][w];

                if (!items[i - 1].used &&
                    items[i - 1].weight <= w) {

                    int value = items[i - 1].value;

                    if (items[i - 1].priority == 1)
                        value += 10;

                    dp[i][w] = max(
                        dp[i][w],
                        value + dp[i - 1][w - items[i - 1].weight]
                    );
                }
            }
        }

        cout << "\nTruck " << t;
        cout << "\nMaximum Utility: " << dp[n][W];
        cout << "\nSelected items:\n";

        // Find selected items
        int w = W;

        for (int i = n; i >= 1; i--) {
            if (dp[i][w] != dp[i - 1][w]) {
                cout << "Item " << i
                     << " (Weight: " << items[i - 1].weight
                     << " kg)\n";

                items[i - 1].used = true;
                w -= items[i - 1].weight;
            }
        }

        cout << "\n";
    }

    return 0;
}
