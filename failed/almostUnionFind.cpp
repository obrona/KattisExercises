#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int v;
    int weight;
    //int height;
    long long sum;
    Node* left;
    Node* right;
    Node* parent;

    Node(int x) {
        v = x;
        weight = 1;
        //height = 0;
        sum = x;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    
    static int getWeight(Node* n) {
        return (n == nullptr) ? 0 : n->weight;
    }

    static int getSum(Node* n) {
        return (n == nullptr) ? 0 : n->sum;
    }

    /*static int getHeight(Node* n) {
        return (n == nullptr) ? -1 : n->height;
    }*/

    static void reset(Node* n) {
        n->parent = nullptr;
        n->left = nullptr;
        n->right = nullptr;
        n->weight = 1;
        n->sum = n->v;
        //n->height = 0;
    }

    // n is never nullptr, l, r and can be nullptr
    static void update(Node* n, Node* l, Node* r) {
        //n->height = 1 + max(getHeight(l), getHeight(r));
        n->weight = 1 + getWeight(l) + getWeight(r);
        n->left = l;
        n->right = r;
        if (l != nullptr) {
            l->parent = n;
        }
        if (r != nullptr) {
            r->parent = n;
        }
    }

    // result[0] = the new n with 1 leaf deleted, result[1] is the leaf that is deleted, also the leaf parent is changed to nullptr
    static vector<Node*> findDeleteLeaf(Node* n) {
        if (n->left == nullptr && n->right == nullptr) {
            n->parent = nullptr;
            return {nullptr, n};
        } else if (n->right == nullptr) {
            //if (n->left == nullptr) {cout << n->v << endl;}
            vector<Node*> res = findDeleteLeaf(n->left);
            update(n, res[0], n->right);
            res[0] = n;
            return res;
        } else if (n->left == nullptr) {
            //if (n->right == nullptr) {cout << n->v << endl;}
            vector<Node*> res = findDeleteLeaf(n->right);
            update(n, n->left, res[0]);
            res[0] = n;
            return res;
        } else if (getWeight(n->left) <= getWeight(n->right)) {
            vector<Node*> res = findDeleteLeaf(n->left);
            update(n, res[0], n->right);
            res[0] = n;
            return res;
        } else {
            vector<Node*> res = findDeleteLeaf(n->left);
            update(n, res[0], n->right);
            res[0] = n;
            return res;
        }
    }

    static Node* insert(Node* n, Node* x) {
        if (n == nullptr) {
            return x;
        } else if (n->right == nullptr) {
            update(n, n->left, x);
            return n;
        } else if (n->left == nullptr) {
            update(n, x, n->right);
            return n;
        } else if (getWeight(n->left) < getWeight(n->right)) {
            Node* l = insert(n->left, x);
            update(n, l, n->right);
            return n;
        } else {
            Node* r = insert(n->right, x);
            update(n, n->left, r);
            return n;
        }
    }

    static Node* find(Node* n) {
        return (n->parent == nullptr) ? n : find(n->parent);
    }

    
    //invariant: only for the root node, is weight, sum correct
    // for other nodes, including root, only height is correct
    static void Union(Node* n, Node* m) {
        
        
        
        Node* pN = find(n);
        Node* pM = find(m);
        if (pN == pM) {
            return;
        }
        long long sumN = pN->sum;
        long long sumM = pM->sum;
        int wN = pN->weight;
        int wM = pM->weight;
        float ratio = (float) wN / wM;
       
        if (ratio >= 1.0) {
            insert(pN, pM);
            pN->weight = wN + wM;
            pN->sum = sumN + sumM;
            //return;
        } else if (ratio < 1.0) {
            insert(pM, pN);
            pM->weight = wM + wN;
            pM->sum = sumM + sumN;
            //return;
        } /*else if (pN->weight >= pM->weight) {
            vector<Node*>&& res = findDeleteLeaf(pN);
            Node* newN = res[0];
            Node* leaf = res[1];
            //cout << leaf->v << " " << newN->v << endl;
            update(leaf, newN, m);
            leaf->sum = sumN + sumM;
            leaf->weight = wN + wM;
        } else {
            vector<Node*>&& res = findDeleteLeaf(pM);
            Node* newM = res[0];
            Node* leaf = res[1];
            update(leaf, n, newM);
            leaf->sum = sumN + sumM;
            leaf->weight = wN + wM;
        }*/
        
    }

    // invariant: only for the root node, is weight, sum correct
    // for other nodes, including root, only height/weight(depends on the change) is correct
    static void disconnect(Node* n) {
        if (n->left == nullptr && n->right == nullptr && n->parent == nullptr) {
            // n is a isolated node
            return;
        }
        Node* p = find(n);
        long long sum = p->sum;
        int weight = p->weight;
        if (p != n) {
            vector<Node*>&& res = findDeleteLeaf(p);
            if (res[1] != n) {
                Node* pN = n->parent;
                if (pN->left == n) {
                    pN->left = res[1];
                    res[1]->parent = pN;
                } else {
                    pN->right = res[1];
                    res[1]->parent = pN;
                }
                p->sum = sum - n->v;;
                p->weight = weight - 1;
                reset(n);
            } else {
                // we have deleted n
                reset(n);
            }
        } else {
            // n is the root, we replace n, with the leaf node we have found
            vector<Node*>&& res = findDeleteLeaf(p);
            Node* newRoot = res[1];
            update(newRoot, n->left, n->right);
            newRoot->sum = sum - n->v;
            newRoot->weight = weight - 1;
            reset(n);
        }
    }
};

