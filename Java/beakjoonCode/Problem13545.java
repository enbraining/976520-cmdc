import java.util.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    static int[] array, answerArray, prefixSum;
    static int sqrtN;

    static class Query implements Comparable<Query> {
        final int left;
        final int right;
        final int index;
        final int group;

        Query(int left, int right, int index) {
            this.left = left;
            this.right = right;
            this.index = index;
            this.group = left / sqrtN;
        }

        @Override
        public int compareTo(Query otherQuery) {
            if (this.group == otherQuery.group)
                return this.right - otherQuery.right;
            return this.group - otherQuery.group;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer tokenizer = new StringTokenizer(bufferedReader.readLine());
        int numberOfElements = parseInt(tokenizer.nextToken());
        int maxPrefixSumValue = 100_000 * 2; 
        sqrtN = (int) Math.sqrt(numberOfElements);
        array = new int[numberOfElements];
        prefixSum = new int[numberOfElements + 1];
        tokenizer = new StringTokenizer(bufferedReader.readLine());
        for (int i = 0; i < numberOfElements; i++) {
            array[i] = parseInt(tokenizer.nextToken());
            prefixSum[i + 1] = prefixSum[i] + array[i];
        }

        int numberOfQueries = parseInt(bufferedReader.readLine());
        List<Query> queryList = new ArrayList<>();
        answerArray = new int[numberOfQueries];
        for (int i = 0; i < numberOfQueries; i++) {
            tokenizer = new StringTokenizer(bufferedReader.readLine());
            int left = parseInt(tokenizer.nextToken()) - 1;
            int right = parseInt(tokenizer.nextToken());
            queryList.add(new Query(left, right, i));
        }

        Collections.sort(queryList);

        int[] minimumIndex = null, maximumIndex = null, maximumIndexInLeftGroup = new int[maxPrefixSumValue + 1];
        Arrays.fill(maximumIndexInLeftGroup, 0);
        int previousRight = 0, previousGroup = -1, previousAnswer = 0;

        for (Query query : queryList) {
            int left = query.left, right = query.right, group = query.group;
            int groupEnd = (group + 1) * sqrtN;

            if (group > previousGroup) {
                previousAnswer = 0;
                previousRight = 0;
                minimumIndex = new int[maxPrefixSumValue + 1];
                maximumIndex = new int[maxPrefixSumValue + 1];
                Arrays.fill(minimumIndex, numberOfElements);
                Arrays.fill(maximumIndex, 0);
            }

            for (int i = Math.max(groupEnd, previousRight); i <= right; i++) {
                int index = getPrefixSumIndex(i);
                minimumIndex[index] = Math.min(i, minimumIndex[index]);
                maximumIndex[index] = Math.max(i, maximumIndex[index]);

                previousAnswer = Math.max(previousAnswer, maximumIndex[index] - minimumIndex[index]);
            }

            int answer = previousAnswer;

            for (int i = Math.min(groupEnd - 1, right); i >= left; i--) {
                int index = getPrefixSumIndex(i);

                maximumIndexInLeftGroup[index] = Math.max(i, maximumIndexInLeftGroup[index]);
                answer = Math.max(Math.max(maximumIndex[index], maximumIndexInLeftGroup[index]) - i, answer);
            }
            answerArray[query.index] = answer;
            previousGroup = group;
            previousRight = right;
        }

        StringBuilder resultStringBuilder = new StringBuilder();

        for (int answer : answerArray) {
            resultStringBuilder.append(answer);
            resultStringBuilder.append("\n");
        }

        System.out.print(resultStringBuilder);
    }

    static int getPrefixSumIndex(int index) {
        return prefixSum[index] + 100_000;
    }

    static int parseInt(String string) {
        return Integer.parseInt(string);
    }
}
