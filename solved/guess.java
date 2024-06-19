import java.util.Scanner;

public class guess {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int s = 1;
        int e = 1000;
        while (true) {
            int m = (s + e) / 2;
            System.out.println(m);
            System.out.flush();
            String response = scanner.nextLine();
            
            if (response.equals("correct")) {
                scanner.close();
                return;
            } else if (response.equals("lower")) {
                e = m - 1;
            } else {
                s = m + 1;
            }
        }
        //scanner.close();
        //return;
    }

}
