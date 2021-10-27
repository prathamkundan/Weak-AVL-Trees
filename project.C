// Wavl Tree - Project CS201, Academic Year :2021-22 , Fall Semester

/*
    General Info 

    Team Memeber
    1. Name : Pranavkumar Mallela   Entry Number : 2020CSB1112
    2. Name : Akshat Toolaj Sinha   Entry Number : 2020CSB1068  
    3. Name : Pratham kundan        Entry Number : 2020CSB1114

    Whenever you are commenting, do puts substantial commenting to let other person what you are doing

    While Commiting , Put this kind of message

    < Commit_Number >_commit_< Your_Name >_< tell in brief what you did>
    ex. first_commit_Akshat_initializing_the code
*/

// Including standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
    Structure of a node in WAVL Tree
    Structure contains
    1. Value stored in that node
    2. Rank associated with that node
    3. Pointer to Left Child
    4. Pointer to Right Child
    5. Pointer to its Parent

    Pointer points to NULL for a missing value
*/
typedef struct node // Added typedef for ease of reference
{
    int value;
    int rank;
    struct node *left;
    struct node *right;
    struct node *parent; // We will see if we have to include this or not
} TreeNode;

TreeNode *GetNode(int key)
{
    TreeNode *NewNode = (TreeNode *)malloc(sizeof(TreeNode));
    NewNode->value = key;
    NewNode->left = NULL;
    NewNode->right = NULL;
    NewNode->rank = 0;
    NewNode->parent = NULL;
}

// Utility function to return a node after increasing its rank
TreeNode *Promote(TreeNode *X)
{
    X->rank++;
    return X;
}

// Utility function to return a node after decreasing its rank
TreeNode *Demote(TreeNode *X)
{
    X->rank--;
    return X;
}

// Please note: In the paper if it is said that node x is right rotated it means that the function
// RightRotate(p(x)) will be called. p(x) is the pivot.
TreeNode *RightRotate(TreeNode *Y)
{ // Right Rotate about a pivot
    TreeNode *X = Y->left;
    TreeNode *pY = Y->parent;
    Y->left = X->right;
    X->right = Y;
    X->parent = pY;
    Y->parent = X;
    if (Y->left) Y->left->parent = Y;   // Ensuring correctness of parents
    return X;
}

// Please note: In the paper if it is said that node x is left rotated it means that the function
// LeftRotate(p(x)) will be called. p(x) is the pivot.
TreeNode *LeftRotate(TreeNode *X)
{ // Left Rotate about a pivot
    TreeNode *Y = X->right;
    TreeNode *pX = X->parent;
    X->right = Y->left;
    Y->left = X;
    Y->parent = pX;
    X->parent = Y;
    if (X->right)X->right->parent = X;  // Ensuring correctness of parents
    return Y;
}

// Utility function to find rank of any kind of node (even NULL nodes)
int FindRank(TreeNode *N)
{
    return (N == NULL) ? -1 : N->rank;
}

// Utility function to check if a Node is A,B-Node
bool isABnode(TreeNode *N, int A, int B)
{
    bool c1 = ((FindRank(N) - FindRank(N->right) == A) && (FindRank(N) - FindRank(N->left) == B));
    bool c2 = ((FindRank(N) - FindRank(N->right) == B) && (FindRank(N) - FindRank(N->left) == A));
    if (c1 || c2)
        return true;
    return false;
}

// Utility function to check if a Node is A-child
bool isAchild(TreeNode *N, int A)
{
    if (FindRank(N->parent) - FindRank(N) == A)
        return true;
    return false;
}

/* 
    Function to write inorder traversal of Binary Search Tree
    We will include something later to help us know structure of the tree
*/
void inorder_traversal(struct node *root)
{
    if (root == NULL)
        return;
    inorder_traversal(root->left);
    printf(" %d timestamp: %d \n", root->value);
    inorder_traversal(root->right);
}
/*
    Function to insert a number in WAVL Tree
    Arguement are root pointer of the tree in which we want to insert and number which we want to insert
    In first 6 lines we find the position to insert the number and insert it there 
    from then on we perform Bottom's up rebalancing up the tree
    1. If node is 0,1 , we do promote and move up
    2. If node is 0,2 
            < Pranav Work >
    3. If above two are not specified , then that node is balanced, move up the tree, for Proof, Check Report Page No.-
*/
struct node *insert(struct node *root, int number)
{
    if (root == NULL)
        return GetNode(number);
    else if (number > root->value)
        root->right = insert(root->right, number);
    else
        root->left = insert(root->left, number);
    if (isABnode(root, 0, 1))
    {
        root = Promote(root);
        return root;
    }
    else if (isABnode(root, 0, 2))
    {

    }
    else
        return root;
}

int main()
{
    struct node * root=NULL;
    printf("Enter the number you want to insert, Please press Q to quit the sequence of Inserting the number \n");
    char a='a';
    while( a!='Q')
    {
        scanf(" %c",&a);
        if( a=='Q')
            continue;
        else
            root=insert(root,a-'0');
    }
}