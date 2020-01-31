#include <stdio.h>
#include <stdlib.h>

typedef struct WINDOW {
    int id;
    int lx;
    int ly;
    int rx;
    int ry;
    struct WINDOW *next;
} Window;


/* 被点击窗口移动到链表头部，返回新的 head 指针 */
Window *adjust_windows(Window *head, int click_x, int click_y)
{
    Window *p = head, *prev = NULL, *next;
    while(p != NULL) {
        if(click_x >= p->lx && click_x <= p->rx && click_y >= p->ly && click_y <= p->ry) {
            if(prev == NULL)
                return head;
            prev->next = p->next;
            p->next = head;
            head = p; /* 陷阱：别忘了调整 head */
        }
        prev = p;
        p = p->next;
    }

    return head;
}

int main(void)
{
    int n_windows, n_clicks;
    Window *head, *prev, *w;

    scanf("%d", &n_windows);
    if(n_windows == 0)
        return 0;

    /* 构建窗口链表 */
    head = malloc(sizeof(Window));
    scanf("%d %d %d %d %d", &head->id, &head->lx, &head->ly, &head->rx, &head->ry);
    prev = head;
    for(int i=1; i<n_windows; i++) {
        w = malloc(sizeof(Window));
        scanf("%d %d %d %d %d", &w->id, &w->lx, &w->ly, &w->rx, &w->ry);
        w->next = NULL;
        prev->next = w;
        prev = w;
    }

    /* 处理点击 */
    int click_x, click_y;
    scanf("%d", &n_clicks);
    for(int i=0; i<n_clicks; i++) {
        scanf("%d %d", &click_x, &click_y);
        head = adjust_windows(head, click_x, click_y);
    }

    /* 按序打印窗口id */
    w = head;
    printf("%d", w->id);
    w = w->next;
    while(w != NULL) {
        printf(" %d", w->id);
        w = w->next;
    }

    return 0;

}
