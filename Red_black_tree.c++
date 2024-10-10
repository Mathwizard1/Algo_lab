#include <bits/stdc++.h>
using namespace std;

#define black 1
#define dblack 2
#define red -1

typedef struct bin_node
{
    struct bin_node* parent;
    int val;
    struct bin_node* lchild;
    struct bin_node* rchild;
    int color;

    bin_node(int value = -1,struct bin_node *p = nullptr)
    {
        val = value;
        parent = p;
        lchild = rchild = nullptr;
        color = red;
    }
}bin_node;

class RB_tree
{
private:
    bin_node* head = nullptr;

    void insert_node(int value)
    {

    }
public:
    void add_node(int value)
    {

    }
};

int main()
{



    return 0;
}