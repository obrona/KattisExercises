import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class printer {
    static int solve(int n) {
        double x = Math.log((double) n) / Math.log(2.0);
        return 1 + (int) Math.ceil(x);
    }
    
    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = 0;
        try {
            n = Integer.parseInt(br.readLine());
        } catch (IOException e) {
            System.out.println(e.toString());
        }
        int ans = solve(n);
        System.out.println(ans);
    }
}
