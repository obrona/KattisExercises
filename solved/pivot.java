import java.util.Scanner;

public class pivot {
    int[] leftMax(int[] array) {
        int[] out = new int[array.length];
        int currMax = -999999999;
        for (int i = 0; i < array.length; i ++) {
            out[i] = currMax;
            currMax = Math.max(currMax, array[i]);
        }
        return out;
    }

    int[] rightMin(int[] array) {
        int[] out = new int[array.length];
        int currMin = 999999999;
        for (int i = array.length - 1; i >= 0; i --) {
            out[i] = currMin;
            currMin = Math.min(array[i], currMin);
        }
        return out;
    }

    int countPossiblePivots(int[] array) {
        int[] leftMax = leftMax(array);
        int[] rightMin = rightMin(array);
        //System.out.println(Arrays.toString(leftMax));
        //System.out.println(Arrays.toString(rightMin));
        int count = 0;
        for (int i = 0; i < array.length; i ++) {
            count += (array[i] >= leftMax[i] && array[i] <= rightMin[i]) ? 1 : 0;
        }
        return count;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int len = scanner.nextInt();
        scanner.nextLine();
        int[] array = new int[len];
        for (int i = 0; i < len; i ++) {
            array[i] = scanner.nextInt();
        }
        scanner.close();
        int ans = new pivot().countPossiblePivots(array);
        System.out.println(ans);
    }
}
