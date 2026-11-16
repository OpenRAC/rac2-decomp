/* Spawn setup; the cached class-0xFBF moby is accessed through $gp. */
#include "common.h"

/* The parts of a moby this unit touches. */
typedef struct Moby_L05_00425FE0 {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ float position[4];
    /* 0x20 */ char pad20[4];
    /* 0x24 */ char *pClass;
    /* 0x28 */ struct Moby_L05_00425FE0 *pChain;
    /* 0x2C */ float scale;
    /* 0x30 */ unsigned char updateDist;
    /* 0x31 */ unsigned char drawn;
    /* 0x32 */ short drawDist;
    /* 0x34 */ char pad34[0xAA - 0x34];
    /* 0xAA */ short oClass;
    /* 0xAC */ char padAC[0xF0 - 0xAC];
    /* 0xF0 */ float rot[4];
} Moby_L05_00425FE0;

/* The moby of class 0xFBF, found once. */
extern Moby_L05_00425FE0 *g_glow_effect_target_moby __attribute__((sda));
/* The head of the moby list. */
extern Moby_L05_00425FE0 *g_moby_l05_list_head;

extern Moby_L05_00425FE0 *CreateMoby(int);
extern void vec_clear_128(float *);
extern float math_random_angle(void);
extern void glow_l05_ring_init_state_3(Moby_L05_00425FE0 *);

/* Spawns a moby of class 0x117C at the caller's position with a random turn, remembers the
   last moby of class 0xFBF in the list the first time, and sets up the new moby's state. */
Moby_L05_00425FE0 *moby_spawn_class_a(Moby_L05_00425FE0 *object)
{
    Moby_L05_00425FE0 *moby;
    Moby_L05_00425FE0 *m;

    moby = CreateMoby(0x117C);
    if (moby != 0) {
        moby->updateDist = 0xFF;
        moby->drawDist = 0xFF;
        moby->drawn = 1;
        qcopy(moby->position, object->position);
        vec_clear_128(moby->rot);
        moby->rot[2] = math_random_angle();
        if (g_glow_effect_target_moby == 0) {
            for (m = g_moby_l05_list_head; m != 0; m = m->pChain) {
                if (m->oClass == 0xFBF)
                    g_glow_effect_target_moby = m;
            }
        }
        glow_l05_ring_init_state_3(moby);
        moby->scale = *(float *)(moby->pClass + 0x24);
        return moby;
    }
    return 0;
}
