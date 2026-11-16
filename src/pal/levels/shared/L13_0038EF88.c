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
void trigger_list_check_hero_pal(Obj_38C1B8 *obj)
{
    Table_389848 *table = obj->table;
    int *second_half;
    unsigned char *hero_state;
    unsigned char *hero_base;
    int i;
    int j;
    int entry;

    switch (obj->state) {
    case 0:
        obj->state = 1;
        obj->flag = 0xFF;
        break;
    case 1:
        hero_state = (unsigned char *)g_hero_state;
        second_half = table->entries + 32;
        for (i = 0; i < 32; i++) {
            entry = table->entries[i];
            if (entry < 0)
                continue;
            if (IsPointInCuboid(g_hero_position, entry) == 0)
                continue;
            if (table->count != 0) {
                *(float *)(hero_state + 0x24C8) = 0.25f;
                continue;
            }
            hero_base = (unsigned char *)g_hero_position - 0x80;
            if (hero_base[0x22B4] != 0) {
                FadeToBlack(8);
                hero_record_play_counters();
            } else if (*(int *)(hero_base + 0x2294) != 0x74) {
                ref_L13_0038C1B8_00(0x74, 1);
            }
        }
        for (j = 0; j < 32; j++) {
            entry = second_half[j];
            if (entry < 0)
                continue;
            if (IsPointInCuboid(g_hero_position, entry) == 0)
                continue;
            FadeToBlack(8);
            hero_record_play_counters();
        }
        break;
    }
}

