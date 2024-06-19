#include "AVLnode.hpp"

#include <iostream>

using namespace std;

AVLnode::AVLnode(long long v, long long p) {
    val = v;
    paired = p;
    height = 1;
    maxres = p;
    left = nullptr;
    right = nullptr;
}
    
long long AVLnode::getHeight(AVLnode* n) {
    return (n == nullptr) ? 0 : n->height;
}

long long AVLnode::getPairMax(AVLnode* n) {
    return (n == nullptr) ? 0 : n->maxres;
}

bool AVLnode::isBalanced(AVLnode* n) {
    return abs(getHeight(n->left) - getHeight(n->right)) <= 1;
}

void AVLnode::update(AVLnode* n, AVLnode* l, AVLnode* r) {
    n->left = l;
    n->right = r;
    n->height = 1 + max(getHeight(l), getHeight(r));
    n->maxres = max(n->paired, max(getPairMax(l), getPairMax(r)));
}

AVLnode* AVLnode::rightRotate(AVLnode* n, bool forced) {
    if (forced) {
        AVLnode* newNode = n->left;
        update(n, n->left->right, n->right);
        update(newNode, newNode->left, n);
        return newNode;
    } else if (getHeight(n->left->right) > max(getHeight(n->left->left), getHeight(n->right))) {
        n->left = leftRotate(n->left, true);
        return rightRotate(n, true);
    } else {
        return rightRotate(n, true);
    }
}

AVLnode* AVLnode::leftRotate(AVLnode* n, bool forced) {
    if (forced) {
        AVLnode* newNode = n->right;
        update(n, n->left, n->right->left);
        update(newNode, n, newNode->right);
        return newNode;
    } else if (getHeight(n->right->left) > max(getHeight(n->left), getHeight(n->right->right))) {
        n->right = rightRotate(n->right, true);
        return leftRotate(n, true);
    } else {
        return leftRotate(n, true);
    }
}

AVLnode* AVLnode::insert(AVLnode* n, long long v, long long p) {
    if (n == nullptr) {
        return new AVLnode(v, p);
    } else if (n->val == v) {
        n->paired = max(n->paired, p);
        update(n, n->left, n->right);
        return n;
    } else if (v < n->val) {
        AVLnode* left = insert(n->left, v, p);
        update(n, left, n->right);
        if (!isBalanced(n)) {
            n = rightRotate(n, false);
        }
        return n;
    } else {
        AVLnode* right = insert(n->right, v, p);
        update(n, n->left, right);
        if (!isBalanced(n)) {
            n = leftRotate(n, false);
        }
        return n;
    }
}

void AVLnode::printInOrder(AVLnode* n) {
    if (n != nullptr) {
        printInOrder(n->left);
        cout << n->val << " ";
        printInOrder(n->right);
    }
}

// Geq : greather than or equal
long long AVLnode::getMaxPairForKeysGeq(AVLnode* n, long long v) {
    if (n == nullptr) {
        return 0;
    } else if (v > n->val) {
        return getMaxPairForKeysGeq(n->right, v);
    } else {
        long long resL = getMaxPairForKeysGeq(n->left, v);
        return max(resL, max(n->paired, getPairMax(n->right)));
    }
}

/*int main() {
    AVLnode* root = nullptr;
    root = AVLnode::insert(root, 5, 1);
    root = AVLnode::insert(root, 7, 10);
    root = AVLnode::insert(root, 3, 99);
    root = AVLnode::insert(root, 1, 1);
    root = AVLnode::insert(root, 2, 2);
    cout << AVLnode::getHeight(root) << endl;
    cout << AVLnode::getMaxPairForKeysGeq(root, 1);
}*/
    