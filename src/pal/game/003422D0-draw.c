#include "include_asm.h"
#include "names.h"

extern int D_00138344[];
extern char *D_001A8CFC[] __attribute__((sda));
extern int func_PAL_002A9FA0(int, int, int, int, int);
extern int *object_get_fourth_field(void *);
extern float *object_get_second_field(void *);
extern void gfx_draw_screen_element_stored(void *);
extern void func_PAL_00338770(void *);
extern void object_set_flag_value(void *, int);
extern void radial_menu_draw_info_second(void *);
extern void func_PAL_00342518(void *);
extern void radial_menu_layout_items(void *, int, int, int);
typedef struct {
    char reserved00[8];
    short adjustment;
    short reserved0A;
    void (*draw)(void *);
} DrawMethod;

void func_PAL_003422D0(char *self)
{
    char *a, *b, *c, *d, *e, *f, *slot, *slot2;
    int i, j;
    float *v;
    int *color;
    if (*(int *)(self+0xAB8)) {
        if (D_00138344[0]&0xF000) func_PAL_002A9FA0(0,0,1,1,1);
        a=self+0x214; b=self+0x2A8; c=self+0x2F4;
        color=object_get_fourth_field(a);
        f=self+0x5A0;
        *color=func_PAL_002A9FA0(0x60442D00,0x70FFFEED,20,1,0);
        d=self+0x340;
        gfx_draw_screen_element_stored(self);
        slot=self+0x370;
        gfx_draw_screen_element_stored(self+0x4C);
        gfx_draw_screen_element_stored(self+0xE4);
        gfx_draw_screen_element_stored(self+0x130);
        func_PAL_00338770(self+0x828);
        func_PAL_00338770(self+0x8D8);
        func_PAL_00338770(self+0x930);
        func_PAL_00338770(self+0x988);
        func_PAL_00338770(self+0x9E0);
        object_set_flag_value(self+0x880,0);
        radial_menu_draw_info_second(self);
        func_PAL_00342518(self);
        gfx_draw_screen_element_stored(a);gfx_draw_screen_element_stored(b);gfx_draw_screen_element_stored(c);
        v=object_get_second_field(b); *v=-*v;
        v=object_get_second_field(c); *v=-*v;
        gfx_draw_screen_element_stored(b);gfx_draw_screen_element_stored(c);
        v=object_get_second_field(b); *v=-*v;
        v=object_get_second_field(c); *v=-*v;
        for(i=7;i>=0;i--,d+=0x4C,slot+=0x4C) {
            DrawMethod *m=*(DrawMethod **)slot;
            m->draw(d+m->adjustment);
        }
        e=self+0x5EC;slot2=self+0x61C;
        for(j=7;j>=0;j--,e+=0x3C,slot2+=0x3C) {
            DrawMethod *m=*(DrawMethod **)slot2;
            m->draw(e+m->adjustment);
        }
        gfx_draw_screen_element_stored(f);
        *object_get_fourth_field(f)=0x80FFDE8D;
        radial_menu_layout_items(D_001A8CFC[0]+0x36F28,0xF3,0x2B,0x70);
    }
}
