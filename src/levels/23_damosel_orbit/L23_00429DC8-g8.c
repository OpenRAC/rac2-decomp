#include "include_asm.h"
#include "names.h"

/* func_L23_00429DC8 is a unit of its own: retail clears its start vector as plain C, with the
   zero materialised (`por $v0,$zero,$zero` ... `sq $v0,0($sp)`), which -frac2-zero-ti-por keeps,
   and copies it with the grouped quadword copy and its scheduling barrier (-frac2-qcopy
   -frac2-qcopy-barrier; config/cflags.txt). */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef int TI128 __attribute__((mode(TI)));

typedef union { TI128 q; float f[4]; } V4;

/* the globals it arms, and the list it fills */
extern s16 g_effect_sound_handle_a __attribute__((sda));
extern s16 g_effect_sound_handle_b __attribute__((sda));
extern s32 g_trail_spawn_index __attribute__((sda));
extern s32 g_effect_link_count[4] __attribute__((sda));
extern s32 g_effect_link_cursor[4] __attribute__((sda));
extern s32 D_L23_001B3934_2[4] __attribute__((sda)); /* the same word as D_L23_001B3934 */
extern s32 g_trail_effect_cursors[16] __attribute__((sda));
extern float g_trail_ribbon_dirs[][4];
extern s32 g_effect_link_active_flags[];
typedef struct { s16 a; s16 b; s32 c; } Edge; /* 8 bytes; the array is walked through an s16 cast */
extern Edge g_effect_link_edges[];
extern s32 g_effect_link_table[];
extern void moby_set_state(void *, s32, s32);

/* arms the object once: clears the list, builds the 500/500/575 start position and the 16 slots
   (the count, spread over the list of used edges, scaled by sixteenths) */
/* Sets up the controller object the first time it runs. It places it, counts which links
   between points are in use, and fills a table of 16 steps. */
void effect_controller_init_link_table(u8 *obj) {
    s32 *payload = *(s32 **)(obj + 0x68);
    s32 i, j, k, m, n, found;
    V4 v;

    if (obj[0x20] == 0) {
        D_L23_001B3934_2[0] = 0;
        g_effect_sound_handle_b = -1;
        g_effect_sound_handle_a = -1;
        g_trail_spawn_index = 0;
        g_effect_link_cursor[0] = 0;
        *(s16 *)(obj + 0x32) = 0x50;
        obj[0x30] = 0xFF;
        payload[0] = 0;
        payload[2] = 0;
        payload[1] = 0;
        v.q = 0;
        v.f[0] = 500.0f;
        v.f[1] = 500.0f;
        v.f[2] = 575.0f;
        *(TI128 *)(obj + 0x10) = v.q;
        moby_set_state(obj, 1, 0);
        for (i = 0; i < 0x48; i++) {
            float *p = g_trail_ribbon_dirs[i];

            if (0.0f < p[2]) {
                g_effect_link_active_flags[i] = 1;
                for (j = 0; j < 0x9C; j++) {
                    if (((s16 *)g_effect_link_edges)[j * 4] == i || ((s16 *)g_effect_link_edges)[j * 4 + 1] == i) {
                        n = g_effect_link_count[0];
                        found = 0;
                        for (k = 0; k < n; k++) {
                            if (g_effect_link_table[k] == j) {
                                found = 1;
                                break;
                            }
                        }
                        if (!found) {
                            g_effect_link_table[g_effect_link_count[0]] = j;
                            D_L23_001B3934_2[0] = g_effect_link_count[0] + 1;
                        }
                    }
                }
            } else {
                g_effect_link_active_flags[i] = 0;
            }
        }
        {
            s32 count = D_L23_001B3934_2[0];

            for (m = 0; m < 16; m++) {
                g_trail_effect_cursors[m] = (m * count) / 16;
            }
        }
    }
}
