import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
public class ultraquicksort {
    // for each number, count how many numbers on the left are bigger, and how many numbers on the right are smaller
    // they have to 'switch' with this number

    long countSwaps(int[] array) {
        long count = 0;
        //System.out.println(Arrays.toString(array));
        AVLnode root1 = new AVLnode(array[0]);
        for (int i = 1; i < array.length; i ++) {
            long ans = AVLnode.countGreater(root1, array[i]);
            count += ans;
            //System.out.println(ans);
            root1 = AVLnode.insert(root1, array[i]);
        }
        AVLnode root2 = new AVLnode(array[array.length - 1]);
        for (int i = array.length - 2; i >= 0; i --) {
            count +=  AVLnode.countSmaller(root2, array[i]);
            root2 = AVLnode.insert(root2, array[i]);
        }
        return count / 2;

    }

    public static void main(String[] args) {
        ultraquicksort sol = new ultraquicksort();
        BufferedReader scan = new BufferedReader(new InputStreamReader(System.in));
        int size = 0;
        try {
            size = Integer.parseInt(scan.readLine());
        } catch (IOException e) {
            return;
        }
        int[] array = new int[size];
        for (int i = 0; i < size; i ++) {
            try {
                array[i] = Integer.parseInt(scan.readLine());
            } catch (IOException e) {
                return;
            }
        }
        //scan.close();
        
        long ans = sol.countSwaps(array);
        System.out.println(ans);

        
    }
}
