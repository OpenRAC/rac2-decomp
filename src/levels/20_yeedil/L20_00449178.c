#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(char *, int, int);

extern void SpawnExplosion(void *a0, int a1, int a2, int a3, int a4, int a5, int a6,
                          int a7, float f12, float f13, int s1, int s2, int s3,
                          int s4);

extern void coll_sweep_from_object(char *, char *, int, int, float, float, float, int, int);

extern void moby_mark_spawned(char *object);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void snd_stop_voice(int);

/* func_L20_00449178 is defined in L20_00449178-state-g8.c. */

/* func_L20_00449338 is defined in L20_00449178-g8.c (it reaches data through $gp). */

/* func_L20_00449850 is defined in L20_00449850-g8.c (it reaches data through $gp). */

/* func_L20_004499E8 is defined in L20_00449178-g8.c (this unit has no $gp access for it). */

/* Returns the flag that says whether this object has been marked as targeted. */
u32 moby_get_targeted_flag(char *moby) {
    char *state = *(char **)(moby + 0x68);

    return *(u32 *)(state + 0xAC);
}

/* Puts the object back into its quiet idle state and clears its visibility flags. */
void moby_reset_to_idle(char *moby) {
    *(u16 *)(moby + 0x34) &= 0xEFFF;
    moby_set_state(moby, 1, -1);
    *(int *)(moby + 0x98) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
}

/* func_L20_00449AE8 is defined in L20_00449178-g8.c (this unit has no $gp access for it). */

/* func_L20_00449BB0 is defined in L20_00449178-g8.c (this unit has no $gp access for it). */

/* func_L20_00449CE0 is defined in L20_00449CE0-g16.c. */

/* func_L20_00449FD0 is defined in L20_00449178-g8.c (this unit has no $gp access for it). */

/* Blows up the projectile with a burst of sparks, adds an impact mark if it hit something, and removes it. */
void projectile_explode(char *moby, char *hitKind) {
    SpawnExplosion(moby + 0x10, 0, 5, 4, 4, 4, 7, 0, 0.333f, 20.0f, 0, 0, 0, 0);
    if (hitKind != 0) {
        coll_sweep_from_object(*(char **)(moby + 0xB8), moby + 0x10, (int)hitKind, 0, 1.5f,
                      4.0f, 1.0f, 1, 0);
    }
    moby_mark_spawned(moby);
}

/* func_L20_0044A1C8 is defined in L20_0044A1C8-g8.c (it reaches data through $gp). */

/* func_L20_0044A658 is defined in L20_00449178-g8.c (it reaches data through $gp). */

/* func_L20_0044A838 is defined in L20_00449178-g8.c (this unit has no $gp access for it). */

/* func_L20_0044A8F0 is defined in L20_00449178-g8.c (it reaches data through $gp). */

/* func_L20_0044AA88 is defined in L20_00449178-g8.c (this unit has no $gp access for it). */

/* Plays a burst of particles at the object and stops its sound if one is playing. */
void turret_death_burst(char *moby) {
    union {
        TI128 q;
        float f[4];
    } offset;
    char *state;

    offset.q = 0;
    offset.f[2] = 0.3f;
    matrix_mul_vec3(&offset, &offset, moby + 0xC0);
    FastVecAdd(&offset, &offset, moby + 0x10);
    SpawnExplosion(&offset, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, 0.666f, 20.0f, 1, 0,
                  0, 0);
    state = *(char **)(moby + 0x68);
    if (*(int *)(state + 0x1B8) != -1) {
        snd_stop_voice(*(int *)(state + 0x1B8));
        *(int *)(state + 0x1B8) = -1;
    }
}

/* func_L20_0044AC38 is defined in L20_0044AC38-g8.c (it reaches a global
   through $gp).  Its near miss is nonmatching/levels/func_L20_0044AC38.c. */

/* func_L20_0044AE58 is defined in L20_0044AE58-g8.c. */

/* func_L20_0044B100 is defined in L20_00449178-g8.c (this unit has no $gp access for it). */
