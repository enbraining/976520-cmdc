#include <bits/stdc++.h>
using namespace std;

struct BinaryTrie {
private:
	struct TrieNode { 
		int next[2]{}, count = 0; 
	};
	vector<TrieNode> nodes;
public:
	BinaryTrie() : nodes(1) {}
	void Insert(int value) {
		int currentNode = 0;
		for (int bitPosition = 30; bitPosition-- > 0;) {
			const bool bitIsSet = value & (1 << bitPosition);
			if (!nodes[currentNode].next[bitIsSet]) {
				nodes[currentNode].next[bitIsSet] = nodes.size();
				nodes.push_back(TrieNode());
			}
			currentNode = nodes[currentNode].next[bitIsSet];
			nodes[currentNode].count++;
		}
	}
	int FindMinXOR(int value) const {
		int result = 0, currentNode = 0;
		for (int bitPosition = 30; bitPosition-- > 0;) {
			const bool bitIsSet = value & (1 << bitPosition);
			if (nodes[nodes[currentNode].next[bitIsSet]].count) {
				result = result << 1;
				currentNode = nodes[currentNode].next[bitIsSet];
			}
			else {
				result = result << 1 | 1;
				currentNode = nodes[currentNode].next[!bitIsSet];
			}
		}
		return result;
	}
};

int numberOfElements, elementsArray[200'000];

long long DepthFirstSearch(int leftIndex, int rightIndex, int bitDepth) {
	if (bitDepth < 0 || rightIndex <= leftIndex) return 0;
	if (elementsArray[leftIndex] & (1 << bitDepth) || ~elementsArray[rightIndex] & (1 << bitDepth)) 
        return DepthFirstSearch(leftIndex, rightIndex, bitDepth - 1);
	int minimumXOR = INT_MAX, partitionIndex = rightIndex; 
    BinaryTrie trie;
	while (elementsArray[partitionIndex] & (1 << bitDepth)) 
        trie.Insert(elementsArray[partitionIndex--]);
	for (int i = leftIndex; i <= partitionIndex; i++) 
        minimumXOR = min(minimumXOR, trie.FindMinXOR(elementsArray[i]));
	return minimumXOR + DepthFirstSearch(leftIndex, partitionIndex, bitDepth - 1) + DepthFirstSearch(partitionIndex + 1, rightIndex, bitDepth - 1);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> numberOfElements;
	for (int i = 0; i < numberOfElements; i++) 
        cin >> elementsArray[i];
	sort(elementsArray, elementsArray + numberOfElements);
	cout << DepthFirstSearch(0, numberOfElements - 1, 29) << '\n';
}
