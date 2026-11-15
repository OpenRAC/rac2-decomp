#include "common.h"

typedef int BossQuadword __attribute__((mode(TI)));
extern void func_0029FCC0(char *, int, char *);
extern void func_0029FC20(char *, int, char *);
extern void func_00283678(void *, void *);
extern void func_002A0F48(void *);

/* Copies body and arm bone transforms to the corresponding child objects. */
void func_L16_00411600(u8 *moby)
{
    float bone[16] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *body = *(u8 **)(state + 0x1f0);
    u8 **arms = (u8 **)(state + 0x238);
    int i;
    func_0029FCC0((char *)moby, 2, (char *)(body + 0x10));
    *(float *)(body + 0xf8) = *(float *)(moby + 0xf8);
    *(float *)(*(u8 **)(state + 0x1f0) + 0x48) = *(float *)(moby + 0x48);
    func_002A0F48(*(u8 **)(state + 0x1f0));
    for (i = 0; i < 2; i++, arms++) {
        u8 *arm;
        func_0029FC20((char *)body, i, (char *)bone);
        copy_matrix3x4(*arms + 0xc0, bone);
        arm = *arms;
        *(BossQuadword *)(arm + 0x10) = *(BossQuadword *)(bone + 12);
        func_002A0F48(arm);
    }
}
