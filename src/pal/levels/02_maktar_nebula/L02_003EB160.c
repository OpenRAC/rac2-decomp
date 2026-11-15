#include "include_asm.h"




#include "common.h"
extern void moby_set_state(char *, int, int);
extern void moby_set_state();
extern void FastVecAdd(void *, void *, void *);
extern void math_random_planar_offset(float *, float);
extern void moby_compute_local_point(char *, float *, float, float, float);
extern int PlayMobySound(int, int, void *);
extern void part_spawn_bolt_pickups(char *, int, int, int, int, int, float);
extern int PickAmmoDropItem(char *, int *);
extern char *SpawnWeaponAmmoPickup(float *, int, int, int);
extern void FastVecScale(char *, char *, float);
extern u8 *moby_create_effect_at_position(float *, int);
extern void STUB_printf(const char *, ...);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern void value_set_entry_by_index(int, int);
extern char D_L02_001B09C8[];
extern int g_hovering_object_count __attribute__((sda));
extern int D_L02_001A903C __attribute__((sda));
extern int g_player_bolts __attribute__((sda));
extern void *D_L02_002A52D0[5];
typedef struct {
    char pad0[0xA4];
    int flag;
} State003E77E0;
typedef struct {
    char pad0[0x79];
    u8 once;
} Global001A7A00;
extern Global001A7A00 D_001A7A00 __attribute__((sda));
extern u8 D_L02_00220730;

/* Re-arms the actor (func_002A7750 with 1), builds a random point near it (a, from
   func_L01_0031A278, plus the offset b from func_L02_0031E9E8) and acts on the mode at +0x5C of
   its state (the one func_L02_003E79F8 rolls), through the level's own jump table. Mode 1 starts
   an effect (func_L00_00321878). Mode 2 sets the word at +0xA4, decrements D_L02_001AEC78 and
   changes the actor's state to 5. Mode 3 scales by 0.35 the state of the object func_003202E8
   makes at the point. Mode 4 calls func_L02_003A8770 and prints D_L02_001B09C8. Mode 5 runs a
   one-shot (the flag at D_001A7A00 + 0x79, func_002E5E58, func_002B0A18 and D_L02_001A903C) and
   adds 300 to D_001A79F8. Modes 1, 3, 4 and 5 call func_002E5CF8 with 2 first, any other mode
   with 3. */
void func_PAL_L02_003EBBD0(char *arg0) {
    static void *tab[] = { &&c1, &&c2, &&c3, &&c4, &&c5 };
    char *state = *(char **)(arg0 + 0x68);
    float a[4];
    float b[4];
    int out;
    char *p;
    unsigned int sel;

    moby_set_state(arg0, 1, -1);
    math_random_planar_offset(b, 1.0f);
    moby_compute_local_point(arg0, a, 3.0f, 0.0f, 2.0f);
    FastVecAdd(a, b, a);
    sel = *(int *)(state + 0x5C) - 1;
    if (sel < 5)
        goto *D_L02_002A52D0[sel];
    goto other;
c1:
    PlayMobySound(2, 0x20, arg0);
    part_spawn_bolt_pickups(arg0, 0xF, 0x41, 3, -1, 4, 0.0f);
    goto done;
c2:
    ((State003E77E0 *)state)->flag = 1;
    g_hovering_object_count--;
    moby_set_state(arg0, 5, -1);
    goto done;
c3:
    PlayMobySound(2, 0x20, arg0);
    PickAmmoDropItem(arg0, &out);
    p = *(char **)(SpawnWeaponAmmoPickup(a, out, -1, 0) + 0x68);
    FastVecScale(p, p, 0.35f);
    goto done;
c4:
    PlayMobySound(2, 0x20, arg0);
    moby_create_effect_at_position(a, 0);
    STUB_printf(D_L02_001B09C8);
    goto done;
c5:
    PlayMobySound(2, 0x20, arg0);
    if (D_001A7A00.once == 0) {
        D_001A7A00.once = 1;
        snd_play_from_global_bank(1, 0, 0);
        value_set_entry_by_index(0x1233, -1);
        D_L02_001A903C = 1;
    }
    g_player_bolts += 300;
    goto done;
other:
    PlayMobySound(3, 0x20, arg0);
done:
    return;
}

