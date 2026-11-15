#include "include_asm.h"

#include "common.h"
typedef int GateQuad __attribute__((mode(TI)));
typedef union {
    struct {
        float x, y, z, w;
    } v;
    GateQuad q;
} GateVec;
typedef struct GatePath {
    int count;
    char pad04[12];
    GateVec points[0];
} GatePath;
typedef struct GateObject {
    char pad00[0x10];
    GateVec position;
    char pad20[0x10];
    u8 opacity, pad31;
    u16 drawFlags, flags;
    char pad36[0x32];
    void *state;
    char pad6c[0x3e];
    short classId;
    char padac[0x14];
    GateVec forward, right, up;
} GateObject;
extern int g_mission_initialized __attribute__((sda));
extern GateObject *D_L10_001B1400 __attribute__((sda));
extern GateObject *D_L10_001B1404 __attribute__((sda));
extern char *D_L10_001B1408 __attribute__((sda));
extern float D_L10_001B140C __attribute__((sda)), D_L10_001B1410 __attribute__((sda));
extern int D_L10_001B1414 __attribute__((sda)), D_L10_001B1418 __attribute__((sda));
extern int D_L10_001B141C __attribute__((sda));
extern int D_L10_001B1434 __attribute__((sda));
extern int D_L10_001B3550 MACRO_ADDR;
typedef struct {
    char pad[0x2c];
    int field2c;
    char pad30[8];
    int field38;
} GateGlobals;
extern GateGlobals D_L10_00221CD0;
extern GatePath *D_L10_001FE340[];
extern char *D_L10_001B251C[] __attribute__((sda));
extern char D_L10_001B9680[];
extern int g_current_map_index;
extern unsigned char D_0019B278[];
extern void music_Unpause(void), cloud_destroy_leftover_objects(void), entry_init_all_registered(void);
extern void hero_set_state_value_b(int), hero_set_state_value_a(int);
extern GateObject **level_get_object_list(void);
extern int level_get_saved_value(void);
extern GateObject *level_find_object_by_class_id(int);
extern int level_get_saved_value_b(void *);
extern void func_PAL_L05_0037D9D0(void *, int);
extern GateObject *CreateMoby(int);
extern void moby_mark_spawned(void *);
extern void FastVecSub(void *, void *, void *), FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *), fast_vec_dist(void *, void *);
extern void func_PAL_L10_00429620(void *, int), hrugis_reset_mission_state(void *);
extern int math_fast_float_d(int *);
extern char *GetLocalizedString(int);
extern void func_PAL_L00_0030FBC0(void *, int);
extern void snd_play_from_class_bank(int, int, void *, int);
extern void hero_add_clamped_stat(float);
extern void effect_set_enabled(void *, int), effect_set_color(void *, int);
extern char *func_PAL_L05_00432530(void *, int, int, int);

