#include "include_asm.h"


#include "common.h"
typedef struct {
    s32 a;
    s32 b;
    s32 c;
} L20_0039DCF8_Args;
extern void moby_set_state(char *, int, int);
extern void anim_start_immediate(char *, int, int);
extern int math_random_int_range(int, int);
extern void func_002A0F48(void *);
extern int trooper_spawn_parts_pal(char *, int);
extern void trooper_destroy_parts(char *);
extern int moby_fuse_linked_objects(void *, void *, void *, L20_0039DCF8_Args, int);

/* Sets up a spawned object at pos/rot; if it finds its slot it passes the three link words on. */
int trooper_init_spawned_pal(char *obj, char *pos, char *rot)
{
    char *vars = *(char **)(obj + 0x68);
    u8 *bytes = (u8 *)(vars + 0x270);
    s32 i;
    L20_0039DCF8_Args arg;
    L20_0039DCF8_Args st;
    int ret;

    *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) & 0xFFBE) | 0x1000;
    *(s32 *)(obj + 0x98) = *(s32 *)(*(char **)(obj + 0x24) + 0x10);
    moby_set_state(obj, 2, 0);
    anim_start_immediate(obj, 2, 0);
    *(u8 *)(obj + 0x7F) = 0;
    *(f32 *)(obj + 0x48) = 1.0f;
    for (i = 0; i < 12; i++)
        bytes[i] = math_random_int_range(0x40, 0xFE);
    *(s32 *)(vars + 0x27C) = 0;
    qcopy(obj + 0x10, pos);
    qcopy(obj + 0xF0, rot);
    *(u16 *)(obj + 0x7C) = 0xF;
    func_002A0F48(obj);
    if (trooper_spawn_parts_pal(obj, 1) == 0) {
        trooper_destroy_parts(obj);
        ret = 0;
    } else {
        *(f32 *)(vars + 0x20) = *(s16 *)(vars + 0x24);
        *(u16 *)(vars + 0x178) = 0;
        anim_start_immediate(*(char **)(vars + 0x254), 2, 0);
        st.a = *(s32 *)(vars + 0x254);
        st.b = *(s32 *)(vars + 0x258);
        st.c = *(s32 *)(vars + 0x25C);
        arg = st;
        moby_fuse_linked_objects(obj, pos, rot, arg, 3);
        ret = 1;
    }
    return ret;
}

