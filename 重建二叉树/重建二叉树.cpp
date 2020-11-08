#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node* lchild;
    struct Node* rchild;
}BiTNode, * PBiTNode;
int s = 0;
int inordindex[100000000];
void PreOrder(PBiTNode bt, int* out1);
void CreatepostBiTree(int preord[], int inord[], int i, int j, int k, int h, PBiTNode &t);
void solve(int n, int* preOrder, int* inOrder, int* outOrder)
{
    PBiTNode root=NULL;
    if (n <= 0 || preOrder==NULL|| inOrder==NULL|| outOrder==NULL)
    {
        return;
    }
    else
    {
        for (int i = 0; i < n; i++)
            inordindex[inOrder[i]] = i;
        CreatepostBiTree(preOrder, inOrder, 0, n - 1, 0, n - 1, root);
        PreOrder(root, outOrder);
    }
}
void CreatepostBiTree(int preord[], int inord[], int i, int j, int k, int h, PBiTNode &t) 
{
    /* 先序序列中从i到j，中序序列从k到h，建立一棵二叉树放在t中*/
    int m;
    t = (BiTNode*)malloc(sizeof(BiTNode));
    if (t == NULL) return ;
        t->data = preord[i];  /*二叉树的根*/
        m = inordindex[preord[i]];  /*在中序序列中定位树的根*/
        /*递归调用建立左子树*/
        if (m == k) t->lchild = NULL;    /*左子树空*/
        else CreatepostBiTree(preord, inord, i + 1, i + m - k, k, m - 1, (t->lchild));
        /*递归调用建立右子树*/
        if (m == h) t->rchild = NULL;   /*右子树空*/
        else CreatepostBiTree(preord, inord, i + m - k + 1, j, m + 1, h, (t->rchild));
}
void PreOrder(PBiTNode bt, int* out1)
{
    if (bt != NULL) { /* 如果bt为空，结束*/
        out1[s++] = bt->data;  /*访问根结点*/
        printf("%d ", bt->data);
        PreOrder(bt->rchild, out1);   /*先序遍历左子树（递归调用）*/
        PreOrder(bt->lchild, out1);   /*先序遍历右子树（递归调用）*/
    }
}
int main()
{
    int N;
    scanf_s("%d", &N);
    int* pre = (int*)malloc(N * sizeof(int));
    if (pre == NULL) return 0;
    int* in = (int*)malloc(N * sizeof(int));
    if (in == NULL) return 0;
    int* out = (int*)malloc(N * sizeof(int));
    if (out == NULL) return 0;
    for (int i = 0; i < N; i++)
    {
        scanf_s("%d", &pre[i]);
    }
    for (int j = 0; j < N; j++)
    {
        scanf_s("%d", &in[j]);
    }
    solve(N, pre, in, out);
    printf("\n");
    return 0;
}