import java.io.*;
import java.util.*;

public class Main {
    static final int ALPHABET_SIZE = 26;
    static class TrieNode {
        boolean isWordEnd;
        Map<Character, TrieNode> childNodes = new HashMap<>();
        TrieNode failNode;

        public void insert(String word) {
            TrieNode currentNode = this;
            for (int i = 0; i < word.length(); i++) {
                char c = word.charAt(i);

                currentNode.childNodes.putIfAbsent(c, new TrieNode());
                currentNode = currentNode.childNodes.get(c);

                if (i == word.length() - 1) {
                    currentNode.isWordEnd = true;
                }
            }
        }

        public void computeFailFunction() {
            Queue<TrieNode> queue = new LinkedList<>();
            this.failNode = this;
            queue.add(this);

            while (!queue.isEmpty()) {
                TrieNode currentNode = queue.poll();
                for (int i = 0; i < ALPHABET_SIZE; i++) {
                    char c = (char)(i + 'a');

                    TrieNode nextNode = currentNode.childNodes.get(c);
                    if (nextNode == null) continue;

                    if (currentNode == this) {
                        nextNode.failNode = this;
                    } else {
                        TrieNode failLinkNode = currentNode.failNode;
                        while (failLinkNode != this && failLinkNode.childNodes.get(c) == null) {
                            failLinkNode = failLinkNode.failNode;
                        }
                        if (failLinkNode.childNodes.get(c) != null) {
                            failLinkNode = failLinkNode.childNodes.get(c);
                        }
                        nextNode.failNode = failLinkNode;
                    }

                    if (nextNode.failNode.isWordEnd) {
                        nextNode.isWordEnd = true;
                    }
                    queue.add(nextNode);
                }
            }
        }

        public boolean ahoCorasick(String word) {
            TrieNode currentNode = this;
            for (int i = 0; i < word.length(); i++) {
                char c = word.charAt(i);
                while (currentNode != this && currentNode.childNodes.get(c) == null) {
                    currentNode = currentNode.failNode;
                }
                if (currentNode.childNodes.get(c) != null) {
                    currentNode = currentNode.childNodes.get(c);
                }

                if (currentNode.isWordEnd) {
                    return true;
                }
            }
            return false;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());

        TrieNode trieSet = new TrieNode();
        for (int i = 0; i < n; i++) {
            trieSet.insert(br.readLine());
        }

        trieSet.computeFailFunction();

        StringBuilder sb = new StringBuilder();
        int q = Integer.parseInt(br.readLine());
        for (int i = 0; i < q; i++) {
            if (trieSet.ahoCorasick(br.readLine())) {
                sb.append("YES\n");
            } else {
                sb.append("NO\n");
            }
        }
        System.out.println(sb.toString());
    }
}
