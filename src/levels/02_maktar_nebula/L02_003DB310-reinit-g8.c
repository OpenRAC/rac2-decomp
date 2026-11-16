#include "common.h"
typedef int Quad __attribute__((mode(TI)));
/* Position window; complete surrounding storage extent is unknown. */
extern char g_brawler_target_position[] SDATA(D_L02_001B03F0);
extern char *g_moby_l02_pool;
typedef struct { char pad[0x80]; float x, y; } HeroPosition;
extern HeroPosition g_hero_state;
extern char *CreateMoby(int);
extern void func_002A0F48(void *);
extern void moby_transform_joint_point(void *, int, void *);
extern float mat_fast_helper_a(float, float);
extern void func_002A05A8(void *);
extern void func_002A10E8(void *);
extern void mem_clear(void *, int, int);
extern void AttachManipulator(void *, int, void *);
extern void moby_set_state(void *, int, int);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern void set_moby_color(void *, int, int, int);
#define PRIVATE (*(char **)(actor + 0x68))
#define ATTACHMENT (*(char **)(PRIVATE + 0x260))
#define CHILD (D_L02_001B359C + *(int *)(PRIVATE + 0x244) * 0x100)
typedef struct { char pad[0x34]; unsigned short flags; char pad36[0xC2]; float heading; } ActorFlags;
/* Reinitializes an actor and its child, attaching the three active effect slots. */
void ReinitializeActorAndChild(char *actor, int use_alt_state) {
    char *state = PRIVATE;
    Quad joint_matrix[4];
    int hit_points;
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(unsigned char *)(actor + 0x31) = 1;
    ((ActorFlags *)actor)->flags &= 0xFFFE;
    hit_points = *(int *)(*(char **)(actor + 0x24) + 0x10);
    ((ActorFlags *)actor)->flags = (((ActorFlags *)actor)->flags | 0x1000) & 0xFFFD;
    *(int *)(actor + 0x98) = hit_points;
    *(int *)(actor + 0x9C) = 0;
    *(unsigned char *)(actor + 0x7F) = 0;
    *(unsigned char *)(state + 0x2E) = 1;
    qcopy(actor + 0x10, g_brawler_target_position);
    *(char **)(PRIVATE + 0x260) = CreateMoby(0xA4C /* moby class 2636 */);
    if (ATTACHMENT != 0) {
        *(unsigned char *)(ATTACHMENT + 0x30) = *(unsigned char *)(actor + 0x30);
        *(unsigned short *)(ATTACHMENT + 0x32) = *(unsigned short *)(actor + 0x32);
        *(unsigned char *)(ATTACHMENT + 0x31) = 1;
        *(long long *)(ATTACHMENT + 0x38) = *(long long *)(actor + 0x38);
        func_002A0F48(ATTACHMENT);
        *(int *)(ATTACHMENT + 0x98) = 0;
        ((ActorFlags *)ATTACHMENT)->flags |= 2;
        ((ActorFlags *)ATTACHMENT)->flags &= 0xFFFE;
        *(unsigned char *)(ATTACHMENT + 0x31) = 1;
    }
    moby_transform_joint_point(actor, 0, joint_matrix);
    qcopy(CHILD + 0x10, &joint_matrix[3]);
    *(float *)(actor + 0xF8) = mat_fast_helper_a(g_hero_state.x - *(float *)(actor + 0x10), g_hero_state.y - *(float *)(actor + 0x14));
    ((ActorFlags *)CHILD)->heading = mat_fast_helper_a(g_hero_state.x - *(float *)(actor + 0x10), g_hero_state.y - *(float *)(actor + 0x14));
    func_002A05A8(CHILD);
    func_002A0F48(CHILD);
    func_002A10E8(CHILD);
    ((ActorFlags *)CHILD)->flags &= 0xFFFE;
    *(unsigned char *)(CHILD + 0x31) = 1;
    *(int *)(CHILD + 0x98) = *(int *)(*(char **)(CHILD + 0x24) + 0x10);
    if (*(unsigned char *)(state + 0x171) == 0) {
        mem_clear(state + 0x170, 0, 0x40);
        AttachManipulator(CHILD, 2, state + 0x170);
    }
    if (*(unsigned char *)(state + 0x1B1) == 0) {
        mem_clear(state + 0x1B0, 0, 0x40);
        AttachManipulator(CHILD, 3, state + 0x1B0);
    }
    if (*(unsigned char *)(state + 0x1F1) == 0) {
        mem_clear(state + 0x1F0, 0, 0x40);
        AttachManipulator(CHILD, 4, state + 0x1F0);
    }
    if (use_alt_state == 0) {
        moby_set_state(actor, 2, 0);
        *(int *)(state + 0x264) = 0;
    } else moby_set_state(actor, 4, 0);
    *(short *)(state + 0x288) = FloatToInt(math_random_float_range(600.0f, 1200.0f));
    *(short *)(state + 0x280) = 0;
    *(short *)(state + 0x282) = 0;
    if (*(short *)(state + 0x140) != 0) {
        *(short *)(state + 0x140) = 0;
        set_moby_color(actor, *(int *)(state + 0x270), *(int *)(state + 0x274), *(int *)(state + 0x278));
        *(short *)(state + 0x142) = 1;
    }
}
