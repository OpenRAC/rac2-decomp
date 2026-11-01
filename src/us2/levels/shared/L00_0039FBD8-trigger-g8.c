#include "common.h"
extern int D_L00_001B19C8;
extern unsigned char D_0018C0D4 NOT_SDA;
extern u32 D_0018C0BC NOT_SDA;
extern int D_0018C0B4 NOT_SDA;
extern int D_001A79F0;
extern unsigned char D_0019B2E8[], D_0019B4A8[];
typedef struct { char pad[0x464]; u8 disabled[1]; } TriggerTable;
extern TriggerTable D_L00_0021D140, D_L00_0021DDB0;
extern float D_00189EA0[4];
extern char *D_L00_001AF440 __attribute__((sda));
extern void func_L00_0042A500(int arg0);
extern int func_00282948(int *), func_002ACBC8(void *, int);
extern void func_002A0430(unsigned int);
extern float func_002A89A8(void *, int, float), func_00282C48(float);
extern void func_002DF3F8(void *, void *), func_002B0A18(int, int);
/* Applies a regional activation trigger and records its checkpoint flags. */
void func_US2_L00_0039FBD8(char *actor) {
    int *state = *(int **)(actor + 0x68);
    unsigned long long flags;
    unsigned short id;
    unsigned char *packed;
    int bits;
    int active;
    float point[4];
    if (*(u8 *)(actor + 0x30) < 0x20) *(u8 *)(actor + 0x30) = 0x20;
    if (D_L00_001B19C8 == 0 && state[5] != -1) func_L00_0042A500(state[5]);
    {
        int currentFlags = state[2];
        int disabled = currentFlags & 8;
        flags = currentFlags;
        if (disabled) return;
    }
    if (*(u8 *)(actor + 0xBC) == 0) {
        *(u8 *)(actor + 0xBC) = 1;
        state[7] = 0;
        state[8] = 0;
        return;
    }
    if (state[6] != -1 && !(D_0019B2E8[state[6] + D_001A79F0 * 16] & 0x80)) return;
    if ((flags & 2) && D_0018C0D4 != 1) return;
    if ((flags & 4) && D_0018C0D4 != 3 && D_0018C0D4 != 0) return;
    if ((flags & 16) && D_0018C0BC > 1 && D_0018C0BC != 9) return;
    if ((flags & 32) && D_0018C0B4 == 49) return;
    if (state[3] == 2 && func_00282948(state + 8)) state[3] = 0;
    active = func_002ACBC8(D_00189EA0, state[0]);
    if (active) goto activate;
    {
        unsigned short triggerId = *(u16 *)(actor + 0xB2);
        if (D_L00_0021DDB0.disabled[(short)triggerId]) goto activate;
        bits = D_0019B4A8[((short)triggerId >> 1) + D_001A79F0 * 0x400];
        if (triggerId & 1) {
            if ((bits >> 4) & 7) goto activate;
            goto inactive;
        }
        if (!(bits & 7)) goto inactive;
    }
activate:
    {
        if (state[3] && (state[4] == 0 || state[8] != 0)) goto finish;
        state[3] = 1;
        func_002A0430(*(u8 *)(actor + 0xB0));
        qcopy(point, (actor + 0x10));
        point[2] = func_002A89A8(point, 0, 0.5f);
        if (func_00282C48(*(float *)(actor + 0x18) - point[2]) > 2.0f) point[2] = *(float *)(actor + 0x18);
        func_002DF3F8(point, actor + 0xF0);
        D_L00_0021D140.disabled[*(short *)(actor + 0xB2)] = 0;
        D_L00_0021DDB0.disabled[*(short *)(actor + 0xB2)] = 0;
        id = *(u16 *)(actor + 0xB2);
        {
            int index = (short)id >> 1;
            index += D_001A79F0 * 0x400;
            packed = D_0019B4A8 + index;
        }
        bits = *packed;
        {
            int value = bits & 0xF8;
            if (id & 1) value = bits & 0x8F;
            *packed = value;
        }
        if (state[9] && D_L00_001AF440 != actor) {
            func_002B0A18(0x2DCC, 90);
            D_L00_001AF440 = actor;
        }
        state[8] = 900;
        goto finish;
    }
inactive:
    if (state[3]) state[3] = 2;
finish:
    if (*(u8 *)(actor + 0x20) == 0 && (D_0019B2E8[*(u8 *)(actor + 0xB0) + D_001A79F0 * 16] & 0x80)) *(u8 *)(actor + 0x20) = 1;
}
