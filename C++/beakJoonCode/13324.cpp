#include <cstdio>
#include <queue>
using namespace std;

int num_elements, index, element, result[1000001];
priority_queue<int> max_heap;

int main() {
    scanf("%d", &num_elements);
    for (index = 1; index <= num_elements; index++) {
        scanf("%d", &element);
        element -= index;
        max_heap.push(element);
        max_heap.push(element);
        max_heap.pop();
        result[index] = max_heap.top();
    }

    --index;
    while (--index) {
        if (result[index] > result[index + 1]) {
            result[index] = result[index + 1];
        }
    }

    for (index = 1; index <= num_elements; index++) {
        printf("%d\n", result[index] + index);
    }

    return 0;
}
