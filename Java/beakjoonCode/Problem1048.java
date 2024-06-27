import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    private static final BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in), 1 << 16);
    private static final int MODULO = 1_000_000_007;
    private int rows, columns;

    public void solution() throws Exception {
        StringTokenizer stringTokenizer = new StringTokenizer(bufferedReader.readLine());
        rows = Integer.parseInt(stringTokenizer.nextToken());
        columns = Integer.parseInt(stringTokenizer.nextToken());
        int limit = Integer.parseInt(stringTokenizer.nextToken());

        String baseString = bufferedReader.readLine();
        int baseLength = baseString.length();
        if (isInvalid(limit, baseString, baseLength)) {
            System.out.println(0);
            return;
        }

        long[][][] dp = new long[baseLength][rows + 1][columns + 1];
        char[][] map = new char[rows + 1][columns + 1];
        initializeMapAndDp(rows, columns, baseString, dp, map);

        for (int k = 1; k < baseLength; k++) {
            for (int i = 1; i <= rows; i++) {
                for (int j = 1; j <= columns; j++) {
                    if (map[i][j] != baseString.charAt(k)) continue;
                    dp[k][i][j] = countCases(dp[k - 1], i, j);
                }
            }

            for (int i = 1; i <= rows; i++) {
                for (int j = 1; j <= columns; j++) {
                    dp[k][i][j] += dp[k][i - 1][j] + dp[k][i][j - 1] - dp[k][i - 1][j - 1];
                    dp[k][i][j] = positiveModuloResult(dp[k][i][j]);
                }
            }
        }
        System.out.println(dp[baseLength - 1][rows][columns]);
    }

    private boolean isInvalid(int limit, String baseString, int baseLength) {
        for (int i = 0; i < baseLength; i++) {
            if (baseString.charAt(i) - 'A' + 1 > limit) {
                return true;
            }
        }
        return false;
    }

    private void initializeMapAndDp(int rows, int columns, String baseString, long[][][] dp, char[][] map) throws Exception {
        for (int i = 0; i < rows; i++) {
            String row = bufferedReader.readLine();
            for (int j = 0; j < columns; j++) {
                map[i + 1][j + 1] = row.charAt(j);
                dp[0][i + 1][j + 1] = (map[i + 1][j + 1] == baseString.charAt(0) ? 1 : 0) + dp[0][i][j + 1] + dp[0][i + 1][j] - dp[0][i][j];
            }
        }
    }

    private long countCases(long[][] previousDp, int row, int column) {
        long result = previousDp[rows][columns];
        result -= get2dRangeSum(previousDp, row - 1, 1, row + 1, columns);
        result -= get2dRangeSum(previousDp, 1, column - 1, rows, column + 1);
        result += get2dRangeSum(previousDp, row - 1, column - 1, row + 1, column + 1);

        result -= get2dRangeSum(previousDp, row - 2, column - 2, row - 2, column - 2);
        result -= get2dRangeSum(previousDp, row + 2, column - 2, row + 2, column - 2);
        result -= get2dRangeSum(previousDp, row - 2, column + 2, row - 2, column + 2);
        result -= get2dRangeSum(previousDp, row + 2, column + 2, row + 2, column + 2);

        return positiveModuloResult(result);
    }

    private long get2dRangeSum(long[][] array, int row1, int column1, int row2, int column2) {
        if (row1 == row2 && column1 == column2 && (row1 <= 0 || row1 > rows || column1 <= 0 || column1 > columns)) return 0;

        if (row1 == 0) row1 = 1;
        if (row1 == rows + 1) row1 = rows;
        if (row2 == 0) row2 = 1;
        if (row2 == rows + 1) row2 = rows;
        if (column1 == 0) column1 = 1;
        if (column1 == columns + 1) column1 = columns;
        if (column2 == 0) column2 = 1;
        if (column2 == columns + 1) column2 = columns;

        long result = array[row2][column2] - array[row1 - 1][column2] - array[row2][column1 - 1] + array[row1 - 1][column1 - 1];

        return positiveModuloResult(result);
    }

    private long positiveModuloResult(long value) {
        while (value < 0) value += MODULO;
        return value % MODULO;
    }

    public static void main(String[] args) throws Exception {
        new Main().solution();
    }
}
