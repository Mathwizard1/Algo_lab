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

int main()
{




}