#include <stdio.h>
#include <stdlib.h>

long long min2(long long a, long long b){
    return (a < b)? a : b;
}

int parent(int i){
    return (i - 1) / 2;
}

int left_child(int i){
    return 2 * i + 1;
}

int right_child(int i){
    return 2 * i + 2;
}

void merge_s(long long [][4], long long [][4], long long [][4], int, int, int);
void merge_sort_s(long long [][4], long long [][4], long long [][4], int, int);

void merge_p(long long [][4], long long [][4], long long [][4], int, int, int);
void merge_sort_p(long long [][4], long long [][4], long long [][4], int, int);

void swap(long long [][4], int, int);
void insert(long long [][4], long long [], int*);
void heapify(long long [][4], int, int);
long long *extract_min(long long [][4], int*);

long long solve(long long [][4], long long [][4], long long [][4], int);

int main(){
    int n;
    scanf("%d", &n);
    int i, j;
    long long array_global[n][4]; // start, end, unit, pay
    for (i = 0; i < n; i++){
        for (j = 0; j < 4; j++)
            scanf("%lld", &array_global[i][j]);
    }
    long long array_local[n][4], array1[n][4], array2[n][4];
    merge_sort_p(array_global, array1, array2, 0, n - 1);
    long long prev = array_global[0][2];
    long long ans = prev * array_global[0][3];
    long long cur;
    for (i = 0; i < 4; i++)
        array_local[0][i] = array_global[0][i];
    i = 1;
    while (i < n){
        while (i < (n - 1) && array_global[i][3] == array_global[i + 1][3]){
            for (j = 0; j < 4; j++)
                array_local[i][j] = array_global[i][j];
            i++;
        }
        for (j = 0; j < 4; j++)
            array_local[i][j] = array_global[i][j];
        cur = solve(array_local, array1, array2, i);
        ans += (cur - prev) * array_global[i][3];
        prev = cur;
        i++;
    }
    printf("%lld", ans);
    return 0;
}

void merge_s(long long array[][4], long long array1[][4], long long array2[][4], int head, int mid, int tail){
    int len1 = mid - head + 1;
    int len2 = tail - mid;
    int i, j;
    for (i = 0; i < len1; i++){
        for (j = 0; j < 4; j++)
            array1[i][j] = array[head + i][j];
    }
    for (i = 0; i < len1; i++){
        for (j = 0; j < 4; j++)
            array2[i][j] = array[mid + 1 + i][j];
    }
    i = 0;
    j = 0;
    int k = head;
    int l = 0;
    while (i < len1 && j < len2){
        if (array1[i][0] < array2[j][0]){
            for (l = 0; l < 4; l++)
                array[k][l] = array1[i][l];
            i++;
        }
        else{
            for (l = 0; l < 4; l++)
                array[k][l] = array2[j][l];
            j++;
        }
        k++;
    }
    while (i < len1){
        for (l = 0; l < 4; l++)
            array[k][l] = array1[i][l];
        i++;
        k++;
    }
    while (j < len2){
        for (l = 0; l < 4; l++)
            array[k][l] = array2[j][l];
        j++;
        k++;
    }
}

void merge_sort_s(long long array[][4], long long array1[][4], long long array2[][4], int head, int tail){
    if (head < tail){
        int mid = (head + tail) / 2;
        merge_sort_s(array, array1, array2, head, mid);
        merge_sort_s(array, array1, array2, mid + 1, tail);
        merge_s(array, array1, array2, head, mid, tail);
    }
}

void merge_p(long long array[][4], long long array1[][4], long long array2[][4], int head, int mid, int tail){
    int len1 = mid - head + 1;
    int len2 = tail - mid;
    int i, j;
    for (i = 0; i < len1; i++){
        for (j = 0; j < 4; j++)
            array1[i][j] = array[head + i][j];
    }
    for (i = 0; i < len1; i++){
        for (j = 0; j < 4; j++)
            array2[i][j] = array[mid + 1 + i][j];
    }
    i = 0;
    j = 0;
    int k = head;
    int l = 0;
    while (i < len1 && j < len2){
        if (array1[i][3] > array2[j][3]){
            for (l = 0; l < 4; l++)
                array[k][l] = array1[i][l];
            i++;
        }
        else{
            for (l = 0; l < 4; l++)
                array[k][l] = array2[j][l];
            j++;
        }
        k++;
    }
    while (i < len1){
        for (l = 0; l < 4; l++)
            array[k][l] = array1[i][l];
        i++;
        k++;
    }
    while (j < len2){
        for (l = 0; l < 4; l++)
            array[k][l] = array2[j][l];
        j++;
        k++;
    }
}

void merge_sort_p(long long array[][4], long long array1[][4], long long array2[][4], int head, int tail){
    if (head < tail){
        int mid = (head + tail) / 2;
        merge_sort_p(array, array1, array2, head, mid);
        merge_sort_p(array, array1, array2, mid + 1, tail);
        merge_p(array, array1, array2, head, mid, tail);
    }
}

void swap(long long heap[][4], int x, int y){
    long long temp;
    int k;
    for (k = 0; k < 4; k++){
        temp = heap[x][k];
        heap[x][k] = heap[y][k];
        heap[y][k] = temp;
    }
}

void insert(long long heap[][4], long long element[], int *size){
    int k = 0;
    int x = *size;
    for (k = 0; k < 4; k++)
        heap[x][k] = element[k];
    while (x != 0 && heap[parent(x)][1] > heap[x][1]){
        swap(heap, x, parent(x));
        x = parent(x);
    }
    *size = *size + 1;
}

void heapify(long long heap[][4], int k, int size){
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

long long *extract_min(long long heap[][4], int *size){
    long long *min = (long long *)malloc(4 * sizeof(long long));
    int k;
    for (k = 0; k < 4; k++)
        min[k] = heap[0][k];
    for (k = 0; k < 4; k++)
        heap[0][k] = heap[*size - 1][k];
    *size = *size - 1;
    heapify(heap, 0, *size);
    return min;
}

long long solve(long long array[][4], long long array1[][4], long long array2[][4], int m){
    int i, j;
    merge_sort_s(array, array1, array2, 0, m);
    long long heap[m + 1][4];
    int size = 0;
    int next = 0;
    int org;
    long long time = 1;
    long long result = 0;
    long long temp[4];
    while (size != 0 || next < (m + 1)){
        org = next;
        while (next < (m + 1) && array[next][0] == time){
            insert(heap, array[next], &size);
            next++;
        }
        if (size == 0 && next != (m + 1) && next == org)
            time = array[next][0];
        else{
            while (1){
                if (size == 0)
                    break;
                long long *min = extract_min(heap, &size);
                if (min[1] >= time){
                    long long end;
                    if (next == (m + 1))
                        end = min[1];
                    else
                        end = min2(min[1], array[next][0] - 1);
                    result += min2(min[2], end - time + 1);
                    if (end - time + 1 < min[2]){
                        for (i = 0; i < 4; i++){
                            if (i == 2)
                                continue;
                            else
                                temp[i] = min[i];
                        }
                        temp[2] = min[2] - (end - time + 1);
                        insert(heap, temp, &size);
                    }
                    time += min2(min[2], end - time + 1);
                    break;
                }
            }
        }
    }
    return result;
}
