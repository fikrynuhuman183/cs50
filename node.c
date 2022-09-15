#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int number;
    struct node* left;
    struct node* right;
}node;

int main(void){

    node *tree = NULL;
    node *n = malloc(sizeof(node));
    if(n == NULL)
    {
        return 1;
    }
    n->number = 2;
    n->right = NULL;
    n->left = NULL;
    tree = n;

    n = malloc(sizeof(node));
    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;

    for
}