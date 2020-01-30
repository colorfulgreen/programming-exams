#include <stdio.h>
#include <stdlib.h>


typedef struct SEGMENT {
    int id;
    int sx;
    int sy;
    int ex;
    int ey;
    int used;
} Segment;

int num;
Segment *segments; 

int find_connected_segments(Segment *seg)
{
    Segment *cur;
    int n_segs = 1;
    seg->used = 1;
    for(int i=0; i<num; i++) {
        cur = &segments[i];
        if(cur->id == seg->id || cur->used == 1)
            continue;
        if((cur->sx == seg->sx && cur->sy == seg->sy) ||
                (cur->ex == seg->ex && cur->ey == seg->ey) ||
                (cur->ex == seg->sx && cur->ey == seg->sy) ||
                (cur->sx == seg->ex && cur->sy == seg->ey)) {
            cur->used = 1;
            n_segs += find_connected_segments(cur);
        }
    }
    printf("<< seg s=(%d,%d) e=(%d %d) n_segs=%d\n", 
            seg->sx, seg->sy, 
            seg->ex, seg->ey, n_segs);
    return n_segs;
}

int main(void) 
{
    int sx, sy, ex, ey;
    int i;
    scanf("%d", &num);
    segments = malloc(sizeof(Segment) * num);
    for(i=0; i<num; i++) {
        scanf("%d %d %d %d", &segments[i].sx, &segments[i].sy, 
                             &segments[i].ex, &segments[i].ey);
        segments[i].id = i;
        segments[i].used = 0;
    }

    int n_segs = 0, max_n_segs = 0;
    int left_x, left_y;
    Segment *seg;
    for(i=0; i<num; i++) {
        /* 陷阱：这里需要用指针，若用 seg=segments[i] 则创建了一份拷贝 */
        seg = &segments[i];
        if(seg->used)
            continue;
        n_segs = find_connected_segments(seg); 
        printf("##### seg s=(%d,%d) e=(%d %d) n_segs=%d\n", 
                seg->sx, seg->sy, 
                seg->ex, seg->ey, n_segs);
        if(n_segs > max_n_segs) {
            max_n_segs = n_segs;
            left_x = seg->sx;
            left_y = seg->sy;
        }
    }

    printf("%d %d %d\n", max_n_segs, left_x, left_y);
    return EXIT_SUCCESS;
}
