//discuss with b06303131 沈家睿

#include <stdio.h>
#include <stdlib.h>

int front, back, length;

typedef struct Node{
    int vertex;
    struct Node* next;
} node;

typedef struct Graph{
    int amount;
    node** adjLists;
    int* visited;
} graph;

int empty(int queue[]){
    if (length == 0)
        return 1;
    else
        return 0;
}

void enqueue(int queue[], int value){
    back++;
    queue[back] = value;
    length++;
}

int dequeue(int queue[]){
    int item;
    item = queue[front];
    front++;
    length--;
    return item;
}

node* createNode(int v){
    node* newNode = (node*) malloc(sizeof(node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

graph* createGraph(int vertices){
    graph* map = (graph*) malloc(sizeof(graph));
    map->amount = vertices;
    map->adjLists = (node**) malloc((vertices + 1) * sizeof(node*));
    map->visited = (int*) malloc((vertices + 1) * sizeof(int));
    int i;
    for (i = 1; i <= vertices; i++){
        map->adjLists[i] = NULL;
        map->visited[i] = 0;
    }
    return map;
}

void addEdge(graph* map, int a, int b){
    node* newNode = createNode(b);
    newNode->next = map->adjLists[a];
    map->adjLists[a] = newNode;
    newNode = createNode(a);
    newNode->next = map->adjLists[b];
    map->adjLists[b] = newNode;
}

void bfs(graph* map, int queue[], int parent[], int vertex_search, int vertex_original, int flag){
    map->visited[vertex_search] = 1;
    enqueue(queue, vertex_search);
    while (!empty(queue)){
        int i;
        int len = length;
        for (i = 0; i < len; i++){
            int currentVertex = dequeue(queue);
            node* temp = map->adjLists[currentVertex];
            while (temp){
                int adjVertex = temp->vertex;
                if (!map->visited[adjVertex]){
                    map->visited[adjVertex] = 1;
                    enqueue(queue, adjVertex);
                    if (flag)
                        parent[adjVertex] = currentVertex;
                    else
                        parent[adjVertex] = vertex_original;
                }
                temp = temp->next;
            }
        }
    }
}

int main(){
    int n, q, s, r;
    scanf("%d%d%d%d", &n, &q, &s, &r);
    graph* map = createGraph(n);
    int i, a, b;
    for (i = 0; i < (n - 1); i++){
        scanf("%d%d", &a, &b);
        addEdge(map, a, b);
    }
    front = 0;
    back = -1;
    length = 0;
    int queue[n];
    int parent[n + 1];
    parent[s] = -1;
    bfs(map, queue, parent, s, 0, 1);
    for (i = 1; i <= n; i++)
        map->visited[i] = 0;
    int index = r;
    int diameter[n];
    int num = 0;
    while (index != -1){
        map->visited[index] = 1;
        diameter[num] = index;
        index = parent[index];
        num++;
    }
    front = 0;
    back = -1;
    length = 0;
    for (i = 0; i < num; i++){
        parent[diameter[i]] = diameter[i];
        bfs(map, queue, parent, diameter[i], diameter[i], 0);
    }
    int c;
    for (i = 0; i < q; i++){
        scanf("%d", &c);
        printf("%d\n", parent[c]);
    }
    return 0;
}
