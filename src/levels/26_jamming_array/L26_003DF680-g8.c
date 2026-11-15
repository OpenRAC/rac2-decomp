#include "include_asm.h"
#include "names.h"

/* Kind 0 arms the record; kind 1 advances the two wrapped counters by a sixtieth of the
   frame time, re-rolling the second one whenever the first wraps. */
typedef unsigned char u8;

extern void moby_set_state(unsigned char *, int, int);
extern float math_random_float_range(float, float);
extern void gfx_add_draw_callback_first(void *, void *);
extern void DrawDoubleLayerQuadMesh(void);

extern int D_L26_001A8FF0;
extern float D_L26_001B0660 __attribute__((sda));

typedef struct { float f[2]; float g[2]; } Counters;

/* Per-frame update for the moby of class 3217: it advances two pairs of cycling values that drive
   the flicker of the double-layer quad mesh, then asks for that mesh to be drawn. */
void quad_flicker_update(char *moby) {
    char *obj = moby;
    char *vars = *(char **)(obj + 0x68);
    int i;
    int next;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        *(u8 *)(obj + 0x30) = 0xFF;
        moby_set_state((unsigned char *)obj, 1, -1);
        *(int *)vars = 0;
        *(float *)(vars + 4) = 0.5f;
        break;
    case 1:
        if (D_L26_001A8FF0 != 0) {
            for (i = 0; i < 2; i = next) {
                float value;

                next = i + 1;
                value = ((Counters *)vars)->f[i] + D_L26_001B0660 * 0.016666667f;
                ((Counters *)vars)->f[i] = value;
                if (1.0f < value) {
                    value = value - 1.0f;
                    ((Counters *)vars)->f[i] = value;
                    value = ((Counters *)vars)->g[next & 1] + math_random_float_range(0.333f, 0.666f);
                    ((Counters *)vars)->g[i] = value;
                    if (1.0f < value) {
                        value = value - 1.0f;
                        ((Counters *)vars)->g[i] = value;
                    }
                }
            }
            gfx_add_draw_callback_first((void *)DrawDoubleLayerQuadMesh, obj);
        }
        break;
    }
}
