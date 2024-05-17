#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b){
    return (a > b)? a : b;
}

int cmp(int m[], int n[], int a, int b){
    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    else{
        for (int i = (a - 1); i >= 0; i++){
            if (m[255 - i] > n[255 - i])
                return 1;
            else if (m[255 - i] < n[255 - i])
                return -1;
        }
        return 0;
    }
}

void swap(int** m, int** n, int* a, int* b){
    int *ptr;
    ptr = *m;
    *m = *n;
    *n = ptr;
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void divide(int* m, int* a){
    for (int i = ((*a) - 1); i > 0; i--){
        m[255 - i + 1] += 10 * (m[255 - i] % 2);
        m[255 - i] = m[255 - i] / 2;
    }
    m[255] = m[255] / 2;
    while (m[256 - *a] == 0)
        (*a) = (*a) - 1;
}

void times(int* n, int* b){
    int carry = 0;
    int temp;
    for (int i = 0; i < *b; i++){
        temp = n[255 - i];
        n[255 - i] = (n[255 - i] * 2) % 10 + carry;
        carry = (temp * 2) / 10;;
    }
    if (carry != 0){
        n[255 - *b] = carry;
        (*b) = (*b) + 1;
    }
}

void minus(int* m, int* n, int* a){
    for (int i = 0; i < *a; i++){
        if (m[255 - i] < n[255 - i]){
            m[255 - i - 1]--;
            m[255 - i] = m[255 - i] + 10 - n[255 - i];
        }
        else
            m[255 - i] = m[255 - i] - n[255 - i];
    }
    while (m[256 - *a] == 0)
        (*a) = (*a) - 1;
}

int main(){
    int text[256] = {0};
    int *m = malloc(256 * sizeof(int));
    memset(m, 0, 256 * sizeof(int));
    int *n = malloc(256 * sizeof(int));
    memset(n, 0, 256 * sizeof(int));
    char ch;
    int a = 0;
    while (scanf("%c", &ch) != EOF){
        if (ch == ' ')
            break;
        text[a] = (int) ch - 48;
        a++;
    }
    int i;
    for (i = 0; i < a; i++)
        m[255 - i] = text[a - i - 1];
    int b = 0;
    while (scanf("%c", &ch) != EOF){
        if (ch == '\n')
            break;
        text[b] = (int) ch - 48;
        b++;
    }
    for (i = 0; i < b; i++)
        n[255 - i] = text[b - i - 1];
    if (cmp(m, n, a, b) < 0)
        swap(&m, &n, &a, &b);
    int ans = 0;
    while (a > 0 && b > 0){
        if (m[255] % 2 == 0 && n[255] % 2 == 0){
            ans++;
            divide(m, &a);
            divide(n, &b);
        }
        else if (n[255] % 2 == 0)
            divide(n, &b);
        else if (m[255] % 2 == 0)
            divide(m, &a);
        if (cmp(m, n, a, b) < 0)
            swap(&m, &n, &a, &b);
        minus(m, n, &a);
    }
    for (i = 0; i < ans; i++)
        times(n, &b);
    for (i = (256 - b); i < 256; i++)
        printf("%d", n[i]);
    return 0;
}
