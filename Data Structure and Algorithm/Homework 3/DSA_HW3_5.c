//discuss with b06303131 ¨H®aºÍ

#include <stdio.h>
#include <limits.h>

typedef struct Node{
    int index;
    unsigned long long value;
} node;

int char_to_int(char ch){
    return ((int) ch - 33);
}

void merge(node array[], node array1[], node array2[], int left, int mid, int right){
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
        if (array1[i].value <= array2[j].value){
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

void merge_sort(node array[], node array1[], node array2[], int left, int right){
    if (left < right){
        int mid = (left + right) / 2;
        merge_sort(array, array1, array2, left, mid);
        merge_sort(array, array1, array2, (mid + 1), right);
        merge(array, array1, array2, left, mid, right);
    }
}

int main(){
    unsigned long long k, l;
    int flag;
    int flag0_printed = 0;
    scanf("%llu%llu%d", &k, &l, &flag);
    unsigned long long q = ULLONG_MAX / 94 + 1;
    unsigned long long i, j;
    unsigned long long pow[l];
    pow[0] = 1;
    for (i = 1; i < l; i++)
        pow[i] = (pow[i - 1] * 94) % q;
    char string[k][l + 1];
    char temp;
    node rabin_karp[k];
    for(i = 0; i < k; i++){
        scanf("%s", string[i]);
        rabin_karp[i].index = i;
        rabin_karp[i].value = char_to_int(string[i][0]);
        for (j = 1; j < l; j++)
            rabin_karp[i].value = ((rabin_karp[i].value * 94) % q + char_to_int(string[i][j])) % q;
    }
    node array[k], array1[k], array2[k];
    for (i = 0; i < k; i++)
        array[i] = rabin_karp[i];
    merge_sort(array, array1, array2, 0, (k - 1));
    unsigned long long same = 0;
    unsigned long long left = 0;
    for (i = 1; i < k; i++){
        if (array[i].value != array[i - 1].value){
            same += (unsigned long long) (i - left) * (i - left - 1) / 2;
            left = i;
        }
    }
    same += (k - left) * (k - left - 1) / 2;
    if (flag == 0 && same > 0){
        for (i = 1; i < k; i++){
            if (array[i].value == array[i - 1].value){
                printf("Yes\n%d %d\n", array[i - 1].index, array[i].index);
                flag0_printed = 1;
                break;
            }
        }
    }
    unsigned long long similar = same;
    for (i = 0; i < l; i++){
        for (j = 0; j < k; j++){
            array[j].index = j;
            array[j].value = (rabin_karp[j].value + ((93 - char_to_int(string[j][i])) * pow[l - i - 1]) % q) % q;
        }
        merge_sort(array, array1, array2, 0, (k - 1));
        left = 0;
        for (j = 1; j < k; j++){
            if (array[j].value != array[j - 1].value){
                similar += (j - left) * (j - left - 1) / 2;
                left = j;
            }
        }
        similar += (k - left) * (k - left - 1) / 2;
        if (flag == 0 && similar > 0 && flag0_printed == 0){
            for (j = 1; j < k; j++){
                if (array[j].value == array[j - 1].value){
                    printf("Yes\n%d %d\n", array[j - 1].index, array[j].index);
                    flag0_printed = 1;
                    break;
                }
            }
            break;
        }
    }
    if (flag == 0){
        if (flag0_printed == 0)
            printf("No\n");
    }
    else{
        similar -= same * l;
        if (similar == 0)
            printf("No\n");
        else
            printf("Yes\n%llu\n", similar);
    }
    return 0;
}
