import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer stringTokenizer;
        StringBuilder stringBuilder = new StringBuilder();

        int N = Integer.parseInt(bufferedReader.readLine());
        int SIZE = 1000001;
        int[] players = new int[N];
        boolean[] hasCard = new boolean[SIZE];
        int[] scores = new int[SIZE];
        stringTokenizer = new StringTokenizer(bufferedReader.readLine());
        for (int i = 0; i < N; ++i) {
            players[i] = Integer.parseInt(stringTokenizer.nextToken());
            hasCard[players[i]] = true;
        }

        for (int player : players) {
            for (int j = player * 2; j < SIZE; j += player) {
                if (hasCard[j]) {
                    ++scores[player];
                    --scores[j];
                }
            }
        }

        for (int num : players)
            stringBuilder.append(scores[num]).append(' ');
        
        System.out.println(stringBuilder.toString());
    }
}
