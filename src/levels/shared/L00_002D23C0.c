#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef struct { u8 pad[0x10]; u8 count; } Sub_2D23C0;
typedef struct { u8 pad[0x48]; Sub_2D23C0 *items[1]; } Tab_2D23C0;
typedef struct {
    u8 pad0[0x24];
    Tab_2D23C0 *tab;
    u8 pad1[0x40 - 0x28];
    u8 b40, b41, b42, b43;
    int w44;
    u8 pad2[0x58 - 0x48];
    int w58;
    int w5C;
} Obj_2D23C0;
extern Obj_2D23C0 *g_hero_moby;
extern void update_moby_animation_state(void *);
extern int anim_copy_entry_data(void *a0, int a1, int a2, char *a3);
extern char g_anim_entry_buffer[];

/* Starts the object's animation at the given sequence and frame, ending one frame later or at the last frame. */
void anim_start_object_at_frame(int seq, int frame)
{
    Obj_2D23C0 *obj = g_hero_moby;
    int lastFrame;
    obj->b41 = frame + 1;
    obj->b40 = frame;
    lastFrame = obj->tab->items[seq]->count - 1;
    if (lastFrame < obj->b41)
        obj->b41 = lastFrame;
    obj->w44 = 0;
    obj->b42 = seq;
    obj->b43 = seq;
    update_moby_animation_state(obj);
    obj->w58 = anim_copy_entry_data(obj, obj->b42, obj->b40, g_anim_entry_buffer);
    obj->w5C = anim_copy_entry_data(obj, obj->b43, obj->b41, g_anim_entry_buffer + 0x600);
}
