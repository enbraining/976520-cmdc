#include <bits/stdc++.h>
using namespace std;


struct Line {
    long long slope, yIntercept;
    long long evaluate(long long x) {
        return slope * x + yIntercept;
    }
    long double calculateIntersectionX(Line otherLine) {
        return static_cast<long double>(yIntercept - otherLine.yIntercept) / (otherLine.slope - slope);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int numberOfElements;
    cin >> numberOfElements;
    long long coefficientA, coefficientB, coefficientC;
    cin >> coefficientA >> coefficientB >> coefficientC;
    vector<long long> elements(numberOfElements + 1, 0), prefixSum(numberOfElements + 1, 0);

    for (int index = 1; index <= numberOfElements; ++index) {
        cin >> elements[index];
        prefixSum[index] = elements[index] + prefixSum[index - 1];
    }

    deque<Line> convexHullTrickDeque;
    convexHullTrickDeque.push_front({ 0, 0 });
    long long maximumValue = 0;

    for (int index = 1; index <= numberOfElements; ++index) {
        while (convexHullTrickDeque.size() >= 2 &&
            convexHullTrickDeque[0].evaluate(prefixSum[index]) <= convexHullTrickDeque[1].evaluate(prefixSum[index])) {
            convexHullTrickDeque.pop_front();
        }

        maximumValue = convexHullTrickDeque.front().evaluate(prefixSum[index]);

        Line newLine = {
            -2LL * coefficientA * prefixSum[index],
            coefficientA * prefixSum[index] * prefixSum[index] - coefficientB * prefixSum[index] + maximumValue +
            coefficientA * prefixSum[index] * prefixSum[index] + coefficientB * prefixSum[index] + coefficientC
        };

        while (convexHullTrickDeque.size() >= 2 &&
            newLine.calculateIntersectionX(convexHullTrickDeque.back()) <=
            convexHullTrickDeque.back().calculateIntersectionX(convexHullTrickDeque[convexHullTrickDeque.size() - 2])) {
            convexHullTrickDeque.pop_back();
        }

        convexHullTrickDeque.push_back(newLine);
    }

    cout << maximumValue + coefficientA * prefixSum[numberOfElements] * prefixSum[numberOfElements] +
        coefficientB * prefixSum[numberOfElements] + coefficientC << '\n';

    return 0;
}
