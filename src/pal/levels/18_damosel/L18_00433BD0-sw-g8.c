#include "include_asm.h"

#include "common.h"
extern void func_0029F338(void *);
extern int func_002E59B0(u8 *, int);
extern int func_002E5CF8(int, int, u8 *);
extern void func_002E59F8(int);
extern u8 D_00188660[];
extern int func_002A9640(u8 *, int, int);
extern float func_PAL_002AA108(u8 *, int);
extern void func_PAL_002B3F18(void *, void *, void *);
extern char *func_PAL_L00_003FB330(void *, int, int, int, float, float, int, int, int, int, int, int, int, void *);
extern u8 *D_L18_001B281C;
extern void func_PAL_L18_00437A28(u8 *);
extern void func_L18_00432B30(u8 *, int);
extern void func_L18_00432D08(u8 *);
extern void func_L18_0042F768(u8 *);
extern void func_PAL_L18_00434320(u8 *, int, int);
extern int func_L18_0042F688(u8 *, void *, int, void *, int, float);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002B0A68(u8 *, int, void *, int, float, float, float, float);
extern void func_002A7470(u8 *, int, int, int);
extern void func_002A7750(u8 *, int, int);
extern int func_002ACBC8(u8 *, int);
extern u8 D_00189EA0[];
extern float func_0029F530(u8 *);
extern int func_002B3868(u8 *);
extern int *D_L18_001FE480[];
extern int func_L09_0033E690(void *, int, float);
typedef struct {
    u8 pad00[0x20];
    float health;
    u8 pad24[10];
    u8 state;
    u8 pad2F[0x21];
    float hit[4];
    u8 pad60[0x10];
    float movement[4];
    float velocity[4];
    int ids[6];
    int paths[2];
    short groups[6];
    short waypoint;
    short group;
    int escapePath;
    int trigger;
    u8 padC8[0x14];
    int voice;
} LeaderState;
static inline void ReleaseVoice(u8 *a, LeaderState *s) {
    int slot = s->voice;
    if (slot != -1) {
        u8 *record = D_00188660 + slot * 0x70;
        if (*(u8 **)(record + 0x88) == a && record[0x74])
            func_002E59F8(slot);
    }
    s->voice = -1;
}
extern u8 *D_PAL_FFFF001B;

void func_PAL_L18_00433BD0(u8 *a) {
    LeaderState *s = *(LeaderState **)(a + 0x68);
    float hit;
    float vec[4];

    if (a[0x20] >= 2) {
        if (!func_002E59B0(a, s->voice))
            s->voice = func_002E5CF8(0, 4, a);
    } else if (func_002E59B0(a, s->voice)) {
        ReleaseVoice(a, s);
    }
    hit = func_PAL_002AA108(a, func_002A9640(a, 0x10000, 0));
    if (a[0x20] >= 2) {
        s->health -= hit;
        func_PAL_002B3F18(a, s->hit, &s->health);
        if (s->health <= 0.0f || s->state == 2) {
            int i;
            func_PAL_L00_003FB330(a + 0x10, 1, 0x19, 20, 1.0f, 20.0f, 20, 20, 45, 1, 1, 1, 0, 0);
            for (i = 0; i < 6; i++) {
                if (s->ids[i] != -1)
                    func_PAL_L18_00437A28(D_L18_001B281C + (s->ids[i] << 8));
            }
            if (func_002E59B0(a, s->voice))
                ReleaseVoice(a, s);
            func_002A7A00(vec, 0.120000005f, 0.3f);
            func_00282CC0(vec, vec, s->velocity);
            func_002B0A68(a, 63, vec, 255, 3.0f, 6.0f, 3.0f, 6.0f);
            func_0029F338(a);
            return;
        }
    }
    switch (a[0x20]) {
    case 0: {
        int i;
        int all;
        u8 *base;
        func_002A7470(a, 1, 0, 0);
        *(int *)(a + 0x48) = 0;
        *(int *)(a + 0x98) = 0;
        *(u16 *)(a + 0x34) = (*(u16 *)(a + 0x34) | 0x41) & 0xEFFF;
        func_002A7750(a, 1, -1);
        s->state = 1;
        ReleaseVoice(a, s);
        base = D_PAL_FFFF001B;
        *(u16 *)(a + 0x34) |= 0x1000;
        all = 1;
        for (i = 0; i < 6; i++) {
            u8 *e;
            if (s->ids[i] == -1)
                continue;
            e = base + (s->ids[i] << 8);
            if (e == 0)
                continue;
            if (e[0x20] == 0xFE)
                continue;
            if (e[0x20] == 0xFD)
                continue;
            all = 0;
            break;
        }
        if (all) {
            func_0029F338(a);
            return;
        }
        break;
    }
    case 1:
        if (s->trigger != -1 && func_002ACBC8(D_00189EA0, s->trigger))
            func_L18_0042F768(a);
        break;
    case 2: {
        float damage = func_0029F530(a);
        if (func_002B3868(a)) {
            int i;
            a[0xBC] = 0;
            *(float *)(a + 0x48) = 1.0f;
            for (i = 0; i < 6; i++) {
                if (s->ids[i] != -1)
                    func_L18_00432B30(D_L18_001B281C + (s->ids[i] << 8), (int)a);
            }
        } else if (a[0xBC] == 0) {
            func_PAL_L18_00434320(a, 1, 1);
            if (damage > 8.0f) {
                int i;
                a[0xBC] = 1;
                for (i = 0; i < 6; i++) {
                    if (s->ids[i] != -1 && s->groups[i] == s->group) {
                        func_L18_00432D08(D_L18_001B281C + (s->ids[i] << 8));
                        s->ids[i] = -1;
                    }
                }
                s->group++;
                *(int *)(a + 0x48) = 0;
            }
        } else if (a[0xBC] == 1) {
            func_PAL_L18_00434320(a, 1, 1);
            if (*(u16 *)(a + 0x96) >= 26) {
                a[0xBC] = 2;
                *(float *)(a + 0x48) = 1.0f;
            }
        } else if (a[0xBC] == 2) {
            func_PAL_L18_00434320(a, 1, 1);
            if (damage > 59.0f) {
                *(int *)(a + 0x48) = 0;
                func_002A7750(a, a[0x94], -1);
            }
        }
        break;
    }
    case 3:
        if (func_002B3868(a)) {
            s->waypoint = func_L09_0033E690(a + 0x10, s->paths[s->group], 0.0f);
            break;
        } else {
            int id = s->paths[s->group];
            float speed = 5.0f;
            if (s->waypoint == D_L18_001FE480[id][0] - 1)
                speed = 0.3f;
            if (!func_L18_0042F688(a, s->movement, id, &s->waypoint, 0, speed)) {
                if (s->group <= 0 && s->paths[1] != -1)
                    func_002A7750(a, 3, -1);
                else
                    func_002A7750(a, 4, -1);
                func_002A7750(a, 2, -1);
            }
        }
        func_PAL_L18_00434320(a, 1, 1);
        break;
    case 4:
        if (func_002B3868(a)) {
            s->waypoint = func_L09_0033E690(a + 0x10, s->escapePath, 0.0f);
            break;
        } else if (!func_L18_0042F688(a, s->movement, s->escapePath, &s->waypoint, 0, 2.0f)) {
            if (func_002E59B0(a, s->voice))
                ReleaseVoice(a, s);
            func_0029F338(a);
            return;
        }
        func_PAL_L18_00434320(a, 1, 1);
        break;
    }
    if (*(u16 *)(a + 0x96) <= 0xFFFE)
        (*(u16 *)(a + 0x96))++;
}
