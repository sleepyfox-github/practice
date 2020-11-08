# 重建二叉树

用先序序列和中序序列构建二叉树，采用二叉链表存储。编写递归算法，交换二叉树的左右子树，
输出新二叉树按先序遍历得到的结果。

提交格式：实现void solve(int n, int *preOrder, int *inOrder, int *outOrder)函数。
函数参数为序列长度n、先序序列preOrder、中序序列inOrder和输出序列outOrder。1<=n<=1000000，树的深度<=2000。请不要printf输出任何内容。

输入样例：
n=5,preOrder={1,2,3,4,5},inOrder={3,2,4,1,5}
输出样例：
outOrder={1,5,2,4,3}