import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class adventuresMoving4 {
    Integer[][] dp;

    int helper(int i, int fuel, ArrayList<Integer> stations, ArrayList<Integer> prices, int distance) {
        if (fuel < 0 || fuel > 200) {
            return 20000001;
        } else if (i == stations.size() - 1) {
            return (fuel >= 100) ? 0 : 20000001;
        } else if (dp[i][fuel] != null) {
            return dp[i][fuel];
        } else {
            int topUp = prices.get(i) + helper(i, fuel + 1, stations, prices, distance);
            int goNext = helper(i + 1, fuel - (stations.get(i + 1) - stations.get(i)), stations, prices, distance);
            int ans = Math.min(topUp, goNext);
            dp[i][fuel] = ans;
            return ans;
        }
    }

    public static void main(String[] args) {
        adventuresMoving4 sol = new adventuresMoving4();
        sol.dp = new Integer[101][201];
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int distance = 0;
        ArrayList<Integer> stations = new ArrayList<>();
        ArrayList<Integer> prices = new ArrayList<>();
        try {
            distance = Integer.parseInt(br.readLine());
        } catch (IOException e) {}
        while (true) {
            String s = null;
            try {
                s = br.readLine();
                //throw new IOException("Boo");
            } catch (Exception e) {
                //System.out.println(e.toString());
            }
            if (s == null) {
                break;
            } else {
                String[] data = s.split(" ");
                stations.add(Integer.parseInt(data[0]));
                prices.add(Integer.parseInt(data[1]));
            }
        }
        stations.add(distance);
        prices.add(0);
        //sol.dp = new Integer[stations.size()][201];
        if (stations.get(0) > 100) {
            System.out.println("Impossible");
        } else {
            int ans = sol.helper(0, 100 - stations.get(0), stations, prices, distance);
            System.out.println((ans >= 20000001) ? "Impossible" : ans);
        }
    }
}
