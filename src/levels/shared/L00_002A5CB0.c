#include "common.h"

typedef int Vector __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x80];
    Vector q080;
    Vector q090;
    unsigned char pada0[0x1864 - 0xA0];
    char *object;
    float phase;
    unsigned char pad186c[0x2010 - 0x186C];
    Vector joint;
    unsigned char pad2020[0x2290 - 0x2020];
    char *moby;
    unsigned char pad2294[0x2520 - 0x2294];
    short timer;
    short variant;
    unsigned int color;
} Hero5CB0;
extern Hero5CB0 D_00189E20;
extern unsigned char D_001A7A40[] __attribute__((sda));
extern char *func_0029EFD0(int);
extern void func_002A0F48(char *);
extern void func_0029FCC0(char *, int, char *);
extern void func_L00_002A7A10(void);
extern void func_0029FC20(char *, int, char *);
extern void func_00283678(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern float func_00283B98(float, float);
extern int func_00282978(short *);
extern int func_002E5CF8(int, int, char *);
extern float func_00283198(float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);

/* Create and pose the hero effect object, then advance and blend its colors. */
void func_L00_002A5CB0(void)
{
    float joint[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    float scale;
    unsigned int first;
    unsigned int second;
    unsigned int color;
    if (gHeroState.object == 0) {
        char *created;
        created = CreateMoby(0x4B4 /* moby class 1204 */);
        gHeroState.object = created;
        if (created) {
            *(unsigned int *)(created + 0x78) = 0x801432D7;
            gHeroState.color = 0x301432D7;
            {
                char *placed = gHeroState.object;
                qcopy_nc(placed + 0x10, &gHeroState.q080);
                qcopy_nc(placed + 0xF0, &gHeroState.q090);
                *(short *)(placed + 0x32) = 0x40;
                (gHeroState.object)[0x31] = 1;
                (gHeroState.object)[0x30] = 0;
                *(short *)(gHeroState.object + 0x34) = 0;
                *(float *)(gHeroState.object + 0x2C) *= 1.7f;
                *(unsigned short *)(gHeroState.object + 0x34) |= 0x10;
                func_002A0F48(gHeroState.object);
            }
        }
    }
    if ((*(unsigned short *)(gHeroState.moby + 0x34) ^ 1) & 1) {
        TransformMobyJointToWorld(gHeroState.moby, 7, (char *)joint);
        qcopy(&gHeroState.joint, joint);
        QueueHeroGlowDrawRoutine();
        if (gHeroState.object) {
            TransformMobyJointPoint(gHeroState.moby, 7, (char *)matrix);
            qcopy_nc(gHeroState.object + 0x10, matrix + 12);
            copy_matrix3x4(gHeroState.object + 0xC0, matrix);
            func_002A0F48(gHeroState.object);
            scale = 1.7f;
            if (D_001A7A40[3])
                scale = 3.1f;
            if (gHeroState.timer)
                scale *= 1.4f;
            ApproachValue((float *)(gHeroState.object + 0x2C), *(float *)(*(char **)(gHeroState.object + 0x24) + 0x24) * scale, 0.02f);
        }
    }
    gHeroState.phase = FastAddRotations(gHeroState.phase, 0.049451005f);
    first = 0x281414C8;
    second = 0x1E00004B;
    if (!FastDecTimer(&gHeroState.timer)) {
        gHeroState.phase = FastAddRotations(gHeroState.phase, 0.20362177f);
        switch (gHeroState.variant) {
        case 1: first = 0x2814C814; second = 0x1E004B00; break;
        case 2: first = 0x2814C8C8; second = 0x1E004B4B; break;
        case 3: first = 0x323232FA; second = 0x1E000078; break;
        case 4: first = 0x28F01414; second = 0x1E4B0000; break;
        }
        if (gHeroState.timer >= 50 && (gHeroState.timer & 1))
            PlayMobySound(gHeroState.variant + 16, 0, gHeroState.moby);
    }
    color = FastTweenColor(first, second, FastSinOrCosB(gHeroState.phase) * 0.5f + 0.5f);
    if (gHeroState.object)
        *(unsigned int *)(gHeroState.object + 0x78) = FastTweenColor(*(unsigned int *)(gHeroState.object + 0x78), color, 0.1f);
    gHeroState.color = FastTweenColor(gHeroState.color, color, 0.1f);
}
