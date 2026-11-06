/* func_PAL_L12_003E6730, the PAL copy of func_L12_003E2460 (levels 12 and 17): the same C at 50 Hz.
 * Timers scale by ((x) * 5 + 2) / 6, per-frame rates by 6/5, and the speed values read from data go through
 * the float form of the same scale, written out where it happens.
 * The kill counter is read through two views of D_L12_001A79F0, as in the template.
 */
#include "common.h"

typedef struct { float x, y, z, w; } L12Vector __attribute__((aligned(16)));

/* The path and combat portion of the object's private state. */
typedef struct {
    u8 prefix[0x1A8];
    int flags;
    u8 reserved1AC[0xB4];
    s16 idleTimer;
    s16 attackTimer;
    int pathIndex;
    int nextPoint;
    int destination;
    u8 *targetObject;
    s16 alertTimer;
    s16 perception;
    int damageState;
    u8 reserved27C[0x18];
    int *ownerSlot;
    int grouped;
    s16 groupTimer;
    s16 reserveTimer;
    int reserved2A0;
    int persistent;
    float minimumHeight;
} L12PathEnemyState;

extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0;
extern int D_L12_001A79F0_GP SDATA(D_L12_001A79F0);
extern u8 D_L12_0019B4A8[];
extern int D_L12_001A8F00[3] __attribute__((sda));
extern int D_L12_001A79F0[] __attribute__((sda));
extern u8 *D_L12_001FEAC0[];
extern u8 D_L12_001B0A90[8] __attribute__((sda));
extern float D_L12_001B0AA8 __attribute__((sda));
extern float D_L12_001B0AAC __attribute__((sda));
extern float D_L12_001B0AB0 __attribute__((sda));
extern float D_L12_001B0B04 __attribute__((sda));
extern float D_L12_001B0B08 __attribute__((sda));
extern float D_L12_001B0B14 __attribute__((sda));
extern float D_L12_001B0B34 __attribute__((sda));
extern float D_L12_001B0A50 __attribute__((sda));
extern float D_L12_001B0A54 __attribute__((sda));
extern int D_L12_001B0A58 __attribute__((sda));
extern float D_L12_001B0A80 __attribute__((sda));
extern float D_L12_001B0A84 __attribute__((sda));
extern float D_L12_001B0A88 __attribute__((sda));
extern int D_L12_001B0A8C __attribute__((sda));
extern char D_L12_001B0B18[], D_L12_001B0B38[], D_L12_001B0B50[];
extern u8 D_L12_001A8F20[] __attribute__((sda));

