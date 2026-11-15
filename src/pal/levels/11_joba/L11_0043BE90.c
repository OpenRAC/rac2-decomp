#include "include_asm.h"
#include "names.h"


extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern void func_002A05A8(char *);
extern void arena_add_waiting_fighter(unsigned char *object, int class_id);
extern char *SpawnExplosion(char *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void anim_start_blended(void *, int, int, int);
extern void func_002A05A8(char *);
extern void moby_set_state(void *, int, int);

/* Retires the measured stage-46 record: clears the guard, drops the effect and re-tags the object. */
void func_PAL_L11_0043BFF8(char *obj)
{
    char *state = *(char **)(obj + 0x68);

    if (*(short *)(state + 0x282) == 1) {
        arena_add_waiting_fighter(*(unsigned char **)(obj + 0xB8), 0xD37);
        *(int *)(state + 0x270) = 0;
    } else {
        *(int *)(state + 0x270) = 0;
    }
    *(short *)(state + 0x282) = 0;
    if (*(unsigned char *)(obj + 0x31)) {
        SpawnExplosion(obj + 0x10, 0, 0, 0x1E, 5, 0, 0x32, 1, 0.3f, 0.0f, 0, 0, 0, 0);
        snd_play_from_class_bank(0, 0, obj, 0xDF7);
    }
    anim_start_blended(obj, 0, 0, 3);
    func_002A05A8(obj);
    moby_set_state(obj, 1, 0);
    *(unsigned char *)(obj + 0x31) = 0;
    *(int *)(obj + 0x98) = 0;
    *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) & 0xEFFF) | 0x47;
}

