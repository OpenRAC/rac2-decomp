#include "include_asm.h"
#include "names.h"

typedef short s16;
extern s16 moby_get_vars_counter(char *);
extern char *D_L02_001B35A8 __attribute__((sda));
extern void explosion_effect_update(char *);
extern void moby_explode_and_hurt_nearby(char *);
extern void moby_copy_sub_byte_40_to_25(char *);
extern void moby_copy_vars_byte_40_to_25(char *);
extern void moby_raise_state_to_eight(char *);
extern void moby_raise_state_to_eight_copy(char *);
extern void moby_release_slots_retire(char *);
extern void moby_call_helper_10000(char *);
extern void moby_mark_spawned(char *);

/* Walks the list of objects at D_L02_001B35A8 (linked through +0x28) and hands each one to the
   handler of its kind, the half-word at +0xAA. */
void func_PAL_L02_00405450(void) {
    char *e;

    for (e = D_L02_001B35A8; e != 0; e = *(char **)(e + 0x28)) {
        switch (*(s16 *)(e + 0xAA)) {
        case 0xE7D:
            explosion_effect_update(e);
            break;
        case 0xEB0:
            moby_explode_and_hurt_nearby(e);
            break;
        case 0xCB2:
            moby_copy_sub_byte_40_to_25(e);
            break;
        case 0xB02:
            moby_copy_vars_byte_40_to_25(e);
            break;
        case 0x1366:
            moby_raise_state_to_eight(e);
            break;
        case 0x1367:
            moby_raise_state_to_eight_copy(e);
            break;
        case 0x326:
            moby_release_slots_retire(e);
            break;
        case 0xA5C:
        case 0x1192:
            moby_call_helper_10000(e);
            break;
        case 0xAE0:
        case 0xAE1:
        case 0xAE2:
        case 0xAEC:
        case 0xB06:
        case 0xB09:
        case 0xCC0:
        case 0xCC1:
        case 0xCC2:
        case 0xCC3:
        case 0xCC4:
        case 0xCC5:
        case 0xCC6:
        case 0xCC7:
        case 0xCC8:
        case 0xCC9:
        case 0xCDB:
            moby_mark_spawned(e);
            break;
        }
    }
}

