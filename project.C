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
    return NewNode;
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
//Pranav: changed variable names to z,x,y
TreeNode *RightRotate(TreeNode *z)
{ // Right Rotate about a pivot
    TreeNode *x = z->left;
    TreeNode *pz = z->parent;

    z->left = x->right;
    x->right = z;
    x->parent = pz;
    z->parent = x;
    if (z->left)
        z->left->parent = z; // Ensuring correctness of parents
    if (pz){
        if(x->value<pz->value)pz->left = x;
        else pz->right = x;
    }
    return x;
}

// Please note: In the paper if it is said that node x is left rotated it means that the function
// LeftRotate(p(x)) will be called. p(x) is the pivot.
//Pranav: changed variable names to z,x,y
TreeNode *LeftRotate(TreeNode *z)
{ // Left Rotate about a pivot
    TreeNode *x = z->right;
    TreeNode *pz = z->parent;
    z->right = x->left;
    x->left = z;
    x->parent = pz;
    z->parent = x;
    if (z->right)
        z->right->parent = z; // Ensuring correctness of parents
    if (pz){
        if(x->value<pz->value)pz->left = x;
        else pz->right = x;
    }
    return x;
}

// Utility function to find rank of any kind of node (even NULL nodes)
int FindRank(TreeNode *N)
{
    return (N == NULL) ? -1 : N->rank;
}

