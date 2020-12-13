#include<stdio.h>
#include <stdlib.h>

long long m[500][500], s[500][500];
long long number;
void traceback(long long i, long long j, int* out);
void solve(int n, int p[], int out[])
{
	for (long long i = 1; i <= n; i++) m[i][i] = 0;
	for (long long r = 1; r <= n - 1; r++)  //r是i和j的间隔宽度
		for (long long i = 1; i <= n - r; i++) //随着间隔宽度r的增长，i递减，直到i为1
		{ 
			long long j = i + r;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j]; // 在i的位置断链,分解为m[i][i]和m[i+1][j]。
			s[i][j] = i;
			for (long long k = i + 1; k < j; k++) // 计算最小的m[i][j]
			{ 
				long long t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j]) 
				{
					m[i][j] = t;
					s[i][j] = k;
				} //k是i和j之间的最佳断链位置
			}
		}
	out[0] = m[1][n]% 1000000007;
	for (long long i = 1; i <= n; i++)
	{
		out[i] = i;
	}
	number = n;
	traceback(1,n,out);
}

void traceback(long long i, long long j, int* out)
{
	long long k;
	if (i == j) return ;
	else {
		for (k = number; out[k + 1] != i; k--)
		{
			out[k + 1] = out[k];
		}
		out[k+1] = -1;
		number++;
		for (k = number; out[k] != j; k--)
		{
			out[k + 1] = out[k];
		}
		out[k + 1] = -2;
		number++;
		traceback(i, s[i][j], out);
		traceback(s[i][j] + 1, j, out);
	}
}

int main()
{
	int n=5;
	int p[6] = { 10,5,2,8,6,3 };
	int out[1500] = {0};
	solve(n, p, out);
	printf("out=");
	for (int i = 0; i <= number; i++)
	{
		printf("%d,", out[i]);
	}
	system("pause");
	return 0;
}