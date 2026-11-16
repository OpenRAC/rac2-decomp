#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    float x, y, z, w;
    float pad[4];
} Rec32;
extern unsigned short **g_record_lists;
extern Rec32 *g_sky_records;
extern u8 *g_record_table;
extern u8 *g_actor_shared_state;
extern float g_spinning_parts_timer_rate __attribute__((sda));
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);

/* Spins a group of parts: doubles their weight at the start, then turns them every frame. */
void spinning_parts_group_update_pal(u8 *moby) {
    int *vars = *(int **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0: {
        unsigned short *p;
        Rec32 *e;
        u8 none = 0xFF;

        if (vars[0] == -1)
            break;
        moby[0x30] = none;
        for (p = g_record_lists[vars[0]];
             p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == g_record_lists[vars[0]]) &&
             (e = g_sky_records + (*p & 0x7FFF)) != 0;
             p++)
            e->w = e->w + e->w;
        moby[0x20] = 1;
        break;
    }
    case 1: {
        unsigned short *p;
        u8 *e;
        float v[4];
        float m[12];
        float x;
        u8 *g;

        for (p = g_record_lists[vars[0]];
             p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == g_record_lists[vars[0]]) &&
             (e = g_record_table + ((*p & 0x7FFF) << 6)) != 0;
             p++) {
            *(TI128 *)v = 0;
            v[2] = 0.00942478f;
            euler_rotation_basis(m, v);
            multiply_matrix3x3(e, e, m);
        }
        g = g_actor_shared_state;
        x = *(float *)(g + 0x74) + g_spinning_parts_timer_rate * 0.020000001f;
        *(float *)(g + 0x74) = x;
        if (x > 1.0f)
            *(float *)(g + 0x74) = x - 1.0f;
        break;
    }
    }
}
