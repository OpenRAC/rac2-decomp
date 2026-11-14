/* func_PAL_0028DC40 (2,584 bytes): PAL release of the radial weapon-select panel
 * (v1.01 func_0028D1E8). PAL draws the panel at fixed coordinates and passes the
 * vertical scale to func_00300A00 instead of scaling each Y position. Own unit:
 * -O2 -G8 -ffunction-sections -frac2-loop-align-in-loop-only (config/cflags.txt).
 */
#include "common.h"

typedef struct { int xy[8][2]; } RadialPositions;
typedef struct { int ids[8]; } RadialLabels;
typedef struct { int icon, frame; int rest[5]; } RadialItem;
extern RadialPositions D_001A8E30;
extern RadialLabels D_001A8E70;
extern short D_001B189C[] __attribute__((sda));
extern int D_001B18D0;
extern RadialItem **D_001B18D4;
extern int D_001A8D48 __attribute__((sda));
extern char *D_001A8CFC;
extern float D_001B23A8;
extern float func_00283CE0(int);
extern float func_00283B98(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00336D50(char *,int);
extern void func_00300A00(char *,int,float,float,float,float,float);
extern int func_002A9588(int,int,int,int,int);
extern void func_0028FC48(int,int,int,int,unsigned long,int);
extern int func_0028E588(int,int);
extern void func_0028EA58(int,int,int,int,int,int *);
extern int func_00288FB8(int);
extern int func_001157AC(char *);
extern int func_00283D38(int,int,float);
extern int func_0027FAA8(int,int,u64,char *,int);

static __inline__ void draw_background(char *tex, int color, float sx, float rot)
{
    func_00300A00(tex, color, 129.0f, 208.0f, sx, D_001B23A8, rot);
}

int func_PAL_0028DC40(unsigned char *o)
{
    int total = D_001B189C[2] + D_001B189C[4] + D_001B189C[3];
    RadialPositions positions = D_001A8E30;
    int colors[4], colors2[4];
    float open, text, angle, zero;
    char *tex;
    int sel;
    char *label;
    int i, selectedAvailable, x, y, frame, available, color, previous;
    unsigned char *fade = o + 0x70;
    open = func_00283CE0(o[0x70]) / func_00283CE0(8);
    if (open > 1.0f) open = 1.0f;
    else if (open < 0.0f) open = 0.0f;
    text = func_00283CE0(fade[1]) / func_00283CE0(8);
    if (text > 1.0f) text = 1.0f;
    else if (text < 0.0f) text = 0.0f;
    /* FAKEMATCH: do { } while (0) group; its loop notes make the read after the last draw a
     * scheduling barrier, so the last draw loads $f12 before $a1 as retail (v1.01 has the same group) */
    do {
        zero = 0.0f;
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 8);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 9);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 10);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 11);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 12);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 13);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 14);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 15);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 7);
        draw_background(tex, 0x60442D00, 1.0f, zero);
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 7);
        draw_background(tex, 0x60442D00, -1.0f, zero);
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 134);
        draw_background(tex, 0x55F0C070, 1.0f, zero);
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 134);
        draw_background(tex, 0x55F0C070, -1.0f, zero);
    } while (0);
    if (*(int *)(o+0x74) >= 0) {
        colors[0] = func_002A9588(0x80442D00,0x80FFDE8D,25,0,0);
        previous = *(int *)(o+0x74)-1;
        if (previous < 0) previous = 7;
        tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 16);
        draw_background(tex, colors[0], 1.0f, (float)previous);
        {
            int k = *(int *)(o+0x74);
            func_0028FC48(positions.xy[k][0], positions.xy[k][1],
                positions.xy[k][0]+33, positions.xy[k][1]+7, colors[0], 0);
        }
    }
    selectedAvailable = 0;
    for (i=0;i<D_001B18D0;i++) {
        angle = func_00283B98((float)i * 2.0f * 3.1415927f / (float)D_001B18D0 - 3.1415927f,1.5707964f);
        x = (int)(func_00283180(angle)*80.0f)+114;
        y = (int)(func_00283198(angle)*75.0f)+192;
        if (!D_001B18D4[D_001A8D48][i].icon) continue;
        frame = D_001B18D4[D_001A8D48][i].frame;
        previous = 0;
        if (frame == 6 && !D_001B189C[1]) frame = 7;
        available = 0;
        switch (frame) {
        case 2:
            if (D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x6000FF00;
                available=1; previous=1;
            }
            break;
        case 3:
            if (D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x6029A1FF;
                previous=1; available=1;
            }
            break;
        case 0:
            if (D_001B189C[0] && total < D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x600000FF;
                previous=1; available=1;
            }
            break;
        case 1:
            if (D_001B189C[0] && total < D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x60FF0000;
                previous=1; available=1;
            }
            break;
        case 6: case 7:
            if (D_001B189C[2]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 4:
            if (D_001B189C[3]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 8:
            if (D_001B189C[4]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 9:
            if (D_001B189C[0]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        }
        if (previous) func_0028EA58(func_0028E588(D_001B18D4[D_001A8D48][i].icon,10),x+2,y+2,28,26,colors);
        if (available) {
            colors2[3]=colors2[2]=colors2[1]=colors2[0]=0x80FFDE8D;
        } else {
            colors2[3]=colors2[2]=colors2[1]=colors2[0]=0x40808080;
        }
        func_0028EA58(func_0028E588(D_001B18D4[D_001A8D48][i].icon,frame),x,y,30,28,colors2);
    }
    sel = *(int *)(o+0x74);
    if (selectedAvailable && sel>=0 && sel<8) {
        RadialLabels labels=D_001A8E70;
        int id=labels.ids[sel];
        if (id==0xE59 && D_001B189C[1]) id=0xE5A;
        label=(char *)func_00288FB8(id);
        if (label && func_001157AC(label)) {
            float alpha = text * open;
            color=func_00283D38(0x00E0C0A0,0x80E0C0A0,alpha);
            previous=func_00283D38(0,0x80000000,alpha);
            func_0027FAA8(128,200,previous,label,-1);
            func_0027FAA8(129,201,color,label,-1);
        }
    }
    return *(int *)(o+0x58);
}
