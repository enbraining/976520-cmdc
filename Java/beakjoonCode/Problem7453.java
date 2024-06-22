// 투포인터 쓰기 솔직히 ㅈ같애서 이분탐색으로 해봤는데 이게되네 ;;
// https://www.acmicpc.net/problem/7453

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        int numberOfElements = Integer.parseInt(bufferedReader.readLine());
        int[] arrayA = new int[numberOfElements];
        int[] arrayB = new int[numberOfElements];
        int[] arrayC = new int[numberOfElements];
        int[] arrayD = new int[numberOfElements];
        
        for (int i = 0; i < numberOfElements; i++) {
            StringTokenizer stringTokenizer = new StringTokenizer(bufferedReader.readLine());
            arrayA[i] = Integer.parseInt(stringTokenizer.nextToken());
            arrayB[i] = Integer.parseInt(stringTokenizer.nextToken());
            arrayC[i] = Integer.parseInt(stringTokenizer.nextToken());
            arrayD[i] = Integer.parseInt(stringTokenizer.nextToken());
        }
        
        int[] arrayCDSum = new int[numberOfElements * numberOfElements];
        int index = 0;
        for (int i = 0; i < numberOfElements; i++) {
            for (int j = 0; j < numberOfElements; j++) {
                arrayCDSum[index++] = arrayC[i] + arrayD[j];
            }
        }
        
        Arrays.sort(arrayCDSum);
        
        long totalPairs = 0;
        for (int i = 0; i < numberOfElements; i++) {
            for (int j = 0; j < numberOfElements; j++) {
                int targetSum = arrayA[i] + arrayB[j];
                int upperBoundIndex = findUpperBound(-targetSum, arrayCDSum);
                int lowerBoundIndex = findLowerBound(-targetSum, arrayCDSum);
                totalPairs += (upperBoundIndex - lowerBoundIndex);
            }
        }
        
        System.out.println(totalPairs);
    }
    
    static int findUpperBound(int key, int[] array) {
        int start = 0;
        int end = array.length - 1;
        while (start <= end) {
            int mid = (start + end) / 2;
            if (array[mid] > key) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        return end;
    }
    
    static int findLowerBound(int key, int[] array) {
        int start = 0;
        int end = array.length - 1;
        while (start <= end) {
            int mid = (start + end) / 2;
            if (array[mid] >= key) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        return end;
    }
}