// Utility function to check if a Node is A,B-Node
bool isABnode(TreeNode *N, int A, int B)
{
    if (N==NULL)return false; // minor change to avoid exceptions
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
    Utility function to check if a node is a leaf
*/
bool isLeaf (TreeNode* N){
    if (N->left==NULL && N->right == NULL)return true;
    return false;
}

/*
    Function to write inorder traversal of Binary Search Tree
    We will include something later to help us know structure of the tree like giving timestamp
*/
void inorder_traversal(struct node *root)
{
    if (root == NULL)
        return;
    inorder_traversal(root->left);
    printf("%d->%d ", root->value, root->rank);
    inorder_traversal(root->right);
}

/*
    Utility function to free memory and remove a node
*/
void Remove(TreeNode* N){
    TreeNode* P = N->parent;
    if (P->left == N)P->left = NULL;
    else P->right= NULL;
    free(N);
}

/*
    Function to search for a node with given key value and return node
*/
TreeNode *search(TreeNode *R, int key)
{
    if (R->value == key) return R;
    else if (R->value > key) return search(R->left, key);
    else if (R->value < key) return search(R->right, key);
    else return NULL;
}

/*
    Function to return the min node in a given subtree
*/
TreeNode *MinNode(TreeNode *R)
{
    if (R == NULL)
        return NULL;
    if (R->left == NULL)
        return R;
    else
        return MinNode(R->left);
}

/*
    Function to return the max node in a given subtree
*/
TreeNode *MaxNode(TreeNode *R)
{
    if (R == NULL)
        return NULL;
    if (R->right == NULL)
        return R;
    else
        return MaxNode(R->right);
}

/*
    Function to return the sibling of a given node if exists
*/
TreeNode *Sibling(TreeNode *N)
{
    TreeNode *P = N->parent;
    if (P)
    {
        return (P->left == N) ? P->right : P->left;
    }
    return NULL;
}

/*
    Function to insert a number in WAVL Tree
    Arguement are root pointer of the tree in which we want to insert and number which we want to insert
    In first 6 lines we find the position to insert the number and insert it there
    from then on we perform Bottom's up rebalancing up the tree
    1. If node is 0,1 , we do promote and move up
    2. If node is 0,2
            
    3. If above two are not specified , then that node is balanced, move up the tree, 
*/
struct node *insert(struct node *root, int number)
{
    // We get to point where we have to insert the number
    if (root == NULL)
        return GetNode(number);
    // otherwise we insert on proper subtree depending on the conditions
    else if (number > root->value)
    {
        root->right = insert(root->right, number);
        root->right->parent = root;
    }
    else
    {
        root->left = insert(root->left, number);
        root->left->parent = root;
    }
    // until my node is 0,1 we promote and move up
    if (isABnode(root, 0, 1))
    {
        // root = Promote(root);
        return Promote(root);
    }
    // if node is 0,2, then we find the 0 child of root and rotate it to make it root and then do proper demotions and promotions
    else if (isABnode(root, 0, 2)) //Enter if root is a 0,2 node
    {
        int f; //flag to represent how z(root-(0,2) node), x(child of z), y(1-child or 2-child) are connected
        TreeNode *x, *y;
        if (FindRank(root) - FindRank(root->right) == 0) //Finding which side has rank diff=0, and setting x and y correspondingly
        {
            f = 0;
            x = root->right;
            y = x->left;
        }
        else
        {
            f = 1;
            x = root->left;
            y = x->right;
        }
        // y is null or is a 2 child, we use single rotations case as demonstrated in the paper
        if (y == NULL || isAchild(y, 2))  (single rotation case)
        {
            // I think here is the error
            if (f)
            {
                root = RightRotate(root);
                Demote(root->right);
            }
            else
            {
                root = LeftRotate(root);
                Demote(root->left);
            }
            //printf("Completed rotation(1)!\n");
            // root = Demote(root);
            return root;
        }
        // if y is 1 child ,we use double rotations case 
        else //y is a 1-child (double rotation case)
        {
            if (f)
            {
                root->left = LeftRotate(x);
                root = RightRotate(root);
                // Demote( root->right);
            }
            else
            {
                root->right = RightRotate(x);
                root = LeftRotate(root);
                // Demote( root->left);
            }
            //printf("Completed rotation(2)!\n");
            Demote(root->left);
            Demote( root->right);
            return Promote(root);
        }
    }
    // we have found the node where WAVL rule is not violated , just go up from here
    else
        return root;
}

/*
    Function to delete a node from a WAVL tree and perform bottom up rebalancing
*/

TreeNode* Delete(TreeNode* R, int key){
    TreeNode* N = search(R, key);   // Search for the node to be deleted
    if (N!=NULL){   
        if (N->rank == 0){  // If node is a leaf node
            if (N->parent ==NULL){  // If the remaining node is Root
                free(N);
                return NULL;    // Simply remove and return NULL
            };

            TreeNode* X;
            if (isAchild(N,1))X = N->parent;    // If node to be deleted is a 1-child
            else if(isAchild(N,2))X = N;    // If node to be deleted is a 2-child
            N->rank = -1;
            if (isABnode(X,2,2)){   // Demoting any 2,2 nodes we find
                X = Demote(X);
            }
            TreeNode* Y = Sibling(X);
            
            while (isAchild(X,3) && (isABnode(Y,2,2) || isAchild(Y,2))){    // While x is a 3-child and y is a 2-child or 2,2 repeat
                if (isAchild(Y,2))X->parent = Demote(X->parent);    // If Y is sa 2-child demote parent of X
                else {
                    X->parent = Demote(X->parent);  // If y is a 2,2-node demote parent of X
                    Y = Demote(Y);  // Demote Y as well
                }
                X = X->parent;  // Change X
                Y = Sibling(X); // Reset sibling of X
            }

            if (isABnode(X->parent,1,3) && !(isABnode(Y,2,2))){ // Once above condition is not satisfied
                // Finishing rebalancing using rotaions
                if (X->parent->left == X){
                    TreeNode* Z = X->parent;
                    TreeNode* V = Y->left;
                    TreeNode* W = Y->right;
                    if (isAchild(W,1)){ // If right child of Y is a 1-child
                        // perform single rotation and corresponding demotion steps
                        Y = Promote(Y); 
                        Z = Demote(Z);
                        
                        // Left Rotate
                        Z = LeftRotate(Z);

                        Remove(N);// freeing memory and removing node

                        if (isLeaf(Z->left))Z->left = Demote(Z->left);  // Incase a node becomes NULL
                        if (Z->parent==NULL)return Z;
                        else return R;
                    }
                    else if (isAchild(W,2)){    // If right child of Y is a 2-child
                        // Perform double rotation and corresponding demotion steps
                        Z = Demote(Z); Z = Demote(Z);
                        Y = Demote(Y);
                        V = Promote(V); V = Promote(V);
                        
                        // Double Rotation
                        Y = RightRotate(Y);
                        Z = LeftRotate(Z);
                        
                        Remove(N); // freeing memory and removing node

                        // Rebalancing with promotion
                        // if (isABnode(Z->left,1,1) && !isLeaf(Z->left))Z->left = Promote(Z->left);
                        // else if (isABnode(Z->right,1,1) && !isLeaf(Z->right))Z->right = Promote(Z->right);
                        
                        if (Z->parent==NULL)return Z;   // Incase the top of the rebalance becomes the root
                        else return R;
                    }
                }
                // Mirror case of 1st case
                if (X->parent->right == X){// If right child of Y is a 1-child
                    // perform single rotation and corresponding demotion steps
                    TreeNode* Z = X->parent;
                    TreeNode* V = Y->right;
                    TreeNode* W = Y->left;
                    if (isAchild(W,1)){
                        Y = Promote(Y);
                        Z = Demote(Z);
                        
                        // Right Rotation
                        Z = RightRotate(Z);
                        
                        Remove(N); // freeing memory and removing node

                        if (isLeaf(Z->right))Z->right = Demote(Z->right);   // Incase a node becomes NULL
                        if (Z->parent==NULL)return Z; // Incase the top of the rebalance becomes the root
                        else return R;
                    }
                    else if (isAchild(W,2)){// If left child of Y is a 2-child 
                        // Perform double rotation and corresponding demotion steps
                        Z = Demote(Z); Z = Demote(Z);
                        Y = Demote(Y);
                        V = Promote(V); V = Promote(V);
                        
                        // Double Rotation
                        Y = LeftRotate(Y);
                        Z = RightRotate(Z);
                        
                        Remove(N);  // freeing memory and removing node
                        
                        // Rebalancing with promotion
                        // if (isABnode(Z->right,1,1) && !isLeaf(Z->right))Z->right = Promote(Z->right);
                        // else if (isABnode(Z->left,1,1) && !isLeaf(Z->left))Z->left = Promote(Z->left);
                        
                        if (Z->parent==NULL)return Z;   // Incase the top of the rebalance becomes the root
                        else return R;
                    }
                }
            }
            else { // Incase no rebalancing is needed
                Remove(N);  // freeing memory and removing node
                return R;
            }
        }
        else {  // Incase a node is not leaf node

            // We delete a successor/predecessor leaf node
            // We then replace the value of the deleted node with the value
        
            TreeNode* S = MinNode(N->right);
            if (S==N || S==NULL) S = MaxNode(N->left);
            int k = S->value;  
            R = Delete(R,k);
            TreeNode* S1 = search(R,key);
            S1->value = k;
        }
        return R;
    }
    else return R;
}


int main()
{
    struct node *root = NULL;
    for (int i=0;i<=10;i++)root = insert(root,i);
    inorder_traversal(root);
    printf("\n");
    for (int i=0;i<=10;i++){
        root = Delete(root,i);
        inorder_traversal(root);
        printf("\n");
    }
    return 0;
}
