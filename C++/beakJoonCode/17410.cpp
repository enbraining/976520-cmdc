#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

vector<int> blocks[320];
int dataList[100001];

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    int numElements, numQueries, blockSize;
    cin >> numElements;
    for (int i = 0; i < numElements; i++) {
        cin >> dataList[i];
    }

    blockSize = 1000;
    for (int i = 0; i < numElements; i++) {
        blocks[i / blockSize].push_back(dataList[i]);
    }
    for (int i = 0; i < 320; i++) {
        sort(blocks[i].begin(), blocks[i].end());
    }

    int queryType, left, right, value;
    cin >> numQueries;
    while (numQueries--) {
        cin >> queryType;
        if (queryType == 2) {
            cin >> left >> right >> value;
            left--;
            right--;

            int countGreaterThanValue = 0;
            while (left % blockSize && left <= right) {
                if (dataList[left] > value) {
                    countGreaterThanValue++;
                }
                left++;
            }
            while ((right + 1) % blockSize && left <= right) {
                if (dataList[right] > value) {
                    countGreaterThanValue++;
            }
                right--;
            }
            while (left <= right) {
                countGreaterThanValue += (blocks[left / blockSize].end() - upper_bound(blocks[left / blockSize].begin(), blocks[left / blockSize].end(), value));
                left += blockSize;
            }

            cout << countGreaterThanValue << '\n';
        }
        else {
            cin >> left >> value;
            left--;
            blocks[left / blockSize].erase(lower_bound(blocks[left / blockSize].begin(), blocks[left / blockSize].end(), dataList[left]));
            blocks[left / blockSize].insert(lower_bound(blocks[left / blockSize].begin(), blocks[left / blockSize].end(), value), value);
            dataList[left] = value;
        }
    }

    return 0;
}