void func_PAL_L10_00429E20(GateObject *p)
{
    GateVec up, pos, v1, v2;
    char *st = p->state, *other;
    GatePath *path;
    GateObject *obj;
    GateObject **list;
    int count, i;
    float d1, d2;

    up.q = 0;
    up.v.z = 1;

    if (!g_mission_initialized) {
        D_L10_001B140C = -1;
        D_L10_001B1410 = -1;
        g_mission_initialized = 1;
        D_L10_001B1400 = 0;
        D_L10_001B1404 = 0;
        D_L10_001B1414 = 0;
        D_L10_001B1418 = 0;
        D_L10_001B141C = 0;
        D_L10_001B3550 = 0;
        D_L10_00221CD0.field2c = 0;
        music_Unpause();
        cloud_destroy_leftover_objects();
        if (D_L10_001B1408)
            moby_mark_spawned(D_L10_001B1408);
        entry_init_all_registered();
        D_L10_001B1408 = 0;
        hero_set_state_value_b(1);
        D_L10_00221CD0.field38 = *(int *)(st + 0x20);
        hero_set_state_value_a(0);
        list = level_get_object_list();
        count = level_get_saved_value();
        for (i = 0; i < count; i++) {
            if (list[i]->classId == 0xf82)
                func_PAL_L05_0037D9D0(list[i], 1);
        }
        path = D_L10_001FE340[*(int *)(st + 0x20)];
        while ((!D_L10_001B1400 || !D_L10_001B1404) && D_L10_001B1418 != path->count) {
            if (path->points[D_L10_001B1418].v.w != -1) {
                obj = CreateMoby(0x114a);
                obj->opacity = 255;
                obj->drawFlags = 0x1ff;
                obj->flags |= 0x100;
                if (!D_L10_001B1400)
                    D_L10_001B1400 = obj;
                else
                    D_L10_001B1404 = obj;
                if (D_L10_001B1418 == path->count - 1) {
                    FastVecSub(&obj->forward, (char *)path + D_L10_001B1418 * 16,
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    obj->forward.v.w = 0;
                    vec_scale_to_length(&obj->forward, &obj->forward, -1);
                } else {
                    FastVecSub(&obj->forward, (char *)path + (D_L10_001B1418 * 16 + 0x20),
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    obj->forward.v.w = 0;
                    vec_scale_to_length(&obj->forward, &obj->forward, 1);
                }
                FastVecCross(&obj->right, &obj->forward, &up);
                vec_scale_to_length(&obj->right, &obj->right, 1);
                FastVecCross(&obj->up, &obj->right, &obj->forward);
                qcopy(&obj->position, (char *)path + (D_L10_001B1418 * 16 + 0x10));
                obj->position.v.w = 0;
            }
            D_L10_001B1418++;
        }
    }

    if (!D_L10_001B1400 && !D_L10_001B1404 && !D_L10_001B1434) {
        func_PAL_L10_00429620(p, 3);
        return;
    }

    if (level_get_saved_value_b(level_find_object_by_class_id(0xf82))) {
        D_L10_001B1434 = 1;
        if (math_fast_float_d((int *)(st + 0x50))) {
            D_L10_001B1434 = 0;
            *(int *)(st + 0x50) = 200;
            hrugis_reset_mission_state(p);
            entry_init_all_registered();
        } else
            goto warning;
    } else if (D_L10_001B141C >= 12) {
        D_L10_001B1434 = 1;
        if (!math_fast_float_d((int *)(st + 0x50))) {
        warning:
            func_PAL_L00_0030FBC0(GetLocalizedString(0x10F6), -1);
        } else {
            D_L10_001B1434 = 0;
            hrugis_reset_mission_state(p);
            entry_init_all_registered();
            *(int *)(st + 0x50) = 200;
        }
    }

    if (D_L10_001B1434)
        return;
    D_L10_001B3550 = D_L10_001B3550 + 1;
    if (D_L10_001B3550 < 2)
        return;

    other = D_L10_001B251C[0] + (*(int *)(st + 0x24) << 8);
    qcopy(&pos, D_L10_001B9680);
    FastVecSub(&v2, &pos, &D_L10_001B1400->position);
    vec_scale_to_length(&v2, &v2, 1);
    FastVecSub(&v1, other + 0x10, &D_L10_001B1400->position);
    vec_scale_to_length(&v1, &v1, 1);
    d1 = FastVecDot(&D_L10_001B1400->forward, &v1);
    d2 = FastVecDot(&D_L10_001B1400->forward, &v2);

    if ((d1 != D_L10_001B140C && d1 > 0) || (d2 != D_L10_001B1410 && d2 > 0)) {
        path = D_L10_001FE340[*(int *)(st + 0x20)];
        if (fast_vec_dist(&pos, &D_L10_001B1400->position) <= 1.25f
            || fast_vec_dist(other + 0x10, &D_L10_001B1400->position) <= 1.25f) {
            snd_play_from_class_bank(15, 0, p, 0xfbf);
            hero_add_clamped_stat(0.5f);
        } else {
            hero_add_clamped_stat(-0.75f);
            D_L10_001B141C++;
        }
        moby_mark_spawned(D_L10_001B1400);
        D_L10_001B1400 = D_L10_001B1404;
        D_L10_001B1404 = 0;
        while (!D_L10_001B1404 && D_L10_001B1418 != path->count) {
            if (path->points[D_L10_001B1418].v.w != -1) {
                obj = CreateMoby(0x114a);
                obj->opacity = 255;
                obj->drawFlags = 0x1ff;
                obj->flags |= 0x100;
                D_L10_001B1404 = obj;
                if (D_L10_001B1418 == path->count - 1) {
                    FastVecSub(&obj->forward, (char *)path + D_L10_001B1418 * 16,
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    obj->forward.v.w = 0;
                    vec_scale_to_length(&obj->forward, &obj->forward, -1);
                } else {
                    FastVecSub(&obj->forward, (char *)path + (D_L10_001B1418 * 16 + 0x20),
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    obj->forward.v.w = 0;
                    vec_scale_to_length(&obj->forward, &obj->forward, 1);
                }
                FastVecCross(&obj->right, &obj->forward, &up);
                vec_scale_to_length(&obj->right, &obj->right, 1);
                FastVecCross(&obj->up, &obj->right, &obj->forward);
                qcopy(&obj->position, (char *)path + (D_L10_001B1418 * 16 + 0x10));
                obj->position.v.w = 0;
            }
            D_L10_001B1418++;
        }
    }

    D_L10_001B140C = d1;
    D_L10_001B1410 = d2;

    if (D_L10_001B1400) {
        effect_set_enabled(D_L10_001B1400, 1);
        if (D_L10_001B1404)
            effect_set_color(D_L10_001B1400, 0x40008000);
        else
            effect_set_color(D_L10_001B1400, 0x4000c6ff);
    }

    if (D_L10_001B1404) {
        effect_set_enabled(D_L10_001B1404, 1);
        effect_set_color(D_L10_001B1404, 0x40808000);
    } else if (!D_L10_001B141C && !D_L10_001B1408 && !D_0019B278[g_current_map_index * 4]) {
        D_L10_001B1408 = func_PAL_L05_00432530(&D_L10_001B1400->position, 0, -1, -1);
    }
}
