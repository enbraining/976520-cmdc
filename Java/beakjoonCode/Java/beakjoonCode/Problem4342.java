import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    static StringBuilder answer = new StringBuilder();
    static Reader scanner = new Reader();
    static int maxNum;
    static int minNum;

    static boolean input() {
        int num1 = scanner.nextInt();
        int num2 = scanner.nextInt();
        if (num1 == 0 && num2 == 0) {
            return false;
        }
        maxNum = Math.max(num1, num2);
        minNum = Math.min(num1, num2);
        return true;
    }
    static void solution() {
        if (gcd(maxNum, minNum)) {
            answer.append("A wins").append('\n');
            return;
        }
        answer.append("B wins").append('\n');
    }

    static boolean gcd(int max, int min) {
        if (max % min == 0) {
            return true;
        }
        if (max - min < min) {
            return !gcd(Math.max(max - min, min), Math.min(max - min, min));
        }
        return true;
    }

    public static void main(String[] args) {
        while (true) {
            if (!input()) {
                break;
            }
            solution();
        }

        System.out.print(answer);
    }

    static class Reader {
        BufferedReader br;
        StringTokenizer st;

        public Reader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}