#include "include_asm.h"

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
void func_PAL_L00_002A5B40(void)
{
    float joint[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    float scale;
    unsigned int first;
    unsigned int second;
    unsigned int color;
    if (D_00189E20.object == 0) {
        char *created;
        created = func_0029EFD0(0x4B4);
        D_00189E20.object = created;
        if (created) {
            *(unsigned int *)(created + 0x78) = 0x801432D7;
            D_00189E20.color = 0x301432D7;
            {
                char *placed = D_00189E20.object;
                qcopy_nc(placed + 0x10, &D_00189E20.q080);
                qcopy_nc(placed + 0xF0, &D_00189E20.q090);
                *(short *)(placed + 0x32) = 0x40;
                (D_00189E20.object)[0x31] = 1;
                (D_00189E20.object)[0x30] = 0;
                *(short *)(D_00189E20.object + 0x34) = 0;
                *(float *)(D_00189E20.object + 0x2C) *= 1.7f;
                *(unsigned short *)(D_00189E20.object + 0x34) |= 0x10;
                func_002A0F48(D_00189E20.object);
            }
        }
    }
    if ((*(unsigned short *)(D_00189E20.moby + 0x34) ^ 1) & 1) {
        func_0029FCC0(D_00189E20.moby, 7, (char *)joint);
        qcopy(&D_00189E20.joint, joint);
        func_L00_002A7A10();
        if (D_00189E20.object) {
            func_0029FC20(D_00189E20.moby, 7, (char *)matrix);
            qcopy_nc(D_00189E20.object + 0x10, matrix + 12);
            func_00283678(D_00189E20.object + 0xC0, matrix);
            func_002A0F48(D_00189E20.object);
            scale = 1.7f;
            if (D_001A7A40[3])
                scale = 3.1f;
            if (D_00189E20.timer)
                scale *= 1.4f;
            func_002AA2E8((float *)(D_00189E20.object + 0x2C), *(float *)(*(char **)(D_00189E20.object + 0x24) + 0x24) * scale, 0.02f);
        }
    }
    D_00189E20.phase = func_00283B98(D_00189E20.phase, 0.059341207f);
    first = 0x281414C8;
    second = 0x1E00004B;
    if (!func_00282978(&D_00189E20.timer)) {
        D_00189E20.phase = func_00283B98(D_00189E20.phase, 0.24434614f);
        switch (D_00189E20.variant) {
        case 1: first = 0x2814C814; second = 0x1E004B00; break;
        case 2: first = 0x2814C8C8; second = 0x1E004B4B; break;
        case 3: first = 0x323232FA; second = 0x1E000078; break;
        case 4: first = 0x28F01414; second = 0x1E4B0000; break;
        }
        if (D_00189E20.timer >= 41 && (D_00189E20.timer & 1))
            func_002E5CF8(D_00189E20.variant + 16, 0, D_00189E20.moby);
    }
    color = func_00283D38(first, second, func_00283198(D_00189E20.phase) * 0.5f + 0.5f);
    if (D_00189E20.object)
        *(unsigned int *)(D_00189E20.object + 0x78) = func_00283D38(*(unsigned int *)(D_00189E20.object + 0x78), color, 0.120000005f);
    D_00189E20.color = func_00283D38(D_00189E20.color, color, 0.120000005f);
}
