import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class airconditioned {
    // greedy solution
    static int solve(int[][] minions) {
        Arrays.sort(minions, (x, y) -> x[0] - y[0]);
        int count = 0;
        int e = minions[0][1];
        for (int i = 0; i < minions.length; i ++) {
            int[] m = minions[i];
            if (m[0] > e) {
                count += 1;
                e = m[1];
            } else {
                e = Math.min(e, m[1]);
            }
        }
        count += 1;
        return count;
    }

    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int size = 0;
        try {
            size = Integer.parseInt(br.readLine());
        } catch (IOException e) {}

        
        int[][] minions = new int[size][2];
        for (int i = 0; i < size; i ++) {
            String[] data = null;
            try {
                data = br.readLine().split(" ");
                minions[i][0] = Integer.parseInt(data[0]);
                minions[i][1] = Integer.parseInt(data[1]);
            } catch (IOException e) {}
        }
        int ans = solve(minions);
        System.out.println(ans);
    }
}
