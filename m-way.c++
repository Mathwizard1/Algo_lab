#include <bits/stdc++.h>
using namespace std;

#define m_way 4

typedef struct m_way_node
{
    int parent;
    int keys[m_way - 1];
    int num_keys;
    int val[m_way];
    int num_vals;

    m_way_node(int value, int p = -1):parent(p)
    {
        num_keys = 1;
        num_vals = 0;
        for(int i = 0; i < m_way; i++)
        {
            if(i <  m_way - 1)
            {
                keys[i] = -1;
            }
            val[i] = -1;
        }
        keys[0] = value;
    };
}m_way_node;


void insertSort(int arr[], int Size)
{
    for(int i = 1; i < Size; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int get_num()
{
    int n;
    printf("Enter the number: ");
    cin >> n;
    return n;
}

void add_node(vector<m_way_node> &m_way_tree, int root, int numvalue, int parent = -1)
{
    if(m_way_tree.size() > 0)
    {
        int flag = 1;
        int curr_root;

        if(parent != -1)
        {
            curr_root = m_way_tree[parent].val[root];
        }
        else
        {
            curr_root = root;
        }

        if(curr_root == -1)
        {
            m_way_tree[parent].val[root] = m_way_tree.size();
            m_way_tree[parent].num_vals++;
            m_way_tree.emplace_back(numvalue, parent);
            return;
        }


        int curr_vals = m_way_tree[curr_root].num_vals;
        int curr_keys = m_way_tree[curr_root].num_keys;

        if(curr_vals == 0 && curr_keys < m_way - 1)
        {
            m_way_tree[curr_root].keys[curr_keys] = numvalue;
            m_way_tree[curr_root].num_keys++;
            insertSort(m_way_tree[curr_root].keys, m_way_tree[curr_root].num_keys);
            return;
        }

        for(int i = 0; i < curr_keys; i++)
        {
            if(numvalue < m_way_tree[curr_root].keys[i])
            {
                flag = 0;
                add_node(m_way_tree, i, numvalue, curr_root);
                break;
            }
        } 

        if(flag)
        {
            if(curr_keys == m_way - 1)
            {
                add_node(m_way_tree, curr_keys, numvalue, curr_root);
            }
            else
            {
                m_way_tree[curr_root].keys[curr_keys] = numvalue;
                m_way_tree[curr_root].num_keys++;
            }
        }
    }
    else
    {
        m_way_tree.emplace_back(numvalue, parent);
    }
}

void delete_node(vector<m_way_node> &m_way_tree, int root, int numvalue, int parent = -1)
{
    
}

int search_node(vector<m_way_node> m_way_tree, int root, int value)
{
    if(root != -1)
    {
        int curr_keys = m_way_tree[root].num_keys;
        for(int i = 0; i < curr_keys; i++)
        {
            if(value < m_way_tree[root].keys[i])
            {
                return search_node(m_way_tree, m_way_tree[root].val[i], value);
            }
            else if(value == m_way_tree[root].keys[i])
            {
                return root;
            }
        }

        return search_node(m_way_tree, m_way_tree[root].val[curr_keys], value);
    }
    return -1;
}

void traverse_m_way_node(m_way_node curr_node, int depth)
{
    printf("depth: %d parent: %d->[.", depth, curr_node.parent);
    for(int i = 0; i < m_way - 1; i++)
    {
        if(curr_node.keys[i] != -1)
        {
            printf("%d.", curr_node.keys[i]);
        }
    }
    printf("]\n");
}

void traverse_m_way_tree(vector<m_way_node> m_way_tree, int root, int depth = 0)
{
    if(root != -1)
    {
        m_way_node curr_node = m_way_tree[root];
        traverse_m_way_node(curr_node, depth);
        for(int i = 0; i < m_way; i++)
        {
            traverse_m_way_tree(m_way_tree, curr_node.val[i], depth + 1);
        }
    }
}

int main()
{
    int root = 0;
    vector<m_way_node> m_way_tree;

    int num;
    printf("Enter the number of nodes to add: ");
    cin >> num;

    for(int i = 0; i < num; i++)
    {
        int n = get_num();
        add_node(m_way_tree, root, n);
    }

    traverse_m_way_tree(m_way_tree, root);

    int srch;
    printf("Enter the nodes to search: ");
    cin >> srch;

    printf("The node is at root: %d", search_node(m_way_tree, root, srch));

    return 0;
}