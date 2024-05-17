// discuss with b06303131 ¨H®aºÍ, b08501098 ¬_±á½n
//reference : https://github.com/PetarV-/Algorithms/blob/master/Graph%20Algorithms/Kosaraju%27s%20Algorithm.cpp

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

class node1{
public:
    bool visited;
    vector<int> adjList;
    vector<int> rev_adjList;
    node1():visited(0){}
};

class node2{
public:
    bool visited;
    int in;
    int out;
    vector<int> adjList;
    node2():visited(0), in(0), out(0){}
};

void dfs1(node1 graph[], stack<int> &ary, int x){
    graph[x].visited = 1;
    int j;
    for (j = 0; j < graph[x].adjList.size(); j++){
        if (graph[graph[x].adjList[j]].visited == 0)
            dfs1(graph, ary, graph[x].adjList[j]);
    }
    ary.push(x);
}

void dfs2(node1 graph[], int SCC_idx[], vector<vector<int>> &SCC, int x, int num){
    SCC_idx[x] = num;
    SCC[num].push_back(x);
    graph[x].visited = 1;
    int j;
    for (j = 0; j < graph[x].rev_adjList.size(); j++){
        if (graph[graph[x].rev_adjList[j]].visited == 0)
            dfs2(graph, SCC_idx, SCC, graph[x].rev_adjList[j], num);
    }
}

int find_sink(node2 graph[], unordered_set<int> &sink, int x){
    graph[x].visited = 1;
    if (sink.count(x)){
        sink.erase(x);
        return x;
    }
    int j;
    int ans = -1;
    for (j = 0; j < graph[x].adjList.size(); j++){
        if (graph[graph[x].adjList[j]].visited == 0){
            ans = find_sink(graph, sink, graph[x].adjList[j]);
            if (ans != -1)
                return ans;
        }
    }
    return -1;
}

int main(){
    int t, flag;
    scanf("%d%d", &t, &flag);
    int i, j, k, n, m, u, v;
    int num_sink, num_source;
    int idx_sink;
    for (i = 0; i < t; i++){
        scanf("%d%d", &n, &m);
        node1 graph1[n + 1];
        for (j = 0; j < m; j++){
            scanf("%d%d", &u, &v);
            graph1[u].adjList.push_back(v);
            graph1[v].rev_adjList.push_back(u);
        }
        stack<int> ary;
        for (j = 1; j <= n; j++){
            if (graph1[j].visited == 0)
                dfs1(graph1, ary, j);
        }
        int SCC_idx[n + 1];
        vector<vector<int>> SCC(n, vector<int>({}));
        int num = 0;
        for (j = 1; j <= n; j++)
            graph1[j].visited = 0;
        while (!ary.empty()){
            j = ary.top();
            ary.pop();
            if (graph1[j].visited == 0){
                dfs2(graph1, SCC_idx, SCC, j, num);
                num++;
            }
        }
        node2 graph2[num];
        int idx1, idx2;
        for (j = 1; j <= n; j++){
            idx1 = SCC_idx[j];
            for (k = 0; k < graph1[j].adjList.size(); k++){
                idx2 = SCC_idx[graph1[j].adjList[k]];
                if (idx1 != idx2){
                    graph2[idx1].adjList.push_back(idx2);
                    graph2[idx1].out++;
                    graph2[idx2].in++;
                }
            }
        }
        if (num == 1)
            printf("0\n");
        else{
            num_source = 0;
            num_sink = 0;
            for (j = 0; j < num; j++){
                if (graph2[j].in == 0)
                    num_source++;
                if (graph2[j].out == 0)
                    num_sink++;
            }
            printf("%d\n", max(num_source, num_sink));
        }
        if (num != 1 && flag){
            unordered_set<int> source;
            unordered_set<int> sink;
            vector<int> isolated;
            for (j = 0; j < num; j++){
                if (graph2[j].in == 0 && graph2[j].out != 0)
                    source.insert(j);
                else if (graph2[j].in != 0 && graph2[j].out == 0)
                    sink.insert(j);
                else if (graph2[j].in == 0 && graph2[j].out == 0)
                    isolated.push_back(j);
            }
            vector<pair<int, int>> edges;
            vector<pair<int, int>> chain;
            auto it = source.begin();
            while (it != source.end()){
                idx_sink = find_sink(graph2, sink, *it);
                if (idx_sink == -1)
                    it++;
                else{
                    chain.push_back({*it, idx_sink});
                    it = source.erase(it);
                }
            }
            if (chain.size() > 1){
                for (j = 0; j < chain.size() - 1; j++)
                    edges.push_back({SCC[chain[j].second][0], SCC[chain[j + 1].first][0]});
            }
            if (isolated.size() > 1){
                for (j = 0; j < isolated.size() - 1; j++)
                    edges.push_back({SCC[isolated[j]][0], SCC[isolated[j + 1]][0]});
            }
            if (chain.size() == 0 && isolated.size() > 1)
                edges.push_back({SCC[isolated[isolated.size() - 1]][0], SCC[isolated[0]][0]});
            else if (chain.size() >= 1 && isolated.size() == 0)
                edges.push_back({SCC[chain[chain.size() - 1].second][0], SCC[chain[0].first][0]});
            else {
                edges.push_back({SCC[isolated[isolated.size() - 1]][0], SCC[chain[0].first][0]});
                edges.push_back({SCC[chain[chain.size() - 1].second][0], SCC[isolated[0]][0]});
            }
            auto source_itr = source.begin();
            auto sink_itr = sink.begin();
            while(source_itr != source.end() && sink_itr != sink.end()){
                edges.push_back({SCC[*sink_itr][0], SCC[*source_itr][0]});
                source_itr = source.erase(source_itr);
                sink_itr = sink.erase(sink_itr);
            }
            source_itr = source.begin();
            sink_itr = sink.begin();
            while(source_itr != source.end()){
                edges.push_back({edges[0].first, SCC[*source_itr][0]});
                source_itr = source.erase(source_itr);
            }
            while(sink_itr != sink.end()){
                edges.push_back({SCC[*sink_itr][0], edges[0].first});
                sink_itr = sink.erase(sink_itr);
            }
            for (auto it : edges)
                printf("%d %d\n", it.first, it.second);
        }
    }
    return 0;
}
