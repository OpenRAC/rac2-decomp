#include "common.h"
typedef struct SUB_3B0AB0 {
    char pad0[0x17];
    unsigned char f17;
} SUB_3B0AB0;

typedef struct OBJ_3B0AB0 {
    long f0;
    char pad0[0x20 - 8];
    SUB_3B0AB0 s20;
} OBJ_3B0AB0;

extern char g_effect_path_node_table[];

extern void part_kill(void *);

/* Removes the effect object tied to a trail point if it still belongs to that point. */
void node_free_effect_object(int idx)
{
    unsigned char index = idx;
    char *base = g_effect_path_node_table;
    char *at = base + 0x10;
    char *slot = at + (unsigned char)idx * 0x1C;
    OBJ_3B0AB0 *obj = *(OBJ_3B0AB0 **)slot;

    if (obj != 0) {
        SUB_3B0AB0 *extra = &obj->s20;

        if ((obj->f0 & 0x80FF) == 0x51)
            if (extra->f17 == index) {
                part_kill(obj);
                *(OBJ_3B0AB0 **)slot = 0;
            }
    }
}
