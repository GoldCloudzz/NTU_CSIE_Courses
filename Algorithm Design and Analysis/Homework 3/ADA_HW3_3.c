//discuss with b06303131 ¨H®aºÍ

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int parent(int i){
    return (i - 1) / 2;
}

int left_child(int i){
    return 2 * i + 1;
}

int right_child(int i){
    return 2 * i + 2;
}

void swap(long long [][2], int, int);
void insert(long long [][2], int, long long, int*);
void heapify(long long [][2], int, int);
long long *extract_min(long long [][2], int*);

void merge(int [], int [], int [], int, int, int);
void merge_sort(int [], int [], int [], int, int);

typedef struct Node{
    int id;
    int adj_vertex;
    int weight;
    struct Node* next;
} node;

typedef struct Graph{
    int amount;
    node** adjLists;
} graph;

node* createNode(int, int, int);
void createEdge(graph* , int, int, int, int);
graph* createGraph(int);

int main(){
    long long POS_INF = LONG_LONG_MAX;
    int n, m;
    scanf("%d%d", &n, &m);
    graph* map = createGraph(n);
    int i, a, b, c;
    for (i = 0; i < m; i++){
        scanf("%d%d%d", &a, &b, &c);
        createEdge(map, a, b, i + 1, c);
    }
    long long heap1[m][2]; // adjVertex, weight
    int size = 0;
    bool inMST[n + 1];
    for (i = 1; i <= n; i++)
        inMST[i] = 0;
    insert(heap1, 1, 0, &size);
    inMST[1] = 0;
    long long *array;
    node *temp;
    long long cost1 = 0;
    int currentVertex;
    while (size > 0){
        array = extract_min(heap1, &size);
        currentVertex = array[0];
        if (inMST[currentVertex])
            continue;
        cost1 += array[1];
        temp = map->adjLists[currentVertex];
        while (temp != NULL){
            if (inMST[temp->adj_vertex] == 0)
                insert(heap1, temp->adj_vertex, temp->weight, &size);
            temp = temp->next;
        }
        inMST[currentVertex] = 1;
    }
    bool inSPT[n + 1];
    for (i = 1; i <= n; i++)
        inSPT[i] = 0;
    long long shortest[n + 1];
    long long last_edge[n + 1][2];
    long long heap2[m][2]; // adjVertex, weight
    size = 0;
    insert(heap2, 1, 0, &size);
    shortest[1] = 0;
    for (i = 2; i <= n; i++)
        shortest[i] = POS_INF;
    int edge[n - 1];
    int index = 0;
    long long cost2 = 0;
    while (size > 0){
        array = extract_min(heap2, &size);
        currentVertex = array[0];
        if (inSPT[currentVertex])
            continue;
        if (currentVertex != 1){
            edge[index] = last_edge[currentVertex][0];
            index++;
            cost2 += last_edge[currentVertex][1];
        }
        temp = map->adjLists[currentVertex];
        while (temp != NULL){
            if (inSPT[temp->adj_vertex] == 0){
                insert(heap2, temp->adj_vertex, (temp->weight + shortest[currentVertex]), &size);
                if (shortest[currentVertex] + temp->weight < shortest[temp->adj_vertex]){
                    shortest[temp->adj_vertex] = shortest[currentVertex] + temp->weight;
                    last_edge[temp->adj_vertex][0] = temp->id;
                    last_edge[temp->adj_vertex][1] = temp->weight;
                }
                else if (shortest[currentVertex] + temp->weight == shortest[temp->adj_vertex] && temp->weight < last_edge[temp->adj_vertex][1]){
                    last_edge[temp->adj_vertex][0] = temp->id;
                    last_edge[temp->adj_vertex][1] = temp->weight;
                }
            }
            temp = temp->next;
        }
        inSPT[currentVertex] = 1;
    }
    if (cost1 == cost2){
        printf("Yes\n");
        int array1[index], array2[index];
        merge_sort(edge, array1, array2, 0, index - 1);
        for (i = 0; i < index; i++)
            printf("%d ", edge[i]);
    }
    else
        printf("No");
    return 0;
}

void swap(long long heap[][2], int x, int y){
    long long temp;
    int k;
    for (k = 0; k < 2; k++){
        temp = heap[x][k];
        heap[x][k] = heap[y][k];
        heap[y][k] = temp;
    }
}

void insert(long long heap[][2], int node, long long weight, int *size){
    int k = 0;
    int x = *size;
    heap[x][0] = node;
    heap[x][1] = weight;
    while (x != 0 && heap[parent(x)][1] > heap[x][1]){
        swap(heap, x, parent(x));
        x = parent(x);
    }
    *size = *size + 1;
}

void heapify(long long heap[][2], int k, int size){
    int left = left_child(k);
    int right = right_child(k);
    int smallest = k;
    if (left <= size && heap[left][1] < heap[smallest][1])
        smallest = left;
    if (right <= size && heap[right][1] < heap[smallest][1])
        smallest = right;
    if (smallest != k){
        swap(heap, k, smallest);
        heapify(heap, smallest, size);
    }
}

long long *extract_min(long long heap[][2], int *size){
    long long *min = (long long *)malloc(2 * sizeof(long long));
    int k;
    for (k = 0; k < 2; k++)
        min[k] = heap[0][k];
    for (k = 0; k < 2; k++)
        heap[0][k] = heap[*size - 1][k];
    *size = *size - 1;
    heapify(heap, 0, *size);
    return min;
}

void merge(int array[], int array1[], int array2[], int head, int mid, int tail){
    int len1 = mid - head + 1;
    int len2 = tail - mid;
    int i, j, k;
    for (i = 0; i < len1; i++)
        array1[i] = array[head + i];
    for (j = 0; j < len2; j++)
        array2[j] = array[mid + 1 + j];
    i = 0;
    j = 0;
    k = head;
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

void merge_sort(int array[], int array1[], int array2[], int head, int tail){
    if (head < tail){
        int mid = (head + tail) / 2;
        merge_sort(array, array1, array2, head, mid);
        merge_sort(array, array1, array2, mid + 1, tail);
        merge(array, array1, array2, head, mid, tail);
    }
}
node* createNode(int id_vertex, int id_edge, int weight){
    node* newNode = (node*) malloc(sizeof(node));
    newNode->id = id_edge;
    newNode->adj_vertex = id_vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void createEdge(graph* map, int a, int b, int id, int weight){
    node* newNode = createNode(b, id, weight);
    newNode->next = map->adjLists[a];
    map->adjLists[a] = newNode;
    newNode = createNode(a, id, weight);
    newNode->next = map->adjLists[b];
    map->adjLists[b] = newNode;
}

graph* createGraph(int vertices){
    graph* map = (graph*) malloc(sizeof(graph));
    map->amount = vertices;
    map->adjLists = (node**) malloc((vertices + 1) * sizeof(node*));
    int i;
    for (i = 1; i <= vertices; i++)
        map->adjLists[i] = NULL;
    return map;
}
