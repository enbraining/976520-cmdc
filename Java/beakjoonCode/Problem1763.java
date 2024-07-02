import java.util.*;
import java.io.*;

public class Main {
    static int numberOfNodes, rootNode;
    static double[] nodeCosts, nodeCounts;
    static int[] parentNodes;
    static ArrayList<Integer>[] adjacencyList;
    static boolean[] visitedNodes;

    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer stringTokenizer = new StringTokenizer(bufferedReader.readLine());

        numberOfNodes = parseInteger(stringTokenizer.nextToken());
        rootNode = parseInteger(stringTokenizer.nextToken());

        initializeVariables();
        
        stringTokenizer = new StringTokenizer(bufferedReader.readLine());
        for (int i = 1; i <= numberOfNodes; i++) {
            nodeCounts[i] = 1;
            nodeCosts[i] = parseInteger(stringTokenizer.nextToken());
        }

        int nodeU, nodeV;
        for (int i = 1; i < numberOfNodes; i++) {
            stringTokenizer = new StringTokenizer(bufferedReader.readLine());
            nodeU = parseInteger(stringTokenizer.nextToken());
            nodeV = parseInteger(stringTokenizer.nextToken());
            adjacencyList[nodeU].add(nodeV);
            parentNodes[nodeV] = nodeU;
        }
        System.out.println(calculateMinimumCost());
    }

    private static int calculateMinimumCost() {
        int parentNode, currentNode, totalCost = 0;
        for (int i = 0; i < numberOfNodes - 1; i++) {
            currentNode = findNodeWithMaximumCost();
            parentNode = findRootNode(parentNodes[currentNode]);
            visitedNodes[currentNode] = true;

            totalCost += nodeCosts[currentNode] * nodeCounts[parentNode];
            updateNodeCostsAndCounts(currentNode, parentNode);
        }
        return (int) (totalCost + nodeCosts[rootNode]);
    }

    private static int findRootNode(int node) {
        return visitedNodes[node] ? parentNodes[node] = findRootNode(parentNodes[node]) : node;
    }

    private static int findNodeWithMaximumCost() {
        int maxCostNodeIndex = -1;
        double maxCost = Double.MIN_VALUE;
        for (int i = 1; i <= numberOfNodes; i++) {
            if (!visitedNodes[i] && i != rootNode && maxCost < (double) (nodeCosts[i] / nodeCounts[i])) {
                maxCost = (double) (nodeCosts[i] / nodeCounts[i]);
                maxCostNodeIndex = i;
            }
        }
        return maxCostNodeIndex;
    }

    private static void updateNodeCostsAndCounts(int childNode, int parentNode) {
        nodeCounts[parentNode] += nodeCounts[childNode];
        nodeCosts[parentNode] += nodeCosts[childNode];
        parentNodes[childNode] = parentNode;
    }

    private static void initializeVariables() {
        nodeCounts = new double[numberOfNodes + 1];
        nodeCosts = new double[numberOfNodes + 1];
        parentNodes = new int[numberOfNodes + 1];
        visitedNodes = new boolean[numberOfNodes + 1];
        adjacencyList = new ArrayList[numberOfNodes + 1];
        for (int i = 1; i <= numberOfNodes; i++) {
            adjacencyList[i] = new ArrayList<>();
        }
    }

    private static int parseInteger(String input) {
        return Integer.parseInt(input);
    }
}