extern void func_PAL_L12_003E7E08(void *);
extern void func_PAL_L12_003E6620(void *);
extern void func_L12_003E2418(void *);
extern void func_PAL_L12_003E66F8(void *);
extern void func_L12_003E1CB0(void *);
extern void func_PAL_L12_003E63A0(void *);
extern int func_PAL_L12_003E6198(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern int func_002E5CF8(int, int, void *);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern int func_002B1C20(void *, void *);
extern void func_0026FEB8(char *, ...);
extern void func_PAL_002A7650(void *, int, int);
extern void func_0029F338(void *);
extern void func_002A7750(void *, int, int);
/* Keeps state 21's transition from cross-jumping into state 23's call tail, as
   RAC1 pause.c does for its duplicate start_audio_stream_read_r3/r4 calls. Both names
   have the same EE interface. */
extern void changeModeL12Patrol(void *, int, int) __asm__("func_002A7750");
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern int func_00282978(void *);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_0029FC20(void *, int, void *);
extern void func_002830C0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern float func_00283248(float, float);
extern void func_002AA800(void *, int, float, float);
extern int func_PAL_L01_00323068(void *, void *);
extern float func_002A89A8(void *, int, float);
extern float func_00283BE0(float, float);
extern float func_00282C48(float);
extern void func_00282F20(void *, void *, float);
extern int func_PAL_002AF6C0(void *, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void *func_002C2210(void *, int, float, float, int, int, int, void *, int, float);
extern void func_00282CF0(void *, void *, void *);
extern u8 *func_PAL_L12_0040CBA0(void *, void *, void *, int, float);

void func_PAL_L12_003E6730(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    L12Vector pos;
    u8 matrix[64] __attribute__((aligned(16)));
    L12Vector velocity;
    L12Vector target;
    float distance;
    float angle;
    float limit;
    int i, next;
    int forward, backward;

    if (((L12PathEnemyState *)state)->persistent) {
        u16 id = *(u16 *)(obj + 0xB2);
        int value;
        if (D_L12_0021EDF0.flags[(s16)id])
            goto destroy;
        value = D_L12_0019B4A8[((s16)id >> 1) + (D_L12_001A79F0_GP << 10)];
        if (id & 1)
            value = (value >> 4) & 7;
        else
            value &= 7;
        if (value)
            goto destroy;
    }
    if (D_L12_001A8F00[0] == 2) {
        *(int *)(obj + 0x98) = 0;
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & 0xEFFF;
        return;
    }
    if (obj[0x95] != 7) {
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(obj + 0x98) = *(int *)(*(u8 **)(obj + 0x24) + 0x10);
    }
    func_PAL_L12_003E7E08(obj);
    distance = func_00282E80(((L12PathEnemyState *)state)->targetObject + 0x10, obj + 0x10);
    if (distance < 8.0f && !((L12PathEnemyState *)state)->damageState) {
        ((L12PathEnemyState *)state)->damageState = 3;
        ((L12PathEnemyState *)state)->alertTimer = 42;
    }
    if (((L12PathEnemyState *)state)->damageState == 5) {
        func_002E5CF8(3, 0, obj);
        func_PAL_L00_003FB330((obj + 0x10), 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        if (((L12PathEnemyState *)state)->persistent) {
            u16 id = *(u16 *)(obj + 0xB2);
            if (id & 1) {
                if (((D_L12_0019B4A8[((s16)id >> 1) + (D_L12_001A79F0_GP << 10)] >> 4) & 7) != 7)
                    D_L12_0019B4A8[((s16)id >> 1) + (D_L12_001A79F0_GP << 10)] += 0x10;
            } else {
                if ((D_L12_0019B4A8[((s16)id >> 1) + (D_L12_001A79F0[0] << 10)] & 7) != 7)
                    D_L12_0019B4A8[((s16)id >> 1) + (D_L12_001A79F0[0] << 10)]++;
            }
        }
        goto deathFinish;
    } else if (((L12PathEnemyState *)state)->damageState == 1 || ((L12PathEnemyState *)state)->damageState == 5) {
        int damage;
        float oldAngle = *(float *)(obj + 0xF8);
        qcopy(&pos, (obj + 0x10));
        damage = func_002B1C20(obj, state + 0x60);
        if (*(float *)(state + 0x218) >= D_L12_001B0B04 * 0.020000001f) {
            func_0026FEB8(D_L12_001B0B38);
            *(float *)(state + 0x218) = 0;
        }
        if (damage & 1) {
            func_002E5CF8(3, 0, obj);
            func_PAL_L00_003FB330((obj + 0x10), 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
            if (((L12PathEnemyState *)state)->persistent) {
                u16 id = *(u16 *)(obj + 0xB2);
                if (id & 1) {
                    u8 *entry = D_L12_0019B4A8 + (((s16)id >> 1) + (D_L12_001A79F0_GP << 10));
                    if (((*entry >> 4) & 7) != 7)
                        *entry += 0x10;
                } else {
                    u8 *entry = D_L12_0019B4A8 + (((s16)id >> 1) + (D_L12_001A79F0[0] << 10));
                    if ((*entry & 7) != 7)
                        ++*entry;
                }
            }
deathFinish:
            func_PAL_002A7650(obj, 0, 3);
destroy:
            func_0029F338(obj);
            return;
        }
        if (damage & 2)
            ((L12PathEnemyState *)state)->damageState = 2;
        qcopy((obj + 0x10), &pos);
        *(float *)(obj + 0xF8) = oldAngle;
    }
    switch (obj[0x95]) {
    case 0:
        if (((L12PathEnemyState *)state)->perception == 1 || ((L12PathEnemyState *)state)->damageState == 1 || ((L12PathEnemyState *)state)->damageState == 2) {
            ((L12PathEnemyState *)state)->destination = ((L12PathEnemyState *)state)->nextPoint = -1;
            if (!((L12PathEnemyState *)state)->grouped) {
                func_002A7750(obj, 15, 5);
            } else {
                func_PAL_L12_003E6620(obj);
                if (obj[0x20] != 15) {
                    func_002A7750(obj, 4, 10);
                    ((L12PathEnemyState *)state)->reserveTimer = 667;
                }
            }
        }
        break;
    case 7:
        i = ((L12PathEnemyState *)state)->perception;
        if (i == 1) {
            func_002A7750(obj, 3, 8);
            obj[0x31] = i;
            *(u16 *)(obj + 0x34) &= 0xFFFE;
        } else {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        break;
    case 9:
        func_002B3890(obj);
        if (obj[0x20] == 23 && ((L12PathEnemyState *)state)->damageState != 1) {
            func_002A7750(obj, 4, -1);
            if (obj[0x43] != 3)
                func_PAL_002A7E68(obj, 3, 0, 17);
        }
        if (func_00282978(state + 0x29E)) {
            func_L12_003E2418(obj);
            func_002A7750(obj, 4, 10);
            if (obj[0x43] != 3)
                func_PAL_002A7E68(obj, 3, 0, 17);
        } else if (((L12PathEnemyState *)state)->damageState == 1 && obj[0x20] == 4) {
            func_002A7750(obj, 15, 5);
            ((L12PathEnemyState *)state)->groupTimer = 125;
        }
        break;
    case 10:
        if (func_002B3890(obj))
            func_L12_003E1CB0(obj);
        if ((obj[0x60] & 2) && obj[0x42] != 2 && obj[0x43] != 2)
            func_PAL_002A7E68(obj, 2, 0, 17);
        func_PAL_L12_003E6620(obj);
        if (((L12PathEnemyState *)state)->damageState == 1) {
            func_002A7750(obj, 15, 5);
            ((L12PathEnemyState *)state)->groupTimer = 125;
        } else {
            if (((L12PathEnemyState *)state)->perception == 1 || ((L12PathEnemyState *)state)->damageState)
                ((L12PathEnemyState *)state)->idleTimer = 208;
            if (((L12PathEnemyState *)state)->perception == 0 && ((L12PathEnemyState *)state)->damageState == 0 && func_00282978(state + 0x260)) {
                if (obj[0x43] != 0)
                    func_PAL_002A7E68(obj, 0, 0, 17);
                func_002A7750(obj, 5, 0);
            }
        }
        break;
    case 5:
        if (func_002B3890(obj)) {
            float turn = D_L12_001B0AA8 * 0.00040000002f;
            float speed = D_L12_001B0AAC * 0.020000001f;
            *(float *)(state + 0x198) = (D_L12_001B0AB0 * 5.0f + 2.0f) / 6.0f;
            func_002B60B0(obj, turn, speed, 0.0025132746f, 0.25132746f);
            ((L12PathEnemyState *)state)->flags |= 0x10;
        }
        if (((L12PathEnemyState *)state)->damageState == 3) {
            if (obj[0x95] != 15)
                func_002A7750(obj, obj[0x20], 6);
            func_002B3868(obj);
        }
        if (((L12PathEnemyState *)state)->grouped && func_00282978(state + 0x29C) && ((L12PathEnemyState *)state)->damageState != 1) {
            func_PAL_L12_003E66F8(obj);
            break;
        }
        func_0029FC20(obj, 2, matrix);
        func_002830C0(&pos, D_L12_001B0A90, matrix);
        if (obj[0x95] != 15 && func_002761F8(&pos, state + 0x130, 2, obj, 0)) {
            func_002A7750(obj, obj[0x20], 6);
            func_002B3868(obj);
        }
        if (((L12PathEnemyState *)state)->perception == 1 || ((L12PathEnemyState *)state)->damageState)
            ((L12PathEnemyState *)state)->idleTimer = 208;
        if (((L12PathEnemyState *)state)->perception == 0 && ((L12PathEnemyState *)state)->damageState == 0 && func_00282978(state + 0x260)) {
            if (obj[0x43] != 0)
                func_PAL_002A7E68(obj, 0, 0, 17);
            func_002A7750(obj, 5, 0);
            break;
        }
        {
            u8 *other = ((L12PathEnemyState *)state)->targetObject;
            angle = func_00283248(*(float *)(other + 0x10) - *(float *)(obj + 0x10),
                                  *(float *)(other + 0x14) - *(float *)(obj + 0x14));
            func_002AA800(obj + 0xF8, 0, angle, 0.12566373f);
        }
        break;
    case 6: {
        u8 *path;
        int flags;
        float oldZ, ground, angle;
        if (func_002B3890(obj)) {
            u8 *initialPath;
            float initialDistance;
            ((L12PathEnemyState *)state)->destination = -1;
            initialPath = D_L12_001FEAC0[*(int *)(state + 0x158)];
            func_L12_003E1CB0(obj);
            initialDistance = func_00282E48((obj + 0x10), initialPath + 0x10 + (((L12PathEnemyState *)state)->pathIndex << 4));
            if (initialDistance > 0.5f)
                func_0026FEB8(D_L12_001B0B50, (double)initialDistance);
        }
        if (*(int *)(state + 0x16C)) {
            func_PAL_L12_003E63A0(obj);
            break;
        }
        path = D_L12_001FEAC0[*(int *)(state + 0x158)];
        if (*(long long *)(state + 0x268) == -1) {
            ((L12PathEnemyState *)state)->nextPoint = -1;
            i = ((L12PathEnemyState *)state)->pathIndex - 1;
            next = ((L12PathEnemyState *)state)->pathIndex + 1;
            if (i < 0)
                i = *(int *)path - 1;
            if (next == *(int *)path)
                next = 0;
            if (i >= 0 && !func_002761F8(path + 0x10 + i * 16, state + 0x130, 2, 0, 0))
                ((L12PathEnemyState *)state)->destination = i;
            if (((L12PathEnemyState *)state)->destination == -1) {
                if (next < *(int *)path && !func_002761F8(path + 0x10 + next * 16, state + 0x130, 2, 0, 0))
                    ((L12PathEnemyState *)state)->destination = next;
                if (((L12PathEnemyState *)state)->destination == -1) {
                    int j;
                    for (j = i - 1; j >= 0; j--) {
                        if (!func_002761F8(path + 0x10 + j * 16, state + 0x130, 2, 0, 0)) {
                            ((L12PathEnemyState *)state)->destination = j;
                            break;
                        }
                    }
                    if (((L12PathEnemyState *)state)->destination == -1) {
                        for (i = next + 1; i < *(int *)path; i++) {
                            if (!func_002761F8(path + 0x10 + i * 16, state + 0x130, 2, 0, 0)) {
                                ((L12PathEnemyState *)state)->destination = i;
                                break;
                            }
                        }
                        if (((L12PathEnemyState *)state)->destination == -1) {
                            func_002A7750(obj, obj[0x20], 5);
                            func_002B3868(obj);
                            break;
                        }
                    }
                }
            }
            forward = ((L12PathEnemyState *)state)->destination - ((L12PathEnemyState *)state)->pathIndex;
            if (forward < 0)
                { int t = forward - 1; forward = t + *(int *)path; }
            backward = ((L12PathEnemyState *)state)->pathIndex - ((L12PathEnemyState *)state)->destination;
            if (backward < 0)
                { int t = backward - 1; backward = t + *(int *)path; }
            ((L12PathEnemyState *)state)->nextPoint = forward < backward ? ((L12PathEnemyState *)state)->pathIndex + 1 : ((L12PathEnemyState *)state)->pathIndex - 1;
            if (((L12PathEnemyState *)state)->nextPoint < 0)
                ((L12PathEnemyState *)state)->nextPoint = *(int *)path - 1;
            if (((L12PathEnemyState *)state)->nextPoint == *(int *)path)
                ((L12PathEnemyState *)state)->nextPoint = 0;
        }
        {
            u8 *other = ((L12PathEnemyState *)state)->targetObject;
            angle = func_00283248(*(float *)(other + 0x10) - *(float *)(obj + 0x10),
                                  *(float *)(other + 0x14) - *(float *)(obj + 0x14));
            func_002AA800(obj + 0xF8, 0, angle, 7.2000003f);
        }
        oldZ = *(float *)(obj + 0x18);
        *(float *)(state + 0x218) = 0;
        flags = func_PAL_L01_00323068(obj, path + 0x10 + (((L12PathEnemyState *)state)->nextPoint << 4));
        ground = func_002A89A8((obj + 0x10), 0, 0.5f);
        if (flags & 0x20) {
            if (!*(int *)(state + 0x248) || *(float *)(obj + 0x18) - ground > D_L12_001B0B14)
                *(float *)(obj + 0x18) = oldZ;
            else if (*(float *)(obj + 0x18) < ((L12PathEnemyState *)state)->minimumHeight)
                *(float *)(obj + 0x18) = ((L12PathEnemyState *)state)->minimumHeight;
            else
                func_0026FEB8(D_L12_001B0B18, (double)(*(float *)(obj + 0x18) - func_002A89A8((obj + 0x10), 0, 0.5f)), *(s16 *)(obj + 0xB2));
        }
        if (*(float *)(obj + 0x18) < *(float *)(path + (((L12PathEnemyState *)state)->nextPoint << 4) + 0x18) &&
            *(float *)(path + (((L12PathEnemyState *)state)->nextPoint << 4) + 0x18) - *(float *)(obj + 0x18) > 0.8f) {
            *(float *)(obj + 0x18) += D_L12_001B0A54 * 0.020000001f;
            if (*(float *)(obj + 0x18) < ground)
                *(float *)(obj + 0x18) = ground;
        }
        if (*(float *)(obj + 0x18) > *(float *)(path + (((L12PathEnemyState *)state)->nextPoint << 4) + 0x18) &&
            *(float *)(path + (((L12PathEnemyState *)state)->nextPoint << 4) + 0x18) - *(float *)(obj + 0x18) < -0.8f) {
            *(float *)(obj + 0x18) -= D_L12_001B0A54 * 0.020000001f;
            if (*(float *)(obj + 0x18) < ground)
                *(float *)(obj + 0x18) = ground;
        }
        if (flags & 0x80) {
            if (((L12PathEnemyState *)state)->destination == ((L12PathEnemyState *)state)->nextPoint) {
                ((L12PathEnemyState *)state)->pathIndex = ((L12PathEnemyState *)state)->nextPoint;
                ((L12PathEnemyState *)state)->nextPoint = -1;
                func_002A7750(obj, obj[0x20], 5);
                func_002B3868(obj);
            } else {
                forward = ((L12PathEnemyState *)state)->destination - ((L12PathEnemyState *)state)->nextPoint;
                ((L12PathEnemyState *)state)->pathIndex = ((L12PathEnemyState *)state)->nextPoint;
                if (forward < 0)
                    { int t = forward - 1; forward = t + *(int *)path; }
                backward = ((L12PathEnemyState *)state)->nextPoint - ((L12PathEnemyState *)state)->destination;
                if (backward < 0)
                    { int t = backward - 1; backward = t + *(int *)path; }
                ((L12PathEnemyState *)state)->nextPoint = forward < backward ? ((L12PathEnemyState *)state)->nextPoint + 1 : ((L12PathEnemyState *)state)->nextPoint - 1;
                if (((L12PathEnemyState *)state)->nextPoint < 0)
                    ((L12PathEnemyState *)state)->nextPoint = *(int *)path - 1;
                if (((L12PathEnemyState *)state)->nextPoint == *(int *)path)
                    ((L12PathEnemyState *)state)->nextPoint = 0;
            }
        }
        break;
    }
    }
    switch (obj[0x20]) {
    case 5:
        if (func_002B3868(obj)) {
            ((L12PathEnemyState *)state)->flags = (((L12PathEnemyState *)state)->flags & ~0x10) | 1;
            *(float *)(state + 0x198) = (D_L12_001B0AB0 * 0.5f * 5.0f + 2.0f) / 6.0f;
            if (obj[0x43] != 0)
                func_PAL_002A7E68(obj, 0, 0, 17);
            ((L12PathEnemyState *)state)->attackTimer = 125;
        }
        if (func_00282978(state + 0x262)) {
            if (obj[0x43] != 1)
                func_PAL_002A7E68(obj, 1, 0, 17);
            func_002A7750(obj, 21, -1);
        }
        break;
    case 3:
        if (func_002B3868(obj)) {
            func_002B60B0(obj, 0.012800001f, 0.64000005f, 0.12566373f, 0.12566373f);
            ((L12PathEnemyState *)state)->flags = (((L12PathEnemyState *)state)->flags & ~0x10) | 1;
            *(int *)(state + 0x168) = 1;
        }
        if (func_PAL_L12_003E6198(obj, D_L12_001FEAC0[*(int *)(state + 0x164)])) {
            func_002A7750(obj, 5, 0);
            if (obj[0x43] != 0)
                func_PAL_002A7E68(obj, 0, 0, 0);
            ((L12PathEnemyState *)state)->flags |= 0x10;
        }
        break;
    case 21: {
        u8 *path;
        int flags;
        float oldZ, ground, heightLimit;
        path = D_L12_001FEAC0[*(int *)(state + 0x158)];
        if (func_002B3868(obj)) {
            int nextIndex = ((L12PathEnemyState *)state)->pathIndex + 1;
            if (nextIndex == *(int *)path)
                ((L12PathEnemyState *)state)->nextPoint = 0;
            else
                ((L12PathEnemyState *)state)->nextPoint = nextIndex;
            func_L12_003E1CB0(obj);
        }
        if (*(int *)(state + 0x16C))
            func_PAL_L12_003E63A0(obj);
        oldZ = *(float *)(obj + 0x18);
        *(float *)(state + 0x218) = 0;
        flags = func_PAL_L01_00323068(obj, path + 0x10 + (((L12PathEnemyState *)state)->nextPoint << 4));
        ground = func_002A89A8((obj + 0x10), 0, 0.5f);
        if (flags & 0x20) {
            if (!*(int *)(state + 0x248) || *(float *)(obj + 0x18) - ground > D_L12_001B0B14)
                *(float *)(obj + 0x18) = oldZ;
            else if (*(float *)(obj + 0x18) < ((L12PathEnemyState *)state)->minimumHeight)
                *(float *)(obj + 0x18) = ((L12PathEnemyState *)state)->minimumHeight;
            else
                func_0026FEB8(D_L12_001B0B18, (double)(*(float *)(obj + 0x18) - func_002A89A8((obj + 0x10), 0, 0.5f)), *(s16 *)(obj + 0xB2));
            heightLimit = *(float *)(path + (((L12PathEnemyState *)state)->nextPoint << 4) + 0x18) < oldZ ? *(float *)(path + (((L12PathEnemyState *)state)->nextPoint << 4) + 0x18) : oldZ;
            if (*(float *)(obj + 0x18) < heightLimit)
                *(float *)(obj + 0x18) = heightLimit;
        }
        if (*(float *)(obj + 0x18) < *(float *)(path + (((L12PathEnemyState *)state)->nextPoint << 4) + 0x18) &&
            *(float *)(path + (((L12PathEnemyState *)state)->nextPoint << 4) + 0x18) - *(float *)(obj + 0x18) > 0.8f) {
            *(float *)(obj + 0x18) += D_L12_001B0A54 * 0.020000001f;
            if (*(float *)(obj + 0x18) < ground)
                *(float *)(obj + 0x18) = ground;
        }
        if (*(float *)(obj + 0x18) > *(float *)(path + (((L12PathEnemyState *)state)->nextPoint << 4) + 0x18) &&
            *(float *)(path + (((L12PathEnemyState *)state)->nextPoint << 4) + 0x18) - *(float *)(obj + 0x18) < -0.8f) {
            *(float *)(obj + 0x18) -= D_L12_001B0A54 * 0.020000001f;
            if (*(float *)(obj + 0x18) < ground)
                *(float *)(obj + 0x18) = ground;
        }
        if (flags & 0x80) {
            ((L12PathEnemyState *)state)->attackTimer = 167;
            ((L12PathEnemyState *)state)->pathIndex = ((L12PathEnemyState *)state)->nextPoint;
            if (obj[0x43] != 0)
                func_PAL_002A7E68(obj, 0, 0, 17);
            changeModeL12Patrol(obj, 5, -1);
        }
        break;
    }
    case 15:
        if (func_002B3868(obj)) {
            ((L12PathEnemyState *)state)->attackTimer = 33;
            if (obj[0x43] != 8)
                func_PAL_002A7E68(obj, 8, 0, 17);
            func_002B60B0(obj, D_L12_001B0AA8 * 5.0000002e-05f,
                          D_L12_001B0AAC * 0.0025000002f,
                          0.12566373f, 0.12566373f);
            *(float *)(state + 0x198) = (D_L12_001B0AB0 * 0.25f * 5.0f + 2.0f) / 6.0f;
        }
        if (func_00282978(state + 0x262) || (distance < 4.0f && ((L12PathEnemyState *)state)->attackTimer < 17)) {
            float turn = D_L12_001B0AA8 * 0.00040000002f;
            float speed = D_L12_001B0AAC * 0.020000001f;
            *(float *)(state + 0x198) = (D_L12_001B0AB0 * 5.0f + 2.0f) / 6.0f;
            func_002B60B0(obj, turn, speed, 0.0025132746f, 0.25132746f);
            if (obj[0x43] != 7)
                func_PAL_002A7E68(obj, 7, 0, 17);
            ((L12PathEnemyState *)state)->attackTimer = 17;
            func_002A7750(obj, 16, -1);
        } else {
            func_0029FC20(obj, 2, matrix);
            func_002830C0(&pos, D_L12_001B0A90, matrix);
            goto smoke;
        }
        break;
    case 16:
        if (func_002B3868(obj))
            func_002E5CF8(3, 0, obj);
        func_0029FC20(obj, 2, matrix);
        func_002830C0(&pos, D_L12_001B0A90, matrix);
        angle = func_00283248(*(float *)(state + 0x130) - *(float *)(obj + 0x10),
                              *(float *)(state + 0x134) - *(float *)(obj + 0x14));
        if (func_00282C48(func_00283BE0(*(float *)(obj + 0xF8), angle)) > 0.174532949924469f) {
            float speed = func_00282E80(&pos, (obj + 0x10));
            func_00282F20(&velocity, obj + 0xC0, speed * 0.02f);
            velocity.z = (*(float *)(state + 0x138) - pos.z) * 0.02f;
        }
        if (!func_PAL_002AF6C0(obj, D_L12_001B0A50)) {
smoke:
            limit = func_002A7878(D_L12_001B0A80, D_L12_001B0A84);
            i = func_002A77E0(D_L12_001B0A8C);
            func_002C2210(&pos, (int)((D_L12_001B0A88 * 5.0f + 2.0f) / 6.0f), limit * 0.3f, limit,
                         D_L12_001B0A58, 0, i, D_L12_001A8F20, 0, 0.0f);
            break;
        }
        if (func_00282C48(func_00283BE0(*(float *)(obj + 0xF8), angle)) > 0.174532949924469f) {
            func_00282F20(&velocity, obj + 0xC0, 0.64000005f);
            velocity.z = (*(float *)(state + 0x138) - pos.z + D_L12_001B0B34) * 0.02f;
        } else {
            qcopy(&target, state + 0x130);
            target.z += D_L12_001B0B34;
            func_00282CF0(&velocity, &target, &pos);
            func_00282F20(&velocity, &velocity, 0.64000005f);
        }
        if (velocity.z > D_L12_001B0B08 * 0.020000001f)
            velocity.z = D_L12_001B0B08 * 0.020000001f;
        else if (velocity.z < -100.0f)
            velocity.z = -100.0f;
        func_PAL_L12_0040CBA0(obj, &velocity, &pos, 0, (float)state[0x34]);
        ((L12PathEnemyState *)state)->attackTimer = 42;
        func_002A7750(obj, 23, -1);
        break;
    case 23:
        if (func_00282978(state + 0x262))
            func_002A7750(obj, 15, -1);
        if (((L12PathEnemyState *)state)->attackTimer < 25 && obj[0x42] != 3 && obj[0x43] != 3)
            func_PAL_002A7E68(obj, 3, 0, 17);
        if (func_00282E80(state + 0x130, (obj + 0x10)) < 8.0f && ((L12PathEnemyState *)state)->attackTimer < 29) {
            if (obj[0x43] != 7)
                func_PAL_002A7E68(obj, 7, 0, 17);
            func_002A7750(obj, 16, -1);
        }
        break;
    case 24:
        if (func_002B3868(obj) && obj[0x43] != 9)
            func_PAL_002A7E68(obj, 9, 0, 17);
        if (func_PAL_002AF6C0(obj, 12.5f))
            *(int *)(obj + 0x48) = 0;
        break;
    }
}
