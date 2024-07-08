#include <bits/stdc++.h>
using namespace std;


inline int readNextChar();
template<class T = int> inline T readNextInt();
template<class T> inline void writeInt(T value, char endChar = 0);
inline void writeSingleChar(int character);
inline void writeString(const char* str);
static const int BUFFER_SIZE = 1 << 18;

inline int getNextChar() {
    static char buffer[BUFFER_SIZE];
    static int length = 0, position = 0;
    if (position == length) {
        position = 0;
        length = fread(buffer, 1, BUFFER_SIZE, stdin);
    }
    if (position == length) {
        return -1;
    }
    return buffer[position++];
}

inline int readNextChar() {
    int character = getNextChar();
    while (character <= 32) {
        character = getNextChar();
    }
    return character;
}

template <class T>
inline T readNextInt() {
    int sign = 1, character = readNextChar();
    T result = 0;
    if (character == '-') {
        sign = -1;
        character = getNextChar();
    }
    while ('0' <= character && character <= '9') {
        result = result * 10 + character - '0';
        character = getNextChar();
    }
    return sign == 1 ? result : -result;
}

static int writePosition = 0;
static char writeBuffer[BUFFER_SIZE];

inline void writeSingleChar(int character) {
    if (writePosition == BUFFER_SIZE) {
        fwrite(writeBuffer, 1, BUFFER_SIZE, stdout);
        writePosition = 0;
    }
    writeBuffer[writePosition++] = character;
}

template <class T>
inline void writeInt(T value, char endChar) {
    if (value < 0) {
        writeSingleChar('-');
        value = -value;
    }
    char str[24];
    int length = 0;
    while (value || !length) {
        str[length++] = '0' + value % 10;
        value /= 10;
    }
    while (length--) {
        writeSingleChar(str[length]);
    }
    if (endChar) {
        writeSingleChar(endChar);
    }
}

inline void writeString(const char* str) {
    while (*str) {
        writeSingleChar(*str++);
    }
}

struct Flusher {
    ~Flusher() {
        if (writePosition) {
            fwrite(writeBuffer, 1, writePosition, stdout);
            writePosition = 0;
        }
    }
} flusher;

struct SegmentTreeNode {
    long long minValue, maxValue, sumValue, tempValue;
    SegmentTreeNode() : minValue(0), maxValue(0), sumValue(0), tempValue(0) {}
    SegmentTreeNode(long long value) : minValue(value), maxValue(value), sumValue(value), tempValue(0) {}

    void push(SegmentTreeNode& node, long long value) {
        if (minValue == maxValue) {
            node.minValue = node.maxValue = minValue;
            node.tempValue = 0;
            node.sumValue = minValue * value;
        }
        else {
            node.minValue += tempValue;
            node.maxValue += tempValue;
            node.tempValue += tempValue;
            node.sumValue += tempValue * value;
        }
    }
};

const int MAX_SIZE = 1 << 17;

struct SegmentTree {
    SegmentTreeNode tree[1 << 18];

    void merge(int leftChild, int rightChild, int parent) {
        tree[parent].minValue = min(tree[leftChild].minValue, tree[rightChild].minValue);
        tree[parent].maxValue = max(tree[leftChild].maxValue, tree[rightChild].maxValue);
        tree[parent].sumValue = tree[leftChild].sumValue + tree[rightChild].sumValue;
        tree[parent].tempValue = 0;
    }

    void push(int node, long long value) {
        tree[node].push(tree[node << 1], (value + 1) >> 1);
        tree[node].push(tree[node << 1 | 1], value >> 1);
    }

    void initialize(int node, int start, int end, const vector<int>& array) {
        if (start == end) {
            tree[node] = SegmentTreeNode(array[start]);
            return;
        }
        int mid = (start + end) >> 1;
        initialize(node << 1, start, mid, array);
        initialize(node << 1 | 1, mid + 1, end, array);
        merge(node << 1, node << 1 | 1, node);
    }

    void update(int node, int start, int end, int left, int right, long long value) {
        if (right < start || end < left) {
            return;
        }
        if (left <= start && end <= right) {
            if (!value && tree[node].maxValue == 0) {
                return;
            }
            long long minValueSqrt = sqrt(tree[node].minValue);
            long long maxValueSqrt = sqrt(tree[node].maxValue);
            if (!value && minValueSqrt == maxValueSqrt) {
                tree[node].minValue = tree[node].maxValue = minValueSqrt;
                tree[node].tempValue = 0;
                tree[node].sumValue = minValueSqrt * (end - start + 1);
                return;
            }
            else if (!value && tree[node].maxValue - tree[node].minValue == 1) {
                value = minValueSqrt - tree[node].minValue;
            }
            if (value) {
                tree[node].minValue += value;
                tree[node].maxValue += value;
                tree[node].tempValue += value;
                tree[node].sumValue += value * (end - start + 1);
                return;
            }
        }
        int mid = (start + end) >> 1;
        push(node, end - start + 1);
        if (start <= right) {
            update(node << 1, start, mid, left, right, value);
        }
        if (left <= end) {
            update(node << 1 | 1, mid + 1, end, left, right, value);
        }
        merge(node << 1, node << 1 | 1, node);
    }

    long long query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) {
            return 0;
        }
        int mid = (start + end) >> 1;
        push(node, end - start + 1);
        long long result = 0;
        if (left <= start && mid <= right) {
            result += tree[node << 1].sumValue;
        }
        else if (start <= right) {
            result += query(node << 1, start, mid, left, right);
        }
        if (left <= mid + 1 && end <= right) {
            result += tree[node << 1 | 1].sumValue;
        }
        else if (left <= end) {
            result += query(node << 1 | 1, mid + 1, end, left, right);
        }
        merge(node << 1, node << 1 | 1, node);
        return result;
    }
} segmentTree;

void solve() {
    int numNodes = readNextInt();
    int numQueries = readNextInt();
    vector<int> array(numNodes + 1);
    for (int i = 1; i <= numNodes; i++) {
        array[i] = readNextInt();
    }
    segmentTree.initialize(1, 1, numNodes, array);
    while (numQueries--) {
        int operation = readNextInt();
        int left = readNextInt();
        int right = readNextInt();
        int value;
        if (operation == 1) {
            segmentTree.update(1, 1, numNodes, left, right, 0);
        }
        else if (operation == 3) {
            value = readNextInt();
            segmentTree.update(1, 1, numNodes, left, right, value);
        }
        else {
            writeInt(segmentTree.query(1, 1, numNodes, left, right), '\n');
        }
    }
}

int main() {
    int numTestCases = readNextInt();
    for (int i = 1; i <= numTestCases; i++) {
        solve();
    }
    Flusher();
}
