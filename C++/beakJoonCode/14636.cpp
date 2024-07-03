#include <bits/stdc++.h>
using namespace std;

int numPowerPlants, numCities;
vector<pair<long long, long long>> powerPlants, cities;
vector<pair<long long, long long>> lowerEnvelope, upperEnvelope;
long long dp[600000];
long long maxProduct;

void findMaxProduct(int start, int end, int optStart, int optEnd) {
    if (start > end) {
        return;
    }
    
    int mid = (start + end) >> 1;
    int optimalIndex = optStart;
    long long& currentMax = dp[mid];
    currentMax = LLONG_MIN;
    
    for (int i = optStart; i <= optEnd; ++i) {
        long long deltaTime = upperEnvelope[i].second - lowerEnvelope[mid].second;
        long long deltaPower = upperEnvelope[i].first - lowerEnvelope[mid].first;
        
        if (deltaTime >= 0 || deltaPower >= 0) {
            long long product = deltaTime * deltaPower;
            if (currentMax <= product) {
                currentMax = product;
                optimalIndex = i;
            }
        }
    }
    
    findMaxProduct(start, mid - 1, optStart, optimalIndex);
    findMaxProduct(mid + 1, end, optimalIndex, optEnd);
    
    maxProduct = max(maxProduct, currentMax);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    cin >> numCities >> numPowerPlants;
    powerPlants.resize(numCities);
    cities.resize(numPowerPlants);
    
    for (int i = 0; i < numCities; ++i) {
        cin >> powerPlants[i].first >> powerPlants[i].second;
    }
    
    for (int i = 0; i < numPowerPlants; ++i) {
        cin >> cities[i].first >> cities[i].second;
    }
    
    sort(powerPlants.begin(), powerPlants.end());
    sort(cities.begin(), cities.end());
    
    for (int i = 0; i < numCities; ++i) {
        if (lowerEnvelope.empty() || lowerEnvelope.back().second > powerPlants[i].second) {
            lowerEnvelope.push_back(powerPlants[i]);
        }
    }
    
    for (int i = 0; i < numPowerPlants; ++i) {
        while (!upperEnvelope.empty() && upperEnvelope.back().second <= cities[i].second) {
            upperEnvelope.pop_back();
        }
        upperEnvelope.push_back(cities[i]);
    }
    
    for (int i = 0; i < lowerEnvelope.size() - 1; ++i) {
        assert(lowerEnvelope[i].first < lowerEnvelope[i + 1].first && lowerEnvelope[i].second > lowerEnvelope[i + 1].second);
    }
    
    for (int i = 0; i < upperEnvelope.size() - 1; ++i) {
        assert(upperEnvelope[i].first < upperEnvelope[i + 1].first && upperEnvelope[i].second > upperEnvelope[i + 1].second);
    }
    
    findMaxProduct(0, lowerEnvelope.size() - 1, 0, upperEnvelope.size() - 1);
    assert(maxProduct >= 0);
    
    cout << maxProduct << '\n';
    
    return 0;
}
