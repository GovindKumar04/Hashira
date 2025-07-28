#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include "json.hpp" // downloaded file

using json = nlohmann::json;
using namespace std;


long long convertToDecimal(const string &val, int b) {
    long long res = 0;
    for (char c : val) {
        int dgt;
        if (isdigit(c)) dgt = c - '0';
        else dgt = tolower(c) - 'a' + 10;
        res = res * b + dgt;
    }
    return res;
}


long long poly(const vector<pair<int, long long>> &points) {
    long double res = 0.0;
    int k = points.size();

    for (int i = 0; i < k; i++) {
        long double term = points[i].second;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0.0 - points[j].first);
                term /= (points[i].first - points[j].first);
            }
        }
        res += term;
    }

    return llround(res);
}

void solve(const string &filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout<<"Can not open file"<<endl;
        return;
    }

    json j;
    inputFile >> j;

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    vector<pair<int, long long>> points;

    for (json::iterator it = j.begin(); it != j.end(); it++) {
    string key = it.key();
    json value = it.value();
    
    if (key == "keys") continue;

    int x = stoi(key);
    int base = stoi(value["base"].get<string>());
    string val = value["value"].get<string>();
    long long y = convertToDecimal(val, base);

    points.push_back({x, y});
}


    sort(points.begin(), points.end());
    vector<pair<int, long long>> selected(points.begin(), points.begin() + k);

    long long c = poly(selected);
    cout << c << endl;
}

int main() {
    cout << "Secret for test case 1: ";
    solve("testcase1.json");

    cout << "Secret for test case 2: ";
    solve("testcase2.json");

    return 0;
}
