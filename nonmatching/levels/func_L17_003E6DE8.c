/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G0 -ffunction-sections (src/levels/17_smolg/L17_003C7C70.c, which declares
 * D_L17_001B2C1C as `extern s32 ... __attribute__((sda))`).
 * Retail: 312 bytes; compiled: 312 bytes.
 * Coverage: us: 0/1 (tools/check.py, 2026-10-28, master 1243c8ea).
 * Residual: register copies and scheduling. Retail loads the owner pointer (+0x720) into $v0
 * and copies it to $a3 in the delay slot of the `== -1` test, computing the entity address
 * only after that test; this C keeps the pointer in $a3 and hoists `sll` into the slot. In
 * the claim, retail reads the +0x74C pointer into $s0 in the call's delay slot.
 * Tried: claim block after the phase logic (block order wrong, 44 lines); the entity
 * computed inside the condition or behind a goto (43); the +0x74C pointer read into a local
 * before or after the phase store (316 bytes); the distance through a local (as here).
 * Reopen: a second spelling of the owner-pointer read that gives retail's copy.
 */
typedef int s32;
typedef unsigned char u8;
typedef float f32;
extern s32 D_L17_001B2C1C;

extern f32 func_00282E48(void *, void *);

/* Claims the object's shared slot (the owner index at the state's +0x720) when it is free
   or its owner (an entity of D_L17_001B2C1C) is gone (kind byte 0xFE or 0xFD): the object
   becomes the owner, the phase word at +0x748 becomes 1 and its distance to the state's
   +0x240 point goes to +0x74C. In phase 1 the owner moves the phase to 2 and a closer
   object takes the slot over; in phase 2 only the owner gets 1. An object whose +0x21
   byte is 0xFF always gets 1. */
s32 func_L17_003E6DE8(s32 a0)
{
    s32 table = D_L17_001B2C1C;
    s32 self = (a0 - table) >> 8;
    s32 obj = *(s32 *)(a0 + 0x68);
    s32 *owner;
    s32 entity;
    s32 *phase;
    f32 distance;

    if (*(u8 *)(a0 + 0x21) == 0xFF)
        return 1;
    owner = *(s32 **)(obj + 0x720);
    entity = table + (*owner << 8);
    if (*owner == -1 || entity == 0 || *(u8 *)(entity + 0x20) == 0xFE ||
        *(u8 *)(entity + 0x20) == 0xFD) {
        *owner = self;
        **(s32 **)(obj + 0x748) = 1;
        **(f32 **)(obj + 0x74C) = func_00282E48((void *)(a0 + 0x10), (void *)(obj + 0x240));
        return 0;
    }
    phase = *(s32 **)(obj + 0x748);
    if (*phase == 1) {
        if (self == *owner) {
            *phase = 2;
            return 1;
        }
        distance = func_00282E48((void *)(a0 + 0x10), (void *)(obj + 0x240));
        if (distance < **(f32 **)(obj + 0x74C)) {
            **(s32 **)(obj + 0x720) = self;
            **(f32 **)(obj + 0x74C) = distance;
            return 0;
        }
    }
    if (**(s32 **)(obj + 0x748) == 2)
        return **(s32 **)(obj + 0x720) == self;
    return 0;
}
