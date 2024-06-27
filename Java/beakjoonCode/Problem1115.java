import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in), 1<<16);
        int numberOfElements = Integer.parseInt(bufferedReader.readLine());
        StringTokenizer stringTokenizer = new StringTokenizer(bufferedReader.readLine());
        int[] elementArray = new int[numberOfElements];
        for (int index = 0; index < numberOfElements; index++) {
            elementArray[index] = Integer.parseInt(stringTokenizer.nextToken());
        }
        boolean[] visitedElements = new boolean[numberOfElements];
        int cycleCount = 0;
        for (int currentIndex = 0; currentIndex < numberOfElements; currentIndex++) {
            if (visitedElements[currentIndex]) continue;
            cycleCount++;
            int startIndex = currentIndex;
            while (!visitedElements[startIndex]) {
                visitedElements[startIndex] = true;
                startIndex = elementArray[startIndex];
            }
        }
        System.out.println(cycleCount == 1 ? 0 : cycleCount);
    }
}
