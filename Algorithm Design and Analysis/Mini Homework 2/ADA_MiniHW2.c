//discuss with b06303131 ¨H®aºÍ
//reference: https://www.programiz.com/dsa/graph-bfs, https://www.programiz.com/dsa/graph-dfs

#include <stdio.h>
#include <stdlib.h>

int num, front, back, length;

typedef struct Node{
    int vertex;
    struct Node* next;
} node;

typedef struct Graph{
    int amount;
    node** adjLists;
    int* visited;
} graph;

void merge_int(int [], int [], int [], int, int, int);
void merge_sort_int(int [], int [], int [], int, int);

void merge_node(node**, node**, node**, int, int, int);
void merge_sort_node(node**, node**, node**, int, int);

int empty(int[]);
void enqueue(int[], int);
int dequeue(int[]);

node* createNode(int);
graph* createGraph(int);

void addEdge1(graph*, int, int);
void addEdge2(graph* , int, int);

void dfs(graph*, int[], int);
void bfs(graph*, int[], int[], int[], int[], int);

int main(){
    int m, n;
    scanf("%d%d", &n, &m);
    struct Graph* map = createGraph(n);
    int i, j, a, b;
    for (i = 0; i < m; i++){
        scanf("%d%d", &a, &b);
        addEdge1(map, a, b);
    }
    node* array[n];
    node* array1[n];
    node* array2[n];
    int len = 0;
    for (i = 1; i <= n; i++){
        len = 0;
        node* temp = map->adjLists[i];
        while (temp != NULL){
            array[len] = temp;
            len++;
            temp = temp->next;
        }
        merge_sort_node(array, array1, array2, 0, len - 1);
        for (j = (len - 1); j >= 0; j--){
            addEdge2(map, i, array[j]->vertex);
        }
    }
    int array3[n], array4[n];
    num = 0;
    front = 0;
    back = -1;
    length = 0;
    int dfs_path[n];
    dfs(map, dfs_path, 1);
    for (i = 0; i < n; i++)
        printf("%d ", dfs_path[i]);
    printf("\n");
    for (i = 1; i <= n; i++)
        map->visited[i] = 0;
    num = 0;
    front = 0;
    back = -1;
    length = 0;
    int queue_bfs[n], bfs_path[n];
    bfs(map, queue_bfs, array3, array4, bfs_path, 1);
    for (i = 0; i < n; i++)
        printf("%d ", bfs_path[i]);
    return 0;
}

void merge_int(int array[], int array1[], int array2[], int head, int mid, int tail){
    int len1 = mid - head + 1;
    int len2 = tail - mid;
    int i, j;
    for (i = 0; i < len1; i++)
        array1[i] = array[head + i];
    for (j = 0; j < len2; j++)
        array2[j] = array[mid + 1 + j];
    i = 0;
    j = 0;
    int k = head;
    while (i < len1 && j < len2){
        if (array1[i] < array2[j]){
            array[k] = array1[i];
            i++;
        }
        else{
            array[k] = array2[j];
            j++;
        }
        k++;
    }
    while (i < len1){
        array[k] = array1[i];
        i++;
        k++;
    }
    while (j < len2){
        array[k] = array2[j];
        j++;
        k++;
    }
}
void merge_sort_int(int array[], int array1[], int array2[], int head, int tail){
    if (head < tail){
        int mid = (head + tail) / 2;
        merge_sort_int(array, array1, array2, head, mid);
        merge_sort_int(array, array1, array2, mid + 1, tail);
        merge_int(array, array1, array2, head, mid, tail);
    }
}

void merge_node(node** array, node** array1, node** array2, int head, int mid, int tail){
    int len1 = mid - head + 1;
    int len2 = tail - mid;
    int i, j;
    for (i = 0; i < len1; i++)
        array1[i] = array[head + i];
    for (j = 0; j < len2; j++)
        array2[j] = array[mid + 1 + j];
    i = 0;
    j = 0;
    int k = head;
    while (i < len1 && j < len2){
        if (array1[i]->vertex < array2[j]->vertex){
            array[k] = array1[i];
            i++;
        }
        else{
            array[k] = array2[j];
            j++;
        }
        k++;
    }
    while (i < len1){
        array[k] = array1[i];
        i++;
        k++;
    }
    while (j < len2){
        array[k] = array2[j];
        j++;
        k++;
    }
}

void merge_sort_node(node** array, node** array1, node** array2, int head, int tail){
    if (head < tail){
        int mid = (head + tail) / 2;
        merge_sort_node(array, array1, array2, head, mid);
        merge_sort_node(array, array1, array2, mid + 1, tail);
        merge_node(array, array1, array2, head, mid, tail);
    }
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

void addEdge1(graph* map, int a, int b){
    node* newNode = createNode(b);
    newNode->next = map->adjLists[a];
    map->adjLists[a] = newNode;
    newNode = createNode(a);
    newNode->next = map->adjLists[b];
    map->adjLists[b] = newNode;
}

void addEdge2(graph* map, int a, int b){
    node* newNode = createNode(b);
    newNode->next = map->adjLists[a];
    map->adjLists[a] = newNode;
}

void dfs(graph* map, int path[], int vertex){
    node* adjList = map->adjLists[vertex];
    node* temp = adjList;
    map->visited[vertex] = 1;
    path[num] = vertex;
    num++;
    while (temp != NULL){
        int currentVertex = temp->vertex;
        if (map->visited[currentVertex] == 0){
            dfs(map, path, currentVertex);
        }
        temp = temp->next;
    }
}

void bfs(graph* map, int queue[], int array1[], int array2[], int path[], int vertex){
    map->visited[1] = vertex;
    enqueue(queue, vertex);
    while (!empty(queue)){
        merge_sort_int(queue, array1, array2, front, back);
        int i;
        for (i = 0; i < length; i++){
            path[num] = queue[front + i];
            num++;
        }
        int len = length;
        for (i = 0; i < len; i++){
            int currentVertex = dequeue(queue);
            node* temp = map->adjLists[currentVertex];
            while (temp){
                int adjVertex = temp->vertex;
                if (map->visited[adjVertex] == 0){
                    map->visited[adjVertex] = 1;
                    enqueue(queue, adjVertex);
                }
                temp = temp->next;
            }
        }
    }
}
