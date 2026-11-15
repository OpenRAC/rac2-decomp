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
extern Obj_2D23C0 *D_0018C0B0;
extern void func_0029F390(void *);
extern int func_L00_002A4DB0(void *a0, int a1, int a2, char *a3);
extern char D_001B4400[];

/* Starts the object's animation at the given sequence and frame, ending one frame later or at the last frame. */
void func_L00_002D23C0(int seq, int frame)
{
    Obj_2D23C0 *obj = gHeroMoby_0018C0B0;
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
    obj->w58 = CopyAnimationEntryData(obj, obj->b42, obj->b40, D_001B4400);
    obj->w5C = CopyAnimationEntryData(obj, obj->b43, obj->b41, D_001B4400 + 0x600);
}
