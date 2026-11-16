/* Spawn setup; the cached class-0xFBF moby is accessed through $gp. */
#include "common.h"

/* The parts of a moby this unit touches. */
typedef struct Moby_L05_0041C118 {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ float position[4];
    /* 0x20 */ char pad20[4];
    /* 0x24 */ char *pClass;
    /* 0x28 */ struct Moby_L05_0041C118 *pChain;
    /* 0x2C */ float scale;
    /* 0x30 */ unsigned char updateDist;
    /* 0x31 */ unsigned char drawn;
    /* 0x32 */ short drawDist;
    /* 0x34 */ char pad34[0xAA - 0x34];
    /* 0xAA */ short oClass;
    /* 0xAC */ char padAC[0xF0 - 0xAC];
    /* 0xF0 */ float rot[4];
} Moby_L05_0041C118;

/* The moby of class 0xFBF, found once. */
extern Moby_L05_0041C118 *g_homing_pickup_target __attribute__((sda));
/* The head of the moby list. */
extern Moby_L05_0041C118 *g_moby_l05_list_head;

extern Moby_L05_0041C118 *CreateMoby(int);
extern void vec_clear_128(float *);
extern float math_random_angle(void);
extern void glow_l05_ring_init_state(Moby_L05_0041C118 *);

/* Spawns a moby of class 0x10CF at the caller's position with a random turn, remembers the
   last moby of class 0xFBF in the list the first time, and sets up the new moby's state. */
Moby_L05_0041C118 *pickup_spawn_homing(Moby_L05_0041C118 *caller)
{
    Moby_L05_0041C118 *moby;
    Moby_L05_0041C118 *other;

    moby = CreateMoby(0x10CF /* moby class 4303 */);
    if (moby != 0) {
        moby->updateDist = 0xFF;
        moby->drawDist = 0xFF;
        moby->drawn = 1;
        qcopy(moby->position, caller->position);
        vec_clear_128(moby->rot);
        moby->rot[2] = math_random_angle();
        if (g_homing_pickup_target == 0) {
            for (other = g_moby_l05_list_head; other != 0; other = other->pChain) {
                if (other->oClass == 0xFBF /* moby class 4031 */)
                    g_homing_pickup_target = other;
            }
        }
        glow_l05_ring_init_state(moby);
        moby->scale = *(float *)(moby->pClass + 0x24);
        return moby;
    }
    return 0;
}
