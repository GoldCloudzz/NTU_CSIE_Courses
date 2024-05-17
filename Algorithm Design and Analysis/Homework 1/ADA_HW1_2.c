// discuss with b06303131 ¨H®aºÍ

#include <stdio.h>
#include <stdbool.h>
long long int count = 0;
long long int a, b, c;

void merge_z(long long int[], long long int[], long long int[], long long int[], long long int[], long long int[], int, int, int);

void merge_sort_z(long long int[], long long int[], long long int[], long long int[], long long int[], long long int[], int, int);

void merge_p(long long int[], long long int[], long long int[], long long int[], long long int[], long long int[], int, int, int, bool);

void merge_sort_p(long long int[], long long int[], long long int[], long long int[], long long int[], long long int[], int, int);

int main(){
    int n;
    scanf("%d%lld%lld%lld", &n, &a, &b, &c);
    long long int p[n];
    long long int z[n];
    for (int i = 0; i < n; i++)
        scanf("%lld%lld", &p[i], &z[i]);
    long long int z1[n];
    long long int p1[n];
    long long int z2[n];
    long long int p2[n];
    merge_sort_z(z, p, z1, z2, p1, p2, 0, (n - 1));
    merge_sort_p(p, z, p1, p2, z1, z2, 0, (n - 1));
    printf("%lld", count);
    return 0;
}

void merge_z(long long int z[], long long int p[], long long int z1[], long long int z2[], long long int p1[], long long int p2[], int head, int mid, int tail){
    int lenA = mid - head + 1;
    int lenB = tail - mid;
    int i, j;
    for(i = 0; i < lenA; i++){
        z1[i] = z[head + i];
        p1[i] = p[head + i];
    }
    for(j = 0; j < lenB; j++){
        z2[j] = z[mid + 1 + j];
        p2[j] = p[mid + 1 + j];
    }
    i = 0;
    j = 0;
    int k = head;
    while(i < lenA && j < lenB){
        if(z1[i] < z2[j]){
            z[k] = z1[i];
            p[k] = p1[i];
            i++;
        }
        else{
            z[k] = z2[j];
            p[k] = p2[j];
            j++;
        }
        k++;
    }
    while(i < lenA){
        z[k] = z1[i];
        p[k] = p1[i];
        i++;
        k++;
    }
    while(j < lenB){
        z[k] = z2[j];
        p[k] = p2[j];
        j++;
        k++;
    }
}

void merge_sort_z(long long int z[], long long int p[], long long int z1[], long long int z2[], long long int p1[], long long int p2[], int head, int tail){
    if(head < tail){
        int mid = (head + tail) / 2;
        merge_sort_z(z, p, z1, z2, p1, p2, head, mid);
        merge_sort_z(z, p, z1, z2, p1, p2, mid + 1, tail);
        merge_z(z, p, z1, z2, p1, p2, head, mid, tail);
    }
}

void merge_p(long long int p[], long long int z[], long long int p1[], long long int p2[], long long int z1[], long long int z2[], int head, int mid, int tail, bool flag){
    int lenA = mid - head + 1;
    int lenB = tail - mid;
    int i, j;
    for(i = 0; i < lenA; i++){
        p1[i] = p[head + i];
        z1[i] = z[head + i];
    }
    for(j = 0; j < lenB; j++){
        p2[j] = p[mid + 1 + j];
        z2[j] = z[mid + 1 + j];
    }
    j = 0;
    if (flag){
        for (i = 0; i < lenA; i++){
            while (j < lenB && a * p2[j] <= b * p1[i] + c){
                j++;
            }
            count += (lenB - j);
        }
    }
    i = 0;
    j = 0;
    int k = head;
    while(i < lenA && j < lenB){
        if(p1[i] < p2[j]){
            p[k] = p1[i];
            z[k] = z1[i];
            i++;
        }
        else{
            p[k] = p2[j];
            z[k] = z2[j];
            j++;
        }
        k++;
    }
    while(i < lenA){
        p[k] = p1[i];
        z[k] = z1[i];
        i++;
        k++;
    }
    while(j < lenB){
        p[k] = p2[j];
        z[k] = z2[j];
        j++;
        k++;
    }
}

void merge_sort_p(long long int p[], long long int z[], long long int p1[], long long int p2[], long long int z1[], long long int z2[], int head, int tail){
    if (head < tail){
        int mid = (head + tail) / 2;
        if (z[head] == z[tail]){
            merge_sort_p(p, z, p1, p2, z1, z2, head, mid);
            merge_sort_p(p, z, p1, p2, z1, z2, mid + 1, tail);
            merge_p(p, z, p1, p2, z1, z2, head, mid, tail, 0);
        }
        else{
            int mid_final = mid;
            bool end = 1;
            for (int i = (mid + 1); i <= tail; i++){
                if (z[i] != z[mid]){
                    mid_final = i - 1;
                    end = 0;
                    break;
                }
            }
            if (end){
                for (int i = (mid - 1); i >= head; i--){
                    if (z[i] != z[mid]){
                        mid_final = i;
                        break;
                    }
                }
            }
            merge_sort_p(p, z, p1, p2, z1, z2, head, mid_final);
            merge_sort_p(p, z, p1, p2, z1, z2, mid_final + 1, tail);
            merge_p(p, z, p1, p2, z1, z2, head, mid_final, tail, 1);
        }
    }
}
