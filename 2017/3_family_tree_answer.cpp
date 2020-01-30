#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct node {
    char name[20];
    int depth;
    struct node *father;
} Node;

int main()
{
    char s[1000];
    int lineno = 0;
    Node nodes[100];
    memset(nodes, 0, sizeof(nodes));
    int node_index = 0;
    
    while(cin.getline(s, 1000)) {
        char names[3][20];
        int name_index = 0, pos_index = 0;
        memset(names, 0, sizeof(names));
        bool last_is_space = false;
        for(int i=0; i<strlen(s); ++i) {
            if(s[i] == ' ') {
                if(!last_is_space) {
                    name_index += 1;
                    pos_index = 0;
                    last_is_space = true;
                }
            }
            else {
                names[name_index][pos_index++] = s[i];
                last_is_space = false;
            }
        }
        name_index += 1;
        if(name_index == 3) {
            if(lineno == 0) {
                strcpy(nodes[node_index].name, names[0]);
                nodes[node_index].father = NULL;
                nodes[node_index].depth = 0;
                node_index++;
            }
            for(int i=0; i<node_index; ++i) {
                if(strcmp(names[0], nodes[i].name) == 0) {
                    for(int j=1; j<name_index; ++j) {
                        /* 没有构建树，用数组存储结构，结构中存储两个额外属性：
                         * 1. father 指针
                         * 2. depth = father.depth + 1 */
                        strcpy(nodes[node_index].name, names[j]);
                        nodes[node_index].father = &nodes[i];
                        nodes[node_index].depth = nodes[i].depth + 1;
                        node_index++;
                    }
                }
            }
        }
        /* 最后一行输入，待查找节点 */
        else {
            Node *p0, *p1;
            for(int i=0; i<node_index; ++i) {
                if(strcmp(names[0], nodes[i].name) == 0) 
                    p0 = &nodes[i];
                if(strcmp(names[1], nodes[i].name) == 0) 
                    p1 = &nodes[i];
            }
            int d_depth = p0->depth - p1->depth;
            while(p0->depth > p1->depth)
                p0 = p0->father;
            while(p1->depth > p0->depth)
                p1 = p1->father;
            while (p0 != p1) {
                p0 = p0->father;
                p1 = p1->father;
            }
            cout << p0->name << ' ' << abs(d_depth) << endl;
        }
        lineno++;
    }
    return 0;
}
