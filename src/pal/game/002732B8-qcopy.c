#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad00[0x20];
    unsigned char *obj;
    short flag;
    char pad26[10];
} F273418Mark;
typedef struct {
    F273418Mark e[6];
    int count;
} F273418Marks;
extern int g_game_mode;
extern int g_reticle_screen_params[] __attribute__((sda));
extern F273418Marks g_hud_reticle_marks;
extern void DrawTargetReticle_pal(void);
extern void gfx_project_world_point_to_screen(void *, void *);
extern void gfx_draw_screen_sprite(void *, float, float);
extern float IntToFloat(int);

void hud_draw_reticle_and_markers_pal(void) {
    float base[4] __attribute__((aligned(16)));
    float vec[4] __attribute__((aligned(16)));
    F273418Mark *m;
    int i;

    if (g_game_mode == 111) {
        g_hud_reticle_marks.count = 0;
        return;
    }
    DrawTargetReticle_pal();
    if (g_hud_reticle_marks.count != 0) {
        base[0] = IntToFloat(g_reticle_screen_params[0]);
        base[1] = IntToFloat(g_reticle_screen_params[1]);
        for (i = 0; i < g_hud_reticle_marks.count; i++) {
            m = &g_hud_reticle_marks.e[i];
            if (m->obj != 0 && m->obj[0x20] != 0xFE && m->obj[0x20] != 0xFD) {
                if (m->flag != 0) {
                    gfx_project_world_point_to_screen(vec, m);
                    vec[0] = (vec[0] - IntToFloat(g_reticle_screen_params[2])) * 0.0625f;
                    vec[1] = (vec[1] - IntToFloat(g_reticle_screen_params[3])) * 0.0625f;
                } else {
                    qcopy(vec, base);
                }
                gfx_draw_screen_sprite(m, vec[0], vec[1]);
            }
        }
        g_hud_reticle_marks.count = 0;
    }
}
