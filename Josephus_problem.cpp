#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int d;
	struct node* next;
} node;
int* solve(int N, int M, int K);
void print(int* a,int n,int k);
int main()
{
	int n, k, m;
	int* data;
	printf("请输入人数n，间隔人数m,剩余人数k:\n");
	scanf_s("%d%d%d", &n, &m, &k);
	data = solve(n, m, k);
	print(data,n,k);
	return 0;
}
int* solve(int N, int M, int K)
{
	node* Header = (node*)malloc(sizeof(node));
    if (!Header)return NULL;
	node* p, *q;
	Header->next = Header;
	p = Header;
	for (int i = 1; i <= N; ++i)
	{
		q = (node*)malloc(sizeof(node));
		if (!q)
		{
			return NULL;
		}
		q->d = i;
		q->next = p->next;
		p->next = q;
		p = q;
	}
	p = Header->next;
	int z = N - K;
	int* a = (int*)malloc(z*sizeof(int));
	if (!a)
	{
		return NULL;
	}
	int i = 1, j = N,s=0;//i控制每M个人删除;j存储剩余人数 
	if (M == 1)
	{
		for (i = 0; i < z; i++)
		{
			a[s++] = i + 1;
		}
	}
	else 
	{
		while (j > K)
		{
			if (i == M - 1)
			{
				if (p->next != Header)//不是删除第一个结点 
				{
					q = p->next;
					p->next = q->next;
					a[s++] = q->d;
				}
				else//删除第一个结点 
				{
					q = Header->next;
					Header->next = q->next;
					a[s++] = q->d;
				}
				free(q);
				if (p->next != Header)
				{
					p = p->next;
				}
				else
				{
					p = Header->next;
				}
				--j;
				i = 1;
			}
			else
			{
				if (p->next == Header)
				{
					p = Header->next;
				}
				else
				{
					p = p->next;
				}
				++i;
			}
		}
	}
	return a;
}
void print(int* a,int n,int k)
{
	for (int i = 0; i < (n-k); i++)
	{
		printf("%d  ",a[i]);
	}
}

