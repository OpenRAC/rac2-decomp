/* func_L08_0041D808 (DrawLevelStatusHud): draws the status bar and its two texture labels, the
   warning and counter texts, the pickup icon and its labels. The same C as func_PAL_L19_00417318
   (src/pal/levels/19_grelbin/L19_00417318-g8.c), with this level's data and string ids.

   Built with -fno-gcse (as the HUD units func_0032F3D0 and func_L02_003C43F0: `half`, `one`,
   `entry` and the label floats stay in registers) and -g (the nop pair before div.s).

   `hero` is one int local that holds the hero's address and later the counter colour. With two
   sets alias analysis has no base for it, so the palette stores stay behind the hero load. */
#include "common.h"

extern unsigned char D_00189E20[];
extern int D_001A7340, D_001A7344;
extern int D_00138320 __attribute__((section(".data")));
extern int D_001A79F0;
extern int D_L08_001B2508;
extern unsigned char *D_L08_001A904C;
extern int D_L08_001B3240;
extern float D_L08_001B3244;
extern unsigned char D_L08_001B1A34 __attribute__((sda));
extern unsigned char D_L08_001B1A35 __attribute__((sda));
extern unsigned char D_L08_001B1A36 __attribute__((sda));
extern unsigned char D_L08_001B1A37 __attribute__((sda));
extern unsigned char D_L08_001B1A38 __attribute__((sda));
extern unsigned char D_L08_001B1A39 __attribute__((sda));
extern unsigned char D_L08_001B1A3A __attribute__((sda));
extern unsigned char D_L08_001B1A3B __attribute__((sda));
extern unsigned char D_L08_001B1A3C __attribute__((sda));
extern unsigned char D_L08_001B1A3D __attribute__((sda));
extern unsigned char D_L08_001B1A3E __attribute__((sda));
extern unsigned char D_L08_001B1A3F __attribute__((sda));
extern unsigned char D_L08_001B1A40 __attribute__((sda));
extern int D_L08_001B1A74 __attribute__((sda));
extern int D_L08_001B1A78 __attribute__((sda));
extern float D_L08_001B1A80 __attribute__((sda));
extern float D_L08_001B1A84 __attribute__((sda));
extern float D_L08_001B1A88 __attribute__((sda));
extern float D_L08_001B1A8C __attribute__((sda));
extern int D_L08_001B1A90 __attribute__((sda));
extern int D_L08_001B1A94 __attribute__((sda));
extern int D_L08_001B1A98 __attribute__((sda));
extern float D_L08_001B1AAC __attribute__((sda));
extern float D_L08_001B1AB0 __attribute__((sda));
extern float D_L08_001B1AB4 __attribute__((sda));
extern float D_L08_001B1AB8 __attribute__((sda));
extern float D_L08_001B1ABC __attribute__((sda));
extern float D_L08_001B1AC0 __attribute__((sda));
extern float D_L08_001B1AC4 __attribute__((sda));
extern float D_L08_001B1AC8 __attribute__((sda));
extern float D_L08_001B1ACC __attribute__((sda));
extern float D_L08_001B1AD0 __attribute__((sda));
extern unsigned int D_L08_001B1AD4 __attribute__((sda));
extern unsigned int D_L08_001B1AD8 __attribute__((sda));
extern float D_L08_001B199C __attribute__((sda));
extern float D_L08_001B031C __attribute__((sda));
extern void func_L08_00389B68(int,int,unsigned long,int,unsigned long);
extern int func_00282978(void *);
extern int func_L08_00300090(void);
extern void func_L08_00300100(void);
extern int func_L08_003000C0(void);
extern char *func_00336D50(void *,int);
extern void func_00300A00(char *,int,float,float,float,float,float);
extern float func_00282C48(float);
extern unsigned int func_00283D38(unsigned int,unsigned int,float);
extern void func_0027EAE8(int,int,int,int,int,void *);
extern int func_002E5DA0(int,int,char *,int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_002A7798(float);
extern float func_002A7790(float);
extern float func_L08_003277C0(int,float);
extern unsigned char *func_00288FB8(int);
extern void func_L08_002F5CB8(int,int,u64,void *,int,float);
extern void func_L08_0033CD18(s32,s32,...);
extern int func_001157AC(void *);
extern void func_0027F5B8(int,int,u64,void *,int);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern int func_0028E588(int,int);
extern int func_0028EA58(int,int,int,int,int,void *);
extern void func_L08_004207D0(void *);
typedef struct { unsigned char pad[0xA4]; float level; } HudState;
static __inline__ unsigned long PackGaugeFlag(unsigned long flags, unsigned char value, int shift)
{
    return flags | ((unsigned long)value << shift);
}

/* A screen coordinate scaled for the display, offset in display mode `active`. */
static __inline__ int hud_coord(int mode, float value, float half, int active, float offset)
{
    float scaled = value * D_L08_001B3244 + half;
    if (mode == active)
        return (int)(scaled + offset);
    return (int)scaled;
}

/* The status bar's height (a float) scaled for the display and rounded. scaled_coord's
   display-mode test, on the display mode its caller has already read (as scaled_screen_size(mode,
   ...) in src/game/002D3390.c takes it), compared with the 1 its caller's own test uses. The test
   has no effect on the result: flow deletes it after allocation. */
static __inline__ int hud_size(int mode, float value, float scale, float half)
{
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == 1)
        scaled = 1.0f;
    return result;
}

