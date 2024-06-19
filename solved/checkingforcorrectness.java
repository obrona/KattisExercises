import java.util.Scanner;

public class checkingforcorrectness {
    long fastModuloExpo(long base, long power) {
        if (power == 1) {
            return base % 10000;
        } else if (power % 2 == 0) {
            long next = fastModuloExpo(base, power / 2);
            long ans = (next * next) % 10000;
            return ans;
        } else {
            long next = fastModuloExpo(base, power / 2);
            long ans = next * next * (base % 10000);
            ans %= 10000;
            return ans;
        }
    }

    long moduloMult(long a, long b) {
        return ((a % 10000) * (b % 10000)) % 10000;
    }

    long moduloAdd(long a, long b) {
        return ((a % 10000) + (b % 10000)) % 10000;
    }

    long helper(long a, long b, char c) {
        if (c == '+') {
            return moduloAdd(a, b);
        } else if (c == '*') {
            return moduloMult(a, b);
        } else {
            return fastModuloExpo(a, b);
        }
    }

    public static void main(String[] args) {
        checkingforcorrectness sol = new checkingforcorrectness();
        Scanner scanner = new Scanner(System.in);
        do {
            long a = scanner.nextLong();
            char c = scanner.next().charAt(0);
            long b = scanner.nextLong();
            long ans = sol.helper(a, b, c);
            System.out.println(ans);
            scanner.nextLine();
        } while (scanner.hasNextLine());
        scanner.close();
    }
}
