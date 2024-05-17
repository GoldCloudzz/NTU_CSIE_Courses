#include <stdio.h>
#include <stdlib.h>

int parent(int i){
    return (i - 1) / 2;
}

int left_child(int i){
    return 2 * i + 1;
}

int right_child(int i){
    return 2 * i + 2;
}

void swap(long long [][3], int, int);
void insert(long long [][3], long long , int, int, int*);
void heapify(long long [][3], int, int);
long long *extract_min(long long [][3], int*);

int main(){
    int t, flag;
    scanf("%d%d", &t, &flag);
    int i, j, k, n, cur, len;
    long long max;
    for (i = 0; i < t; i++){
        scanf("%d", &n);
        long long num[n];
        for (j = 0; j < n; j++)
            scanf("%lld", &num[j]);
        long long s[n];
        len = 0;
        if (num[0] > 0)
            cur = 0;
        else
            cur = 1;
        max = num[0];
        long long sum = 0;
        for (j = 1; j < n; j++){
            if (num[j] > 0){
                if (cur == 0){
                    if (num[j] > max)
                        max = num[j];
                }
                else{
                    s[len] = max;
                    sum += max;
                    len++;
                    max = num[j];
                    cur = 0;
                }
            }
            else{
                if (cur == 0){
                    s[len] = max;
                    sum += max;
                    len++;
                    max = num[j];
                    cur = 1;
                }
                else{
                    if (num[j] > max)
                        max = num[j];
                }
            }
        }
        s[len] = max;
        sum += max;
        len++;
        long long result[n];
        for (j = len; j < n; j++)
            result[j] = 0;
        long long heap1[len][3];
        int used1[len], front1[len], back1[len];
        for (j = 0; j < len; j++)
            used1[j] = 0;
        int size1 = 0;
        for (j = 0; j < len; j++){
            if (j == 0){
                insert(heap1, s[j] + s[j + 1], j, j + 1, &size1);
                front1[j] = len - 1;
                back1[j] = j + 1;
            }
            else if (j == (len - 1)){
                insert(heap1, s[j] + s[0], j, 0, &size1);
                front1[j] = j - 1;
                back1[j] = 0;
            }
            else{
                insert(heap1, s[j] + s[j + 1], j, j + 1, &size1);
                front1[j] = j - 1;
                back1[j] = j + 1;
            }
        }
        result[len - 1] = sum;
        int time1 = (len - 1) / 2;
        for (j = 0; j < time1; j++){
            while (1){
                long long *min = extract_min(heap1, &size1);
                if (used1[min[1]] == 0 && used1[min[2]] == 0){
                    used1[min[1]] = 1;
                    used1[min[2]] = 1;
                    result[len - 3 - 2 * j] = result[len - 1 - 2 * j] - min[0];
                    insert(heap1, s[front1[min[1]]] + s[back1[min[2]]], front1[min[1]], back1[min[2]], &size1);
                    front1[back1[min[2]]] = front1[min[1]];
                    back1[front1[min[1]]] = back1[min[2]];
                    break;
                }
            }
        }
        long long heap2[len][3];
        int used2[len], front2[len], back2[len];
        for (j = 0; j < len; j++)
            used2[j] = 0;
        int size2 = 0;
        if (s[0] >= s[len - 1]){
            result[len - 2] = sum - s[len - 1];
            for (j = 0; j < (len - 1); j++){
                if (j == 0){
                    insert(heap2, s[j] + s[j + 1], j, j + 1, &size2);
                    front2[j] = len - 2;
                    back2[j] = j + 1;
                }
                else if (j == (len - 2)){
                    insert(heap2, s[j] + s[0], j, 0, &size2);
                    front2[j] = j - 1;
                    back2[j] = 0;
                }
                else{
                    insert(heap2, s[j] + s[j + 1], j, j + 1, &size2);
                    front2[j] = j - 1;
                    back2[j] = j + 1;
                }
            }
        }
        else{
            result[len - 2] = sum - s[0];
            for (j = 1; j < len; j++){
                if (j == 1){
                    insert(heap2, s[j] + s[j + 1], j, j + 1, &size2);
                    front2[j] = len - 1;
                    back2[j] = j + 1;
                }
                else if (j == (len - 1)){
                    insert(heap2, s[j] + s[1], j, 1, &size2);
                    front2[j] = j - 1;
                    back2[j] = 1;
                }
                else{
                    insert(heap2, s[j] + s[j + 1], j, j + 1, &size2);
                    front2[j] = j - 1;
                    back2[j] = j + 1;
                }
            }
        }
        int time2 = (len - 2) / 2;
        for (j = 0; j < time2; j++){
            while (1){
                long long *min = extract_min(heap2, &size2);
                if (used2[min[1]] == 0 && used2[min[2]] == 0){
                    used2[min[1]] = 1;
                    used2[min[2]] = 1;
                    result[len - 4 - 2 * j] = result[len - 2 - 2 * j] - min[0];
                    insert(heap2, s[front2[min[1]]] + s[back2[min[2]]], front2[min[1]], back2[min[2]], &size2);
                    front2[back2[min[2]]] = front2[min[1]];
                    back2[front2[min[1]]] = back2[min[2]];
                    break;
                }
            }
        }
        for (j = 0; j < n; j++)
            printf("%lld ", result[j]);
        printf("\n");
    }
    return 0;
}

void swap(long long heap[][3], int x, int y){
    long long temp;
    int k;
    for (k = 0; k < 3; k++){
        temp = heap[x][k];
        heap[x][k] = heap[y][k];
        heap[y][k] = temp;
    }
}

void insert(long long heap[][3], long long value, int a, int b, int *size){
    int k = *size;
    heap[k][0] = value;
    heap[k][1] = a;
    heap[k][2] = b;
    while (k != 0 && heap[parent(k)][0] > heap[k][0]){
        swap(heap, k, parent(k));
        k = parent(k);
    }
    *size = *size + 1;
}

void heapify(long long heap[][3], int l, int size){
    int left = left_child(l);
    int right = right_child(l);
    int smallest = l;
    if (left <= size && heap[left][0] < heap[smallest][0])
        smallest = left;
    if (right <= size && heap[right][0] < heap[smallest][0])
        smallest = right;
    if (smallest != l){
        swap(heap, l, smallest);
        heapify(heap, smallest, size);
    }
}

long long *extract_min(long long heap[][3], int *size){
    long long *min = (long long *)malloc(3 * sizeof(long long));
    int k;
    for (k = 0; k < 3; k++)
        min[k] = heap[0][k];
    for (k = 0; k < 3; k++)
        heap[0][k] = heap[*size - 1][k];
    *size = *size - 1;
    heapify(heap, 0, *size);
    return min;
}
