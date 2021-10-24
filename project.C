// Wavl Tree - Project CS201, Academic Year :2021-22 , Fall Semester


/*
    General Info 

    Team Memeber
    1. Name : Pranavkumar Mallela   Entry Number : 2020CSB1112
    2. Name : Akshat Toolaj Sinha   Entry Number : 2020CSB1068  
    3. Name : Pratham kundan        Entry Number : 2020CSB1114

    Whenever you are commenting, do puts substantial commenting to let other person what you are doing

    While Commiting , Put this kind of message

    < Commit_Number >_commit_< Your_Name >
    ex. first_commit_Akshat
*/

// Including standard libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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
struct node
{
    int value;
    int rank;
    struct node* left;
    struct node* right;
    struct node* parent;    // We will see if we have to include this or not
};

int main()
{

}