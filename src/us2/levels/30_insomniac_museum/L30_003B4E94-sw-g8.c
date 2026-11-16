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
extern void anim_start_blended(void *, int, int, int);
extern void cam_reset_entry(int);
extern int TryClaimNotice(int, int, int);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void museum_info_stand_advance_state(char *);

/* Updates a museum info stand: waits for the player to look at it and press the button, then moves the hero to the exhibit and back. */
void museum_info_stand_update_us2(char *object) {
    char *hero;
    char *state = *(char **)(object + 0x68);
    int id;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (*(int *)(state + 4) != 0) {
            *(unsigned char *)(object + 0x20) = 1;
            if (*(unsigned char *)(object + 0x43) != 0)
                anim_start_blended(object, 0, 0, 5);
        } else {
            *(unsigned char *)(object + 0x20) = 3;
            if (*(unsigned char *)(object + 0x43) != 2)
                anim_start_blended(object, 2, 0, 5);
        }
        break;
    case 1:
        break;
    case 2:
        if (*(unsigned char *)(object + 0x60) & 2) {
            *(unsigned char *)(object + 0x20) = 5;
            if (*(unsigned char *)(object + 0x43) != 2)
                anim_start_blended(object, 2, 0, 5);
            if (*(int *)(state + 0xC) != -1)
                cam_reset_entry(*(int *)(state + 0xC));
        }
        break;
    case 3:
        id = -1;
        if (g_current_map_index != 0x15 && g_current_map_index != 0x1E) {
            switch (*(int *)(state + 8)) {
            case 0:
                id = 0x12EE;
                break;
            case 1:
                id = 0x12EF;
                break;
            }
        } else {
            id = 0x133F;
        }
        hero = g_hero_state;
        if (*(char **)(hero + 0x33C) == object && *(int *)(hero + 0x340) != 0) {
            TryClaimNotice(8, id, 1);
            if (g_pad_state.f1A4 & 0x10) {
                char *entry = g_museum_entries + (*(int *)state << 8);

                museum_info_stand_advance_state(entry);
                hero_reset_position_and_direction(entry + 0x10, entry + 0xF0, 0x6F, 1);
                *(unsigned char *)(hero + 0x22B5) = 1;
            }
        }
        break;
    case 4:
        break;
    case 5: {
        char *h = g_hero_state;

        if (*(int *)(h + 0x2294) == 0x6F) {
            *(unsigned char *)(h + 0x22B5) = 0;
            hero_reset_position_and_direction(h + 0x80, h + 0x90, 0, 0);
        }
        *(unsigned char *)(object + 0x20) = 3;
        break;
    }
    }
}
