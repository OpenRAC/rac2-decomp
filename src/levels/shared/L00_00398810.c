#include "common.h"
typedef struct { int active; unsigned char kind; char pad05[0xDB]; } WeaponRecord;
typedef struct { short count; short index[31]; } ProjectileList;
extern char *D_0018C0B0;
extern unsigned char D_00139568[];
extern WeaponRecord D_L00_00262570[];
extern ProjectileList D_L00_001B1FF0 MACRO_ADDR;
extern s32 D_L00_001B1E9C_base __asm__("D_L00_001B1E9C") MACRO_ADDR;
extern s16 D_L00_001B1FF0_list[] __asm__("D_L00_001B1FF0") MACRO_ADDR;
extern char *func_0029EFD0(int);
extern int func_002FED90(void *, int, float, float, float);
extern void func_002AB650(u8 *);
extern void func_002A0F48(char *);
extern void func_002ACAD0(int, unsigned short *), func_002ACA50(int, short *, short);
/* Separate predicates match the weapon pool's two active families. */
static __inline__ int projectile_standard_weapon(void) {
    unsigned char *game = D_00139568;
    WeaponRecord *entry = D_L00_00262570 + game[0x11];
    int result;
    if (!entry->active) goto no;
    if (entry->kind == 2) goto yes;
    if (entry->kind != 1) goto no;
yes:
    result = 1;
    goto done;
no:
    result = 0;
done:
    return result;
}
static __inline__ int projectile_upgraded_weapon(void) {
    unsigned char *game = D_00139568;
    WeaponRecord *entry = D_L00_00262570 + game[0x11];
    int result = 0;
    if (entry->active) result = entry->kind == 3;
    return result;
}
/* Creates a projectile and retires the oldest live entries when the shared list is full. */
char *func_L00_00398810(char *position, char *direction) {
    char *actor = func_0029EFD0(0xCB);
    char *state, *hero, *oldest;
    int i, count, age, oldestAge;
    if (actor) {
        *(unsigned char *)(actor + 0x30) = 0xFF;
        *(unsigned short *)(actor + 0x32) = 0x1FF;
        *(unsigned short *)(actor + 0x34) |= 0x100;
        state = *(char **)(actor + 0x68);
        qcopy(actor + 0x10, position);
        qcopy(state + 0x10, direction);
        *(unsigned char *)(actor + 0x20) = 0;
        hero = D_0018C0B0;
        qcopy(actor + 0xC0, hero + 0xC0);
        qcopy(actor + 0xD0, hero + 0xD0);
        qcopy(actor + 0xE0, hero + 0xE0);
        *(int *)(state + 0x30) = 0;
        *(int *)(state + 0x2C) = 0;
        *(int *)(state + 0x28) = 0;
        *(int *)(state + 0x20) = func_002FED90(actor, 0, 1.0f, 1.0f, 1.0f);
        func_002AB650((u8 *)actor);
        *(unsigned char *)(state + 7) = 250;
        *(short *)(state + 0xC) = 4;
        *(short *)(state + 0xE) = 15;
        *(short *)state = 0;
        *(unsigned char *)(state + 8) = 0;
        *(unsigned char *)(state + 9) = 0;
        *(int *)(state + 0x44) = 0;
        *(int *)(state + 0x48) = 0;
        *(int *)(state + 0x4C) = 0;
        *(int *)(state + 0x40) = 0;
        *(int *)(state + 0x3C) = 0;
        *(int *)(state + 0x38) = 0;
        if (projectile_standard_weapon() || projectile_upgraded_weapon()) *(float *)(state + 0x24) = 60.0f;
        else *(float *)(state + 0x24) = 6.0f;
        while (D_L00_001B1FF0_list[0] >= 6) {
            unsigned char retired = 5;
            oldest = 0;
            oldestAge = 0;
            for (i = 1; i <= D_L00_001B1FF0_list[0]; i++) {
                char *candidate = (char *)(D_L00_001B1E9C_base + (D_L00_001B1FF0_list[i] << 8));
                if (candidate && *(short *)(candidate + 0xAA) == 0xCB && *(unsigned char *)(candidate + 0x20) < 4) {
                    age = *(int *)(*(char **)(candidate + 0x68) + 0x3C);
                    if (oldestAge <= age) { oldest = candidate; oldestAge = age; }
                }
            }
            if (oldest) {
                *(unsigned char *)(oldest + 0x20) = retired;
                func_002ACAD0((int)oldest, (unsigned short *)&D_L00_001B1FF0);
                *(int *)(*(char **)(oldest + 0x68) + 0x40) = 1;
            }
        }
        func_002ACA50((int)actor, (short *)&D_L00_001B1FF0, 31);
        func_002A0F48(actor);
    }
    return actor;
}
