#include <iostream>
#include <list>
#include <numeric>
#include <algorithm>

using namespace std;

typedef struct treeNode {
    treeNode *left;
    treeNode *center;
    treeNode *right;
    treeNode *parent;
    int value; // 优先级, >500 是乘客
    int vipLevel;
    list<int> arrivalNodes;
} TreeNode;

list<TreeNode *> waitPassengers;
list<TreeNode *> waitPassengersSort;
int totalFloor;

int input[1000][4]; // 记录输入


void CreateTree(TreeNode *root)
{
    int childNum = 0;
    int i = 0;
    for(i=0; i<totalFloor; i++) {
        if(input[i][0] == root->value)
            break;
    }
    if(input[i][1] != 0) {
        TreeNode *node = new TreeNode;
        root->left = node;
        node->value = input[i][1];
        node->parent = root;
        childNum++;
        CreateTree(node);
    } else {
        root->left = NULL;
    }
    if(input[i][2] != 0) {
        TreeNode *node = new TreeNode;
        root->center = node;
        node->value = input[i][2];
        node->parent = root;
        childNum++;
        CreateTree(node);
    } else {
        root->center = NULL;
    }
    if(input[i][3] != 0) {
        TreeNode *node = new TreeNode;
        root->right = node;
        node->value = input[i][3];
        node->parent = root;
        childNum++;
        CreateTree(node);
    } else {
        root->right = NULL;
    }

    if(childNum == 0) {
        waitPassengers.push_back(root);
    }
}


// 先序遍历
void PreOrder(TreeNode *node)
{
    if(node->left != NULL) 
        PreOrder(node->left);
    if(node->center != NULL) 
        PreOrder(node->center);
    if(node->right != NULL) 
        PreOrder(node->right);
    return;
}


void SortPassenger() {
    list<int> vipLevel;
    list<TreeNode *>::iterator i;
    for(i = waitPassengers.begin(); i != waitPassengers.end(); i++) {
        vipLevel.push_back((*i)->value);
    }
    vipLevel.sort();

    list<int>::iterator j;
    for(j = vipLevel.begin(); j != vipLevel.end(); j++) {
        for(i = waitPassengers.begin(); i != waitPassengers.end(); i++) {
            if((*i)->value == *j) {
                waitPassengersSort.push_front(*i);
            }
        }
    }
}

// 递归记录每个点所能到达的后代结点
list<int> InitAllNodeArrivalValue(TreeNode *node) {
    list<int> valueList;
    valueList.push_back(node->value);
    int mySonNum = 0;
    if(node->left != NULL) {
        mySonNum++;
        list<int> tmpList = InitAllNodeArrivalValue(node->left);
        valueList.splice(valueList.begin(), tmpList);
    }
    if(node->center != NULL) {
        mySonNum++;
        list<int> tmpList = InitAllNodeArrivalValue(node->center);
        valueList.splice(valueList.begin(), tmpList);
    }
    if(node->right != NULL) {
        mySonNum++;
        list<int> tmpList = InitAllNodeArrivalValue(node->right);
        valueList.splice(valueList.begin(), tmpList);
    }
    valueList.sort();
    node->arrivalNodes = valueList;
    return valueList;
}


// 往上寻找到达下个旅客位置的父节点或者祖父
TreeNode *FindParentIncludeNode(TreeNode *curNode, TreeNode *endNode) {
    cout << curNode->value << "-->";
    if(curNode == endNode) {
        return curNode;
    }
    while(true) {
        if(std::find(curNode->parent->arrivalNodes.begin(),
                    curNode->parent->arrivalNodes.end(),
                    endNode->value) != curNode->parent->arrivalNodes.end()) {
            return curNode->parent;
        } 
        else {
            curNode = curNode->parent;
            cout << curNode->value << "-->";
        }
    }
}


// 往下寻找到达下个旅客位置的子节点或者孙子
void FindSonIncludeNode(TreeNode *curNode, TreeNode *endNode, TreeNode *root) {
    if(curNode == endNode) {
        if(curNode->value == root->value) {
            cout << endNode->value << "回到出发点";
            return;
        }
        cout << endNode->value << "到达";
        return;
    }
    if(std::find(curNode->arrivalNodes.begin(),
                curNode->arrivalNodes.end(),
                endNode->value) != curNode->arrivalNodes.end()) {
        cout << curNode->value << "-->";
    }
    if(curNode->left != NULL) {
        FindSonIncludeNode(curNode->left, endNode, root);
    }
    if(curNode->center != NULL) {
        FindSonIncludeNode(curNode->center, endNode, root);
    }
    if(curNode->right != NULL) {
        FindSonIncludeNode(curNode->right, endNode, root);
    }
}


void Send(TreeNode *curNode, TreeNode *sendNode, TreeNode *root) {
    cout << endl << "从 " << curNode->value << "到 " << sendNode->value << "的最短距离为：";
    if(std::find(curNode->arrivalNodes.begin(),
                curNode->arrivalNodes.end(),
                sendNode->value) != curNode->arrivalNodes.end()) {
        // 向下寻找
        FindSonIncludeNode(curNode, sendNode, root);
    }
    else {
        // 向上寻找
        TreeNode *parentNode = FindParentIncludeNode(curNode, sendNode);
        FindSonIncludeNode(parentNode, sendNode, root);
    }
}


int main()
{
    cout << "请输入节点数：";
    cin >> totalFloor;
    int rt, l, c, r;
    for(int i=0; i<totalFloor; i++) {
        cin >> rt >> l >> c >> r;
        input[i][0] = rt;
        input[i][1] = l;
        input[i][2] = c;
        input[i][3] = r;
    }
    TreeNode *root = new TreeNode;
    root->value = input[0][0];
    root->parent = NULL;
    CreateTree(root);
    cout << endl;
    int size = waitPassengers.size();
    // 初始化每个节点所能到达的值
    InitAllNodeArrivalValue(root);
    PreOrder(root);
    // 优先级排队
    SortPassenger();
    // 送旅客
    TreeNode *curNode = root; // 开始时在根结点
    for(list<TreeNode *>::iterator node = waitPassengersSort.begin();
            node != waitPassengersSort.end();
            node++) {
        Send(curNode, *node, root);
        curNode = *node;
    }
    Send(curNode, root, root);
    getchar();
    getchar();
    return 0;
}
