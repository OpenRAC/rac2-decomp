#include "common.h"

extern u8 *D_L12_001B2E9C __attribute__((sda));

extern u16 *D_L12_001FB960[];

extern s32 D_L12_001B09F4 __attribute__((sda));

extern s32 func_31DEF0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

extern void func_31E1D0(void *arg0, s32 arg1, s32 arg2);

extern void func_2F1958(f32 *buf, u8 *arg1, u8 *arg2);

extern void func_323F98(f32 *buf, f32 x);

extern void func_2F1928(u8 *arg0, u8 *arg1, f32 *buf);

extern void func_321940(u8 *arg0, s32 arg1, f32 x, f32 y);

extern void func_3239B8(void *arg0, void *arg1, s32 arg2, f32 x, f32 y);

extern s32 D_L12_001B1838 __attribute__((sda));

extern s32 D_L12_001B183C __attribute__((sda));

extern s32 D_L12_001B1840 __attribute__((sda));

extern u16 D_L12_001B1834 __attribute__((sda));

extern f32 D_L12_001B1858 __attribute__((sda));

extern s32 func_2F15C8(void *arg0);

extern s32 func_31E2E0(s32 arg0, s32 arg1);

extern void func_3296A8(void *arg0, void *arg1, s32 arg2, f32 x, s32 arg3);

/* Walks the measured table of the given index down to its terminator. */
s32 space_tourist_all_idle(s32 list_index) {
    u16 *list_cursor = D_L12_001FB960[list_index];
    u16 packed_id;
    u8 *moby_base;

    if (list_cursor == 0)
        return 1;
    moby_base = D_L12_001B2E9C;
    do {
        u8 *moby_record;
        packed_id = *list_cursor;
        moby_record = moby_base + (packed_id & 0x7FFF) * 0x100;
        if (*(s16 *)(moby_record + 0xAA) == MOBY_CLASS_SPACE_TOURIST) {
            if (*(u8 *)(moby_record + 0x20) != 1)
                return 0;
        }
        list_cursor++;
    } while ((s16)packed_id >= 0);
    return 1;
}

/* Arms the measured sub-object on the first entry. */
void sub_object_start_move(u8 *object, u8 *source_obj, u8 *dims, s32 first_entry) {
    f32 move_vec[4];
    u16 old_flags;

    if (*(u8 *)(object + 0x43) != 0xA)
        func_31DEF0(object, 0xA, 0, 5);
    if (*(u8 *)(object + 0xBC) != 8)
        func_31E1D0(object, 8, 1);
    func_2F1958(move_vec, source_obj, object + 0x10);
    func_323F98(move_vec, 0.16666667f);
    func_2F1928(object + 0x10, object + 0x10, move_vec);
    func_321940(object + 0xF8, 0, *(f32 *)(dims + 8), 0.20943954f);
    if (first_entry != 0) {
        old_flags = *(u16 *)(object + 0x34);
        D_L12_001B09F4 = D_L12_001B09F4 + 1;
        *(s32 *)(object + 0x98) = 0;
        *(u16 *)(object + 0x34) = (old_flags | 0x41) & 0xEFFF;
        func_3239B8(object, object + 0x10, -1, 1.0f, 0.0f);
        func_31E1D0(object, 1, 0);
    }
}

/* Steps the measured slot timer and restarts the tracked sub-object. */
void slot_timers_update(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 age;

    if (*(u8 *)(state + 0x2EA) != 0) {
        *(u8 *)(state + 0x2EA) = 0;
        if (*(s16 *)(state + 0x2E0) < D_L12_001B1838)
            *(u16 *)(state + 0x2E0) = func_31E2E0(D_L12_001B183C, D_L12_001B1840);
    }
    if (func_2F15C8(state + 0x2E0) == 0)
        *(u16 *)(state + 0x2E8) = D_L12_001B1834;
    func_2F15C8(state + 0x2E2);
    func_2F15C8(state + 0x2E6);
    func_2F15C8(state + 0x2E8);
    age = *(u16 *)(object + 0x96);
    if (age <= 0xFFFE)
        *(u16 *)(object + 0x96) = age + 1;
    func_3296A8(*(void **)(state + 0x2F8), state + 0x420, 3, D_L12_001B1858, 1);
}

extern u8 *D_L12_001B090C __attribute__((sda));

extern u8 *D_L12_001B1360 __attribute__((sda));

