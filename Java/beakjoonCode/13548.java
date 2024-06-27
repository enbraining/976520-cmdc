import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

class 쿼리 implements Comparable<쿼리> {
    int 시작, 끝, 인덱스, 비교인자;
    static int sqrtN;
    public static void sqrtN설정(int n) { sqrtN = (int)Math.sqrt(n); }
    public 쿼리(int 시작, int 끝, int 인덱스) {
        this.시작 = 시작;
        this.끝 = 끝;
        this.인덱스 = 인덱스;
        this.비교인자 = this.시작/sqrtN;
    }
    @Override
    public int compareTo(쿼리 o) {
        if (this.비교인자 == o.비교인자)
            return this.끝 - o.끝;
        return this.비교인자 - o.비교인자;
    }
}
public class Main {
    int[] 빈도 = new int[100010];
    int[] 버킷 = new int[100010];
    int 최대값 = 0;
    private void 추가(int 숫자) {
        버킷[빈도[숫자]]--;
        if (++버킷[++빈도[숫자]] == 1 && 빈도[숫자] > 최대값) 최대값 = 빈도[숫자];
    }
    private void 제거(int 숫자) {
        if (--버킷[빈도[숫자]] == 0 && 최대값 == 빈도[숫자]) 최대값--;
        버킷[--빈도[숫자]]++;
    }
    private void 해결() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        쿼리.sqrtN설정(n);
        int[] 배열 = new int[n + 1];
        StringTokenizer st = new StringTokenizer(br.readLine());
        for (int i = 1; i <= n; i++) 배열[i] = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(br.readLine());
        쿼리[] 쿼리들 = new 쿼리[m];
        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            쿼리들[i] = new 쿼리(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), i);
        }
        Arrays.sort(쿼리들);
        for (int i = 쿼리들[0].시작; i <= 쿼리들[0].끝; i++) 추가(배열[i]);
        int[] 답배열 = new int[m];
        답배열[쿼리들[0].인덱스] = 최대값;
        int 시작 = 쿼리들[0].시작;
        int 끝 = 쿼리들[0].끝;
        for (int i = 1; i < m; i++) {
            쿼리 q = 쿼리들[i];
            for (int x = q.시작; x < 시작; x++) 추가(배열[x]);
            for (int x = 끝 + 1; x <= q.끝; x++) 추가(배열[x]);
            for (int x = 시작; x < q.시작; x++) 제거(배열[x]);
            for (int x = q.끝 + 1; x <= 끝; x++) 제거(배열[x]);
            시작 = q.시작;
            끝 = q.끝;
            답배열[q.인덱스] = 최대값;
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < m; i++) sb.append(답배열[i]).append('\n');
        System.out.print(sb);
    }
    public static void main(String[] args) throws Exception {
        new Main().해결();
    }
}
