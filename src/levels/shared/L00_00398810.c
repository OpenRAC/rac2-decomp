#include "common.h"
typedef struct { int active; unsigned char kind; char pad05[0xDB]; } WeaponRecord;
typedef struct { short count; short index[31]; } ProjectileList;
extern char *g_hero_moby;
extern unsigned char g_item_slot_to_record[];
extern WeaponRecord g_weapon_l00_table[];
extern ProjectileList D_L00_001B1FF0 MACRO_ADDR;
extern s32 D_L00_001B1E9C_base __asm__("D_L00_001B1E9C") MACRO_ADDR;
extern s16 D_L00_001B1FF0_list[] __asm__("D_L00_001B1FF0") MACRO_ADDR;
extern char *CreateMoby(int);
extern int part_alloc_effect_slot(void *, int, float, float, float);
extern void hero_copy_field_to_moby(u8 *);
extern void func_002A0F48(char *);
extern void RemoveMobyFromIndexList(int, unsigned short *), AddMobyToIndexList(int, short *, short);
/* Separate predicates match the weapon pool's two active families. */
static __inline__ int projectile_standard_weapon(void) {
    unsigned char *game = g_item_slot_to_record;
    WeaponRecord *entry = g_weapon_l00_table + game[0x11];
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
    unsigned char *game = g_item_slot_to_record;
    WeaponRecord *entry = g_weapon_l00_table + game[0x11];
    int result = 0;
    if (entry->active) result = entry->kind == 3;
    return result;
}
/* Creates a projectile and retires the oldest live entries when the shared list is full. */
char *decoy_create_projectile(char *position, char *direction) {
    char *actor = CreateMoby(MOBY_CLASS_DECOY);
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
        hero = g_hero_moby;
        qcopy(actor + 0xC0, hero + 0xC0);
        qcopy(actor + 0xD0, hero + 0xD0);
        qcopy(actor + 0xE0, hero + 0xE0);
        *(int *)(state + 0x30) = 0;
        *(int *)(state + 0x2C) = 0;
        *(int *)(state + 0x28) = 0;
        *(int *)(state + 0x20) = part_alloc_effect_slot(actor, 0, 1.0f, 1.0f, 1.0f);
        hero_copy_field_to_moby((u8 *)actor);
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
                if (candidate && *(short *)(candidate + 0xAA) == MOBY_CLASS_DECOY && *(unsigned char *)(candidate + 0x20) < 4) {
                    age = *(int *)(*(char **)(candidate + 0x68) + 0x3C);
                    if (oldestAge <= age) { oldest = candidate; oldestAge = age; }
                }
            }
            if (oldest) {
                *(unsigned char *)(oldest + 0x20) = retired;
                RemoveMobyFromIndexList((int)oldest, (unsigned short *)&D_L00_001B1FF0);
                *(int *)(*(char **)(oldest + 0x68) + 0x40) = 1;
            }
        }
        AddMobyToIndexList((int)actor, (short *)&D_L00_001B1FF0, 31);
        func_002A0F48(actor);
    }
    return actor;
}
