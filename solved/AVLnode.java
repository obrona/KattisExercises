public class AVLnode {
    long weight;
    long height;
    long value;
    long count;
    long sum;
    AVLnode left;
    AVLnode right;

    AVLnode(long val) {
        value = val;
        count = 1;
        weight = 1;
        height = 0;
        sum = val;
    }

    static long getWeight(AVLnode n) {
        return (n == null) ? 0 : n.weight;
    }
    
    static long getHeight(AVLnode n) {
        return (n == null) ? -1 : n.height;
    }

    static long getSum(AVLnode n) {
        return (n == null) ? 0 : n.sum;
    }

    static void updateNode(AVLnode n, AVLnode l, AVLnode r) {
        n.left = l;
        n.right = r;
        n.height = 1 + Math.max(getHeight(l), getHeight(r));
        n.weight = n.count + getWeight(l) + getWeight(r);
        n.sum = n.count * n.value + getSum(n.left) + getSum(n.right);
    }

    static boolean isBalanced(AVLnode node) {
        return (Math.abs(getHeight(node.left) - getHeight(node.right)) <= 1) ? true : false;
    }

    static void printInorder(AVLnode node) {
        if (node != null) {
            printInorder(node.left);
            System.out.print(node.value + " ");
            printInorder(node.right);
        }
    }
    
    
    static AVLnode rightRotate(AVLnode node, boolean forced) {
         
        if (forced) {
            AVLnode newNode = node.left;
            updateNode(node, node.left.right, node.right);
            updateNode(newNode, newNode.left, node);
            return newNode;
        } else if (getHeight(node.left.right) > Math.max(getHeight(node.left.left), getHeight(node.right))) {
            node.left = leftRotate(node.left, true);
            return rightRotate(node, true);
        } else {
            return rightRotate(node, true);
        }
    }

    

    static AVLnode leftRotate(AVLnode node, boolean forced) {
        if (forced) {
            AVLnode newNode = node.right;
            updateNode(node, node.left, node.right.left);
            updateNode(newNode, node, newNode.right);
            return newNode;
        } else if (getHeight(node.right.left) > Math.max(getHeight(node.left), getHeight(node.right.right))) {
            node.right = rightRotate(node.right, true);
            return leftRotate(node, true);
        } else {
            return leftRotate(node, true);
        }
    }

    static AVLnode insert(AVLnode node, long val) {
        // invariant: node is balanced
        if (node == null) {
            return new AVLnode(val);
        } else if (node.value == val) {
            node.weight += 1;
            node.count += 1;
            node.sum += val;
            return node;
        } else if (node.value < val) {
            AVLnode r = insert(node.right, val);
            updateNode(node, node.left, r);
            if (!isBalanced(node)) {
                // right heavy
                node = leftRotate(node, false);
            }
            return node;
        } else {
            AVLnode l = insert(node.left, val);
            updateNode(node, l, node.right);
            if (!isBalanced(node)) {
                // left heavy
                node = rightRotate(node, false);
            }
            return node;
        }
    }

    static AVLnode delete(AVLnode node, long val, long c) {
        if (node == null) {
            return null;
        } else if (node.value < val) {
            AVLnode r = delete(node.right, val, c);
            updateNode(node, node.left, r);
            if (!isBalanced(node)) {
                // left heavy only
                node = rightRotate(node, false);
            }
            return node;
        } else if (node.value > val) {
            AVLnode l  = delete(node.left, val, c);
            updateNode(node, l, node.right);
            if (!isBalanced(node)) {
                // right heavy
                node = leftRotate(node, false);
            }
            return node;
        } else if (node.count > c) {
            node.count -= c;
            node.weight -= c;
            node.sum -= val * c;
            return node;
        } else if (node.left == null && node.right == null) {
            return null;
        } else if (node.left != null && node.right != null) {
            AVLnode replace = node.right;
            while (replace.left != null) {
                replace = replace.left;
            }
            AVLnode r = delete(node.right, replace.value, replace.count);
            updateNode(replace, node.left, r);
            if (!isBalanced(replace)) {
                // left heavy, because we delete from right
                // don't forget to balance the replaced node
                replace = rightRotate(replace, false);
            }
            return replace;
        } else if (node.left != null) {
            return node.left;
        } else {
            return node.right;
        }
    }

    static long countGreater(AVLnode node, long val) {
        if (node == null) {
            return 0;
        } else if (node.value == val) {
            return countGreater(node.right, val);
        } else if (node.value < val) {
            return countGreater(node.right, val);
        } else {
            return countGreater(node.left, val) + node.count + getWeight(node.right);
        }
    }

    static long countSmaller(AVLnode node, long val) {
        if (node == null) {
            return 0;
        } else if (node.value >= val) {
            return countSmaller(node.left, val);
        } else {
            return node.count + getWeight(node.left) + countSmaller(node.right, val);
        }
    }

    // for convenience, l, r are 1 index
    static long getRangeSum(AVLnode node, long l, long r) {
        if (node == null) {
            return 0;
        } else if (l > r) {
            return 0;
        }
        long left = getWeight(node.left);
        long currS = left + 1;
        long currE = left + node.count;
        long right =  currE + 1;
        if (l == 1 && r == getWeight(node)) {
            return getSum(node);
        } else if (r <= left) {
            return getRangeSum(node.left, l, r);
        } else if (l >= right) {
            return getRangeSum(node.right, l - currE, r - currE);
        } else {
            // r > left && l < right
            long ll = getRangeSum(node.left, l, left);
            long rr = getRangeSum(node.right, 1, r - currE);
            long cl = (l > left) ? l : currS;
            long cr = (r < right) ? r : currE;
            long c = node.value * (cr - cl + 1);
            return c + ll + rr;

        }
        
        
    }

    public static void main(String[] args) {
        AVLnode root = new AVLnode(1);
        for (int i = 2; i <= 1000000; i ++) {
            root = root.insert(root, i);
        }
        System.out.println(AVLnode.getHeight(root));
        System.out.println(root.getRangeSum(root, 1, 10));
        for (int i = 1; i <= 999500; i ++) {
            root = root.delete(root, i, 1);
        }
        System.out.println(AVLnode.getHeight(root));
        System.out.println(AVLnode.getRangeSum(root, 1, 10));
        
    }

}