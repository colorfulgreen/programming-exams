#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
    int id;
    struct NODE *leftChild;
    struct NODE *centerChild;
    struct NODE *rightChild;
    struct Node *next;

    int n_children;
    int depth;
    int layer_seq;
} Node;

int num;
int **inputs;
Node *root;

/* 记录找到的节点 */
int target_id;
int max_n_children = 0;
int max_depth;

int cal_n_children(int *input) {
    int n_children = 0;
    for(int i=1; i<=3; i++) {
        if(input[i] != 0)
            n_children++;
    }
    return n_children;
}

Node *build_tree(int id)
{
    if(id == 0)
        return NULL;
    Node *node;
    node = malloc(sizeof(Node));
    for(int i=0; i<num; i++) {
        if(inputs[i][0] == id) {
            node->id = id;
            node->leftChild = build_tree(inputs[i][1]);
            node->centerChild = build_tree(inputs[i][2]);
            node->rightChild = build_tree(inputs[i][3]);
            node->n_children = cal_n_children(inputs[i]); 
        }
    }
    return node;
}


/* 层序遍历*/
void layer_order_traversal(Node **nodes, int n_nodes, int depth) {
    Node *node;
    /* TODO 存储层序遍历的节点，按最多情况申请内存 */
    Node **next_layer_nodes = malloc(sizeof(Node *) * n_nodes * 3);
    int n_next_layer_nodes = 0;
    for(int i=0; i<n_nodes; i++) {
        node = nodes[i];
        node->depth = depth;
        node->layer_seq = i;
        if(node->leftChild) 
            next_layer_nodes[n_next_layer_nodes++] = node->leftChild;
        if(node->centerChild) 
            next_layer_nodes[n_next_layer_nodes++] = node->centerChild;
        if(node->rightChild) 
            next_layer_nodes[n_next_layer_nodes++] = node->rightChild;
    }
    if(n_next_layer_nodes > 0)
        layer_order_traversal(next_layer_nodes, n_next_layer_nodes, depth+1);

    /* 寻找目标节点 */
    for(int i=0; i<n_nodes; i++) {
        if(nodes[i]->n_children > max_n_children && depth > max_depth) {
            max_n_children = nodes[i]->n_children;
            max_depth = depth;
            target_id = nodes[i]->id;
        }
    }
}


int main(void) 
{
    int *input;
    Node *node;
    scanf("%d", &num);
    /* TODO NOTE 存储输入数据 - 动态申请二维数组的内存 */
    inputs = malloc(sizeof(int *) * num);
    for(int i=0; i<num; i++) {
        input = malloc(sizeof(int) * 4);
        scanf("%d %d %d %d", &input[0], &input[1], &input[2], &input[3]);
        /* 陷阱：处理输入数据时不要 inputs++，需保留 inputs 位置供后面使用 */
        inputs[i] = input;
    }

    if(num <= 0)
        return EXIT_SUCCESS;

    /* 构建树 */
    root = malloc(sizeof(Node));
    root->id = inputs[0][0];
    root->leftChild = build_tree(inputs[0][1]);
    root->centerChild = build_tree(inputs[0][2]);
    root->rightChild = build_tree(inputs[0][3]);
    root->n_children = cal_n_children(inputs[0]); 

    /* 层序遍历，同时寻找目标节点 */
    layer_order_traversal(&root, 1, 0);

    printf("%d\n", target_id);

    return EXIT_SUCCESS;
}
