/*
 * 思路：
 * 1. 先在每个交换机节点存储后代设备，之后据此寻找打印机；
 * 2. 打印路径时，向上的路径和向下的路径分开处理；
 */

#include <iostream>
#include <list>

using namespace std;
#define PRINTER 2

typedef struct equipmentNode
{
    int id;
    int type;
    int parentId;
    list<int> includeEquipId;
    equipmentNode *parent;
    equipmentNode *port1;
    equipmentNode *port2;
    equipmentNode *port3;
    equipmentNode *port4;
} *EquipmentNode;

int totalNum = 0;       // 保存设备总台数
int inputInfo[1000][4];
list<EquipmentNode> equipList;  // 保存前序遍历的所有设备的结果


// 记录每个交换机所能到达的下界设备
list<int> UpdateAllEquipArrivalPath(EquipmentNode equip) {
    list<int> valueList;
    valueList.push_back(equip->id);
    if(equip->type != 0)
        return valueList;
    
    int mySonNum = 0;
    if(equip->port1 != NULL) {
        mySonNum++;
        list<int> tmpList = UpdateAllEquipArrivalPath(equip->port1);
        valueList.splice(valueList.begin(), tmpList);
    }
    if(equip->port2 != NULL) {
        mySonNum++;
        list<int> tmpList = UpdateAllEquipArrivalPath(equip->port2);
        valueList.splice(valueList.begin(), tmpList);
    }
    if(equip->port3 != NULL) {
        mySonNum++;
        list<int> tmpList = UpdateAllEquipArrivalPath(equip->port3);
        valueList.splice(valueList.begin(), tmpList);
    }
    if(equip->port4 != NULL) {
        mySonNum++;
        list<int> tmpList = UpdateAllEquipArrivalPath(equip->port4);
        valueList.splice(valueList.begin(), tmpList);
    }
    equip->includeEquipId = valueList;


    /*
    cout << "########## equip = " << equip->id << endl; 
    for(list<int>::iterator j = valueList.begin();
            j!=valueList.end();
            j++) {
        cout << *j << endl;
    }
    */
    return valueList;
}


// 连接输入设备
void ConnectEquipment(EquipmentNode node) {
    int childNUm = 0;
    int sonSum = 0; // 记录孩子的数量
    int i = 0;
    node->port1 = NULL;
    node->port2 = NULL;
    node->port3 = NULL;
    node->port4 = NULL;
    if(node->type == 1 || node->type == 2)
        return;
    for(i = 0; i < totalNum; i++) {
        if(inputInfo[i][2] == node->id && node->type == 0) { // 只有交换机才有端口
            EquipmentNode temp_node = new equipmentNode; // TODO ?
            temp_node->id = inputInfo[i][0];
            temp_node->type = inputInfo[i][1];
            temp_node->parentId = inputInfo[i][2];
            temp_node->parent = node;
            switch(inputInfo[i][3]) {
                case 1:
                    node->port1 = temp_node;
                    break;
                case 2:
                    node->port2 = temp_node;
                    break;
                case 3:
                    node->port3 = temp_node;
                    break;
                case 4:
                    node->port4 = temp_node;
                    break;
                default:
                    break;
            }
            ConnectEquipment(temp_node);
        }
    }
}


// 通过 id 找到该设备的类型
int FindEquipmentTypeById(int id) {
    for(list<EquipmentNode>::iterator j = equipList.begin();
            j!=equipList.end();
            j++) {
        if((*j)->id == id)
            return (*j)->type;
    }
    return -1;
}


// 向上发现最近父亲包含的打印机 ?
EquipmentNode FindShortestPath(EquipmentNode equip) {
    int lastId = 0;     // 保存上一次的 id
    cout << equip->id << "-->";     // 输出路径
    while(true) {
        for(list<int>::iterator i = equip->includeEquipId.begin();
                i!=equip->includeEquipId.end();
                i++) {
            if(FindEquipmentTypeById(*i) == PRINTER) {
                return equip;
            }
        }
        if(equip->parent == NULL)
            return equip;
        else {
            lastId = equip->id;
            equip = equip->parent;
            cout << lastId << "-->";
        }
    }
}


// 先序遍历
void PreOrder(EquipmentNode equip)
{
    equipList.push_back(equip);
    if(equip->port1 != NULL)
        PreOrder(equip->port1);
    if(equip->port2 != NULL)
        PreOrder(equip->port2);
    if(equip->port3 != NULL)
        PreOrder(equip->port3);
    if(equip->port4 != NULL)
        PreOrder(equip->port4);
    return;
}


