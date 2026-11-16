#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad[0x1A0];
    unsigned int f1A0;
    unsigned int f1A4;
} D00138180_Flags;
extern D00138180_Flags g_pad_state;
extern int g_current_map_index;
extern char g_hero_state[];
extern char *g_museum_entries __attribute__((sda));
extern void anim_start_blended_pal(void *, int, int, int);
extern void cam_reset_entry(int);
extern int TryClaimNotice(int, int, int);
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);
extern void museum_info_stand_advance_state(char *);

/* Updates an info stand in the museum: it waits to be used, shows a notice when the hero stands at it, and sends the hero to the stand's exhibit (PAL version). */
void museum_info_stand_update_pal(char *object) {
    char *hero;
    char *state = *(char **)(object + 0x68);
    int notice_id;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (*(int *)(state + 4) != 0) {
            *(unsigned char *)(object + 0x20) = 1;
            if (*(unsigned char *)(object + 0x43) != 0)
                anim_start_blended_pal(object, 0, 0, 5);
        } else {
            *(unsigned char *)(object + 0x20) = 3;
            if (*(unsigned char *)(object + 0x43) != 2)
                anim_start_blended_pal(object, 2, 0, 5);
        }
        break;
    case 1:
        break;
    case 2:
        if (*(unsigned char *)(object + 0x60) & 2) {
            *(unsigned char *)(object + 0x20) = 5;
            if (*(unsigned char *)(object + 0x43) != 2)
                anim_start_blended_pal(object, 2, 0, 5);
            if (*(int *)(state + 0xC) != -1)
                cam_reset_entry(*(int *)(state + 0xC));
        }
        break;
    case 3:
        notice_id = -1;
        if (g_current_map_index != 0x15 && g_current_map_index != 0x1E) {
            switch (*(int *)(state + 8)) {
            case 0:
                notice_id = 0x12EE;
                break;
            case 1:
                notice_id = 0x12EF;
                break;
            }
        } else {
            notice_id = 0x133F;
        }
        hero = g_hero_state;
        if (*(char **)(hero + 0x33C) == object && *(int *)(hero + 0x340) != 0) {
            TryClaimNotice(8, notice_id, 1);
            if (g_pad_state.f1A4 & 0x10) {
                char *entry = g_museum_entries + (*(int *)state << 8);

                museum_info_stand_advance_state(entry);
                hero_reset_position_and_direction_pal(entry + 0x10, entry + 0xF0, 0x6F, 1);
                *(unsigned char *)(hero + 0x22B5) = 1;
            }
        }
        break;
    case 4:
        break;
    case 5: {
        char *hero_now = g_hero_state;

        if (*(int *)(hero_now + 0x2294) == 0x6F) {
            *(unsigned char *)(hero_now + 0x22B5) = 0;
            hero_reset_position_and_direction_pal(hero_now + 0x80, hero_now + 0x90, 0, 0);
        }
        *(unsigned char *)(object + 0x20) = 3;
        break;
    }
    }
}
