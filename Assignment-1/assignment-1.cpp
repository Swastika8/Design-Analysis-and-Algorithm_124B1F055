#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Record {
    string name;
    double price;
    int units_sold;
    double rating;
};

// Quicksort
void quickSort(vector<Record>& data, int low, int high, int choice) {
    if (low >= high)
        return;

    int i = low;
    int j = high;
    Record pivot = data[(low + high) / 2];
    while (i <= j) {
        // CHANGE THESE COMPARISONS FOR EACH PROBLEM
        if (choice == 1) {
            while (data[i].price < pivot.price)
                i++;
            while (data[j].price > pivot.price)
                j--;
        }
        else if (choice == 2) {
            while (data[i].units_sold < pivot.units_sold)
                i++;
            while (data[j].units_sold > pivot.units_sold)
                j--;
        }
        else {
            while (data[i].rating < pivot.rating)
                i++;
            while (data[j].rating > pivot.rating)
                j--;
        }
        if (i <= j) {
            swap(data[i], data[j]);
            i++;
            j--;
        }
    }
    if (low < j)
        quickSort(data, low, j, choice);
    if (i < high)
        quickSort(data, i, high, choice);
}

int main() {
    vector<Record> data;
    // CHANGE CSV FILE NAME HERE
    ifstream file("ecommerce_dataset.csv");
    if (!file) {
        cout << "Error opening file!";
        return 1;
    }

    string line;
    // Skip header
    getline(file, line);

    // Read CSV
    // Actual column order in this file:
    // product_id, product_name, category, price, units_sold, rating, in_stock
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Record r;

        getline(ss, temp, ',');        // product_id -> skip
        getline(ss, r.name, ',');      // product_name
        getline(ss, temp, ',');        // category -> skip
        getline(ss, temp, ',');
        r.price = stod(temp);
        getline(ss, temp, ',');
        r.units_sold = stoi(temp);
        getline(ss, temp, ',');
        r.rating = stod(temp);
        // remaining field (in_stock) is ignored

        data.push_back(r);
    }
    file.close();

    int choice;
    cout << "Sort by:\n";
    cout << "1. Price\n";
    cout << "2. Units Sold\n";
    cout << "3. Rating\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice < 1 || choice > 3) {
        cout << "Invalid Choice! " << endl;
        return 1;
    }

    if (!data.empty()) {
        quickSort(data, 0, data.size() - 1, choice);
    }

    // Choose output filename
    string filename;
    if (choice == 1)
        filename = "sorted_by_value1.csv";
    else if (choice == 2)
        filename = "sorted_by_value2.csv";
    else
        filename = "sorted_by_value3.csv";

    // Create output CSV
    ofstream outFile(filename);
    // Write header
    outFile << "Name,Value1,Value2,Value3\n";
    // Write sorted data
    for (Record r : data) {
        outFile << r.name << ","
                << r.price << ","
                << r.units_sold << ","
                << r.rating << "\n";
    }
    outFile.close();

    cout << "\nSorted data saved to " << filename << endl;
    return 0;
}
