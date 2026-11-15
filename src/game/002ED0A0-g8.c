#include "names.h"
/* func_002ED0A0: the state block is one struct global (retail bases every field on
   &D_001B8840 and re-derives it from the kept %hi after the calls). The colour loop counts
   j up with the source table indexed by it: loop.c reverses the counter and emits the
   reduced table pointer and count after the hoisted invariants, retail's preheader order. */
#include "include_asm.h"
#include "names.h"
typedef struct { char pad0[0x30]; int a30; int count34; char pad38[0xC]; short n44; char pad46[0xA]; char *obj50; char pad54[0x138]; char *list[1]; } State_2ED0A0;
extern State_2ED0A0 g_scene_playback_state;
extern void FastVecAdd(unsigned char *, unsigned char *, unsigned char *);
/* Sets up the four fading quads of one record in the resident state block:
   picks the 0xD54 record, rebuilds its 0x10-byte blocks through the colour
   helpers and stores the record's first word into the state's draw object. */
extern int D_001AC200 __attribute__((sda));
extern char D_002628D0[];
extern char D_002628F0[];
extern char g_camera_eye_state[];

extern void matrix_mul_vec3(char *, char *, char *);
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);

/* Moves the four backdrop quads of the scene to follow a special object. */
void scene_update_backdrop_quads(void)
{
    char *record;
    int index = -1;
    int flag = 0;
    int limit = 0x270F;
    int i;

    if (g_scene_playback_state.a30 == 0) {
        index = 0x32;
        flag = 1;
    }
    if (index == -1)
        return;
    if (g_scene_playback_state.count34 < index)
        return;
    if (limit < g_scene_playback_state.count34)
        return;
    g_scene_playback_state.obj50 = D_002628D0;
    record = 0;
    for (i = 0; i < g_scene_playback_state.n44; i++) {
        char *entry = g_scene_playback_state.list[i];

        if (*(short *)(entry + 0xAA) == 0xD54 /* moby class 3412 */) {
            record = entry;
            break;
        }
    }
    if (record != 0) {
        char *base = D_002628F0;
        char buf[16];
        int j;

        for (j = 0; j < 4; j++) {
            matrix_mul_vec3(base, (char *)&D_001AC200 + j * 0x10, record + 0xC0);
            FastVecAdd((unsigned char *)base, (unsigned char *)base, (unsigned char *)(record + 0x10));
            FastVecSub(buf, g_camera_eye_state, base);
            vec_scale_to_length(buf, buf, 0.15f);
            FastVecAdd((unsigned char *)base, (unsigned char *)base, (unsigned char *)buf);
            base += 0x10;
        }
    }
    *(int *)(g_scene_playback_state.obj50 + 0x68) = (int)g_scene_playback_state.list[flag];
}
