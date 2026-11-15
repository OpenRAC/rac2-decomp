#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad00[0x1830]; unsigned char *player;
    char pad1834[0xA60]; int mode;
} ControllerGlobals;
extern ControllerGlobals g_hero_state;
extern char D_L06_00188660[], D_L06_001B9840[];
extern char D_L06_002AA500[], D_L06_00257CC0[], D_L06_002DF000[], D_L06_00257FC0[], D_L06_002DF060[];
extern int D_L06_001B1858[] SDATA(D_L06_001B1858);
extern int D_L06_001B187C SDATA(D_L06_001B187C);
extern int D_L06_001B1880 SDATA(D_L06_001B1880);
extern void effect_pool_clear(void), gfx_add_draw_callback_third(void);
extern int snd_start_in_slot(int, int, char *);
extern void snd_stop_voice(int);
extern void func_PAL_L04_003A47C0(void *), func_PAL_L04_003A49E0(void *), water_advance_controller_state(void *), water_update_ripple_patches(void *);
extern void water_add_splash_entry(char *, float);
extern float math_fabs(float);
extern void math_step_value_toward_target(char *, char *, float, float, float, float);
extern int IsPointInCuboid(char *, int);
typedef struct {
    int kind, count; char *items, *models, *data; int *states; char *aux, *more;
    int *a, *b; unsigned char *owner; void (*update)(void), (*callback)(void);
} Context;

void func_PAL_L06_0045BCD0(unsigned char *obj)
{
    char *d;
    Context context;
    float position[4];
    int count, id, allowed;
    unsigned char *player = g_hero_state.player;
    if (player && *(short *)(player + 0xAA) == 0x45 && player[0x20] != 254 && player[0x20] != 253 && g_hero_state.mode == 49) return;
    d = *(char **)(obj + 0x68);
    if (!d) return;
    count = 1;
    if (*(int *)(d + 0x18) != -1) count = D_L06_001B1858[*(int *)(d + 0x18)];
    count += *(int *)(d + 0x10);
    context.kind = 48; context.count = count;
    context.a = &D_L06_001B187C; context.b = &D_L06_001B1880;
    context.items = D_L06_002AA500; context.models = D_L06_00257CC0; context.data = D_L06_002DF000;
    context.states = D_L06_001B1858; context.aux = D_L06_00257FC0; context.more = D_L06_002DF060;
    context.update = effect_pool_clear; context.callback = gfx_add_draw_callback_third;
    context.owner = obj;
    if (*(unsigned char *)(d + 0x14) == 0 && *(int *)(d + 0x18) != -1) {
        char *firstTarget = D_L06_00188660 + *(int *)(d + 0x38) * 0x70;
        if (*(unsigned char **)(firstTarget + 0x88) != obj || *(unsigned char *)(firstTarget + 0x74) == 0)
            *(int *)(d + 0x38) = snd_start_in_slot(20, 4, (char *)obj);
    } else {
        id = *(int *)(d + 0x38);
        if (id != -1) {
            char *secondTarget = D_L06_00188660 + id * 0x70;
            if (*(unsigned char **)(secondTarget + 0x88) == obj && *(unsigned char *)(secondTarget + 0x74)) snd_stop_voice(id);
        }
        *(int *)(d + 0x38) = -1;
    }
    switch (obj[0x20]) {
    case 0:
        func_PAL_L04_003A47C0(&context);
        water_add_splash_entry((char *)obj, *(float *)(d + 0x34));
        if (*(int *)(d + 0x28) != -1) {
            int alpha = 255;

            obj[0x30] = alpha;
        }
        /* fall through */
    case 1:
        func_PAL_L04_003A49E0(&context);
        break;
    case 2:
        water_advance_controller_state(&context);
        if (math_fabs(*(float *)(obj + 0x18) - *(float *)(d + 0x2C)) <= 2 && *(int *)(d + 0x18) != -1)
            math_step_value_toward_target((char *)obj + 0x18, d + 0x30, *(float *)(d + 0x2C), 0.0024f, 0.0024f, 0.120000005f);
        break;
    }
    water_update_ripple_patches(&context);
    if (*(int *)(d + 0x28) != -1 && !IsPointInCuboid(D_L06_001B9840, *(int *)(d + 0x28))) {
        allowed = 1;
        if (*(int *)(D_L06_001B9840 + 0x2C0)) {
            qcopy(position, D_L06_001B9840);
            position[2] = *(float *)d;
            if (IsPointInCuboid((char *)position, *(int *)(d + 0x28))) allowed = 0;
        }
        if (allowed) {
            for (id = *(int *)(d + 0x10); id < context.count; ++id)
                *(short *)(context.items + id * 0x1190 + 0x1E) = 0;
        }
    }
}
