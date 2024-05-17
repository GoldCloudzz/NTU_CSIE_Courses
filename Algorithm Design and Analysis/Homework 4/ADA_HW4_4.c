//discuss with b06303131 ¨H®aºÍ & b08902149 ®}±á¯§

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long ab(long long n){
    if (n >= 0)
        return n;
    else
        return -1 * n;
}

long long bit_op(long long a, long long b, long long c){
    return (b * ((a & b) ^ (b | c) ^ (a + c)));
}

int main(){
    long long INF = LONG_LONG_MAX;
    int n, m;
    scanf("%d%d", &n, &m);
    int i, j, k;
    int num[n];
    for (i = 0; i < n; i++)
        scanf("%d", &num[i]);
    int x = 10 * n / m;
    long long dp[n][m];
    time_t t;
    srand(20211223);
    int start;
    long long min = INF;
    long long min_local, temp;
    int way, last;
    for (k = 0; k < x; k++){
        start = rand() % n;
        dp[0][0] = num[start];
        for (i = 1; i < n; i++){
            dp[i][0] = dp[i - 1][0] + num[(start + i) % n] - ab(num[(start + i) % n] - num[(start + i - 1) % n]);
            if (i > 1)
                dp[i][0] += bit_op(num[(start + i - 2) % n], num[(start + i - 1) % n], num[(start + i) % n]);
        }
        for (j = 1; j < m; j++){
            for (i = j; i < n; i++){
                if (i == j){
                    dp[i][j] = dp[i - 1][j - 1] + num[(start + i) % n];
                    last = i;
                }
                else{
                    min_local = INF;
                    temp = dp[i - 1][j] + num[(start + i) % n] - ab(num[(start + i) % n] - num[(start + i - 1) % n]);
                    if ((i - last) >= 2)
                        temp += bit_op(num[(start + i - 2) % n], num[(start + i - 1) % n], num[(start + i) % n]);
                    if (temp < min_local){
                        min_local = temp;
                        way = 1;
                    }
                    temp = dp[i - 1][j - 1] + num[(start + i) % n];
                    if (temp < min_local){
                        min_local = temp;
                        way = 2;
                    }
                    temp = dp[i - 2][j - 1] + num[(start + i - 1) % n] + num[(start + i) % n] - ab(num[(start + i) % n] - num[(start + i - 1) % n]);
                    if (temp < min_local){
                        min_local = temp;
                        way = 3;
                    }
                    dp[i][j] = min_local;
                    if (way == 2)
                        last = i;
                    else if (way == 3)
                        last = i - 1;
                }
            }
        }
        if (dp[n - 1][m - 1] < min)
            min = dp[n - 1][m - 1];
    }
    printf("%lld", min);
    return 0;
}
