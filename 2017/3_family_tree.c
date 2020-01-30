#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_MAX_LEN 100

char *input[1000][3];
int n_lines;
typedef struct NODE {
    char *name;
    struct NODE *left;
    struct NODE *right;

    /* 为便于输出共同祖先，保存父指针 */
    struct NODE *father; 
    int depth;
} Node;


Node *build_tree(char *name, Node *father, int depth) 
{
    Node *node = NULL;
    for(int i=0; i<n_lines; i++) {
        if(strcmp(name, input[i][0]) == 0) {
            node = malloc(sizeof(Node));
            node->name = name;
            node->left = build_tree(input[i][1], node, depth + 1);
            node->right = build_tree(input[i][2], node, depth + 1);
            node->father = father;
            node->depth = depth;
            break;
        }
    }
    /* 陷阱：输入数据中，叶子节点没有单独行，也需要为其创建节点 */
    /* 处理叶子节点 */
    if(node == NULL) {
        node = malloc(sizeof(Node));
        node->name = name;
        node->left = NULL;
        node->right = NULL;
        node->father = father;
        node->depth = depth;
    }
    return node;
}


Node *find_node(char *name, Node *node)
{
    Node *target = NULL;
    if(node == NULL)
        return NULL;
    if(strcmp(node->name, name) == 0) {
        return node;
    }
    target = find_node(name, node->left);
    if(target == NULL)
        target = find_node(name, node->right);
    return target;
}


int main(void)
{ 
    int j;

    /* 输入 */
    char *line = malloc(sizeof(char) * LINE_MAX_LEN);
    char *token;
    char whitespace[] = " \t\n"; /* whilespace 需要包括换行 */
    for(n_lines=0; ; n_lines++) {
        fgets(line, 100, stdin);
        j = 0;
        /* NOTE strtok 后续调用时，第1个参数传 NULL */
        for(token = strtok(line, whitespace);
                token != NULL && j < 3;
                token = strtok(NULL, whitespace)) {
            /* 陷阱：不同 token 共用内存，每次复制需要拷贝一份 */
            input[n_lines][j++] = strdup(token);
        }
        /* NOTE break 后不再执行调整语句，即最后一轮不自增 n_lines */
        if(j < 3)
            break;
    }

    if(n_lines == 0)
        return 0;

    /* 构建树 */
    Node *root;
    root = malloc(sizeof(Node));
    root->name = input[0][0];
    root->depth = 0;
    root->left = build_tree(input[0][1], root, 1);
    root->right = build_tree(input[0][2], root, 1);

    /* 查找节点 */
    Node *target1 = NULL, *target2 = NULL;
    target1 = find_node(input[n_lines][0], root);
    target2 = find_node(input[n_lines][1], root);
    if(target1 == NULL || target2 == NULL) {
        printf("Not found.\n");
        return EXIT_FAILURE;
    }

    /* 寻找共同祖先 */
    int depth_diff = target1->depth > target2->depth ? \
                     target1->depth - target2->depth : \
                     target2->depth - target1->depth;
    while(target1->depth > target2->depth) 
        target1 = target1->father;
    while(target2->depth > target1->depth) 
        target2 = target2->father;
    while(target1->father != target2->father) {
        target1 = target1->father;
        target2 = target2->father;
    }
    printf("%s %d\n", target1->father->name, depth_diff);
    
    return 0;
}
