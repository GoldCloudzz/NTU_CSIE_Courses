//discuss with b06303131 沈家睿 & b08902149 徐晨祐
//reference https://www.youtube.com/watch?v=132XR-RLNoY

#include <bits/stdc++.h>
#include "ypglpk.hpp"

#define MAX_N 80

using namespace std;

class node{
public:
    vector<int> adjList;
    node(){}
};

void Bron_Kerbosch(bitset<MAX_N> P, bitset<MAX_N> R, bitset<MAX_N> X, vector<node> &graph, vector<bitset<MAX_N>> &maximal_clique){
    if ((P | X).none()){
        maximal_clique.push_back(R);
        return;
    }
    int max_deg = -1;
    int u;
    int i, j;
    for (i = 0; i < (int) graph.size(); i++){
        if (P[i] == 1 || X[i] == 1){
            if ((int) graph[i].adjList.size() > max_deg){
                u = i;
                max_deg = graph[i].adjList.size();
            }
        }
    }
    bitset<MAX_N> neighbor_u = 0;
    for (i = 0; i < (int) graph[u].adjList.size(); i++)
        neighbor_u[graph[u].adjList[i]] = 1;
    bitset<MAX_N> Y = P ^ (P & neighbor_u);
    bitset<MAX_N> temp = 1;
    while (Y.any()){
        int v = Y._Find_first();
        bitset<MAX_N> neighbor_v = 0;
        for (i = 0; i < (int) graph[v].adjList.size(); i++)
            neighbor_v[graph[v].adjList[i]] = 1;
        temp = 1;
        Bron_Kerbosch((P & neighbor_v), (R | (temp << v)), (X & neighbor_v), graph, maximal_clique);
        Y[v] = 0;
        P[v] = 0;
        X[v] = 1;
    }
}

int main(){
    int t, n, m;
    int a, b;
    int x, i, j;
    scanf("%d", &t);
    for (x = 0; x < t; x++){
        scanf("%d%d", &n, &m);
        vector<node> graph(n);
        for (i = 0; i < m; i++){
            scanf("%d%d", &a, &b);
            graph[a].adjList.push_back(b);
            graph[b].adjList.push_back(a);
        }
        bitset<MAX_N> P;
        for (i = 0; i < n; i++)
            P[i] = 1;
        bitset<MAX_N> R = 0;
        bitset<MAX_N> X = 0;
        vector<bitset<MAX_N>> maximal_clique;
        Bron_Kerbosch(P, R, X, graph, maximal_clique);
        int num = maximal_clique.size();
        vector<vector<double>> A((2 * num + n), vector<double>(num, 0));
        vector<double> b(2 * num + n, 0);
        vector<double> c(num, -1);
        vector<bool> isint(num, true);
        for (i = 0; i < num; i++){
            A[i][i] = 1;
            A[num + i][i] = -1;
            b[i] = 1;
            b[num + i] = 0;
        }
        for (i = 0; i < num; i++){
            for (j = 0; j < n; j++){
                if (maximal_clique[i][j] == 1)
                    A[2 * num + j][i] = -1;
            }
        }
        for (i = 0; i < n; i++)
            b[2 * num + i] = -1;
        pair<double, vector<double>> ans = ypglpk::mixed_integer_linear_programming(A, b, c, isint);
        vector<bool> chosen(n, false);
        printf("%d\n", -1 * (int) ans.first);
        for (i = 0; i < (int) num; i++){
            if (ans.second[i] == 1){
                vector<int> vertex;
                for (j = 0; j < n; j++){
                    if (maximal_clique[i][j] == 1 && !chosen[j]){
                        vertex.push_back(j);
                        chosen[j] = true;
                    }
                }
                printf("%d ", (int) vertex.size());
                for (j = 0; j < (int) vertex.size(); j++)
                    printf("%d ", vertex[j]);
                printf("\n");
            }
        }
    }
    return 0;
}
