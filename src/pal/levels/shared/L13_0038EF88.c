#include "include_asm.h"
#include "names.h"

typedef struct {
    int entries[64];     
    int count;           
} Table_389848;
extern Table_389848 ref_L13_00232450_00;
typedef struct {
    char pad_00[0x20];         
    unsigned char state;       
    char pad_21[0x0F];
    unsigned char flag;        
    char pad_31[0x37];
    Table_389848 *table;       
} Obj_38C1B8;
extern int IsPointInCuboid(void *, int);
extern void FadeToBlack(int);
extern void hero_record_play_counters(void);
extern void ref_L13_0038C1B8_00(int, int);
extern char g_hero_position[];
extern char g_hero_state[];

/* The state byte at +0x20 drives the work: state 0 clears the flag at +0x30 and moves the
 * object to state 1, state 1 walks the sixty-four entries of the table at +0x68 in two
 * halves of thirty-two, and any other state does nothing.  D_00189EA0 is the pointer the
 * entry test hands to func_002ACBC8, and the map selection block D_00189E20 sits 0x80
 * before it. */
void func_PAL_L13_0038EF88(Obj_38C1B8 *a0)
{
    Table_389848 *t = a0->table;
    int *e;
    unsigned char *q;
    unsigned char *m;
    int i;
    int j;
    int v;

    switch (a0->state) {
    case 0:
        a0->state = 1;
        a0->flag = 0xFF;
        break;
    case 1:
        q = (unsigned char *)g_hero_state;
        e = t->entries + 32;
        for (i = 0; i < 32; i++) {
            v = t->entries[i];
            if (v < 0)
                continue;
            if (IsPointInCuboid(g_hero_position, v) == 0)
                continue;
            if (t->count != 0) {
                *(float *)(q + 0x24C8) = 0.25f;
                continue;
            }
            m = (unsigned char *)g_hero_position - 0x80;
            if (m[0x22B4] != 0) {
                FadeToBlack(8);
                hero_record_play_counters();
            } else if (*(int *)(m + 0x2294) != 0x74) {
                ref_L13_0038C1B8_00(0x74, 1);
            }
        }
        for (j = 0; j < 32; j++) {
            v = e[j];
            if (v < 0)
                continue;
            if (IsPointInCuboid(g_hero_position, v) == 0)
                continue;
            FadeToBlack(8);
            hero_record_play_counters();
        }
        break;
    }
}

