/* 30 October 2026 retained reconstruction, not a match.
 * Profile: -O2 -G8 -ffunction-sections -fno-force-mem. USA v1.01: 1080/1064 bytes, 0/1.
 * Complete hero-tracking reconstruction with two joint controllers and event-slot
 * lifetime. Five saved FPRs and frame0x70 instead of0x60 remain: repeated spring-call
 * constants are kept across calls. Statement sequencing and no-GCSE remain 1084 bytes; no-force-mem
 * removes one instruction. Constructor retains its real third state-byte argument and
 * pointer return.
 * Older source and trial history remain in Git and the private workspace.
 */
#include "common.h"

extern u8 D_00189E20[];
extern u8 D_00189EA0[];
extern u8 D_00188660[];
extern float D_L12_001AFC70 __attribute__((sda));
extern float D_L12_001AFC74 __attribute__((sda));
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);
extern float func_00282C48(float);
extern void *func_002A9640(void *, unsigned int, int);
extern char *func_L00_00326620(char *, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_0029F338(void *);
extern float func_002AAA00(float *, float *, int, float, float, float, float);
extern void func_002AEC48(void *, void *, unsigned int, float, float);
extern void func_002A0F48(void *);

#define REAL(p, off) (*(float *)((p) + (off)))
#define WORD(p, off) (*(int *)((p) + (off)))

/* Tracks the hero with two joint controllers and owns one event-table slot. */
void func_L12_003BE7D0(u8 *object)
{
    u8 *state;
    u8 *hero;
    u8 *slot;
    int index;
    float yaw = 0.0f;
    float pitch = 0.0f;
    float acceleration, damping;

    *(u16 *)(object + 0x34) |= 4;
    state = *(u8 **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_00282E80(object + 0x10, D_00189EA0) < 16.0f) {
            object[0x20] = 2;
            if (object[0x43] != 1)
                func_002A7470(object, 1, 0, 30);
        }
        break;
    case 2:
        hero = D_00189E20;
        yaw = func_00283248(REAL(hero, 0x80) - REAL(object, 0x10),
            REAL(hero, 0x84) - REAL(object, 0x14));
        yaw = func_00283BE0(yaw, REAL(object, 0xF8));
        yaw = func_00283B98(yaw, 1.5707964897155762f);
        pitch = func_00282E80(hero + 0x80, object + 0x10);
        pitch = func_00283248(pitch, REAL(object, 0x18) - REAL(hero, 0x88));
        if (func_00282E80(object + 0x10, hero + 0x80) > 20.0f) {
            object[0x20] = 1;
            if (object[0x43] != 0)
                func_002A7470(object, 0, 0, 30);
        }
        if (func_002A9640(object, 0x04010000, 0) != 0 && WORD(state, 0x110) == 0)
            func_002A7750(object, 3, -1);
        object[0xA8] = 255;
        break;
    case 3:
        func_L00_00326620((char *)object, 0x1132, object[0x30]);
        func_002E5CF8(0, 0, object);
        index = WORD(state, 0x114);
        if (index != -1) {
            slot = D_00188660 + index * 0x70;
            if (*(u8 **)(slot + 0x88) == object && slot[0x74] != 0)
                func_002E59F8(index);
        }
        WORD(state, 0x114) = -1;
        func_0029F338(object);
        return;
    }

    if (func_00282C48(func_00283BE0(yaw, REAL(state, 0x100))) >
            D_L12_001AFC74 * 0.01745329424738884f) {
        slot = D_00188660 + WORD(state, 0x114) * 0x70;
        if (*(u8 **)(slot + 0x88) != object || slot[0x74] == 0)
            WORD(state, 0x114) = func_002E5CF8(1, 4, object);
    } else {
        index = WORD(state, 0x114);
        if (index != -1) {
            slot = D_00188660 + index * 0x70;
            if (*(u8 **)(slot + 0x88) == object && slot[0x74] != 0)
                func_002E59F8(index);
        }
        WORD(state, 0x114) = -1;
    }
    acceleration = 0.03f;
    func_002AAA00((float *)(state + 0x100), (float *)(state + 0x108), 0,
        yaw, 0.0017453294713050127f, 0.0017453294713050127f, 0.10471977293491364f);
    damping = 0.3f;
    func_002AAA00((float *)(state + 0x104), (float *)(state + 0x10C), 0,
        pitch, 0.0017453294713050127f, 0.0017453294713050127f, 0.10471977293491364f);
    REAL(state, 0xE0) = REAL(state, 0x104) * 0.5f;
    REAL(state, 0xE8) = REAL(state, 0x100) * 0.5f;
    REAL(state, 0x68) = REAL(state, 0x100) * 0.5f;
    REAL(state, 0x60) = REAL(state, 0x104) * 0.5f;
    func_002AEC48(object, state, 0, acceleration, damping);
    func_002AEC48(object, state + 0x80, 1, acceleration, damping);
    func_002A0F48(object);
    REAL(object, 0xC) = D_L12_001AFC70;
}
