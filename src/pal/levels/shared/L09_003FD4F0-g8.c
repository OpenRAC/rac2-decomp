#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
#define S(p,o) (*(short *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
typedef struct __attribute__((packed)) { u64 fields[6]; } AnimationParameters;
typedef struct { char prefix[0x38]; u8 *owner; char suffix[4]; } TargetSlot;
extern TargetSlot D_L09_001C40C0[];
extern char D_L09_001B9A00[];
extern int D_001A79F0 MACRO_ADDR;
extern u8 *D_L09_001B285C __attribute__((sda));
extern int D_L09_001A9040 __attribute__((sda));
extern float func_00282E48(void *,void *);
extern int func_002B0ED8(void *,void *,int),func_002B3380(void *,void *,void *);
extern int func_002A77E0(int),func_002B3BA8(void *,int,void *,int,float,float);
extern u8 *func_L09_00326E90(void *);
extern void func_L09_003F7CE0(void *),func_L09_003F8858(void *);
extern void func_L09_003F8598(void *),func_L09_003F7370(void *,float),func_L09_003F77D0(void *);
extern void func_L09_003F8960(void *),func_L09_003F73E8(void *);
extern void func_002A93B0(void *),func_002A7470(void *,int,int,int),func_002A7750(void *,int,int);
extern void func_00282D30(void *,void *,float),func_002A6C58(void *,int,int),func_0029F338(void *);

/* Mirrors the parent's measured 48-byte animation parameter block into its child,
 * releases detached effects and propagates the live target slot.
 */
void func_PAL_L09_003FD4F0(u8 *object)
{
    u8 *state = P(object,0x68), *vars, *moved, **effects;
    int before, result, i, remove = 0;
    if (object[0x95] == 0) func_L09_003F7CE0(object);
    if (object[0x31] && func_00282E48(object + 0x10, D_L09_001B9A00) < 24.0f) {
        func_002A93B0(object); object[0x6F] = 22;
    }
    if (object[0xA8] == 255) {
        u8 *child = P(state,0x2F8);
        if (child && S(child,0xAA) == 0xD0E && child[0x20] != 0xFE && child[0x20] != 0xFD) {
            if (child[0xA8] != 255) {
                int index = child[0xA8];
                TargetSlot *slots = D_L09_001C40C0;
                if (slots[index].owner == child) {
                    object[0xA8] = index;
                    slots[object[0xA8]].owner = object;
                }
            }
        }
    }
    before = object[0x20];
    result = func_002B0ED8(object, state + 0x50, 0);
    if (D_001A79F0 == 9 && S(state,0xC0) != -1) {
        if (!func_L09_00326E90(D_L09_001B285C + (S(state,0xC0) << 8))) D_L09_001A9040 = 0;
        S(state,0xC0) = -1;
    }
    if (result) {
        u8 *child;
        func_L09_003F8858(object);
        child = P(state,0x2F8);
        if (child) {
            if (result == 4) {
                H(object,0x34) &= 0xEFFF;
                H(P(state,0x2F8),0x34) &= 0xEFFF;
                H(P(state,0x2F8),0x7C) |= 0x300;
                I(state,0x20) = 0;
                moved = P(P(state,0x2F8),0x68);
                *(AnimationParameters *)(moved + 0x20) = *(AnimationParameters *)(state + 0x20);
                func_002B3380(P(state,0x2F8), moved + 0x50, moved + 0x20);
                func_L09_003F8598(object);
                func_L09_003F7370(object,0.4f);
                func_L09_003F77D0(object);
                if (before >= 4 && !func_002A77E0(2) && !I(state,0x428) &&
                    I(state,0x2DC) != -1 && I(state,0x2DC) == I(state,0x2B0)) {
                    if (object[0x43] != 17) func_002A7470(object,17,0,5);
                    F(state,0xB0) = (float)*(s8 *)(state + 0xBF);
                    F(state,0xA4) = (float)*(s8 *)(state + 0xBE);
                    I(state,0xCC) = -1;
                    func_00282D30(state + 0xD0,state + 0xD0,0.05f);
                } else qzero(state + 0xD0);
                {
                    int j;
                    effects = (u8 **)(state + 0x2F0);
                for (j = 0; j < 2; j++) {
                    if (effects[j]) {
                        H(effects[j],0x34) &= 0xFFFD;
                        H(effects[j],0x34) &= 0xFFFE;
                        effects[j][0x31] = 1;
                        effects[j] = 0;
                    }
                } }
            } else {
                vars = P(child,0x68);
                *(AnimationParameters *)(vars + 0x20) = *(AnimationParameters *)(state + 0x20);
                func_002B3380(P(state,0x2F8),vars + 0x50,vars + 0x20);
                func_002A7470(P(state,0x2F8),object[0x43],0,2);
                F(P(state,0x2F8),0x48) = F(object,0x48);
                if (!(H(P(state,0x2F8),0x7C) & 0x80)) {
                    state[0x30F] = 1;
                    if (object[0x95] != 9) func_002A7750(object,13,8);
                }
                { u8 *t = P(state,0x2F8); if (!(H(t,0x7C) & 0x10)) H(t,0x7C) |= 0x100; }
                { u8 *t = P(state,0x2F8); if (!(H(t,0x7C) & 0x20)) H(t,0x7C) |= 0x200; }
                effects = (u8 **)(state + 0x2F0);
                for (i = 0; i < 2; i++) {
                    if (effects[i] && !((H(P(state,0x2F8),0x7C) >> (i+4)) & 1)) {
                        H(effects[i],0x34) &= 0xFFFD;
                        effects[i] = 0;
                    }
                }
            }
        }
    }
    func_002B3BA8(object,I(state,0x2D8),0,0,0.0f,0.0f);
    func_L09_003F8960(object);
    if (state[0x2E] == 2) remove = 1;
    else {
        u8 *child = P(state,0x2F8);
        if (child && S(child,0xAA) == 0xD0E && child[0x20] != 0xFE && child[0x20] != 0xFD)
            remove = P(child,0x68)[0x2E] == 2;
    }
    if (remove) {
        func_L09_003F73E8(object); func_L09_003F77D0(object); func_L09_003F8598(object);
        func_002A6C58(object,0,3); func_0029F338(object);
    }
}
