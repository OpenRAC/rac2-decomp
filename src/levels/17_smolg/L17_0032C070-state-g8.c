#include "common.h"
extern float g_falling_breakable_rate __attribute__((sda));
extern int g_aim_hit_result NOT_SDA;
extern unsigned char g_breakable_model_index[];
extern char *g_breakable_model_table[];
extern float func_0031CD58(void *, int, float);
extern void func_0031ACD8(void *, int, int);
extern int func_002EEAF8(void *);
extern void func_00310EC8(void *);
extern void func_002EEEE8(void *, void *, void *);
extern void func_00323370(void *, void *, void *, void *);
typedef unsigned int StateQuad __attribute__((mode(TI)));
/* Updates an object that falls to the ground. When it is hit it turns into its next form and
   later disappears. */
void falling_breakable_update(char *moby) {
    union { StateQuad q; float f[4]; } old_position, delta;
    char *vars = *(char **)(moby + 0x68);
    float ground;
    unsigned char model_index;
    old_position.q = *(StateQuad *)(moby + 0x10);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        if (*(int *)(vars + 0x90) != -1) {
            ground = func_0031CD58(moby + 0x10, 0, 0.5f);
            *(int *)(vars + 0x9C) = g_aim_hit_result;
            if (ground < *(float *)(moby + 0x18)) {
                *(float *)(vars + 0x98) += g_falling_breakable_rate * 0.00027777778f;
                *(float *)(moby + 0x18) -= *(float *)(vars + 0x98);
            } else {
                *(int *)(vars + 0x98) = 0;
                *(float *)(moby + 0x18) = ground;
            }
        }
        break;
    case 1:
        if (*(unsigned char *)(moby + 0x42) == 1 && (*(unsigned char *)(moby + 0x60) & 2)) {
            *(short *)(moby + 0xAA) = 0x921;
            model_index = g_breakable_model_index[0];
            *(unsigned char *)(moby + 0x22) = model_index;
            *(char **)(moby + 0x24) = g_breakable_model_table[*(unsigned char *)(moby + 0x22)];
            *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
            func_0031ACD8(moby, 0, 0);
            *(unsigned char *)(moby + 0x20) = 2;
            if (*(int *)(vars + 0x90) != -1) *(int *)(vars + 0x94) = 600;
        }
        break;
    case 2:
        if (*(int *)(vars + 0x90) != -1 && func_002EEAF8(vars + 0x94)) {
            func_00310EC8(moby);
            return;
        }
        break;
    }
    func_002EEEE8(&delta, moby + 0x10, &old_position);
    func_00323370(vars + 0x50, &delta, moby + 0xF0, moby + 0xF0);
}
