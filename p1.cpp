#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <json/json.h>
#include <cmath>

using namespace std;

int decodeBase(const string& value, int base) {
    return stoi(value, nullptr, base);
}

double lagrangeInterpolation(const vector<pair<int, int>>& points, int k) {
    double f0 = 0;
    for (int j = 0; j < k; ++j) {
        double term = points[j].second;
        for (int m = 0; m < k; ++m) {
            if (m != j) {
                term *= (0 - points[m].first) / double(points[j].first - points[m].first);
            }
        }
        f0 += term;
    }
    return f0;
}

int main() {
    ifstream file("input.json");
    Json::Value data;
    file >> data;

    int n = data["keys"]["n"].asInt();
    int k = data["keys"]["k"].asInt();
    vector<pair<int, int>> points;

    for (const auto& key : data.getMemberNames()) {
        if (key == "keys") continue;

        int x = stoi(key);
        int base = data[key]["base"].asInt();
        string value = data[key]["value"].asString();
        int y = decodeBase(value, base);

        points.push_back({x, y});
    }

    double secret = lagrangeInterpolation(points, k);
    cout << "The constant term (secret) is: " << secret << endl;

    return 0;
}
