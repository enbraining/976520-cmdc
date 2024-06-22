import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int numberOfElements = scanner.nextInt();
        int[] sequence = new int[numberOfElements];
        int[] longestIncreasingSubsequence = new int[numberOfElements];
        for (int i = 0; i < numberOfElements; i++) {
            sequence[i] = scanner.nextInt();
        }
        longestIncreasingSubsequence[0] = sequence[0];
        int lengthOfLIS = 1;
        for (int i = 1; i < numberOfElements; i++) {
            int currentElement = sequence[i];
            
            if (longestIncreasingSubsequence[lengthOfLIS - 1] < currentElement) {
                lengthOfLIS++;
                longestIncreasingSubsequence[lengthOfLIS - 1] = currentElement;
            } else {
                int low = 0;
                int high = lengthOfLIS;
                while (low < high) {
                    int mid = (low + high) / 2;
                    
                    if (longestIncreasingSubsequence[mid] < currentElement) {
                        low = mid + 1;
                    } else {
                        high = mid;
                    }
                }
                longestIncreasingSubsequence[low] = currentElement;
            }
        }
        System.out.println(lengthOfLIS);
    }
}
