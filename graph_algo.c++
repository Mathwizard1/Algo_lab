#include <bits/stdc++.h>

using namespace std;

typedef struct undir_graph_edge
{
    int node1;
    int node2;
    int cost;
    undir_graph_edge(int f = 0, int t = 0, int c = -1)
    {
        node1 = f;
        node2 = t;
        cost = c;
    }
}uge;

typedef struct AdjacencyList
{
    struct AdjacencyList* next_node;
    int current_node;

    AdjacencyList(int val, struct AdjacencyList* ptr = nullptr)
    {
        current_node = val;
        next_node = ptr;
    }
}Alist;

class graphs
{
private:
    typedef struct graph_edge
    {
        int f_node;
        int t_node;
        int cost;

        graph_edge(int f = 0, int t = 0, int c = -1)
        {
            f_node = f;
            t_node = t;
            cost = c;
        }
    }ge;

    typedef struct graph_path
    {
        int val;
        vector<int> children;

        graph_path(int v = -1)
        {
            val = v;
        }
    }gp;



public:
    int num_nodes;
    int num_edges;

    vector<gp> graph_nodes;
    ge* graph_edges;

    //vector<ge> fringe;
    //int* node_explored;

    graphs(int node_num, int g_from[], int g_to[], int g_weight[], int edge_num)
    {
        num_nodes = node_num;
        num_edges = edge_num;

        for(int i = 0; i < num_nodes; i++)
        {
            graph_nodes[i] = gp();
        }

        ge* graph_edges = new ge[edge_num];

        for(int i = 0; i < num_edges; i++)
        {
            graph_edges[i] = ge(g_from[i], g_to[i], g_weight[i]);
        }
    }
};

/*      vector<vector<int>> D; // n x n matrix
        for(int i = 0; i < n; i++)
        {
            vector<int> temp;
            temp.resize(n);
            D.push_back(temp);
        }

        for(auto edge: edges) // edges = {from, to, weight}
        {
            D[edge[0] - 1][edge[1] - 1] = edge[2];
        }

        for(auto edge: D)
        {
            for(auto val: edge)
            {
                cout << val;
            }
            cout << '\n';
        }
*/

void SortEdge(vector<vector<int>>& edge_data)
{
    int num = edge_data.size();
    for(int i = 1; i < num; i++)
    {
        vector<int> key_edge = edge_data[i];
        int j = i - 1;
        while(j >= 0 && (edge_data[j][2] > key_edge[2]))
        {
            edge_data[j + 1] = edge_data[j];
            j--;
        }   
        edge_data[j + 1] = key_edge;
    }
}

bool check_edge(vector<vector<int>>& nodes, int f, int t, int net)
{
    if(nodes[f][0] == nodes[t][0])
    {
        return false;
    }
        
    int parent = nodes[f][0];

    if(nodes[t][1] == 1)
    {
        int issue_root = nodes[t][0];
        for(int n = 0; n < net; n++)
        {
            if(nodes[n][0] == issue_root)
            {
                nodes[n][0] = parent;
            }
            cout << nodes[n][0];
        }
        cout << '\n';
    }   
    else 
    {
        nodes[parent][1] = 1;
        nodes[t][0] = nodes[parent][0];
    }     

    return true;
}

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight) {
    
    int num_edge = g_weight.size();
    vector<vector<int>> edge_data;
    
    vector<int> parent, rank;
    
    for(int i = 0; i < num_edge; i++)
    {
        vector<int> edge;
        edge.push_back(g_from[i]);
        edge.push_back(g_to[i]);
        edge.push_back(g_weight[i]);
        edge_data.push_back(edge);
    }
    
    SortEdge(edge_data);
    
    int mst = 0;
    
    vector<vector<int>> traversed_nodes;
    for(int i = 0; i < g_nodes; i++)
    {
        vector<int> temp = {i, 0};
        traversed_nodes.emplace_back(temp);
    }
    
    for(int i = 0; i < num_edge; i++)
    {
        cout << edge_data[i][0] << edge_data[i][1] << '\n';
        if(check_edge(traversed_nodes, edge_data[i][0] - 1, edge_data[i][1] - 1, g_nodes))
        {
            mst += edge_data[i][2];
            cout << edge_data[i][0] << edge_data[i][1] << edge_data[i][2] << '\n';
        }
    }
    
    return mst;
}

int main()
{




}