import java.io.*;
import java.util.Arrays;

public class Main {
    private static int numRows;
    private static int numCols;
    private static int[][] seatNumbers;
    private static boolean[][] adjacencyMatrix;
    private static int visitCounter;
    private static int[] visited;
    private static int[] matches;

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
        
        int[][] directions = { { -1, 1 }, { -1, 0 }, { -1, -1 }, { 1, 1 }, { 1, 0 }, { 1, -1 } };
        
        int numCases = Integer.parseInt(reader.readLine());
        
        while (numCases-- > 0) {
            String[] input = reader.readLine().split(" ");
            
            numRows = Integer.parseInt(input[0]);
            numCols = Integer.parseInt(input[1]);
            
            boolean[][] canSit = new boolean[numRows][numCols];
            int seatNumber = 1;
            int numBrokenSeats = 0;
            
            seatNumbers = new int[numRows][numCols];
            adjacencyMatrix = new boolean[numRows * numCols][numRows * numCols];
            
            visitCounter = 1;
            
            for (int row = 0; row < numRows; row++) {
                input = reader.readLine().split("");
                
                for (int col = 0; col < numCols; col++) {
                    seatNumbers[row][col] = seatNumber++;
                    
                    if (input[col].equals(".")) {
                        canSit[row][col] = true;
                    } else {
                        canSit[row][col] = false;
                        numBrokenSeats++;
                    }
                }
            }
            
            for (int row = 0; row < numRows; row++) {
                for (int col = 0; col < numCols; col += 2) {
                    if (canSit[row][col]) {
                        for (int[] direction : directions) {
                            int newRow = row + direction[1];
                            int newCol = col + direction[0];
                            
                            if (newRow > -1 && newCol > -1 && newRow < numRows && newCol < numCols && canSit[newRow][newCol]) {
                                adjacencyMatrix[seatNumbers[row][col] - 1][seatNumbers[newRow][newCol] - 1] = true;
                            }
                        }
                    }
                }
            }
            
            int result = bipartiteMatching();
            
            writer.write(Integer.toString(numRows * numCols - numBrokenSeats - result));
            writer.newLine();
            writer.flush();
        }
        
        writer.close();
        reader.close();
    }
    
    private static int bipartiteMatching() {
        int matchCount = 0;
        
        visited = new int[numRows * numCols];
        matches = new int[numRows * numCols];
        
        Arrays.fill(matches, -1);
        
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col += 2) {
                visitCounter++;
                matchCount += depthFirstSearch(seatNumbers[row][col] - 1);
            }
        }
        
        return matchCount;
    }
    
    private static int depthFirstSearch(int vertex) {
        if (visited[vertex] != visitCounter) {
            visited[vertex] = visitCounter;
            
            for (int i = 0; i < numRows * numCols; i++) {
                if (adjacencyMatrix[vertex][i]) {
                    if (matches[i] == -1 || depthFirstSearch(matches[i]) == 1) {
                        matches[i] = vertex;
                        return 1;
                    }
                }
            }
        }
        
        return 0;
    }
}
