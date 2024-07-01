#include <cstdio>
#include <algorithm>
#define x first
#define y second
using namespace std;

const int MAX_POINTS = 2000;

int numPoints, maxOverlap;
pair<long long, long long> origin;

struct Segment {
    pair<long long, long long> point;
    int value;
    
    bool operator<(const Segment& other) const {
        long long crossProduct = (point.x - origin.x) * (other.point.y - origin.y) - (point.y - origin.y) * (other.point.x - origin.x);
        return crossProduct < 0 || (!crossProduct && value > other.value);
    }
};

Segment segments[MAX_POINTS * 2], sortedSegments[MAX_POINTS * 2];

int main() {
    scanf("%d", &numPoints);
    
    for (int i = 0, x0, x1, y; i < numPoints; i++) {
        scanf("%d%d%d", &x0, &x1, &y);
        segments[i] = { {min(x0, x1), y}, abs(x0 - x1) };
        segments[i + numPoints] = { {max(x0, x1), y}, -abs(x0 - x1) };
    }
    
    for (int i = 0; i < numPoints; i++) {
        int segmentCount = 0;
        int sum = segments[i].value;
        origin = segments[i].point;
        
        for (int j = 0; j < 2 * numPoints; j++) {
            if (origin.y < segments[j].point.y) {
                sortedSegments[segmentCount++] = segments[j];
            }
            if (origin.y > segments[j].point.y) {
                sortedSegments[segmentCount++] = { {2 * origin.x - segments[j].point.x, 2 * origin.y - segments[j].point.y}, -segments[j].value };
            }
        }
        
        sort(sortedSegments, sortedSegments + segmentCount);
        
        for (int j = 0; j < segmentCount; j++) {
            maxOverlap = max(maxOverlap, sum += sortedSegments[j].value);
        }
        maxOverlap = max(maxOverlap, sum);
    }
    
    printf("%d", maxOverlap);
}
