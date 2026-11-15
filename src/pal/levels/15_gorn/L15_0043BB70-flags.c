#include "include_asm.h"

#include "common.h"
typedef int GornQuad __attribute__((mode(TI)));
/* The grouped 16-byte transfer. As an inline its address argument is built in the parameter's own
   register, so a later use of the same record computes its address again, as retail does. */
static __inline__ void GornCopyQuad(void *dst, void *src) {
    *(GornQuad *)dst = *(GornQuad *)src;
}
typedef struct GornPathPoint {
    float position[3];
    float action;
} GornPathPoint;
typedef struct GornPath {
    int count;
    int pad[3];
    GornPathPoint points[1];
} GornPath;
typedef struct GornMoby {
    char pad00[0x10];
    float position[4];
    u8 state;
    char pad21[0x47];
    char *vars;
    char pad6C[0x10];
    short x7C;
    char pad7E[0x42];
    float rotation[16];
} GornMoby;
typedef struct GornSlot {
    char pad00[0x40];
    int active;
    char pad44[0x1C];
} GornSlot;
extern GornSlot D_L15_0026C3E0[];
extern u16 *D_L15_001FB320[];
extern int D_L15_001FE480[];
extern GornMoby *D_L15_001B261C[] __attribute__((sda));
extern u8 *moby_get_motion_data(void *);
extern void set_identity_rotation_rows(void *);
extern void vec_clear_128(void *);
extern void follower_set_state(void *, int);
extern void follower_set_push_vector(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_below(int);

/* Clears the arena's 128 records of 0x60 bytes, then walks the entry's two-byte id list and puts
   every object back at its saved position, on the first point of its path. */
void func_PAL_L15_0043BB70(u8 *self) {
    GornSlot *slots;
    int i;
    u16 *list;
    u16 *p;
    int id;
    char *state;
    u8 *owner;
    GornPath *path;
    u8 *velocity;

    slots = D_L15_0026C3E0;
    for (i = 0; i < 128; i++) {
        slots[i].active = 0;
    }
    list = D_L15_001FB320[self[0x21]];
    if (list == 0)
        return;
    p = list;
    do {
        id = *p & 0x7FFF;
        state = D_L15_001B261C[0][id].vars;
        owner = moby_get_motion_data(&D_L15_001B261C[0][id]);
        D_L15_001B261C[0][id].x7C = 0x3F;
        GornCopyQuad((char *)&D_L15_001B261C[0][id] + 0x10, state + 0x430);
        set_identity_rotation_rows(D_L15_001B261C[0][id].rotation);
        *(int *)(state + 0x27C) = 0;
        vec_clear_128(state + 0x400);
        self[0x23] = 0x7F;
        *(u16 *)(self + 0x34) &= 0xFFF7;
        D_L15_001B261C[0][id].state = 1;
        path = (GornPath *)D_L15_001FE480[*(int *)(state + 0x448)];
        *(int *)(state + 0x44C) = 1;
        GornCopyQuad((char *)&D_L15_001B261C[0][id] + 0x10, &path->points[0]);
        *(int *)&D_L15_001B261C[0][id].position[3] = 0;
        follower_set_state(&D_L15_001B261C[0][id], 2);
        velocity = owner + 0x90;
        follower_set_push_vector(&D_L15_001B261C[0][id], &path->points[(*(int *)(state + 0x44C))++]);
        FastVecSub(velocity, owner + 0x60, (char *)&D_L15_001B261C[0][id] + 0x10);
        vec_scale_to_length(velocity, velocity, 0.020000001f);
        *(int *)(owner + 0x130) = 1666667;
        *(int *)(state + 0x450) = 0;
        *(int *)(state + 0x454) = math_random_int_below(2);
    } while (*(short *)p++ >= 0);
}
