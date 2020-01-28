#include <stdio.h>
#include <stdlib.h>

#define SWITCH 0
#define PC 1
#define PRINTER 2

#define N_PORTS 4

typedef struct DEVICE {
    int id;
    int type;
    int parent_id;
    struct DEVICE *parent;

    /* 交换机特有属性 */
    struct DEVICE *ports[N_PORTS];

} Device;

int count = 0;
int **input;
int g_node = -1, g_min_pc_dis = -1, g_min_printer_dis = -1;
enum {ID, TYPE, PARENT_ID, PORT_ID} F;


void attach_children(Device *parent)
{
    Device *node = NULL;
    for(int i=0; i<count; i++) {
        if(input[i][PARENT_ID] == parent->id) {
            node = malloc(sizeof(Device));
            node->id = input[i][ID];
            node->type = input[i][TYPE];
            node->parent_id = input[i][PARENT_ID];
            node->parent = parent;
            for(int j=0; j<N_PORTS; j++)
                node->ports[j] = NULL;
            parent->ports[input[i][PORT_ID]] = node;
            if(node->type == 0)
                attach_children(node);
        }
    }
}


int min_pc_distance(int pc_id, Device *node)
{
    int pc_dis = -1, min_pc_dis = -1;
    if(node->type == PC && node->id == pc_id) {
        return 0;
    }
    if(node->type == SWITCH) {
        for(int i=0; i<N_PORTS; i++) {
            if(node->ports[i] == NULL)
                continue;
            pc_dis = min_pc_distance(pc_id, node->ports[i]);
            //printf("node=%d port=%d dis=%d\n", node->id, i, pc_dis);
            if(pc_dis == -1)
                continue;
            pc_dis += 1;
            if(min_pc_dis == -1 || pc_dis < min_pc_dis)
                min_pc_dis = pc_dis;
        }
    }
    return min_pc_dis;
}

int min_printer_distance(Device *node)
{
    int pc_dis = -1, min_pc_dis = -1;
    if(node->type == PRINTER) {
        puts("############");
        return 0;
    }
    if(node->type == SWITCH) {
        for(int i=0; i<N_PORTS; i++) {
            if(node->ports[i] == NULL)
                continue;
            pc_dis = min_printer_distance(node->ports[i]);
            //printf("node=%d port=%d dis=%d\n", node->id, i, pc_dis);
            if(pc_dis == -1)
                continue;
            pc_dis += 1;
            if(min_pc_dis == -1 || pc_dis < min_pc_dis)
                min_pc_dis = pc_dis;
        }
    }
    return min_pc_dis;
}

void find_nearest_printers(int pc_id, Device *node)
{
    int pc_dis = -1,
        printer_dis = -1,
        min_pc_dis = -1,
        min_printer_dis = -1;
    if(node->type != SWITCH)
        return;
    for(int i=0; i<N_PORTS; i++) {
        if(node->ports[i] == NULL)
            continue;
        pc_dis = min_pc_distance(pc_id, node->ports[i]);
        printer_dis = min_printer_distance(node->ports[i]);
        if(pc_dis != -1 && printer_dis != -1) {
            find_nearest_printers(pc_id, node->ports[i]);
            return;
        }
        if(pc_dis != -1)
            if(min_pc_dis == -1 || pc_dis + 1 < min_pc_dis)
                min_pc_dis = pc_dis + 1;
        if(printer_dis != -1)
            if(min_printer_dis == -1 || printer_dis + 1 < min_printer_dis) 
                min_printer_dis = printer_dis + 1;
    }
    printf("###%d type=%d %d %d\n", node->id, node->type, min_pc_dis, min_printer_dis);
    if(min_printer_dis == -1 || min_pc_dis == -1)
        return;
    if((g_min_pc_dis == -1 && g_min_printer_dis == -1)
            || min_pc_dis + min_printer_dis < g_min_pc_dis + g_min_printer_dis) {
        g_node = node->id;
        g_min_pc_dis = min_pc_dis;
        g_min_printer_dis = min_printer_dis;
    }
}


void print_tree(Device *root)
{
    printf("%d %d %d\n", root->id, root->type, root->parent_id);
    for(int i=0; i<N_PORTS; i++) {
        if(root->ports[i] != NULL)
            print_tree(root->ports[i]);
    }
}


int main(void){
    FILE *f;
    int id, type, parent_id, port_id;
    int pc_id;
    Device *root, *node = NULL;

    /* 处理输入数据：
     * 设备数
     * id 类型 父节点id 接入父节点的端口号
     */
    f = fopen("2_data", "r");
    fscanf(f, "%d", &count);
    input = malloc(sizeof(int *) * count);
    for(int i=0; i<count; i++){
        fscanf(f, "%d %d %d %d", &id, &type, &parent_id, &port_id);
        input[i] = malloc(sizeof(int) * 4);
        input[i][ID] = id;
        input[i][TYPE] = type;
        input[i][PARENT_ID] = parent_id;
        input[i][PORT_ID] = port_id;
    }
    fscanf(f, "%d", &pc_id);
    fclose(f);

    for(int i=0; i<count; i++){
        printf("%d %d %d %d\n", input[i][0], input[i][1], input[i][2], input[i][3]);
    }

    /* 构建树 */
    for(int i=0; i<count; i++) {
        if(input[i][PARENT_ID] == 0){
            root = malloc(sizeof(Device));
            root->id = input[i][ID];
            root->type = input[i][TYPE];
            root->parent_id = input[i][PARENT_ID];
            root->parent = NULL;
            for(int j=0; j<N_PORTS; j++)
                root->ports[i] = NULL;
            if(root->type == 0)
                attach_children(root);
            break;
        }
    }
    /* print_tree(root); 
    int min_dis = min_printer_distance(root);
    printf("%d\n", min_dis);
    */

    find_nearest_printers(pc_id, root);
    printf("node=%d pc_dis=%d printer_dis=%d\n", g_node, g_min_pc_dis, g_min_printer_dis);

    /* TODO 路径的存储 */
    return EXIT_SUCCESS;
}
