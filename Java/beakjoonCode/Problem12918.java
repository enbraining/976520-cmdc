import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.*;
import java.math.*;
import java.text.DecimalFormat;

public class Main {
    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));

    static class Edge {
        int destination, capacity;
        double cost;

        Edge(int destination, int capacity, double cost) {
            this.destination = destination;
            this.capacity = capacity;
            this.cost = cost;
        }
    }

    static int startNode = 0, endNode = 1, totalNodes;
    static double totalCost = 0;
    static int[][] flowNetwork;
    static ArrayList<Edge>[] graph;
    static final int INFINITY = 1000000000;
    static final int SCALE_FACTOR = (int) Math.pow(10, 8);
    static boolean isFinished = false;
    static int numberOfPoints;

    public static void main(String[] args) throws IOException {
        int numberOfEdges = readIntegerFromInput();
        ArrayList<int[]> leftPoints = new ArrayList<>(), rightPoints = new ArrayList<>();

        for (int i = 0; i < numberOfEdges; i++) {
            int[] edgeInfo = readIntegersFromInput();
            int x = edgeInfo[0];
            if (x == 0) continue;
            if (x > 0) rightPoints.add(edgeInfo);
            else leftPoints.add(edgeInfo);
        }

        int leftPointsSize = leftPoints.size(), rightPointsSize = rightPoints.size();
        numberOfPoints = leftPointsSize + rightPointsSize;
        initializeData();

        for (int i = 0; i < leftPointsSize; i++) {
            int[] leftPointInfo = leftPoints.get(i);
            addEdge(startNode, i + 2, 1, 0);
            addEdge(i + numberOfPoints + 2, endNode, 1, 0);
            addEdge(i + 2, i + numberOfPoints + 2, 1, -leftPointInfo[0]);
            addEdge(i + numberOfPoints + 2, i + 2, 0, leftPointInfo[0]);

            for (int j = 0; j < rightPointsSize; j++) {
                int[] rightPointInfo = rightPoints.get(j);
                int distanceSquared = (leftPointInfo[0] + rightPointInfo[0]) * (leftPointInfo[0] + rightPointInfo[0])
                        + (leftPointInfo[1] - rightPointInfo[1]) * (leftPointInfo[1] - rightPointInfo[1]);
                double distance = Math.sqrt(distanceSquared) / 2;
                distance = (double) Math.round(distance * SCALE_FACTOR) / SCALE_FACTOR;
                int rightNodeIndex = j + leftPointsSize + 2;

                addEdge(i + 2, rightNodeIndex + numberOfPoints, 1, distance);
                addEdge(rightNodeIndex + numberOfPoints, i + 2, 0, -distance);
                addEdge(rightNodeIndex, i + numberOfPoints + 2, 1, distance);
                addEdge(i + numberOfPoints + 2, rightNodeIndex, 0, -distance);
            }
        }

        for (int j = 0; j < rightPointsSize; j++) {
            int[] rightPointInfo = rightPoints.get(j);
            int rightNodeIndex = j + leftPointsSize + 2;

            addEdge(startNode, rightNodeIndex, 1, 0);
            addEdge(rightNodeIndex + numberOfPoints, endNode, 1, 0);
            addEdge(rightNodeIndex, rightNodeIndex + numberOfPoints, 1, rightPointInfo[0]);
            addEdge(rightNodeIndex + numberOfPoints, rightNodeIndex, 0, -rightPointInfo[0]);
        }

        while (!isFinished) {
            performBreadthFirstSearch();
        }

        String result = String.format("%.3f", totalCost);
        writer.write(result);
        writer.flush();
        writer.close();
    }

    static void initializeData() {
        totalNodes = numberOfPoints * 2 + 2;
        flowNetwork = new int[totalNodes][totalNodes];
        graph = new ArrayList[totalNodes];
        for (int i = 0; i < totalNodes; i++) graph[i] = new ArrayList<>();
    }

    static void addEdge(int source, int destination, int capacity, double cost) {
        Edge edge = new Edge(destination, capacity, cost);
        graph[source].add(edge);
    }

    static void performBreadthFirstSearch() {
        boolean[] isInQueue = new boolean[totalNodes];
        double[] edgeCosts = new double[totalNodes];
        int[][] previousNodes = new int[totalNodes][2];

        for (int i = 0; i < totalNodes; i++) edgeCosts[i] = INFINITY;
        edgeCosts[startNode] = 0;

        int currentNode = startNode;
        Deque<Integer> queue = new ArrayDeque<>();
        boolean isEndNodeReached = true;

        while (true) {
            if (currentNode == endNode) isEndNodeReached = false;

            for (Edge edge : graph[currentNode]) {
                if (edge.capacity - flowNetwork[currentNode][edge.destination] <= 0) continue;
                if (edgeCosts[edge.destination] > edgeCosts[currentNode] + edge.cost) {
                    edgeCosts[edge.destination] = edgeCosts[currentNode] + edge.cost;
                    previousNodes[edge.destination][0] = currentNode;
                    previousNodes[edge.destination][1] = edge.capacity;

                    if (isInQueue[edge.destination]) continue;
                    queue.add(edge.destination);
                    isInQueue[edge.destination] = true;
                }
            }

            if (queue.isEmpty()) {
                if (isEndNodeReached) {
                    isFinished = true;
                    return;
                }
                break;
            }

            currentNode = queue.pollFirst();
            isInQueue[currentNode] = false;
        }

        queue.clear();
        currentNode = endNode;

        while (currentNode != startNode) {
            queue.add(currentNode);
            int previousNode = previousNodes[currentNode][0];
            currentNode = previousNode;
        }

        while (currentNode != endNode) {
            int nextNode = queue.pollLast();
            flowNetwork[currentNode][nextNode]++;
            flowNetwork[nextNode][currentNode]--;
            currentNode = nextNode;
        }

        totalCost += edgeCosts[currentNode];
    }

    static String[] readStringArrayFromInput() throws IOException {
        return reader.readLine().split(" ");
    }

    static int readIntegerFromInput() throws IOException {
        return Integer.parseInt(readStringArrayFromInput()[0]);
    }

    static int[] readIntegersFromInput() throws IOException {
        String[] inputStrings = readStringArrayFromInput();
        int[] inputIntegers = new int[inputStrings.length];
        for (int i = 0; i < inputStrings.length; i++)
            inputIntegers[i] = Integer.parseInt(inputStrings[i]);
        return inputIntegers;
    }

    static void writeInteger(long value) throws IOException {
        writer.write(Long.toString(value));
    }


    static void writeNewLine() throws IOException {
        writer.write("\n");
    }
}
