#include "include_asm.h"

#include "common.h"
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00282E80(void *, void *);
extern int func_00283CF0(float);
extern int func_002E5CF8(int, int, void *);
extern void func_002A7750(void *, int, int);
extern void func_0029FCC0(void *, int, void *);
extern void func_002E59F8(int);
extern void func_L00_003294F0(void *, int);
extern void func_002A0430(int);
typedef struct {
    char pad[0x80];
    float pos[4];
    char gap[0x2AC];
    void *owner;
    int active;
} PrisonHero;
extern PrisonHero D_00189E20;
extern unsigned char D_00188660[];
extern unsigned char *D_L14_001B259C __attribute__((sda));
extern unsigned char *D_L14_001B259C_1[] __attribute__((sda));
extern unsigned char D_001395E3 NOT_SDA;

void func_PAL_L14_00435424(unsigned char *object)
{
    float pos[4];
    unsigned char *state = *(unsigned char **)(object + 0x68), *entry, *first;
    int value, id;
    float distance;

    if (!state)
        return;
    *(float *)(state + 8) = func_00283B98(*(float *)(state + 8), 0.12566373f);
    value = func_00283CF0((func_00283198(*(float *)(state + 8)) * 4.0f - 3.0f) * 128.0f);
    if (value > 128)
        value = 128;
    else if (value < 32)
        value = 32;

    if (object[0x20] == 0) {
        *(unsigned short *)(object + 0x34) |= 16;
        func_002A7750(object, 1, -1);
        *(int *)(state + 0x14) = -1;
    } else if (object[0x20] == 1) {
        first = D_00188660 + *(int *)(state + 0x14) * 112;
        if (*(void **)(first + 0x88) != object || !first[0x74])
            *(int *)(state + 0x14) = func_002E5CF8(1, 4, object);
        func_0029FCC0(object, 0, pos);
        distance = func_00282E80(D_00189E20.pos, pos);
        *(int *)(state + 0xC) = 0;
        if (D_00189E20.owner == object && D_00189E20.active && distance < 0.5f) {
            func_002A7750(object, 2, -1);
            id = *(int *)(state + 0x14);
            if (id != -1) {
                entry = D_00188660 + id * 112;
                if (*(void **)(entry + 0x88) == object && entry[0x74])
                    func_002E59F8(id);
            }
            *(int *)(state + 0x14) = -1;
            func_002E5CF8(0, 0, object);
            func_002E5CF8(2, 0, object);
            D_001395E3 = 1;
            if (*(int *)state != -1) {
                func_L00_003294F0(D_L14_001B259C + (*(int *)state << 8), 1);
                {
                    int child = *(int *)(state + 4);
                    unsigned char *base = D_L14_001B259C_1[0];
                    func_L00_003294F0(base + (child << 8), 1);
                }
            }
            func_002A0430(*(int *)(state + 0x10));
        }
        *(unsigned int *)(object + 0x78) = value | (int)0x80000000;
    } else if (object[0x20] == 2) {
        if (!*(int *)(state + 0xC))
            *(int *)(state + 0xC) = 1;
        {
            unsigned int green = (value << 8) | 0x80000000;
            *(unsigned int *)(object + 0x78) = (value << 16) | green;
        }
    }
}
