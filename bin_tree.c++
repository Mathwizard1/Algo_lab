#include <bits/stdc++.h>
using namespace std;

typedef struct bin_node
{
    int parent;
    int val;
    int lchild;
    int rchild;
    int height;

    bin_node(int value = -1, int p = -1)
    {
        val = value;
        parent = p;
        lchild = -1;
        rchild = -1;
        height = 0;
    }
}bin_node;

class BStree
{
private:
    int root = -1;
    vector<bin_node> bin_tree;

    int insert_node(int value, int curr_root, int curr_parent)
    {
        if(curr_root == -1)
        {
            int index = bin_tree.size();
            bin_tree.emplace_back(value, curr_parent);
            return index;
        }

        if(value < bin_tree[curr_root].val)
        {
            bin_tree[curr_root].lchild = insert_node(value, bin_tree[curr_root].lchild, curr_root);
        }
        if(bin_tree[curr_root].val < value)
        {
            bin_tree[curr_root].rchild = insert_node(value, bin_tree[curr_root].rchild, curr_root);
        }

        return curr_root;
    }

    int balance_tree(int curr_root)
    {
        if(curr_root == -1)
        {
            return -1;
        }

        int l,r;
        l = 1 + balance_tree(bin_tree[curr_root].lchild);
        r = 1 + balance_tree(bin_tree[curr_root].rchild);
        bin_tree[curr_root].height = l - r;

        if(l - r >= 2 || l - r <= -2)
        {
            int new_head;
            new_head = balance_aveal_tree(curr_root, bin_tree[curr_root].parent);

            l = 1 + balance_tree(bin_tree[new_head].lchild);
            r = 1 + balance_tree(bin_tree[new_head].rchild);
            bin_tree[new_head].height = l - r;
        }

        return(max(l,r));
    }

    int LL(int lchild, int curr_root, int curr_parent)
    {
        bin_node problem_child = bin_tree[lchild];

        bin_tree[curr_root].lchild = problem_child.rchild;
        if(problem_child.rchild != -1)
        {
            bin_tree[problem_child.rchild].parent = curr_root;
        }

        bin_tree[lchild].rchild = curr_root;
        bin_tree[curr_root].parent = lchild;

        bin_tree[lchild].parent = curr_parent;
        if(curr_parent != -1)
        {
            if(bin_tree[curr_parent].lchild == curr_root)
            {
                bin_tree[curr_parent].lchild = lchild;
            }
            else
            {
                bin_tree[curr_parent].rchild = lchild;
            }
        }
        else
        {
            root = lchild;
            bin_tree[lchild].parent = -1;
        }

        return lchild;
    }

    int RR(int rchild, int curr_root, int curr_parent)
    {
        bin_node problem_child = bin_tree[rchild];

        bin_tree[curr_root].rchild = problem_child.lchild;
        if(problem_child.lchild != -1)
        {
            bin_tree[problem_child.lchild].parent = curr_root;
        }

        bin_tree[rchild].lchild = curr_root;
        bin_tree[curr_root].parent = rchild;

        bin_tree[rchild].parent = curr_parent;
        if(curr_parent != -1)
        {
            if(bin_tree[curr_parent].lchild == curr_root)
            {
                bin_tree[curr_parent].lchild = rchild;
            }
            else
            {
                bin_tree[curr_parent].rchild = rchild;
            }
        }
        else
        {
            root = rchild;
            bin_tree[rchild].parent = -1;
        }

        return rchild;
    }

    int LR(int lchild, int curr_root, int curr_parent)
    {
        int new_head;
        new_head = RR(bin_tree[lchild].rchild, lchild, curr_root);
        new_head = LL(new_head, curr_root, curr_parent);
        return new_head;
    }

    int RL(int rchild, int curr_root, int curr_parent)
    {
        int new_head;
        new_head = LL(bin_tree[rchild].lchild, rchild, curr_root);
        new_head = RR(new_head, curr_root, curr_parent);
        return new_head;
    }

    int balance_aveal_tree(int curr_root, int curr_parent)
    {
        int p;
        if(curr_parent == -1)
        {p = -1;}
        else { p = bin_tree[curr_parent].val; }

        printf("root:%d p:%d\n", bin_tree[curr_root].val, p);

        bin_node curr_node = bin_tree[curr_root];
        bin_node problem_child;
        int new_head;

        if(curr_node.height == -2)
        {
            problem_child = bin_tree[curr_node.rchild];

            if(problem_child.height == -1)
            {
                printf("RR\n");
                new_head = RR(curr_node.rchild, curr_root, curr_parent);
            }
            else
            {
                printf("RL\n");
                new_head = RL(curr_node.rchild, curr_root, curr_parent);
            }
        }
        else
        {
            problem_child = bin_tree[curr_node.lchild];

            if(problem_child.height == -1)
            {
                printf("LR\n");
                new_head = LR(curr_node.lchild, curr_root, curr_parent);
            }
            else
            {
                printf("LL\n");
                new_head = LL(curr_node.lchild, curr_root, curr_parent);
            }
        }

        return new_head;
    }

