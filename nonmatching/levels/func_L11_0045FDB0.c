/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G8 -ffunction-sections (a sibling of src/levels/11_joba/L11_00453358-g8.c,
 * which includes common.h for qcopy; the rate and argument are read through $gp).
 * Retail: 328 bytes; compiled: 328 bytes.
 * Coverage: us: 0/1 (tools/check.py, 2026-10-28, master 1243c8ea).
 * Residual: two stores after func_002A7878 are swapped: retail stores the state's +0x24
 * float before the object's +0x23 byte; this C stores +0x23 first. Every other word matches.
 * Found by search: the header order (0x30, 0x32, 0x31, 0x20) and the $gp argument read into
 * a local before the rate. No order of the six tail statements (0x24, 0x23, both 0x34
 * stores, the argument read, the rate), with or without the read moved before func_002A7940,
 * gives retail's pair.
 * Reopen: a type or spelling for the +0x23 byte or the +0x24 float that changes their
 * scheduling priority.
 */
extern void *func_0029EFD0(int);
extern void func_002E5DA0(int, int, void *, int);
extern void func_L11_00460258(void *, int);
extern float D_L11_001B22C4 __attribute__((sda));
extern int D_L11_001B22CC __attribute__((sda));

/* Spawns a kind-0xE7B object for OWNER at POSITION heading along DIRECTION: opaque, the
   owner's 8-byte word at +0x38, a state holding the direction, the owner, A and B, a value
   from func_002A7940, a random angle between 3 and 6 degrees and D; flags 0x1008 and a
   rate of D_L11_001B22C4 * C. It is then set up and registered. Returns it, or 0. */
u8 *func_L11_0045FDB0(u8 *owner, void *direction, void *position, float a, float b, float c,
                      float d)
{
    u8 *object;
    u8 *state;
    int arg;

    object = func_0029EFD0(0xE7B);
    if (object != 0) {
        object[0x30] = 0xFF;
        *(u16 *)(object + 0x32) = 0xFF;
        object[0x31] = 1;
        object[0x20] = 0;
        *(long *)(object + 0x38) = *(long *)(owner + 0x38);
        qcopy(object + 0x10, position);
        state = *(u8 **)(object + 0x68);
        qcopy(state, direction);
        *(u8 **)(state + 0x10) = owner;
        *(float *)(state + 0x14) = a;
        *(float *)(state + 0x18) = b;
        *(float *)(state + 0x1C) = func_002A7940();
        *(float *)(state + 0x20) = func_002A7878(0.052359887f, 0.10471977f);
        object[0x23] = 0xFF;
        *(float *)(state + 0x24) = d;
        *(u16 *)(object + 0x34) = 8;
        arg = D_L11_001B22CC;
        *(float *)(object + 0x2C) = D_L11_001B22C4 * c;
        *(u16 *)(object + 0x34) |= 0x1000;
        func_L11_00460258(object + 0x10, arg);
        func_002E5DA0(0, 0, object, 0xE7B);
    }
    return object;
}
