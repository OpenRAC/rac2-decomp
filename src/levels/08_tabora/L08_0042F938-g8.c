#include "names.h"
/* func_L08_0042F938 (392 bytes): a moby's three states, idle, waiting for its model, and
   burst (ported from func_L06_00402440 / func_L20_00449178). func_0032C700 returns a
   pointer; declared void it swaps the two stack constants of the next call. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int,
                              int, int, int);
extern void part_spawn_scaled_bolts(void *, int, float);
extern char *moby_l00_spawn_child(void *, int, int);
extern void moby_mark_spawned(void *);

extern float g_burst_piece_param_a __attribute__((sda));
extern float g_burst_piece_param_b __attribute__((sda));
extern float g_burst_piece_param_c __attribute__((sda));

/* a moby's three states: idle, waiting for its model, and burst */
void burst_update(char *obj)
{
    char *vars = *(char **)(obj + 0x68);
    float vec[4] __attribute__((aligned(16)));

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(obj, 0x4010000, 0) != 0) {
            if (*(int *)vars == 0)
                moby_set_state(obj, 2, -1);
        }
        *(unsigned char *)(obj + 0xA8) = 0xFF;
        break;
    case 2:
        *(TI128 *)vec = 0;
        vec[2] = 7.0f;
        FastVecAdd(vec, obj + 0x10, vec);
        SpawnExplosion(vec, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.75f, 20.0f, 1, 1, 0, 0);
        part_explode_object_into_pieces(obj, &g_burst_piece_param_c, &g_burst_piece_param_b, &g_burst_piece_param_a,
                          0xFFFF, 0, -1, 7, 0xFFFF, 0xFF, 0);
        part_spawn_scaled_bolts(obj, 5, 4.0f);
        moby_l00_spawn_child(obj, 0x12A0, 0);
        moby_mark_spawned(obj);
        break;
    }
}