    int get_node(int value, int curr_root)
    {
        if(curr_root == -1)
        {
            return -1;
        }

        if(value < bin_tree[curr_root].val)
        {
            return get_node(value, bin_tree[curr_root].lchild);
        }
        else if(value > bin_tree[curr_root].val)
        {
            return get_node(value, bin_tree[curr_root].rchild);
        }

        return curr_root;
    }

    int get_successor(int curr_root)
    {
        if(curr_root != -1)
        {
            bin_node curr_node = bin_tree[curr_root];
            if(curr_node.rchild == -1)
            {
                return curr_node.parent;
            }
            else
            {
                int index = curr_node.rchild;
                while(bin_tree[index].lchild != -1)
                {
                    index = bin_tree[index].lchild;
                }
                return index;
            }
        }
        return curr_root;
    }

    // needs work here
    int remove_node(int value, int curr_root)
    {
        int index = get_node(value, curr_root);
        if(index == -1)
        {
            return index;
        }

        bin_node curr_node = bin_tree[index];
        printf("val:%d lchild:%d rchild:%d\n", curr_node.val, curr_node.lchild, curr_node.rchild);

        if(curr_node.lchild == -1 || curr_node.rchild == -1)
        {
            int parent_index = curr_node.parent;
            int child_val = -1;
            int child_side;
            
            if(parent_index != -1)
            {
                child_side = (bin_tree[parent_index].lchild == index)? 1:0;
            }

            if(curr_node.lchild == -1 && curr_node.rchild != -1)
            {
                bin_tree[curr_node.rchild].parent = parent_index;
                child_val = curr_node.rchild;
            }
            else if(curr_node.lchild != -1 && curr_node.rchild == -1)
            {
                bin_tree[curr_node.lchild].parent = parent_index;
                child_val = curr_node.lchild;
            }
        
            //bin_tree.erase(bin_tree.begin() + index);

            if(parent_index != -1)
            {
                if(child_side == 1)
                {
                    printf("lchild of %d\n", bin_tree[parent_index].val);
                    bin_tree[parent_index].lchild = child_val;
                }
                else
                {
                    printf("rchild of %d\n", bin_tree[parent_index].val);
                    bin_tree[parent_index].rchild = child_val;   
                }
            }
            else if(bin_tree.size() == 0)
            {
                root = -1;
            }
        }
        else
        {
            int successor_index = get_successor(index);
            int temp_val = bin_tree[successor_index].val;
            printf("successor: %d\n", temp_val);

            remove_node(temp_val, successor_index);
            bin_tree[index].val = temp_val;
        }

        return 0;
    }

    void preorder_traverse(int curr_root)
    {
        if(curr_root != -1)
        {
            int curr_p;
            if(bin_tree[curr_root].parent == -1)
            {
                curr_p = -1;
            }
            else
            {
                curr_p = bin_tree[bin_tree[curr_root].parent].val;
            }

            printf("%d->index: %d,\np: %d, h: %d", bin_tree[curr_root].val, curr_root, curr_p, bin_tree[curr_root].height);
            printf(" lchild: %d, rchild %d\n", bin_tree[curr_root].lchild, bin_tree[curr_root].rchild);

            preorder_traverse(bin_tree[curr_root].lchild);
            preorder_traverse(bin_tree[curr_root].rchild);
        }
    }

    void inorder_traverse(int curr_root)
    {
        if(curr_root != -1)
        {
            inorder_traverse(bin_tree[curr_root].lchild);
            printf(" %d,", bin_tree[curr_root].val);
            inorder_traverse(bin_tree[curr_root].rchild);
        }
    }

public:
    void add_node(int value)
    {
        if(root == -1)
        {
            bin_tree.emplace_back(value);
            root = 0;
        }
        else
        {
            insert_node(value, root, -1);
        }

        //balance_tree(root);
    }

    int search_node(int value)
    {
        int val = get_node(value, root);
        if(val == -1)
        {
            printf("%d not found", value);
        }
        return val;
    }

    void delete_node(int value = -1)
    {
        int curr_size = bin_tree.size();
        if(curr_size > 0)
        {
            if(value == -1)
            {
                bin_tree.pop_back();
            }
            else
            {
                remove_node(value, root);
            }

            if(curr_size - 1 > 0)
            {
                //balance_tree(root);
            }
        }
    }

    void inorder_print()
    {
        inorder_traverse(root);
        printf("\n");
    }

    void preorder_print()
    {
        preorder_traverse(root);
        printf("\n");
    }

    void balance_bstree()
    {
        balance_tree(root);
    }
};


int main()
{
    BStree bst;

    vector<int> sample = {10,5,15,3,8,12,21,42};

    int num = sample.size();

    //printf("Enter the number of nodes: ");
    //cin >> num;

    for(int i = 0; i < num; i++)
    {
        int n = sample[i];
        //printf("Enter the number: ");
        //cin >> n;
        bst.add_node(n);
    }

    bst.inorder_print();
    /*bst.balance_bstree();
    bst.preorder_print();*/

    int del_num = 10;
    //printf("Enter the node to delete: ");
    //cin >> del_num;

    bst.delete_node(del_num);
    bst.inorder_print();
    bst.preorder_print();

    return 0;
}