#include "include_asm.h"
#include "names.h"

extern void *part_find_owned_effect_slot(char *a0, int a1, int a2);

typedef int TI128 __attribute__((mode(TI)));
extern char g_beam_piece_data_a[8] __attribute__((sda));
extern char g_beam_piece_data_b[8] __attribute__((sda));
extern int g_beam_piece_param __attribute__((sda));
extern void func_002A7750_3(char *a0, int a1, int a2);
extern void vec_scale_to_length(void *out, void *in, float scale);
extern void FastVecSub(void *out, void *in1, void *in2);
extern void FastVecAdd(void *out, void *in1, void *in2);
extern void part_explode_object_into_pieces(char *, void *, void *, void *, int, int, int, int, int, int, int);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *a0);

/* Finds a nearby object, fires a beam toward it with a sound, then removes itself. */
void beam_to_target_update(char *self) {
    float beamPoints[2][4] __attribute__((aligned(16)));
    char *state = *(char **)(self + 0x68);
    char *target;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        func_002A7750_3(self, 1, -1);
        break;
    case 1:
        target = (char *)part_find_owned_effect_slot(self, 0x4010000, 0);
        if (target != 0 && *(int *)state == 0) {
            float beamOffset[4] __attribute__((aligned(16)));
            *(TI128 *)beamOffset = 0;
            beamOffset[0] = 3.0f;
            beamOffset[1] = 3.0f;
            vec_scale_to_length(beamPoints[0], target + 0x10, 8.0f);
            vec_scale_to_length(beamPoints[1], target + 0x10, 18.0f);
            FastVecSub(beamPoints[0], beamPoints[0], beamOffset);
            FastVecAdd(beamPoints[1], beamPoints[1], beamOffset);
            part_explode_object_into_pieces(self, beamPoints, g_beam_piece_data_b, g_beam_piece_data_a, 0xFFFF, 0, g_beam_piece_param, 8, 0xFFFF, 0xFF, 0);
            PlayMobySound(0, 0, self);
            func_002A7750_3(self, 2, -1);
        }
        *(unsigned char *)(self + 0xA8) = 0xFF;
        break;
    case 2:
        moby_mark_spawned(self);
        break;
    }
}
