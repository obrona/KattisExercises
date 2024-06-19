import java.util.Scanner;

public class heights {
    int stepsTaken(int[] students) {
        AVLnode root = new AVLnode(students[0]);
        int steps = 0;
        for (int i = 1; i < students.length; i ++) {
            steps += AVLnode.countGreater(root, students[i]);
            root = AVLnode.insert(root, students[i]);
        }
        return steps;
    }

    public static void main(String[] args) {
        heights sol = new heights();
        Scanner scan = new Scanner(System.in);
        int size = scan.nextInt();
        for (int i = 0; i < size; i ++) {
            scan.nextLine();
            int[] array = new int[20];
            scan.nextInt();
            for (int j = 0; j < 20; j ++) {
                array[j] = scan.nextInt();
            }
            System.out.println((i + 1) + " " + sol.stepsTaken(array));
        }
        scan.close();

    }
}
