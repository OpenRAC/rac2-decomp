#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad00[0x1830]; unsigned char *player;
    char pad1834[0xA60]; int mode;
} ControllerGlobals;
extern ControllerGlobals g_hero_state;
extern char g_effect_target_records[], g_hero_l06_position[];
extern char g_effect_items[], g_effect_models[], g_effect_data[], g_effect_aux_buffer[], g_effect_more_data[];
extern int g_effect_group_counts[] SDATA(D_L06_001B1858);
extern int g_effect_context_a SDATA(D_L06_001B187C);
extern int g_effect_context_b SDATA(D_L06_001B1880);
extern void effect_pool_clear(void), gfx_add_draw_callback_third(void);
extern int snd_start_in_slot(int, int, char *);
extern void snd_stop_voice(int);
extern void water_init_object_pal(void *), water_update_controller_pal(void *), water_advance_controller_state(void *), water_update_ripple_patches(void *);
extern void water_add_splash_entry(char *, float);
extern float math_fabs(float);
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern int IsPointInCuboid(char *, int);
typedef struct {
    int kind, count; char *items, *models, *data; int *states; char *aux, *more;
    int *a, *b; unsigned char *owner; void (*update)(void), (*callback)(void);
} Context;

/* Runs a group of effect objects for the owner: sets them up, updates each step and hides them when the hero is too close. */
void effect_group_update_pal(unsigned char *obj)
{
    char *vars;
    Context context;
    float position[4];
    int count, id, allowed;
    unsigned char *player = g_hero_state.player;
    if (player && *(short *)(player + 0xAA) == 0x45 && player[0x20] != 254 && player[0x20] != 253 && g_hero_state.mode == 49) return;
    vars = *(char **)(obj + 0x68);
    if (!vars) return;
    count = 1;
    if (*(int *)(vars + 0x18) != -1) count = g_effect_group_counts[*(int *)(vars + 0x18)];
    count += *(int *)(vars + 0x10);
    context.kind = 48; context.count = count;
    context.a = &g_effect_context_a; context.b = &g_effect_context_b;
    context.items = g_effect_items; context.models = g_effect_models; context.data = g_effect_data;
    context.states = g_effect_group_counts; context.aux = g_effect_aux_buffer; context.more = g_effect_more_data;
    context.update = effect_pool_clear; context.callback = gfx_add_draw_callback_third;
    context.owner = obj;
    if (*(unsigned char *)(vars + 0x14) == 0 && *(int *)(vars + 0x18) != -1) {
        char *first_target = g_effect_target_records + *(int *)(vars + 0x38) * 0x70;
        if (*(unsigned char **)(first_target + 0x88) != obj || *(unsigned char *)(first_target + 0x74) == 0)
            *(int *)(vars + 0x38) = snd_start_in_slot(20, 4, (char *)obj);
    } else {
        id = *(int *)(vars + 0x38);
        if (id != -1) {
            char *second_target = g_effect_target_records + id * 0x70;
            if (*(unsigned char **)(second_target + 0x88) == obj && *(unsigned char *)(second_target + 0x74)) snd_stop_voice(id);
        }
        *(int *)(vars + 0x38) = -1;
    }
    switch (obj[0x20]) {
    case 0:
        water_init_object_pal(&context);
        water_add_splash_entry((char *)obj, *(float *)(vars + 0x34));
        if (*(int *)(vars + 0x28) != -1) {
            int alpha = 255;

            obj[0x30] = alpha;
        }
        /* fall through */
    case 1:
        water_update_controller_pal(&context);
        break;
    case 2:
        water_advance_controller_state(&context);
        if (math_fabs(*(float *)(obj + 0x18) - *(float *)(vars + 0x2C)) <= 2 && *(int *)(vars + 0x18) != -1)
            math_step_value_toward_target((char *)obj + 0x18, vars + 0x30, *(float *)(vars + 0x2C), 0.0024f, 0.0024f, 0.120000005f);
        break;
    }
    water_update_ripple_patches(&context);
    if (*(int *)(vars + 0x28) != -1 && !IsPointInCuboid(g_hero_l06_position, *(int *)(vars + 0x28))) {
        allowed = 1;
        if (*(int *)(g_hero_l06_position + 0x2C0)) {
            qcopy(position, g_hero_l06_position);
            position[2] = *(float *)vars;
            if (IsPointInCuboid((char *)position, *(int *)(vars + 0x28))) allowed = 0;
        }
        if (allowed) {
            for (id = *(int *)(vars + 0x10); id < context.count; ++id)
                *(short *)(context.items + id * 0x1190 + 0x1E) = 0;
        }
    }
}
