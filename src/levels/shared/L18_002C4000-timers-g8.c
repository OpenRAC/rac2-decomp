#include "common.h"
typedef struct {
    unsigned char pad_0[0x88];
    float field_88;
    unsigned char pad_8C[0xE4];
    float field_170;
    unsigned char pad_174[0x10];
    float field_184;
    unsigned char pad_188[0x30];
    int state_frames;
    int control_mode_frames;
    int step_frames;
    int animation_frames;
    int stick_held_frames;
    int stick_idle_frames;
    unsigned char pad_1D0[0x8];
    int item_animation_frames;
    unsigned char pad_1DC[0x4];
    short field_1E0;
    unsigned char pad_1E2[0x6];
    int field_1E8;
    unsigned char pad_1EC[0x16];
    short still_frames;
    unsigned char pad_204[0x8];
    short field_20C;
    unsigned char pad_20E[0xE];
    short field_21C;
    unsigned char pad_21E[0x6];
    short field_224;
    unsigned char pad_226[0x2];
    short field_228;
    short field_22A;
    unsigned char pad_22C[0xF0];
    float field_31C;
    unsigned char pad_320[0x1C];
    unsigned char * field_33C;
    int field_340;
    unsigned char pad_344[0xA];
    short field_34E;
    unsigned char pad_350[0x270];
    unsigned char * field_5C0;
    unsigned char pad_5C4[0xC84];
    int field_1248;
    unsigned char pad_124C[0x208];
    short field_1454;
    unsigned char pad_1456[0xE3A];
    int field_2290;
    int field_2294;
    unsigned char pad_2298[0x4];
    int field_229C;
    unsigned char pad_22A0[0x14];
    unsigned char mode;
    unsigned char pad_22B5[0x3];
    unsigned char item_animation_active;
    unsigned char pad_22B9[0x4];
    unsigned char tilt_disabled;
    unsigned char pad_22BE[0x5];
    unsigned char field_22C3;
    unsigned char pad_22C4[0x100];
    int pos_history_index;
    int pos_history_count;
    unsigned char pad_23CC[0xD8];
    float reach_distance;
    float reach_height;
    unsigned char pad_24AC[0x20];
    int field_24CC;
    unsigned char pad_24D0[0xC];
    float current_path_dist;
} HeroTimerState;

extern HeroTimerState D_00189E20;
extern int D_L18_001B2348;

#define BS(p, o) (*(short *)((p)+(o)))
#define BU(p, o) (*(unsigned short *)((p)+(o)))
#define BP(p, o) (*(unsigned char **)((p)+(o)))

typedef struct {
    unsigned char pad[0x1A0];
    int held;
    int pressed;
    unsigned char pad1[0x2C];
    int no_direction;
} TimerPadState;

extern TimerPadState D_00138180;
extern unsigned char *D_L18_001FB6E0[];
extern unsigned char D_L18_002653E0[];
extern int D_L18_001A8F00_abs __asm__("D_L18_001A8F00");
extern float D_L18_001B2260, D_L18_001B2264;
/* The equipment flag at 0x1A7AFF: a small-data object at a nonzero offset, length 2 for reorg. */
extern unsigned char D_001A7A70[] __attribute__((sda));
extern void func_L00_002B9380(void), func_L00_002A7A10(void), func_L00_002C3838(void), func_L00_002B30E8(void);
extern void func_L18_002E0070(int, int);
extern int func_00282978(void *), func_00282948(void *);
extern void func_00282C88(void *);
extern int func_002ABB78(void *), func_002A77E0(int);
extern void func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float);
extern int func_002A8F70(void *, int, int, void *, void *, float);
extern void func_00282CC0(void *, void *, void *), func_00282D30(void *, void *, float);
extern float func_L00_002D3B00(void *), func_00282DF0(void *);
extern float func_00282E48(void *, void *);
extern void func_L00_002D36E0(void *, int, float, float, float), func_L00_002D3778(void *, void *, float);

/* Corresponds to RAC1 update_hero_timers_and_reach_state in
 * src/overlays/shared/hero_vehicle_and_collision.c. */