EquipmentNode returnSatisfyEquipment(EquipmentNode equip) {
    if(equip->type == PRINTER) 
        return equip;
    else if(equip->type == 1)
        return NULL;
    else if(equip->port1 == NULL && equip->port2 == NULL && equip->port3 == NULL && equip->port4 == NULL)
        return NULL;
    else if(equip->port1 != NULL && equip->port1->type == PRINTER)
        return equip->port1;
    else if(equip->port2 != NULL && equip->port2->type == PRINTER)
        return equip->port2;
    else if(equip->port3 != NULL && equip->port3->type == PRINTER)
        return equip->port3;
    else if(equip->port4 != NULL && equip->port4->type == PRINTER)
        return equip->port4;

    EquipmentNode node = NULL;
    if(equip->port1 != NULL) {
        node = returnSatisfyEquipment(equip->port1);
        if(node != NULL && node->type == PRINTER)
            return node;
    }
    if(equip->port2 != NULL) {
        node = returnSatisfyEquipment(equip->port2);
        if(node != NULL && node->type == PRINTER)
            return node;
    }
    if(equip->port3 != NULL) {
        node = returnSatisfyEquipment(equip->port3);
        if(node != NULL && node->type == PRINTER)
            return node;
    }
    if(equip->port4 != NULL) {
        node = returnSatisfyEquipment(equip->port4);
        if(node != NULL && node->type == PRINTER)
            return node;
    }

    return NULL;
}


void printPath(EquipmentNode startNode, EquipmentNode endNode) {
    cout << startNode->id << "-->";
    if(startNode == endNode)
        return;
    if(startNode->port1 != NULL && std::find(startNode->port1->includeEquipId.begin(),
                startNode->port1->includeEquipId.end(),
                endNode->id) != startNode->port1->includeEquipId.end())
        printPath(startNode->port1, endNode);
    else if(startNode->port2 != NULL && std::find(startNode->port2->includeEquipId.begin(),
                startNode->port2->includeEquipId.end(),
                endNode->id) != startNode->port2->includeEquipId.end())
        printPath(startNode->port2, endNode);
    else if(startNode->port3 != NULL && std::find(startNode->port3->includeEquipId.begin(),
                startNode->port3->includeEquipId.end(),
                endNode->id) != startNode->port3->includeEquipId.end())
        printPath(startNode->port3, endNode);
    else if(startNode->port4 != NULL && std::find(startNode->port4->includeEquipId.begin(),
                startNode->port4->includeEquipId.end(),
                endNode->id) != startNode->port4->includeEquipId.end())
        printPath(startNode->port4, endNode);
}

// 输出到打印机的最短路径，如果有两个，输出前序遍历的第一个
void printShortestPathToPrinter(EquipmentNode equip) {
    EquipmentNode printerEquip = returnSatisfyEquipment(equip);
    printPath(equip, printerEquip);
    cout << printerEquip->id << endl;
    cout << "打印机Id为：" << printerEquip->id;
}

int main()
{
    cout << "请输入设备的台数：";
    cin >> totalNum;
    cout << "依次输入每台设备，id, 类型(0:交换机,1:电脑,2:打印机), 父节点id(根的父节点为0), 端口号(1\\2\\3\\4)" << endl;

    int id, type, parentId, port;
    for(int i = 0; i < totalNum; i++) {
        cin >> id >> type >> parentId >> port;
        inputInfo[i][0] = id;
        inputInfo[i][1] = type;
        inputInfo[i][2] = parentId;
        inputInfo[i][3] = port;
    }

    // 最顶层的设备一定是交换机
    EquipmentNode root = new equipmentNode;
    for(int i=0; i<totalNum; i++) {
        if(inputInfo[i][2] == 0) {
            root->parentId = 0;
            root->id = inputInfo[i][0];
            root->type = inputInfo[i][1];
        }
    }
    ConnectEquipment(root);
    root->includeEquipId = UpdateAllEquipArrivalPath(root);
    PreOrder(root);
    cout << "请输入要查找的ID：";
    int findId; // 想要查到的 ID
    while(true) {
        cin >> findId;
        list<EquipmentNode>::iterator j;
        for(j = equipList.begin(); j != equipList.end(); j++) {
            if((*j)->id == findId) break;
        }
        if(j == equipList.end()) {cout << "你输入的 ID 有误";}
        // 找到包含最近的打印机的父亲或祖父，输入向上的路径
        EquipmentNode findParent = FindShortestPath(*j); 

        // 找到离该父亲最近的打印机，输出向下的路径
        printShortestPathToPrinter(findParent);
        cout << endl;
        cout << endl;
        cout << "请输入要查找的ID：";
        getchar();
        getchar();
        return 0;
    }

}
