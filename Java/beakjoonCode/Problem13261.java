import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int numRooms = Integer.parseInt(st.nextToken()); 
        int numGuards = Integer.parseInt(st.nextToken()); 

        long[] cumulativeCost = new long[numRooms + 1]; 
        long[][] dp = new long[numGuards + 1][numRooms + 1];

        st = new StringTokenizer(br.readLine());
        cumulativeCost[1] = Long.parseLong(st.nextToken());
        for (int i = 2; i <= numRooms; i++) {
            cumulativeCost[i] = Long.parseLong(st.nextToken()) + cumulativeCost[i - 1];
        }

        for (int room = 1; room <= numRooms; room++) {
            dp[1][room] = calculateCost(1, room, cumulativeCost);
        }

        for (int guard = 2; guard <= numGuards; guard++) {
            solveDP(guard, 1, numRooms, 1, numRooms, dp, cumulativeCost);
        }
        System.out.println(dp[numGuards][numRooms]);
    }

    static void solveDP(int guard, int roomLow, int roomHigh, int prisonerLow, int prisonerHigh, long[][] dp, long[] cumulativeCost) {
        if (roomLow > roomHigh || prisonerLow > prisonerHigh) return;

        int roomMid = (roomLow + roomHigh) >> 1;
        int optPrisoner = prisonerLow;
        for (int prisoner = prisonerLow; prisoner <= Math.min(prisonerHigh, roomMid); prisoner++) {
            long cost = dp[guard - 1][prisoner] + calculateCost(prisoner + 1, roomMid, cumulativeCost);
            if (prisoner == prisonerLow || cost < dp[guard][roomMid]) {
                dp[guard][roomMid] = cost;
                optPrisoner = prisoner;
            }
        }
        solveDP(guard, roomLow, roomMid - 1, prisonerLow, optPrisoner, dp, cumulativeCost);
        solveDP(guard, roomMid + 1, roomHigh, optPrisoner, prisonerHigh, dp, cumulativeCost);
    }

    static long calculateCost(int start, int end, long[] cumulativeCost) {
        return (end - start + 1) * (cumulativeCost[end] - cumulativeCost[start - 1]);
    }
}
