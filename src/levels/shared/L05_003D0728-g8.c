#include "names.h"
/* The -G8 sibling of L05_0037B6D0.c: with -G8 the level globals are re-materialised at each use, as in retail. */

extern unsigned char *g_moby_l05_list_head;
extern unsigned char *g_linked_point_table;
extern int ref_L05_003D0728_00(void *dst, void *src);
extern int ref_L05_003D0728_01(void *obj, void *src, int id);
extern void ref_L05_003D0728_02(void *obj);

/* On its first frame, spawns a wave of small enemies of three kinds around the spawner. */
void func_L05_003D0728(unsigned char *obj)
{
    long long buf[2];
    unsigned char *info;
    unsigned char *list;
    unsigned char *entry;
    int i;

    if (obj[0x20] != 0)
        return;
    info = *(unsigned char **)(obj + 0x68);
    obj[0x20] = 1;
    list = g_moby_l05_list_head;
    while (list != 0) {
        if (*(short *)(list + 0xAA) == 0x12B3) {
            *(long long *)(obj + 0x38) = *(long long *)(list + 0x38);
            break;
        }
        list = *(unsigned char **)(list + 0x28);
    }
    entry = g_linked_point_table + (*(int *)info << 7);
    *(float *)(entry + 0x3C) = 1.0f;
    for (i = 0; i < *(short *)(info + 0xE); i++) {
        ref_L05_003D0728_00(buf, entry);
        ref_L05_003D0728_01(obj, buf, 0x956);
    }
    list = g_moby_l05_list_head;
    while (list != 0) {
        if (*(short *)(list + 0xAA) == 0x12B6) {
            *(long long *)(obj + 0x38) = *(long long *)(list + 0x38);
            break;
        }
        list = *(unsigned char **)(list + 0x28);
    }
    for (i = 0; i < *(short *)(info + 0xC); i++) {
        ref_L05_003D0728_00(buf, entry);
        ref_L05_003D0728_01(obj, buf, 0x953);
    }
    for (i = 0; i < *(int *)(info + 0x8); i++) {
        ref_L05_003D0728_00(buf, entry);
        ref_L05_003D0728_01(obj, buf, 0x954);
    }
    ref_L05_003D0728_02(obj);
}
