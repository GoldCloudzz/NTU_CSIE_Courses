// discuss with b06303131 ¨H®aºÍ
//reference: https://www.geeksforgeeks.org/implementing-upper_bound-and-lower_bound-in-c/ & https://www.geeksforgeeks.org/k-th-element-two-sorted-arrays/

#include <stdio.h>
#include <stdlib.h>
#include "price.h"

#define max_k 1000000

typedef struct Node{
    int stock;
    int date;
    unsigned long long price;
} node;

node createNode(int stock, int date, unsigned long long price){
    node* newNode = malloc(sizeof(node));
    newNode->stock = stock;
    newNode->date = date;
    newNode->price = price;
    return *newNode;
}

int parent(int index){
    return (index - 1) / 2;
}

int left_child(int index){
    return 2 * index + 1;
}

int right_child(int index){
    return 2 * index + 2;
}

void swap(node heap[], int index1, int index2){
    node temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}

void heapify(node heap[], int index, int size){
    int left = left_child(index);
    int right = right_child(index);
    int smallest = index;
    if (left < size && heap[left].price < heap[smallest].price)
        smallest = left;
    if (right < size && heap[right].price < heap[smallest].price)
        smallest = right;
    if (smallest != index){
        swap(heap, index, smallest);
        heapify(heap, smallest, size);
    }
}

node extract_min(node heap[], int n, int *size){
    node min = heap[0];
    heap[0] = createNode(min.stock, (min.date + n), price(min.stock, (min.date + n)));
    heapify(heap, 0, *size);
    return min;
}

int upper_bound(unsigned long long array[], unsigned long long n){
    int low = 0;
    int high = max_k;
    int mid;
    while (low < high){
        mid = (low + high) / 2;
        if (n >= array[mid])
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}

void merge(unsigned long long array[], unsigned long long array1[], unsigned long long array2[], int left, int mid, int right){
    int i, j;
    int len1 = mid - left + 1;
    int len2 = right - mid;
    for (i = 0; i < len1; i++)
        array1[i] = array[left + i];
    for (j = 0; j < len2; j++)
        array2[j] = array[mid + 1 + j];
    i = 0;
    j = 0;
    int k = left;
    while (i < len1 && j < len2){
        if (array1[i] <= array2[j]){
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

void merge_sort(unsigned long long array[], unsigned long long array1[], unsigned long long array2[], int left, int right){
    if (left < right){
        int mid = (left + right) / 2;
        merge_sort(array, array1, array2, left, mid);
        merge_sort(array, array1, array2, (mid + 1), right);
        merge(array, array1, array2, left, mid, right);
    }
}

unsigned long long kth(unsigned long long *array1, unsigned long long *array2, unsigned long long *end1, unsigned long long *end2, int k){
	if (array1 == end1)
		return array2[k];
	if (array2 == end2)
		return array1[k];
	int mid1 = (end1 - array1) / 2;
	int mid2 = (end2 - array2) / 2;
	if (mid1 + mid2 < k){
		if (array1[mid1] > array2[mid2])
			return kth(array1, array2 + mid2 + 1, end1, end2, k - mid2 - 1);
		else
			return kth(array1 + mid1 + 1, array2, end1, end2, k - mid1 - 1);
	}
	else{
		if (array1[mid1] > array2[mid2])
			return kth(array1, array2, array1 + mid1, end2, k);
		else
			return kth(array1, array2, end1, array2 + mid2, k);
	}
}

unsigned long long array1[max_k];

int main(){
    int a, q, n;
    scanf("%d%d%d", &a, &q, &n);
    int stock[a];
    int i, j;
    for (i = 0; i < a; i++)
        scanf("%d", &stock[i]);
    node heap[a * n];
    int size = a * n;
    for (i = 0; i < a; i++){
        for (j = 1; j <= n; j++)
            heap[i * n + j - 1] = createNode(stock[i], j, price(stock[i], j));
    }
    for (i = (size / 2 - 1); i >= 0; i--)
        heapify(heap, i, size);
    for (i = 0; i < max_k; i++)
        array1[i] = extract_min(heap, n, &size).price;
    int s, k, index1, index2, length;
    if (n < 10)
        length = 10;
    else
        length = n;
    unsigned long long array2[6 * length + 1];
    unsigned long long merge_sort_array1[3 * length + 2], merge_sort_array2[3 * length + 2];
    for (i = 0; i < q; i++){
        scanf("%d%d", &s, &k);
        if (s == 0)
            printf("%llu\n", array1[k - 1]);
        else{
            index1 = 1;
            while (1){
                index2 = upper_bound(array1, price(s, index1));
                if ((index1 + index2 - n) >= k)
                    break;
                index1 += length;
            }
            if (index1 <= 3 * length){
                for (j = 1; j <= (index1 + 3 * length); j++)
                    array2[j - 1] = price(s, j);
                merge_sort(array2, merge_sort_array1, merge_sort_array2, 0, (index1 + 3 * length - 1));
                printf("%llu\n", kth(array1, array2, (array1 + max_k), (array2 + index1 + 3 * length), (k - 1)));
            }
            else{
                for (j = (index1 - 3 * length); j <= (index1 + 3 * length); j++)
                    array2[j - (index1 - 3 * length)] = price(s, j);
                merge_sort(array2, merge_sort_array1, merge_sort_array2, 0, (6 * length));
                printf("%llu\n", kth(array1, array2, (array1 + max_k), (array2 + 6 * length + 1), (k - index1 + 3 * length)));
            }
        }
    }
    return 0;
}
