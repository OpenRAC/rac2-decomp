#include "common.h"

#define FIELD(p, type, offset) (*(type *)((char *)(p) + (offset)))

typedef struct {
    char pad0000[0x1230];
    int input;
    char pad1234[0x1060];
    int state;
    char pad2298[0x24];
    unsigned char flag;
    char pad22BD[0x277];
    int timer;
} HeroInputState;

typedef struct {
    float v[4];
} InputVector __attribute__((aligned(16)));

extern HeroInputState D_00189E20;
extern int D_00138324;
extern void func_0029FCC0(void *, int, void *);
extern void func_002FDF40(void *, void *, int, int, float, float, float, float);
extern int func_002FE5A0(void *, void *, void *, void *, void *, int, int, float);
extern int func_00282948(void *);
extern int func_L00_002D3F30(int, int);
extern void func_L00_002AF568(void);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_0038A748(void *, void *, void *);
extern void func_L00_002AF7D0(void);
extern void ref_L00_003C8828_00(void (*)(void *), void *);
extern void func_L00_003C8A58(void *);

/* Moby update: Megaturret Glove (class 2661). */
void func_L00_003C8828(char *owner)
{
    InputVector origin, target;
    InputVector *targetVector;
    char *context = FIELD(owner, char *, 0x68);
    int allowed;
    float radius;

    func_0029FCC0(owner, 0, &origin);
    targetVector = &target;
    radius = D_00189E20.state == 29 ? 11.0f : 4.5f;
    CalculateAimedLaunchVelocity(targetVector, &origin, 0, 0, 1.5f, radius, 0.25f, 0.0030555557f);
    allowed = 1;
    FIELD(context, int, 0x24) = func_002FE5A0(&origin, targetVector, context,
        context + 0x10, owner, 0, 0, 0.0030555557f);

    if (D_00189E20.state == 29) {
        if (!func_00282948(&D_00189E20.timer))
            allowed = 0;
    } else {
        D_00189E20.timer = 40;
    }

    switch (FIELD(owner, unsigned char, 0x20)) {
    case 0:
        FIELD(owner, unsigned char, 0x20) = 1;
        FIELD(context, int, 0x24) = 0;
        /* Fall through. */
    case 1:
        if ((D_00138324 & D_00189E20.input) && !D_00189E20.flag && allowed) {
            if (func_L00_002D3F30(-1, 1)) {
                start_equipped_item_animation();
                FIELD(owner, unsigned char, 0x20) = 2;
                FIELD(context, int, 0x20) = 20;
            } else {
                PlayMobySound(2, 0, owner);
            }
        }
        break;
    case 2:
        if (func_00282948(context + 0x20)) {
            PlayMobySound(0, 0, owner);
            func_L00_0038A748(owner, &origin, targetVector);
            cancel_hero_item_animation();
            FIELD(owner, unsigned char, 0x20) = 3;
            FIELD(context, int, 0x20) = 10;
        }
        break;
    case 3:
        if (func_00282948(context + 0x20))
            FIELD(owner, unsigned char, 0x20) = 1;
        break;
    }
    ref_L00_003C8828_00(func_L00_003C8A58, owner);
}
