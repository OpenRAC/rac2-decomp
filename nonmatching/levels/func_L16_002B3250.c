/* The complete 64-byte contact record includes the opaque +0x34 word.
 * The bounded consumer audit found no semantic use of that word here; this
 * is not proof that it is padding or that every indirect consumer ignores it. */
/*
 * Retained manually written near miss; historical evidence only.
 * No linked-image equality or complete retail semantics is established.
 * Compiler: game EE-GCC 2.9-ee-991111b (project profile).
 * Profile: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -fno-gcse.
 * Reported final C / retail: 944 / 940 bytes; size equality is not a match.
 * us: 0/1 placements; 944/940 bytes.
 * us2: absent from catalogue (not a match).
 * pal: absent from catalogue (not a match).
 * Residual: 4 excess bytes; branch/reload allocation differs. E668 float(void), E5F0 float(float) qualified by ABI support and current records retain64-byte extent.
 * Reopening condition: New measured source/data-layout or allocator hypothesis; do not repeat retained flag/control-flow trials or use artificial aliases/barriers.
 * Where listed, tools/check.py measurements predate retention; no compilation was rerun for this copy.
 */

/* 944/940 bytes; -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -fno-gcse.
 * Three bounded trials; typed global view regressed952 bytes. Allocation and conditional load scheduling remain. */
#include "include_asm.h"
typedef int ContactQuad __attribute__((mode(TI)));
typedef struct ContactRecord {
    unsigned char pad0[16];
    ContactQuad normal;
    char *target;
    unsigned int flags;
    unsigned char kind;
    unsigned char pad29[3];
    float remaining;
    unsigned int vectorFlags;
    unsigned char pad34[4];
    char *owner;
    unsigned char pad3C[4];
} ContactRecord;
extern ContactRecord D_L16_001C41C0[];
extern unsigned char D_00189E20[];
extern int D_L16_001A8F00;
extern unsigned char D_001A7A33, D_001A7A32;
extern float func_L00_0037E668(void);
extern float func_L00_0037E5F0(float);
extern void func_L00_002A6708(void);
extern void func_00282CF0(char *, char *, char *);
extern void func_L00_002D36E0(float *, int, float, float, float);
extern int func_L16_002C0BC8(int, int);
extern void *func_002A9640(void *, unsigned int, int);
extern int func_00283CF0(float);
extern void func_L00_002A4EF8(int);
extern int func_L00_002B9B88(int, int);
extern void func_L00_002B2C58(int, int, float, float);
extern void func_L00_002D3C68(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
#define PSHORT(off) (*(short *)(D_00189E20 + (off)))
#define PINT(off) (*(int *)(D_00189E20 + (off)))
#define PBYTE(off) (D_00189E20[(off)])

/* Consume the player's current contact and apply its movement response. */
int func_L16_002B3250(int apply) {
    ContactQuad impulse;
    ContactRecord *contact;
    char *effect;
    char *player;
    int special = 0;
    unsigned char index;
    float lift;
    if (PINT(0x229C) == 20 || PINT(0x229C) == 7 || PINT(0x2294) == 49) return 0;
    if (PSHORT(0x1DC) || D_L16_001A8F00) return 0;
    PINT(0x249C) = 0;
    player = *(char **)(D_00189E20 + 0x2290);
    index = ((unsigned char *)player)[0xA8];
    if (index == 255) return 0;
    contact = D_L16_001C41C0 + index;
    if (contact->owner != player || !(contact->flags & 9)) return 0;
    if (contact->remaining != 0.0f) { D_001A7A33 = 0; D_001A7A32 = 1; }
    if (func_L00_0037E668() != 0.0f && !PBYTE(0x22B4)) {
        contact->remaining = func_L00_0037E5F0(contact->remaining);
        if (contact->remaining == 0.0f) return 0;
    }
    *(char **)(D_00189E20 + 0x249C) = contact->target;
    if (PINT(0x229C) == 15) {
        PSHORT(0x68E) = 1;
        *(ContactRecord **)(D_00189E20 + 0x6C4) = contact;
        return 0;
    }
    if (!apply) return 1;
    func_L00_002A6708();
    if (contact->vectorFlags & 1) {
        impulse = contact->normal;
        if (((float *)&contact->normal)[3] == 5627.925f) special = 1;
    } else if (!contact->target) func_L00_002D36E0((float *)&impulse, 0, -1.0f, 0.0f, 0.0f);
    else func_00282CF0((char *)&impulse, (char *)D_00189E20 + 0x80, contact->target + 16);
    if (!PBYTE(0x22B4)) {
        if (PINT(0x249C) && (*(short *)(PINT(0x249C) + 0xAA) == 0x4EB || *(short *)(PINT(0x249C) + 0xAA) == 0x558)) {
            func_L16_002C0BC8(125, 1);
            return 1;
        }
        if ((PINT(0x2294) == 1 || PINT(0x2294) == 29 || PINT(0x1500)) && !(contact->flags & 8)) {
            effect = func_002A9640(*(char **)(D_00189E20 + 0x2290), 1, 0);
            if (effect) func_L00_002A4EF8(func_00283CF0(*(float *)(effect + 0x2C)));
            if (!PINT(0x24CC)) func_L16_002C0BC8(22, 1);
            PSHORT(0x1DC) = 77;
            if (!PSHORT(0x21C)) PSHORT(0x21C) = 18;
            func_L00_002B9B88(20, 0);
            return 0;
        }
        if (contact->flags & 8) func_L16_002C0BC8(140, 1);
        else func_L16_002C0BC8(22, 1);
        if (PINT(0x2294) == 140) impulse = 0;
        else {
            lift = 0.055000003f;
            if (PBYTE(0x1497)) lift = 0.0f;
            func_L00_002B2C58((int)&impulse, special, lift, 0.028333336f);
            if (special && contact->kind == 4) func_L00_002D3C68((char *)&impulse, (char *)&impulse, 2.0f);
        }
    }
    func_00282CC0((char *)D_00189E20 + 0xF0, (char *)D_00189E20 + 0xF0, (char *)&impulse);
    func_00282CC0((char *)D_00189E20 + 0x110, (char *)D_00189E20 + 0x110, (char *)&impulse);
    return 1;
}
