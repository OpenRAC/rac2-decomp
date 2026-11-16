#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef struct Anim28DF80_Frame {
    u16 unk_0;
    u16 frame_count;
    u16 first_frame;
    u8 pad6;
    u8 frame_time;
} Anim28DF80_Frame;
typedef struct Anim28DF80_State {
    short record_index;
    u8 mode;
    s32 current_frame;
    char pad8[4];
    s32 start_time;
} Anim28DF80_State;
extern Anim28DF80_Frame *g_hud_element_table __attribute__((sda));
extern s32 g_game_time __attribute__((sda));
extern s32 math_random_int_below(s32);

/* Picks the frame of an animation record: clamp, loop, ping-pong or one-shot. */
s32 hud_pick_anim_frame_pal(Anim28DF80_State *anim) {
    s32 frame = 0;
    Anim28DF80_Frame *record = g_hud_element_table + anim->record_index;

    if (record->unk_0 != 0xFFFF) {
        switch (anim->mode) {
        case 0:
            frame = record->first_frame;
            break;
        case 1:
            frame = record->first_frame + (g_game_time - anim->start_time) / record->frame_time % record->frame_count;
            break;
        case 2:
            frame = (g_game_time - anim->start_time) / record->frame_time % (record->frame_count * 2 - 2);
            if (frame >= record->frame_count) {
                s32 offset = frame + 2;
                frame = record->frame_count * 2 - offset;
            }
            frame += record->first_frame;
            break;
        case 3:
            if (anim->start_time < g_game_time) {
                frame = (g_game_time - anim->start_time) / record->frame_time;
                if (frame < record->frame_count * 2 - 2) {
                    if (frame >= record->frame_count) {
                        s32 offset = frame + 2;
                        frame = record->frame_count * 2 - offset;
                    }
                    frame += record->first_frame;
                } else {
                    frame = record->first_frame;
                    {
                        s32 offset = math_random_int_below(25) + 8;
                        anim->start_time = record->frame_count * 2 + offset;
                    }
                }
            } else {
                frame = anim->current_frame;
            }
            break;
        }
    }
    anim->current_frame = frame;
    return frame;
}


extern char g_hud_elements[];
extern int g_hud_record_timer_flag __attribute__((sda));
extern void hud_finish_element_setup(char *);
extern void weapon_menu_update_entry(void);

/* Walks the records, caps their timers, moves their positions on, and lets a
   record run its own handler. */
int hud_update_record_timers_pal(int run_handlers)
{
    char *record;
    char *record_end;
    int count = 0;

    weapon_menu_update_entry();
    record = (char *)g_hud_elements;
    record_end = (char *)g_hud_elements + 0x750;
    do {
        int timer;

        if ((*(int *)(record + 4) & 0x10) || g_hud_record_timer_flag) {
            timer = *(int *)(record + 0x7C);
            if (timer < 8) {
                *(int *)(record + 0x7C) = 8;
            }
            timer = *(int *)(record + 0x7C);
        } else {
            timer = *(int *)(record + 0x7C);
        }

        if (timer > 0) {
            timer = timer - 1;
            *(int *)(record + 0x7C) = timer;
            if (timer > 0) {
                count++;
                if (*(int *)(record + 0x6C) < 30) {
                    *(int *)(record + 0x6C) = *(int *)(record + 0x6C) + 1;
                }
            } else if (*(int *)(record + 0x6C) >= -5) {
                *(int *)(record + 0x6C) = *(int *)(record + 0x6C) - 1;
            }
        } else if (*(int *)(record + 0x6C) >= -5) {
            *(int *)(record + 0x6C) = *(int *)(record + 0x6C) - 1;
        }

        if (*(int *)(record + 0x68) != 0) {
            if (*(int *)(record + 0x6C) == -6) {
                hud_finish_element_setup(record);
            }
        }

        if (run_handlers != 0) {
            void (*handler)(char *) = *(void (**)(char *))(record + 0x14);
            if (handler) {
                handler(record);
            }
        }
        record += 0x90;
    } while ((int)record < (int)record_end);
    return count;
}

