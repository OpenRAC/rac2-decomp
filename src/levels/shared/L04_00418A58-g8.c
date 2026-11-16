#include "common.h"

#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)

extern char g_hero_state[];
extern int ref_L04_00418A58_01;
extern int g_pad_pressed_flags[];
extern int ref_L04_00418A58_04[];
extern int ref_L04_00418A58_00 __attribute__((sda));
extern u8 *ref_L04_00418A58_11 __attribute__((sda));

extern int ref_L04_00418A58_02(char *, int);
extern int ref_L04_00418A58_03(int, int, char *);
extern void ref_L04_00418A58_05(char *, char *);
extern void ref_L04_00418A58_06(char *, char *);
extern void ref_L04_00418A58_07(char *);
extern void ref_L04_00418A58_08(void);
extern void ref_L04_00418A58_09(char *, char *);
extern void ref_L04_00418A58_10(char *);
extern float ref_L04_00418A58_12(char *, char *, char *, char *, int, int);

/* Retargets the hero's entry state (clears its cached pointer record, scales both position records by a quarter), then refreshes each of the 21 linked object slots. */
void hoverbike_update_rider_entry_state(char *obj, char *aux) {
    char *rec;
    char *e;
    int *slot;
    int i;
    int none;

    if (ref_L04_00418A58_00 != 0 && ref_L04_00418A58_01 < 12 && (g_pad_pressed_flags[0] & 0x40)) {
        FLD(aux, int, 0x278) = 240;
        FLD(aux, int, 0x650) = 240;
        if (ref_L04_00418A58_02(obj, FLD(aux, int, 0x714)) == 0) {
            FLD(aux, int, 0x714) = ref_L04_00418A58_03(15, 4, obj);
        }
        ref_L04_00418A58_00 = 0;
    }
    FLD(g_hero_state, int, 0x24A0) = 26;
    ref_L04_00418A58_04[0] = 0;
    FLD(g_hero_state, u8, 0x22B7) = 1;
    FLD(g_hero_state, u8, 0x22B5) = 1;
    FLD(FLD(g_hero_state, char *, 0x2290), int, 0x98) = 0;
    FLD(g_hero_state, u8, 0x22C2) = 1;
    FLD(obj, float, 0x2C) = FLD(FLD(obj, char *, 0x24), float, 0x24) * 0.25f;
    rec = FLD(g_hero_state, char *, 0x2290);
    FLD(rec, float, 0x2C) = FLD(FLD(rec, char *, 0x24), float, 0x24) * 0.25f;
    ref_L04_00418A58_05(obj, aux);
    ref_L04_00418A58_06(obj, aux);
    ref_L04_00418A58_07(obj);
    ref_L04_00418A58_08();
    ref_L04_00418A58_09(obj, aux);
    if (FLD(obj, u8, 0x20) == 3) {
        none = -1;
        ref_L04_00418A58_10(obj);
        for (slot = (int *)(aux + 0x1E4), i = 20; i >= 0; i--) {
            if (*slot != none) {
                char *entry = (char *)ref_L04_00418A58_11 + (*slot << 8);
                e = FLD(entry, char *, 0x68);
                FLD(e, float, 0x11C) = ref_L04_00418A58_12(entry, aux, e + 0x120, e + 0x124, FLD(e, int, 0x160), FLD(e, int, 0x244));
            }
            slot++;
        }
    }
}