/* Whether the tracked object is in a state that still counts as open. */
s32 tracked_object_is_open(void) {
    u8 *object = D_L12_001B090C;
    s32 result = 1;

    if (object == 0) {
        result = 0;
    } else {
        if (*(u8 *)(object + 0x20) == 6 || *(s8 *)(object + 0x20) < 0
            || *(u8 *)(object + 0x20) == 8)
            result = 0;
    }
    return result;
}

/* The same test, with one more state in the closed set. */
s32 second_tracked_object_is_open(void) {
    u8 *object = D_L12_001B1360;
    s32 result = 1;

    if (object == 0) {
        result = 0;
    } else {
        if (*(u8 *)(object + 0x20) == 6) {
            result = 0;
        } else if (*(u8 *)(object + 0x20) == 5 || *(u8 *)(object + 0x20) == 8
                 || *(s8 *)(object + 0x20) < 0) {
            result = 0;
        }
    }
    return result;
}


extern int FloatToInt(float);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended(void *,int,int,int);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object(void *,void *,int);
extern void squirrel_alert_group(void *);
extern int weapon_select_aim_target(void *,int,int,int,float,float);
extern int point_in_path_xy(void *,void *,int,float);
extern void value_set_and_smooth(void *,void *,int,int,float);
extern u8 D_L12_001B9E00[];
extern u8 *g_hero_moby NOT_SDA;
extern u8 *D_L12_001FEAC0[];
extern float D_L12_001B0A40 __attribute__((sda));

/* Sets up the object's AI parameters on its first update, then refreshes its target state and
   clears it when the target leaves the object's zone. */
void guard_creature_update(u8 *creature) {
    u8 *vars=*(u8 **)(creature+0x68);
    if(!creature[0x20]) {
        *(short *)(*(u8 **)(creature+0x24)+0x46)=5;
        *(u16 *)(creature+0x34)|=0x1000;
        vars[0x48]=FloatToInt(15.0f);vars[0x4A]=FloatToInt(6.0f);
        vars[0x29]=1;
        vars[0x70]=8; *(int *)(vars+0xA8)=3; vars[0x71]=11; vars[0x72]=11;
        vars[0x76]=13; vars[0x77]=14;
        *(float *)(vars+0x7C)=1.0f/6.0f; *(float *)(vars+0x80)=1.0f/12.0f;
        *(float *)(vars+0x84)=0.0055555557f;
        *(float *)(vars+0x88)=1.0f/120.0f; *(float *)(vars+0x8C)=1.0f/240.0f;
        *(float *)(vars+0x90)=0.5f; *(float *)(vars+0x94)=0.5f; *(float *)(vars+0x9C)=0.4f;
        vars[0xCC]=7; vars[0xCD]=10; vars[0xCE]=7; vars[0xCF]=10; vars[0xD2]=8; vars[0xD3]=12;
        if(*(float *)(vars+0x36C)==0) *(float *)(vars+0x36C)=16;
        if(*(float *)(vars+0x370)==0) *(float *)(vars+0x370)=24;
        if(*(int *)(vars+0x140)) *(float *)(vars+0x20)=1;
        vars[0x28]=3;
        qcopy_nc(vars+0x340,creature+0x10);
        *(u8 **)(vars+0x198)=vars+0x240;*(u8 **)(vars+0x19C)=vars+0x2C0;
        *(float *)(vars+0x184)=1;*(float *)(vars+0x154)=0.25f;*(float *)(vars+0x150)=0.5f;
        *(float *)(vars+0x158)=0.4f;*(float *)(vars+0x15C)=0.4f;
        *(float *)(vars+0x160)=0.78539824f;*(float *)(vars+0x180)=0.52359885f;
        *(float *)(vars+0x17C)=0.0055555557f;
        if(*(int *)(vars+0x378)!=-1) moby_set_state(creature,14,5);
        else if(*(int *)(vars+0x13C)==-1) {
            moby_set_state(creature,1,0);
            if(creature[0x43]) anim_start_blended(creature,0,0,0);
        } else {
            moby_set_state(creature,9,4);
            if(creature[0x43]!=14) anim_start_blended(creature,14,0,0);
            *(float *)(creature+0x18)+=4;*(int *)(creature+0x98)=0;
            *(u16 *)(creature+0x34)=(*(u16 *)(creature+0x34)|0x41)&0xEFFF;
        }
    }
    if(creature[0x31] && fast_vec_dist(creature+0x10,D_L12_001B9E00)<24) {moby_update_ground_check(creature);creature[0x6F]=22;}
    if(moby_apply_damage_to_object(creature,vars+0x60,0)) squirrel_alert_group(creature);
    *(short *)(vars+0x364)=weapon_select_aim_target(creature,-1,0,0,*(float *)(vars+0x36C),3);
    if(*(u8 **)(vars+0x120)) *(u8 **)(vars+0x368)=*(u8 **)(vars+0x120); else *(u8 **)(vars+0x368)=g_hero_moby;
    if(*(short *)(vars+0x364)==1) {
        float zone_range=D_L12_001B0A40;
        if(*(int *)(vars+0x130)!=-1) {
            u8 *zone_info=D_L12_001FEAC0[*(int *)(vars+0x130)];
            if(!point_in_path_xy(*(u8 **)(vars+0x120)+0x10,zone_info+0x10,*(int *)zone_info,zone_range)) *(short *)(vars+0x364)=0;
        }
    }
    value_set_and_smooth(creature,vars+0x3C0,1,1,D_L12_001B0A40);
}

