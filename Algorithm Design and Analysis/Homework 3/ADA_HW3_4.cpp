//discuss with b06303131 ¨H®aºÍ

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Node{
public:
    int position;
    int size;
    Node* parent;
    Node(int p, int s):position(p), size(s), parent(this){}
    Node(){}
};

Node* find_root(Node* x){
    if(x != x->parent)
        x->parent = find_root(x->parent);
    return x->parent;
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    vector <Node*> arr(n + 1);
    map <int, Node*> graph;
    long long i;
    int x;
    for (i = 1; i <= n; i++){
        scanf("%d", &x);
        if (graph.count(x))
            graph[x]->size++;
        else
            graph[x] = new Node(x, 1);
        arr[i] = graph[x];
    }
    long long C[n + 1];
    C[0] = 0;
    C[1] = 0;
    for (i = 2; i <= n; i++)
        C[i] = i * (i - 1) / 2;
    long long crowdness = 0;
    for (auto it : graph)
        crowdness += C[it.second->size];
    int op, idx, pos, radius;
    Node *root;
    for (i = 0; i < q; i++){
        scanf("%d", &op);
        if (op == 1){
            scanf("%d%d", &pos, &radius);
            if (graph.count(pos) == 0)
                graph[pos] = new Node(pos, 0);
            auto it = graph.lower_bound(pos - radius);
            while (it != graph.end() && it->first <= (pos + radius)){
                if (it->first != pos){
                    crowdness += (C[graph[pos]->size + graph[it->first]->size] - C[graph[pos]->size] - C[graph[it->first]->size]);
                    graph[pos]->size += graph[it->first]->size;
                    graph[it->first]->parent = graph[pos];
                    it = graph.erase(it);
                }
                else
                    it++;
            }
        }
        else{
            scanf("%d%d", &idx, &pos);
            root = find_root(arr[idx]);
            root->size--;
            crowdness -= (C[root->size + 1] - C[root->size]);
            if (root->size == 0)
                graph.erase(root->position);
            if (graph.count(pos) == 0)
                graph[pos] = new Node(pos, 0);
            graph[pos]->size++;
            crowdness += (C[graph[pos]->size] - C[graph[pos]->size - 1]);
            arr[idx] = graph[pos];
        }
        printf("%lld\n", crowdness);
    }
    return 0;
}

