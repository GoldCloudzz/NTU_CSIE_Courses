#include <stdio.h>

long long int x, y, z;

long long int MaxSubarray(int [], int, int);

long long int MaxCrossSubarray(int [], int, int, int);

int main(){
    int n;
    scanf("%d%lli%lli%lli", &n, &x, &y, &z);
    int a[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("%lli", MaxSubarray(a, 0, (n - 1)));
    return 0;
}

long long int MaxSubarray(int a[], int i, int j){
    if (j - i == 1)
        return x * a[i] + z * a[j];
    else if (j - i == 2){
        long long int case1 = x * a[i] + z * a[i + 1];
        long long int case2 = x * a[i + 1] + z * a[j];
        long long int case3 = x * a[i] + y * a[i + 1] + z * a[j];
        return case1 > case2 ? (case1 > case3 ? case1 : case3) : (case2 > case3 ? case2 : case3);
    }
    else{
        int k = (i + j) / 2;
        long long int l_sum = MaxSubarray(a, i, k);
        long long int r_sum = MaxSubarray(a, (k + 1), j);
        long long int c_sum = MaxCrossSubarray(a, i, k, j);
        return l_sum > r_sum ? (l_sum > c_sum ? l_sum : c_sum) : (r_sum > c_sum ? r_sum : c_sum);
    }
}

long long int MaxCrossSubarray(int a[], int i, int k, int j){
    long long int l_sum = x * a[k];
    long long int max_l_sum = l_sum;
    for (int p = (k - 1); p >= i; p--){
        l_sum += (x * a[p] + (y - x) * a[p + 1]);
        if (l_sum > max_l_sum)
            max_l_sum = l_sum;
    }
    long long int r_sum = z * a[k + 1];
    long long int max_r_sum = r_sum;
    for (int q = (k + 2); q <= j; q++){
        r_sum += (z * a[q] + (y - z) * a[q - 1]);
        if (r_sum > max_r_sum)
            max_r_sum = r_sum;
    }
    return (max_l_sum + max_r_sum);
}