void func_L18_002DEFF8(void) {
    unsigned char *m, *pos, *hero;
    float sum[4], delta[4];
    int i, count, history_index, first_index, second_index;
    if (!D_00189E20.tilt_disabled) func_L00_002B9380();
    {
        int state = D_00189E20.state_frames+1;
        int control = D_00189E20.control_mode_frames+1;
        int step = D_00189E20.step_frames+1;
        int animation = D_00189E20.animation_frames+1;
        D_00189E20.state_frames = state;
        D_00189E20.control_mode_frames = control;
        D_00189E20.step_frames = step;
        D_00189E20.animation_frames = animation;
    }
    func_00282978(((unsigned char *)&D_00189E20)+0x1E0);
    func_00282978(((unsigned char *)&D_00189E20)+0x1DC);
    func_00282978(((unsigned char *)&D_00189E20)+0x1D2);
    func_00282978(((unsigned char *)&D_00189E20)+0x1E4);
    func_00282978(((unsigned char *)&D_00189E20)+0x1F8);
    func_00282978(((unsigned char *)&D_00189E20)+0x1FE);
    func_00282948(((unsigned char *)&D_00189E20)+0x1D4);
    func_00282978(((unsigned char *)&D_00189E20)+0x210);
    func_00282978(((unsigned char *)&D_00189E20)+0x1D0);
    func_00282978(((unsigned char *)&D_00189E20)+0x1F4);
    func_00282978(((unsigned char *)&D_00189E20)+0x1F6);
    func_00282978(((unsigned char *)&D_00189E20)+0x204);
    func_00282978(((unsigned char *)&D_00189E20)+0x206);
    func_00282978(((unsigned char *)&D_00189E20)+0x1F0);
    func_00282978(((unsigned char *)&D_00189E20)+0x1EC);
    func_00282978(((unsigned char *)&D_00189E20)+0x1EE);
    func_00282978(((unsigned char *)&D_00189E20)+0x208);
    func_00282978(((unsigned char *)&D_00189E20)+0x200);
    func_00282978(((unsigned char *)&D_00189E20)+0x20E);
    func_00282978(((unsigned char *)&D_00189E20)+0x20A);
    func_00282978(((unsigned char *)&D_00189E20)+0x214);
    func_00282978(((unsigned char *)&D_00189E20)+0x212);
    func_00282978(((unsigned char *)&D_00189E20)+0x1FC);
    func_00282978(((unsigned char *)&D_00189E20)+0x216);
    func_00282978(((unsigned char *)&D_00189E20)+0x1FA);
    func_00282978(((unsigned char *)&D_00189E20)+0x218);
    func_00282978(((unsigned char *)&D_00189E20)+0x1F2);
    func_00282978(((unsigned char *)&D_00189E20)+0x21A);
    func_00282978(((unsigned char *)&D_00189E20)+0x21C);
    func_00282978(((unsigned char *)&D_00189E20)+0x1DE);
    func_00282978(((unsigned char *)&D_00189E20)+0x1E6);
    func_00282978(((unsigned char *)&D_00189E20)+0x222);
    func_00282978(((unsigned char *)&D_00189E20)+0x224);
    func_00282978(((unsigned char *)&D_00189E20)+0x226);

    if (!(D_00138180.held&4)) D_00189E20.field_20C = 0;
    if (D_00189E20.field_21C) func_L00_002A7A10();
    if (D_00189E20.item_animation_active) D_00189E20.item_animation_frames++;
    else D_00189E20.item_animation_frames = 0;
    if (D_00138180.no_direction) {
        D_00189E20.stick_held_frames = 0;
        D_00189E20.stick_idle_frames++;
    }
    else {
        D_00189E20.stick_idle_frames = 0;
        D_00189E20.stick_held_frames++;
    }
    if (D_00189E20.field_22C3 && !D_00189E20.field_229C && D_00189E20.field_340 && D_00189E20.field_170<0.0016666668f && D_00189E20.field_184<0.0016666668f) qcopy(((unsigned char *)&D_00189E20)+0x80, ((unsigned char *)&D_00189E20)+0x2030);
    if (D_00189E20.field_1454) D_00189E20.field_1E8 = 0;
    else D_00189E20.field_1E8++;
    if (D_00189E20.field_24CC && !D_L18_001A8F00_abs && D_00189E20.mode == 4 && D_00189E20.field_2294 != 0x6F && (D_00138180.pressed&0x10)) {
        D_00189E20.field_1E0 = 0;
        D_00189E20.field_24CC = 0;
        func_L18_002E0070(0x91, 1);
    }
    if (!D_L18_001A8F00_abs) {
        if (D_L18_001B2260>0) D_00189E20.field_22A++;
        else D_00189E20.field_22A = 0;
        if (D_00189E20.field_22A>120) {
            D_L18_001B2260 = 0;
            D_00189E20.field_22A = 0;
        }
        if (D_L18_001B2264>0) D_00189E20.field_228++;
        else D_00189E20.field_228 = 0;
        if (D_00189E20.field_228>120) {
            D_00189E20.field_228 = 0;
            D_L18_001B2264 = 0;
        }
    }
    if (D_00189E20.field_224) {
        for (i = 0;(m = D_L18_001FB6E0[i]) != 0;i++) {
            if (func_002ABB78(m) || (m && BP(m, 0x24) && BS(BP(m, 0x24), 0x46) == 22)) {
                if ((D_L18_001B2348&7) == (((int)m>>8)&7) || !func_002A77E0(4)) {
                    hero = (unsigned char *)&D_00189E20+0x80;
                    pos = m+0x10;
                    if (func_00282E48(hero, pos)<15.37f) {
                        func_00282CF0(sum, pos, hero);
                        func_00282F20(sum, sum, 1.7f);
                        func_002A8F70(m, D_00189E20.field_2290, 0x4000000, hero, sum, 1.0f);
                    }
                }
            }
        }
    }
    for (i = 0;i<4;i++) func_00282948(D_L18_002653E0+i*0x70);
    D_00189E20.current_path_dist = 9999.0f;
    if (D_00189E20.field_34E && func_L00_002D3B00(((unsigned char *)&D_00189E20)+0xF0)<0) {
        if (D_00189E20.pos_history_count != 32) goto history_done;
        func_00282C88(sum);
        count = 8;
        for (i = 0;i<count;) {
            history_index = D_00189E20.pos_history_index-i;
            first_index = (history_index+31)%32;
            second_index = (history_index+30)%32;
            func_00282CF0(delta, ((unsigned char *)&D_00189E20)+0x1D90+first_index*16, ((unsigned char *)&D_00189E20)+0x1D90+second_index*16);
            i++;
            func_00282CC0(sum, sum, delta);
        }
        func_00282D30(sum, sum, 1.0f/(float)count);
        if (func_00282DF0(sum)<0.016666668f) {
            D_00189E20.still_frames++;
            goto history_done;
        }
    }
    D_00189E20.still_frames = 0;
history_done:
    func_L00_002C3838();
    if (D_00189E20.mode == 4) func_L00_002D36E0((unsigned char *)&D_00189E20+0xE0, 1, 0, 0, 0.4f);
    else func_L00_002D36E0((unsigned char *)&D_00189E20+0xE0, 1, 0, 0, 0.7f);
    if (!(D_L18_001B2348&3)) {
        if (D_00189E20.mode == 4) {
            D_00189E20.reach_distance = 2.125f;
            D_00189E20.reach_height = 1.25f;
        }
        else if (D_001A7A70[0x8F]) {
            D_00189E20.reach_distance = 14;
            D_00189E20.reach_height = 4.5f;
        }
        else {
            D_00189E20.reach_distance = 4.25f;
            D_00189E20.reach_height = 2.25f;
        }
    }
    if (D_00189E20.field_31C<4) {
        qcopy(((unsigned char *)&D_00189E20)+0xD0, ((unsigned char *)&D_00189E20)+0x2D0);
        func_L00_002D3778(((unsigned char *)&D_00189E20)+0xD0, ((unsigned char *)&D_00189E20)+0xD0, 0.5f);
    }
    else qcopy(((unsigned char *)&D_00189E20)+0xD0, ((unsigned char *)&D_00189E20)+0xE0);
    {
        unsigned char *heldMoby = D_00189E20.field_5C0;
        if (heldMoby) {
            if (!(BU(heldMoby, 0x34)&0x1000) || heldMoby == D_00189E20.field_33C) D_00189E20.field_5C0 = 0;
            if (D_00189E20.field_5C0 && D_00189E20.field_1248 != 46) D_00189E20.field_5C0 = 0;
        }
    }
    if (D_00189E20.field_88<1) func_L00_002B30E8();
}
