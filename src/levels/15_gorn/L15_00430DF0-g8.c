/* func_L15_00430DF0: path-marker course step of a Gorn stage object. Its own unit:
 * the $gp-relative state needs -G8, and retail clears the stack vector at 0($sp)
 * with a materialised por zero (-frac2-zero-ti-por). */
#include "common.h"
typedef struct { char pad[0x30]; unsigned char alpha; char pad31; unsigned short colour, flags; } PathObject;
typedef int PathQuad __attribute__((mode(TI)));
typedef union { PathQuad q; float f[4]; } PathVector;
typedef struct { int pointCount; int pad[3]; PathVector point[1]; } PathRoute;
typedef struct { char pad[0x2C]; int reset; char gap[8]; int route; } PathPhase;
extern PathPhase D_L15_00221E10 NOT_SDA;
extern PathRoute *D_L15_001FE480[] NOT_SDA;
extern int D_L15_001B3698 MACRO_ADDR;
extern char *D_L15_001B261C MACRO_ADDR;
extern PathVector D_L15_001B97C0 NOT_SDA;
extern int g_current_map_index;
extern unsigned char D_0019B278[];
extern void music_Unpause(void), moby_mark_spawned(void *), entry_init_all_registered(void), hero_set_state_value_b(int), hero_set_state_value_a(int), entry_spawn_list_objects_with_flag(char *, int);
extern char **level_get_object_list(void);
extern int level_get_saved_value(void), level_get_saved_value_b(void *), math_fast_float_d(int *);
extern char *CreateMoby(int), *level_find_object_by_class_id(int);
extern void FastVecSub(void *, void *, void *), FastVecCross(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *), fast_vec_dist(void *, void *);
extern void gorn_finish_challenge_stage(void *, int), ResetGornStageCounters(void *);
extern void *GetLocalizedString(int);
extern void level_l00_call_module_handler_with_arg_9(void *, int), hero_add_clamped_stat(float), effect_set_enabled(void *, int), effect_set_color(void *, unsigned int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern char *pickup_spawn_if_not_taken(void *, int, int, int);
extern int D_L15_001B1534 __attribute__((sda));
extern char * D_L15_001B1584 __attribute__((sda));
extern char * D_L15_001B1588 __attribute__((sda));
extern char * D_L15_001B158C __attribute__((sda));
extern float D_L15_001B1590 __attribute__((sda));
extern float D_L15_001B1594 __attribute__((sda));
extern int D_L15_001B1598 __attribute__((sda));
extern int D_L15_001B159C __attribute__((sda));
extern int D_L15_001B15A4 __attribute__((sda));
extern int D_L15_001B15C0 __attribute__((sda));
/* Retail reads this counter absolutely and writes the same address via $gp: D_L15_001B3698 through a second small-data declaration. */
extern int D_L15_001B3698_1 __attribute__((sda));
#define init D_L15_001B1534
#define first D_L15_001B1584
#define next D_L15_001B1588
#define effect D_L15_001B158C
#define oldHero D_L15_001B1590
#define oldCamera D_L15_001B1594
#define index D_L15_001B159C
#define misses D_L15_001B15A4
#define waiting D_L15_001B15C0
#define count D_L15_001B3698_1
/* Runs the Gorn path-marker course: spawns marker rings along a path and scores each one the player or camera reaches. */
void gorn_path_marker_course_update(char *moby)
{
    PathVector up, camera, fromHero, fromCamera;
    char *vars = *(char **)(moby + 0x68), *object, *hero;
    PathRoute *path;
    char **list;
    float heroDot, cameraDot;
    int objectCount, i;
    unsigned short objectFlags;
    char *oldFirst;
    up.q = 0;
    up.f[2] = 1;
    if (!init) {
        first = 0; next = 0;
        oldCamera = oldHero = -1;
        init = 1;
        D_L15_001B1598 = 0; index = 0; misses = 0;
        D_L15_001B3698 = 0; D_L15_00221E10.reset = 0;
        music_Unpause();
        if (effect) moby_mark_spawned(effect);
        entry_init_all_registered(); effect = 0;
        hero_set_state_value_b(1);
        D_L15_00221E10.route = *(int *)(vars + 0x30);
        hero_set_state_value_a(0);
        list = level_get_object_list(); objectCount = level_get_saved_value();
        for (i = 0; i < objectCount; i++) if (*(short *)(list[i] + 0xAA) == 0xF82 /* moby class 3970 */) entry_spawn_list_objects_with_flag(list[i], 1);
        path = D_L15_001FE480[*(int *)(vars + 0x30)];
        while ((!first || !next) && index != path->pointCount) {
            if (path->point[index].f[3] != -1) {
            object = CreateMoby(0x114A /* moby class 4426 */);
            ((unsigned char *)object)[0x30] = 0xFF;
            objectFlags = *(unsigned short *)(object + 0x34);
            oldFirst = first;
            *(short *)(object + 0x32) = 0x1FF;
            *(unsigned short *)(object + 0x34) = objectFlags | 0x100;
            if (!oldFirst) first = object; else next = object;
            if (index == path->pointCount - 1) {
                FastVecSub(object + 0xC0, &path->point[index - 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, -1);
            } else {
                FastVecSub(object + 0xC0, &path->point[index + 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, 1);
            }
            FastVecCross(object + 0xD0, object + 0xC0, &up);
            vec_scale_to_length(object + 0xD0, object + 0xD0, 1);
            FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[index]);
            *(int *)(object + 0x1C) = 0;
            }
            index++;
        }
    }
    if (!first && !next && !waiting) { gorn_finish_challenge_stage(moby, 3); return; }
    if (level_get_saved_value_b(level_find_object_by_class_id(0xF82 /* moby class 3970 */))) {
        waiting = 1;
        if (math_fast_float_d((int *)(vars + 0x64))) { waiting = 0; *(int *)(vars + 0x64) = 240; ResetGornStageCounters(moby); entry_init_all_registered(); }
        else level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x31DE), -1);
    } else if (misses >= 12) {
        waiting = 1;
        if (!math_fast_float_d((int *)(vars + 0x64))) level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x31DE), -1);
        else { waiting = 0; *(int *)(vars + 0x64) = 240; ResetGornStageCounters(moby); entry_init_all_registered(); }
    }
    if (waiting) return;
    count = D_L15_001B3698 + 1;
    if (count < 2) return;
    hero = D_L15_001B261C + (*(int *)(vars + 0x20) << 8);
    qcopy(&camera, &D_L15_001B97C0);
    FastVecSub(&fromCamera, &camera, first + 0x10);
    vec_scale_to_length(&fromCamera, &fromCamera, 1);
    FastVecSub(&fromHero, hero + 0x10, first + 0x10);
    vec_scale_to_length(&fromHero, &fromHero, 1);
    heroDot = FastVecDot(first + 0xC0, &fromHero);
    cameraDot = FastVecDot(first + 0xC0, &fromCamera);
    if ((heroDot != oldHero && heroDot > 0) || (cameraDot != oldCamera && cameraDot > 0)) {
        path = D_L15_001FE480[*(int *)(vars + 0x30)];
        if (fast_vec_dist(&camera, first + 0x10) <= 1.25f || fast_vec_dist(hero + 0x10, first + 0x10) <= 1.25f) {
            snd_play_from_class_bank(15, 0, moby, 0xFBF); hero_add_clamped_stat(0.5f);
        } else { hero_add_clamped_stat(-0.75f); misses++; }
        moby_mark_spawned(first); first = next; next = 0;
        while (!next && index != path->pointCount) {
            if (path->point[index].f[3] != -1) {
            object = CreateMoby(0x114A /* moby class 4426 */);
            ((PathObject *)object)->alpha = 0xFF; ((PathObject *)object)->colour = 0x1FF; ((PathObject *)object)->flags |= 0x100;
            next = object;
            if (index == path->pointCount - 1) {
                FastVecSub(object + 0xC0, &path->point[index - 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, -1);
            } else {
                FastVecSub(object + 0xC0, &path->point[index + 1], &path->point[index]);
                *(int *)(object + 0xCC) = 0;
                vec_scale_to_length(object + 0xC0, object + 0xC0, 1);
            }
            FastVecCross(object + 0xD0, object + 0xC0, &up);
            vec_scale_to_length(object + 0xD0, object + 0xD0, 1);
            FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
            qcopy(object + 0x10, &path->point[index]);
            *(int *)(object + 0x1C) = 0;
            }
            index++;
        }
    }
    oldHero = heroDot; oldCamera = cameraDot;
    if (first) {
        effect_set_enabled(first, 1);
        if (next) effect_set_color(first, 0x40008000);
        else effect_set_color(first, 0x4000C6FF);
    }
    if (next) { effect_set_enabled(next, 1); effect_set_color(next, 0x40808000); }
    else if (!misses && !effect && !D_0019B278[g_current_map_index * 4]) effect = pickup_spawn_if_not_taken(first + 0x10, 0, -1, -1);
}