/* The subtitle history (src/game/00289178.c): per record, its play count, the time it was last
   played and the levels it was played in (bit 31: played at all). */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;
extern void subtitle_request_voice_line(int,int);

/* Plays subtitle lines, each gated on its record in the subtitle history (the record index is
   the second argument of func_00288E18). */

extern u8 g_hero_position[];
extern SubtitleHistory g_subtitle_history[];
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u32 D_001A7390;
extern int g_current_map_index[] __attribute__((sda));
extern int D_0018C0B4 NOT_SDA;
extern int IsPointInCuboid(void *,int);
extern void math_fast_float_d(void *);

/* Plays subtitle lines, each gated on its record in the subtitle history (the record index is
   the second argument of func_00288E18). */
void UpdateTodanoSubtitleTriggers(u8 *creature) {
    u8 *vars = *(u8 **)(creature + 0x68);

    switch (creature[0x20]) {
    case 0:
        creature[0x30] = 255;
        *(int *)(vars + 0x10) = -1;
        moby_set_state(creature, 1, -1);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, *(int *)vars) && *(int *)(g_hero_position + 0x540)
            && !g_subtitle_history[121].count)
            subtitle_request_voice_line(0xA22, 121);
        if (IsPointInCuboid(g_hero_position, *(int *)(vars + 4)) && !g_item_owned_flags[0x33]) {
            if (g_subtitle_history[92].count) {
                u32 now_time = D_001A7390;
                u32 last_time = g_subtitle_history[92].time;

                if (now_time - last_time > 0x438 || last_time == 0)
                    subtitle_request_voice_line(0xA05, 92);
                else if (last_time < now_time)
                    g_subtitle_history[92].time = now_time;
            } else {
                if (g_subtitle_history[92].count < 65535)
                    g_subtitle_history[92].count++;
                if (g_subtitle_history[92].time < D_001A7390)
                    g_subtitle_history[92].time = D_001A7390;
                g_subtitle_history[92].levels = (g_subtitle_history[92].levels | (1u << g_current_map_index[0])) | 0x80000000u;
            }
        }
        if (IsPointInCuboid(g_hero_position, *(int *)(vars + 8))) {
            u8 *watched = D_L12_001B2E9C + (*(int *)(vars + 0xC) << 8);

            if (watched && *(s16 *)(watched + 0xAA) == 0xFB8 /* moby class 4024 */ && watched[0x20] != 254 && watched[0x20] != 253) {
                if (*(int *)(vars + 0x10) < 0)
                    *(int *)(vars + 0x10) = 0x2A30;
                else if (!*(int *)(vars + 0x10)) {
                    u32 seen_before = g_subtitle_history[93].levels & (1 << g_current_map_index[0]);

                    if (!seen_before)
                        subtitle_request_voice_line(0xA06, 93);
                }
            }
        }
        if (g_item_owned_flags[7] && D_0018C0B4 != 0x6F) {
            u32 seen_before = g_subtitle_history[127].levels & (1 << g_current_map_index[0]);

            if (!seen_before)
                subtitle_request_voice_line(0xA28, 127);
        }
        if (*(int *)(vars + 0x10) >= 0)
            math_fast_float_d(vars + 0x10);
        break;
    }
}
