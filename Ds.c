#include <stdio.h>
#include <stdlib.h>

typedef struct bin_node
{
    int num;
    int lchild;
    int rchild;
    int parent;
}bin_node;

void add_element(bin_node bin_tree[], int num)
{

}

int main()
{
    bin_node *bin_tree;
    int num;

    printf("Enter the elements to add in binary tree: ");
    scanf("%d", &num);

    bin_tree = (bin_node*)malloc(sizeof(bin_node) * num);
    for(int i = 0; i < num; i++)
    {
        int n;
        printf("Enter the elements of binary tree: ");
        scanf("%d", &n);
        add_element(bin_tree, num);
    }

    return 0;
}