class UnionFindDelete {
public:
    vector<Node*> map;

    UnionFindDelete(int n) {
        map = vector<Node*>();
        for (int i = 1; i <= n; i ++) {
            map.push_back(new Node(i));
        }
    }

    void join(int p, int q) {
        Node::Union(map[p - 1], map[q - 1]);
    }

    void move(int p, int q) {
        Node::disconnect(map[p - 1]);
        Node::Union(map[p - 1], map[q - 1]);
    }
    
    vector<long long> findSumAndWeight(int p) {
        Node* parent = Node::find(map[p - 1]);
        //cout << Node::find(map[2])->v << endl;
        //cout << parent->v << endl;
        return {parent->weight, parent->sum};
    }

    void printSumWeight(int p) {
        Node* parent = Node::find(map[p - 1]);
        cout << parent->weight << " " << parent->sum <<'\n';
    }
    
    string strSumWeight(int p) {
        Node* parent = Node::find(map[p - 1]);
        string s = "";
        s += to_string(parent->weight);
        s += " ";
        s += to_string(parent->sum);
        return s;
    }

    

};

template <typename T>
void print(vector<T> a) {
    for (int i = 0; i < a.size(); i ++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

/*int main() {
    UnionFindDelete ufd(5);
    ufd.join(1, 2);
    ufd.join(3, 4);
    ufd.join(3, 5);
    //ufd.move(4, 1);
    print(ufd.findSumAndWeight(4));
    ufd.move(4, 1);
    print(ufd.findSumAndWeight(4));
    print(ufd.findSumAndWeight(3));

}*/

int main() {
     ios_base::sync_with_stdio(false);
      cin.tie(NULL);
    vector<string> result;
    int n, m;
    while (cin >> n >> m) {
        UnionFindDelete ufd(n);
        for (int i = 0; i < m; i ++) {
            int instr, p, q;
            cin >> instr >> p;
            if (instr == 1) {
                cin >> q;
                ufd.join(p, q);
            } else if (instr == 2) {
                cin >> q;
                ufd.move(p, q);
            } else {
                result.push_back(ufd.strSumWeight(p));
            }
        }
    }
    for (string s: result) {
        cout << s << '\n';
    }
    return 0;
}

