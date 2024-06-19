import java.util.Scanner;

public class rijeci {
    static long[] helper(int k) {
        if (k == 0) {
            return new long[] {1, 0};
        } else {
            long[] prev = helper(k - 1);
            long a = prev[1];
            long b = prev[0] + prev[1];
            return new long[] {a, b};
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int k = scanner.nextInt();
        scanner.close();
        long[] ans = helper(k);
        System.out.println(ans[0] + " " + ans[1]);
    }
}