#include "include_asm.h"
#include "names.h"

extern void *part_find_owned_effect_slot(char *a0, int a1, int a2);
typedef int TI128 __attribute__((mode(TI)));
extern char g_beam_piece_data_a[8] __attribute__((sda));
extern char g_beam_piece_data_b[8] __attribute__((sda));
extern int g_beam_piece_param __attribute__((sda));
extern void moby_set_state(char *a0, int a1, int a2);
extern void vec_scale_to_length(void *out, void *in, float scale);
extern void FastVecSub(void *out, void *in1, void *in2);
extern void FastVecAdd(void *out, void *in1, void *in2);
extern void part_explode_object_into_pieces_pal(char *, void *, void *, void *, int, int, int, int, int, int, int);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *a0);

/* Finds a nearby object, fires a beam toward it with a sound, then removes itself. (PAL) */
void beam_to_target_update_pal(char *moby) {
    float pts[2][4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    char *effect_slot;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        effect_slot = (char *)part_find_owned_effect_slot(moby, 0x4010000, 0);
        if (effect_slot != 0 && *(int *)vars == 0) {
            float off[4] __attribute__((aligned(16)));
            *(TI128 *)off = 0;
            off[0] = 3.0f;
            off[1] = 3.0f;
            vec_scale_to_length(pts[0], effect_slot + 0x10, 8.0f);
            vec_scale_to_length(pts[1], effect_slot + 0x10, 18.0f);
            FastVecSub(pts[0], pts[0], off);
            FastVecAdd(pts[1], pts[1], off);
            part_explode_object_into_pieces_pal(moby, pts, g_beam_piece_data_b, g_beam_piece_data_a, 0xFFFF, 0, g_beam_piece_param, 8, 0xFFFF, 0xFF, 0);
            PlayMobySound(0, 0, moby);
            moby_set_state(moby, 2, -1);
        }
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        break;
    case 2:
        moby_mark_spawned(moby);
        break;
    }
}
