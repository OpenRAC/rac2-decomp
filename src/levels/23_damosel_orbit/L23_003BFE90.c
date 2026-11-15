#include "include_asm.h"
#include "names.h"

typedef int TI16 __attribute__((mode(TI)));

struct Vecs {
    TI16 a;
    TI16 b;
    TI16 unused[3];
    TI16 c;
    TI16 d;
};

extern char D_00189E20[];

extern float D_L23_001B370C __attribute__((sda));

extern void func_00282D30(char *, char *, float);

extern void func_00282CC0(char *, char *, char *);

extern void func_0029FC20(char *, int, char *);

extern void func_002830C0(char *, char *, char *);

extern void func_00282CF0(char *, char *, char *);

extern void func_00282F20(char *, char *, float);

extern void func_L23_00429098(char *, char *, char *, int, float);

extern void func_002E5DA0(int, int, char *, int);

/* Fills the stack vectors v.a, v.b, v.c and v.d from the table at D_00189E20, the owner's helper and a
   unit vector (0, 1, 0, 1) whose second float is negated when arg2 is set, scales v.d by
   D_L23_001B370C / 60 and passes it with v.c and arg1 to func_L23_00429098; then calls func_002E5DA0.
   The clear of v.c is retail's `sq $zero,0($reg)`, a scheduling barrier (-frac2-zero-ti-barrier): the 1.0f
   is made before it, as retail does, and the table base is one local, so that the `lw 0x2290` and the
   `addiu 0x80` share its register. */
/* Works out a push direction from the hero's position and facing, then launches a hit effect that way and plays its sound. */
void func_L23_003BFE90(char *moby, float strength, int unused1, int mirror) {
    char *vars = *(char **)(moby + 0x68);
    struct Vecs v;
    char *base = gHeroState;
    float one;

    FastVecScale((char *)&v.a, *(char **)(base + 0x2290) + 0xE0, 3.0f);
    FastVecAdd((char *)&v.a, (char *)&v.a, base + 0x80);
    one = 1.0f;
    v.c = 0;
    ((float *)&v.c)[1] = one;
    ((float *)&v.c)[3] = one;
    if (mirror != 0)
        ((float *)&v.c)[1] = -((float *)&v.c)[1];
    TransformMobyJointPoint(*(char **)(vars + 0x2A0), mirror, (char *)&v.b);
    transform_vector((char *)&v.c, (char *)&v.c, (char *)&v.b);
    FastVecSub((char *)&v.d, (char *)&v.a, (char *)&v.c);
    vec_scale_to_length((char *)&v.d, (char *)&v.d, D_L23_001B370C * 0.016666668f);
    CreateChildShotB(moby, (char *)&v.d, (char *)&v.c, 0, strength);
    PlaySoundFromClassBank(3, 0, moby, 0x7E5);
}
