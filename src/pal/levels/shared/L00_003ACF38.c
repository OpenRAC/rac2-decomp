#include "include_asm.h"


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003AD088);



#include "common.h"
typedef float HitVector[4] __attribute__((aligned(16)));
typedef struct {
    char pad[4];
    unsigned char mode;
    char pad5[0x6B];
    float damage, area;
    char tail[0x68];
} WeaponDamageClass;
extern unsigned char D_00139568[];
extern WeaponDamageClass ref_L00_003AB388_0[];
extern char *ref_L00_003AB388_1;
extern char *ref_L00_003AB388_2[];
extern void *D_L00_001ADB2C MACRO_ADDR;
extern void func_002A8E20(void *,void *);
extern void func_PAL_00335DD0(void *,int,void *);
extern int func_00277F48(void *,int,void *,void *,float);
extern void func_002E5CF8(int,int,void *);
extern void func_PAL_L00_003FB330(void *, float, float, int, int, int, int, int, int, int, int, int, int, void *);
extern void func_002AFFD8();
extern void func_00282D30(void *,void *,float);
extern void func_00282F20(void *,void *,float);

/* Applies direct and area hits, then emits the weapon impact effects. */
void func_PAL_L00_003AEB58(char *moby, void *direction, void *position)
{
    struct {
        HitVector dir;
        char *owner;
        int flags;
        unsigned char type, mode;
        unsigned short id;
        float damage;
        int active;
    } hit;
    HitVector forward;
    char *target;
    int count, i;

    hit.flags = 0x810000;
    hit.active = 1;
    hit.owner = moby;
    hit.damage = ((WeaponDamageClass *)(
        D_00139568[0x18] * 0xE0 + (unsigned int)ref_L00_003AB388_0))[0].damage;
    qcopy(hit.dir, direction);
    func_00282F20(hit.dir, hit.dir, 1.0f);
    target = ref_L00_003AB388_1;
    hit.dir[3] = 5627.925f;
    hit.type = 3;
    hit.mode = 2;
    hit.id = *(unsigned short *)(moby + 0xAA);
    if (target) {
        func_002A8E20(target, &hit);
        if (((WeaponDamageClass *)(
        D_00139568[0x18] * 0xE0 + (unsigned int)ref_L00_003AB388_0))[0].mode)
            func_PAL_00335DD0(target, 0x43, *(char **)(moby + 0xB8));
        else
            func_PAL_00335DD0(target, 0x18, *(char **)(moby + 0xB8));
    }
    hit.damage = ((WeaponDamageClass *)(
        D_00139568[0x18] * 0xE0 + (unsigned int)ref_L00_003AB388_0))[0].area;
    count = func_00277F48(position, 1, target, &hit, 2.0f);
    if (((WeaponDamageClass *)(
        D_00139568[0x18] * 0xE0 + (unsigned int)ref_L00_003AB388_0))[0].mode) {
        for (i = 0; i < count; i++)
            func_PAL_00335DD0(ref_L00_003AB388_2[i], 0x43, *(char **)(moby + 0xB8));
    } else {
        for (i = 0; i < count; i++)
            func_PAL_00335DD0(ref_L00_003AB388_2[i], 0x18, *(char **)(moby + 0xB8));
    }
    func_002AFFD8(moby + 0x10, forward, 1);
    func_00282D30(forward, forward, -1.0f);
    func_002E5CF8(2, 0, moby);
    func_PAL_L00_003FB330(moby + 0x10, 0.75f, 20.0f, 1, 0, 1, 0, 0x14, 0x2D,
                  1, 0, 1, 0, D_L00_001ADB2C);
}

