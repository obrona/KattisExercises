#pragma once

class AVLnode {
public:
    long long val;
    long long paired;
    long long height;
    long long maxres;

    AVLnode* left;
    AVLnode* right;

    AVLnode(long long v, long long p);
    
    static long long getHeight(AVLnode* n);
    static long long getPairMax(AVLnode* n);
    static bool isBalanced(AVLnode* n);
    static void update(AVLnode* n, AVLnode* l, AVLnode* r);
    static AVLnode* rightRotate(AVLnode* n, bool forced);
    static AVLnode* leftRotate(AVLnode* n, bool forced);
    static AVLnode* insert(AVLnode* n, long long v, long long p);
    static void printInOrder(AVLnode* n);
    static long long getMaxPairForKeysGeq(AVLnode* n, long long v);
};


