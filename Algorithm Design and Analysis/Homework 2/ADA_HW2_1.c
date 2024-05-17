#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

//discuss with b06303131 ¨H®aºÍ

long long max2(long long a, long long b){
    return (a > b)? a : b;
}

long long max3(long long a, long long b, long long c){
    return (a > b)? (a > c? a : c) : (b > c? b : c);
}

long long max4(long long a, long long b, long long c, long long d){
    long long e = (a > b)? a : b;
    long long f = (c > d)? c : d;
    return (e > f)? e : f;
}

int main(){
    long long NEG_INF = LONG_LONG_MIN;
    int t;
    scanf("%d", &t);
    int time;
    int n, m, k;
    int i, j, l;
    for (time = 0; time < t; time++){
        scanf("%d%d%d", &n, &m, &k);
        long long p[n][m];
        for (i = 0; i < n; i++){
            for (j = 0; j < m; j++){
                char temp[17];
                scanf(" %s", temp);
                if (temp[0] == 'X')
                    p[i][j] = NEG_INF;
                else
                    p[i][j] = atoll(temp);
            }
        }
        int length[k];
        length[0] = k;
        int len = 1;
        while (k > 0){
            if (k > 3){
                length[len] = k - k / 3;
                k -= k / 3;
                len++;
            }
            else{
                k--;
                length[len] = k;
                len++;
            }
        }
        k = len - 1;
        int offset[k];
        for (i = 0; i < k; i++)
            offset[k - 1 - i] = length[i] - length[i + 1];
        long long dp[n + 1][m + 1][k];
        for(i = 0; i < k; i++)
			dp[1][1][i] = 0;
        long long up1, left1, up2, left2;
        for (i = 1; i <= n; i++){
            for (j = 1; j <= m; j++){
                if (i == 1 && j == 1)
                    continue;
                if (i == 1)
                    up1 = NEG_INF;
                else
                    up1 = dp[i - 1][j][k - 1];
                if (j == 1)
                    left1 = NEG_INF;
                else
                    left1 = dp[i][j - 1][k - 1];
                if (i - offset[k - 1] < 1)
                    up2 = NEG_INF;
                else
                    up2 = dp[i - offset[k - 1]][j][k - 1];
                if (j - offset[k - 1] < 1)
                    left2 = NEG_INF;
                else
                    left2 = dp[i][j - offset[k - 1]][k - 1];
                if(max4(up1, left1, up2, left2) == NEG_INF || p[i - 1][j - 1] == NEG_INF)
                    dp[i][j][0] = NEG_INF;
                else
                    dp[i][j][0] = max4(up1, left1, up2, left2) + p[i - 1][j - 1];
                for(l = 1; l < k; l++){
                    if (i - offset[l - 1] < 1)
                        up1 = NEG_INF;
                    else
                        up1 = dp[i - offset[l - 1]][j][l - 1];
                    if (j - offset[l - 1] < 1)
                        left1 = NEG_INF;
                    else
                        left1 = dp[i][j - offset[l - 1]][l - 1];
                    dp[i][j][l] = max3(up1, left1, dp[i][j][l - 1]);
                }
            }
        }
        if (dp[n][m][0] == NEG_INF)
            printf("Impassable\n");
        else{
            printf("Passable\n%lld\n", dp[n][m][0]);
            int trace [m + n][2];
            int cur_k = k - 1;
            i = n;
            j = m;
            int index = 0;
            while (i > 0 && j > 0){
                if (dp[i][j][0] == dp[i][j][cur_k]){
                    cur_k = k - 1;
                    trace[index][0] = i;
                    trace[index][1] = j;
                    index++;
                }
                else
                    cur_k--;
                if (i == 1)
                    up1 = NEG_INF;
                else
                    up1 = dp[i - 1][j][cur_k];
                if (j == 1)
                    left1 = NEG_INF;
                else
                    left1 = dp[i][j - 1][cur_k];
                if (i - offset[cur_k] < 1)
                    up2 = NEG_INF;
                else
                    up2 = dp[i - offset[cur_k]][j][cur_k];
                if (j - offset[cur_k] < 1)
                    left2 = NEG_INF;
                else
                    left2 = dp[i][j - offset[cur_k]][cur_k];
                if(max4(up1, left1, up2, left2) == up1)
                    i--;
                else if(max4(up1, left1, up2, left2) == left1)
                    j--;
                else if(i - offset[cur_k] >= 1 && max4(up1, left1, up2, left2) == up2)
                    i -= offset[cur_k];
                else if(j - offset[cur_k] >= 1 && max4(up1, left1, up2, left2) == left2)
                    j -= offset[cur_k];
            }
            printf("%d\n", index);
            for (i = (index - 1); i >= 0; i--)
                printf("%d %d\n", trace[i][0], trace[i][1]);
        }
    }
    return 0;
}
