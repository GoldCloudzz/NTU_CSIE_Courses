//discuss with b06303131 ¨H®aºÍ

#include <stdio.h>
#include <stdlib.h>

int front, back, length;

int max3(int a, int b, int c){
    return (a > b)? (a > c? a : c) : (b > c? b : c);
}

int radius(int a){
    if (a % 2 == 1)
        return a / 2 + 1;
    else
        return a / 2;
}

typedef struct Node{
    int vertex;
    struct Node* next;
} node;

typedef struct Graph{
    int amount;
    node** adjLists;
    int* visited;
} graph;

int empty(int[]);
void enqueue(int[], int);
int dequeue(int[]);

node* createNode(int);
graph* createGraph(int);

void addEdge(graph*, int, int);

void bfs(graph*, int[], int [], int, int *, int);

int main(){
    int n;
    scanf("%d", &n);
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
    int end1, end2;
    int parent[n + 1];
    int x;
    bfs(map, queue, parent, 1, &end1, 0);
    for (i = 1; i <= n; i++)
        map->visited[i] = 0;
    front = 0;
    back = -1;
    length = 0;
    parent[end1] = -1;
    bfs(map, queue, parent, end1, &end2, 1);
    for (i = 1; i <= n; i++)
        map->visited[i] = 0;
    int index = end2;
    int diameter[n];
    int num = 0;
    while (index != -1){
        map->visited[index] = 1;
        diameter[num] = index;
        index = parent[index];
        num++;
    }
    int max[num][2];
    max[0][0] = 0;
    int max_local, sub;
    int max_left = 0;
    for (i = 1; i < num; i++){
        int currentVertex = diameter[i];
        node* temp = map->adjLists[currentVertex];
        max_local = 0;
        while (temp != NULL){
            sub = 0;
            int adjVertex = temp->vertex;
            if (map->visited[adjVertex] != 1){
                sub = 1;
                front = 0;
                back = -1;
                length = 0;
                bfs(map, queue, parent, adjVertex, &x, 0);
                 while (x != adjVertex){
                    x = parent[x];
                    sub++;
                }
            }
            if (sub > max_local)
                max_local = sub;
            temp = temp->next;
        }
        if (i + max_local > max_left){
            max_left = i + max_local;
            max[i][0] = i + max_local;
        }
        else
            max[i][0] = max_left;
    }
    for (i = 1; i <= n; i++)
        map->visited[i] = 0;
    for (i = 0; i < num; i++)
        map->visited[diameter[i]] = 1;
    max[num - 1][1] = 0;
    int max_right = 0;
    for (i = (num - 2); i >= 0; i--){
        int currentVertex = diameter[i];
        node* temp = map->adjLists[currentVertex];
        max_local = 0;
        while (temp != NULL){
            sub = 0;
            int adjVertex = temp->vertex;
            if (map->visited[adjVertex] != 1){
                sub = 1;
                bfs(map, queue, parent, adjVertex, &x, 0);
                 while (x != adjVertex){
                    x = parent[x];
                    sub++;
                }
            }
            if (sub > max_local)
                max_local = sub;
            temp = temp->next;
        }
        if ((num - i - 1) + max_local > max_right){
            max_right = (num - i - 1) + max_local;
            max[i][1] = (num - i - 1) + max_local;
        }
        else
            max[i][1] = max_right;
    }
    int min = 200001;
    for (i = 0; i < (num - 1); i++){
        max_local = max3(max[i][0], max[i + 1][1], radius(max[i][0]) + radius(max[i + 1][1]) + 1);
        if (max_local < min)
            min = max_local;
    }
    printf("%d", min);
    return 0;
}

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

void bfs(graph* map, int queue[], int parent[], int vertex, int* farthest, int flag){
    map->visited[vertex] = 1;
    enqueue(queue, vertex);
    while (!empty(queue)){
        int i;
        int len = length;
        for (i = 0; i < len; i++){
            int currentVertex = dequeue(queue);
            *farthest = currentVertex;
            node* temp = map->adjLists[currentVertex];
            while (temp){
                int adjVertex = temp->vertex;
                if (map->visited[adjVertex] == 0){
                    map->visited[adjVertex] = 1;
                    enqueue(queue, adjVertex);
                    if (flag)
                        parent[adjVertex] = currentVertex;
                }
                temp = temp->next;
            }
        }
    }
}
