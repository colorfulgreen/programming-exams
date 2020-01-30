#include <stdio.h>
#include "queue"
#include "algorithm"
using namespace std;
#define max 1001

int preorder = 1;
struct node {
    int lchild, mchild, rchild;
    int layer;
    int childNum;
    int preorder; // 先序遍历顺序号
    int index;
} Node[max];

void layerOrder(int root)
{
    queue<int> q;
    Node[root].layer = 1;
    q.push(root);
    while(!q.empty()) {
        root = q.front();
        q.pop();
        /* 技巧：没有构造树。所有节点放在数组中，令节点序号=数组下标 */
        if(Node[root].lchild != 0) {
            Node[Node[root].lchild].layer = Node[root].layer + 1;
            q.push(Node[root].lchild);
        }
        if(Node[root].mchild != 0) {
            Node[Node[root].mchild].layer = Node[root].layer + 1;
            q.push(Node[root].mchild);
        }
        if(Node[root].rchild != 0) {
            Node[Node[root].rchild].layer = Node[root].layer + 1;
            q.push(Node[root].rchild);
        }
    }
}


void preOrder(int root)
{
    Node[root].preorder = preorder++;
    if(Node[root].lchild != 0)
        preOrder(Node[root].lchild);
    if(Node[root].mchild != 0)
        preOrder(Node[root].mchild);
    if(Node[root].rchild != 0)
        preOrder(Node[root].rchild);
}


bool cmp(node a, node b) {
    if(a.childNum > b.childNum)
        return true;
    else if(a.childNum == b.childNum && a.layer > b.layer)
        return true;
    else if(a.childNum == b.childNum && a.layer == b.layer)
        return a.preorder < b.preorder;
    else
        return false;
}


int main()
{
    int n,i,j;
    scanf("%d", &n);
    for(i=1; i<=n; i++) {
        int par, child[3], num=0;
        scanf("%d", &par);
        for(j=0; j<3; j++) {
            scanf("%d", &child[j]);
            if(child[j] != 0)
                num++;
        }
        Node[par].index = par;
        Node[par].childNum = num;
        Node[par].lchild = child[0];
        Node[par].mchild = child[1];
        Node[par].rchild = child[2];
    }
    layerOrder(1);
    preOrder(1);
    sort(Node+1, Node+n+1, cmp);
    i = 1;
    printf("%d %d\n", Node[1].preorder, Node[1].index);
    while(Node[i+1].childNum == Node[1].childNum && Node[i+1].layer == Node[1].layer) {
        printf("%d %d\n", Node[i+1].preorder, Node[i+1].index);
    }

    return 0;
}