/* A coordinate scaled for the display and rounded to a whole pixel (upstream's scaled_coord,
   src/levels/02_maktar_nebula/L02_003FF6E8-g8.c). The display-mode test has no effect on the
   result: flow deletes it after allocation. */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_L08_001B3240;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* A label's y coordinate (a text line or a sprite) scaled for the display and rounded to a whole
   pixel. Its display-mode and handle tests do not change the result: flow deletes them after
   allocation, as with scaled_coord in src/levels/02_maktar_nebula/L02_003FF6E8-g8.c. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L08_001B3240;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

/* Draws one centred texture label. */
static __inline__ void sprite(char *id, int col, float x, int y, float a, float b, float c)
{
    func_00300A00(id, col, x, (float)y, a, b, c);
}

/* The status bar's bottom edge. */
static __inline__ int hud_bar_bottom(void)
{
    int mode = D_L08_001B3240;
    int h = D_001A7344;
    float scaled = D_L08_001B1AC8 * D_L08_001B3244 + 0.5f;
    float scale = D_L08_001B3244;
    int y;

    if (mode == 1)
        y = (int)(scaled + -4.0f);
    else
        y = (int)scaled;
    return h - y + hud_size(mode, D_L08_001B1AD0, scale, 0.5f);
}

int func_L08_0041D808(void)
{
    unsigned int colors[4];
    struct Palette { unsigned int a,b; } palette;
    char text[64];
    int hero = (int)D_00189E20;
    unsigned char *obj = *(unsigned char **)(hero + 0x1830);
    unsigned char *s = *(unsigned char **)(obj + 0x68);
    int mask = -1;

    if (*(float *)(hero + 0x183C) < *(float *)(hero + 0x1840) * 0.25f)
        if ((D_L08_001B2508 / 90) & 1) mask = 0xFF0F0FFF;
    {
        unsigned long test, alpha;
        test = D_L08_001B1A39;
        test = PackGaugeFlag(test, D_L08_001B1A3A, 1);
        test = PackGaugeFlag(test, D_L08_001B1A3B, 4);
        test = PackGaugeFlag(test, D_L08_001B1A3C, 12);
        test = PackGaugeFlag(test, D_L08_001B1A3D, 14);
        test = PackGaugeFlag(test, D_L08_001B1A3E, 15);
        alpha = D_L08_001B1A34;
        alpha = PackGaugeFlag(alpha, D_L08_001B1A35, 2);
        test = PackGaugeFlag(test, D_L08_001B1A3F, 16);
        alpha = PackGaugeFlag(alpha, D_L08_001B1A36, 4);
        alpha = PackGaugeFlag(alpha, D_L08_001B1A37, 6);
        func_L08_00389B68(2, 0x47, test | ((unsigned long)D_L08_001B1A40 << 17),
            0x42, alpha | ((unsigned long)D_L08_001B1A38 << 32));
    }
    func_00282978(s + 0x8E);
    if (D_L08_001A904C) {
        float delta, ratio;
        unsigned char *str;
        int y;
        float x;
        unsigned int c0, c1;
        int one, entry;
        float half, fade, z;
        entry = 0x8710;
        func_L08_00300090();
        one = 1;
        func_L08_00300100();
        half = 0.5f;
        str = (unsigned char *)func_00336D50(D_L08_001A904C + entry,0xA8);
        x = (float)(D_001A7340 / 2);
        y = label_y(str, D_L08_001B199C, D_L08_001B3244, half, 1);
        fade = 1.0f;
        z = 0.0f;
        sprite((char *)str, mask & 0x60442D00, x, D_001A7344 / 2 + y, fade, fade, z);
        str = (unsigned char *)func_00336D50(D_L08_001A904C + entry,0xA9);
        x = (float)(D_001A7340 / 2);
        y = label_y(str, D_L08_001B199C, D_L08_001B3244, half, 1);
        sprite((char *)str, mask & 0x55F0C070, x, D_001A7344 / 2 + y, fade, fade, z);
        delta = *(float *)(hero + 0x183C) - ((HudState *)s)->level;
        delta *= 0.2f;
        {
            float magnitude = func_00282C48(delta);
            if (magnitude > fade) delta /= magnitude;
        }
        c0 = D_L08_001B1AD4;
        c1 = D_L08_001B1AD8;
        ((HudState *)s)->level += delta;
        ratio = ((HudState *)s)->level / *(float *)(hero + 0x1840);
        palette.a = c0;
        palette.b = c1;
        *(struct Palette *)colors = palette;
        colors[1] = func_00283D38(c0,c1,ratio);
        func_0027EAE8((int)D_L08_001B1AC4,
            D_001A7344 - hud_coord(D_L08_001B3240, D_L08_001B1AC8, half, one, -4.0f),
            (int)(D_L08_001B1AC4 + D_L08_001B1ACC * ratio),
            hud_bar_bottom(),
            0xFFFFF1, colors);
        func_L08_003000C0();
    }
    if (D_001A79F0 == 8 || D_001A79F0 == 19) {
        unsigned char *str;
        if (*(short *)(s + 0x8E)) {
            float ratio, scale, alpha;
            int color;
            if (*(short *)(s + 0x8E) == 1) func_002E5DA0(3,0,obj,0x85C);
            ratio = func_00283CE0(180-*(short *)(s + 0x8E)) / func_00283CE0(180);
            scale = D_L08_001B1ABC + (D_L08_001B1AC0-D_L08_001B1AAC)*func_002A7798(ratio);
            alpha = func_L08_003277C0(3,1.0f-ratio)*127.0f;
            color = func_00283CF0(alpha*0.5f) << 24;
            str = func_00288FB8(0x2F59);
            func_L08_002F5CB8(D_001A7340-D_L08_001B1A94,D_001A7344-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f),
                (color|0x80)&mask,str,0x11,scale*0.96f);
            color = func_00283CF0(alpha*0.75f) << 24;
            func_L08_002F5CB8(D_001A7340-D_L08_001B1A94,D_001A7344-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f),
                (color|0x800000)&mask,str,0x11,scale*0.98f);
            color = func_00283CF0(alpha) << 24;
            func_L08_002F5CB8(D_001A7340-D_L08_001B1A94,D_001A7344-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f),
                (color|0x808080)&mask,str,0x11,scale);
        } else if (*(int *)(s + 0x6C)) {
            if (*(float *)(s + 0x68) > D_L08_001B031C) {
                int x, y;
                char *line;
                str = func_00288FB8(0x31E0);
                func_L08_0033CD18((s32)text,(s32)str,func_00283CF0(*(float *)(s + 0x68)));
                line = text;
                x = D_001A7340-D_L08_001B1A90;
                y = D_001A7344-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f);
                hero = 0x80FFDE8D; /* From here on `hero` is the counter's colour. */
                hero = mask & hero;
                func_0027F5B8(x,y,(unsigned int)hero,line,func_001157AC(line));
            } else if (D_00138320 & 0x80) {
                str = func_00288FB8(0x2F57);
                func_L08_002F5CB8(D_001A7340-D_L08_001B1A94,D_001A7344-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f),
                    (unsigned int)(mask&0x80F0F0F0),str,0xD,D_L08_001B1AB0);
            } else {
                float scale;
                scale = func_002ABB18(func_00283CE0(D_L08_001B2508)*0.1f);
                scale = func_00283198(scale);
                scale = D_L08_001B1AB4 + D_L08_001B1AB8*scale;
                str = func_00288FB8(0x2F58);
                func_L08_002F5CB8(D_001A7340-D_L08_001B1A94,D_001A7344-hud_coord(D_L08_001B3240, (float)D_L08_001B1A98, 0.5f, 1, -6.0f),
                    (unsigned int)(mask&0x80F0F0F0),str,0x11,scale);
            }
        }
        if (s[0x8A]) {
            float ratio, width, height, dx, dy, top;
            int color, tex, x, y, a, b, alpha;
            ratio = func_00283CE0(*(short *)(s + 0x88))/func_00283CE0(D_L08_001B1A78);
            width = func_002A7790(ratio)*32.0f;
            height = func_002A7790(ratio)*24.0f;
            dx = D_L08_001B1A80*func_002A7798(ratio);
            dy = D_L08_001B1A84*func_002A7798(ratio);
            color = func_00283CF0(ratio*128.0f)<<24;
            top = 16.0f-width*0.5f;
            if (D_L08_001A904C) {
                func_L08_00300090();
                func_L08_00300100();
                alpha = func_00283CF0(func_00283CE0(96)*ratio)<<24;
                str = (unsigned char *)func_00336D50(D_L08_001A904C+0x8710,0xAA);
                func_00300A00((char *)str,
                    (alpha|0x442D00)&mask,
                    (float)(D_001A7340/2+32)-dx,(float)(D_001A7344/2+D_L08_001B1A74),1.0f,1.0f,0.0f);
                alpha = func_00283CF0(func_00283CE0(85)*ratio)<<24;
                str = (unsigned char *)func_00336D50(D_L08_001A904C+0x8710,0xAB);
                func_00300A00((char *)str,
                    (alpha|0xF0C070)&mask,
                    (float)(D_001A7340/2+32)-dx,(float)(D_001A7344/2+D_L08_001B1A74),1.0f,1.0f,0.0f);
                func_L08_003000C0();
            }
            if (s[0x8A] < 3) {
                int c=color|0xF0F0B0;
                colors[0]=c;
                colors[1]=c;
                colors[2]=c;
                colors[3]=c;
                tex=func_0028E588(0xEAA2,3);
                x=func_00283CF0((float)D_001A7340-D_L08_001B1A8C-dy);
                y=func_00283CF0(D_L08_001B1A88+(float)D_L08_001B1A74+(float)*(short *)(s + 0x8C)+top);
                y=scaled_coord(y,D_L08_001B3244,0.5f,1);
                a=func_00283CF0(height);
                b=func_00283CF0(height);
                func_0028EA58(tex,x,y,a,b,colors);
            }
        }
        func_L08_004207D0(obj);
    }
    func_L08_00389B68(2,0x47,0x5340B,0x42,0x8000000044ULL);
    *(float *)(s + 0x68)=1000000.0f;
    *(int *)(s + 0x6C)=0;
    return 1;
}
