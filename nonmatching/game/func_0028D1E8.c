/* 2 November 2026: corrected physical interface, not a match.
 * Current 0027F980.c defines func_0027FAA8 with an int return and a complete
 * 64-bit style argument; the old draft declared void and a 32-bit style.
 * Packed 32-bit colors now explicitly widen through u32 into u64. The text
 * lookup keeps its actual integer stored-address return (00336A78.c), with
 * explicit pointer casts at the drawing calls.
 * Default G8 check.py: 3020/3056 bytes, 0/28 USA v1.01 placements. The old
 * 3012-byte draft had the narrower, false interface. Shared lookup bases,
 * FP constants and final color-branch lowering remain different. No further
 * equivalent source or flag sweep was run; no linked match is claimed.
 */
#include "common.h"

typedef struct { int xy[8][2]; } RadialPositions;
typedef struct { int ids[8]; } RadialLabels;
typedef struct { int icon, frame; int rest[5]; } RadialItem;
extern RadialPositions D_001A8E30;
extern RadialLabels D_001A8E70;
extern short D_001B189C[] __attribute__((sda));
extern short D_001B189E[] __attribute__((sda));
extern short D_001B18A0[] __attribute__((sda));
extern short D_001B18A2[] __attribute__((sda));
extern short D_001B18A4[] __attribute__((sda));
extern int D_001B18D0;
extern RadialItem **D_001B18D4;
extern int D_001A8D48 __attribute__((sda));
extern char *D_001A8CFC;
extern float D_001B23A4;
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
extern char *func_00288FB8(int);
extern int func_001157AC(char *);
extern int func_00283D38(int,int,float);
extern int func_0027FAA8(int,int,u64,char *,int);

static __inline__ void draw_background(char *tex, int color, float x, float y, float sx, float sy, float rot)
{
    func_00300A00(tex, color, x, (float)(int)(D_001B23A4 * y + 0.5f), sx, sy, rot);
}

int func_0028D1E8(unsigned char *o)
{
    int total = D_001B18A4[0] + D_001B18A0[0] + D_001B18A2[0];
    RadialPositions positions = D_001A8E30;
    int colors[4], colors2[4];
    float open, text, angle;
    float one, zero, minus;
    int i, selectedAvailable, x, y, frame, special, available, color, previous;
    char *label;
    unsigned char *fade = o + 0x70;
    open = func_00283CE0(o[0x70]) / func_00283CE0(8);
    if (open > 1.0f) open = 1.0f;
    else if (open < 0.0f) open = 0.0f;
    text = func_00283CE0(fade[1]) / func_00283CE0(8);
    if (text > 1.0f) text = 1.0f;
    else if (text < 0.0f) text = 0.0f;
    one = 1.0f;
    zero = 0.0f;
    minus = -1.0f;
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 8), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 9), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 10), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 11), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 12), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 13), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 14), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 15), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 7), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 7), 0x60442D00, 129.0f, 208.0f, minus, one, zero);
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 134), 0x55F0C070, 129.0f, 208.0f, one, one, zero);
    draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 134), 0x55F0C070, 129.0f, 208.0f, minus, one, zero);
    if (*(int *)(o+0x74) >= 0) {
        colors[0] = func_002A9588(0x80442D00,0x80FFDE8D,25,0,0);
        previous = *(int *)(o+0x74)-1;
        if (previous < 0) previous = 7;
        draw_background((char *)func_00336D50(D_001A8CFC + 0x8710, 16), colors[0], 129.0f, 208.0f, one, one, (float)previous);
        i = *(int *)(o+0x74);
        func_0028FC48(positions.xy[i][0],(int)((float)positions.xy[i][1]*D_001B23A4+0.5f),
            positions.xy[i][0]+33,(int)((float)(positions.xy[i][1]+7)*D_001B23A4+0.5f),colors[0],0);
    }
    selectedAvailable = 0;
    for (i=0;i<D_001B18D0;i++) {
        angle = func_00283B98((float)i * 2.0f * 3.1415927f / (float)D_001B18D0 - 3.1415927f,1.5707964f);
        x = (int)(func_00283180(angle)*80.0f)+114;
        y = (int)(func_00283198(angle)*75.0f)+192;
        if (!D_001B18D4[D_001A8D48][i].icon) continue;
        frame = D_001B18D4[D_001A8D48][i].frame;
        special = 0;
        if (frame == 6 && !D_001B189E[0]) frame = 7;
        available = 0;
        switch (frame) {
        case 2:
            if (D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[2]=colors[1]=colors[0]=colors[3]=0x6000FF00;
                available=1; special=1;
            }
            break;
        case 3:
            if (D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[2]=colors[1]=colors[0]=colors[3]=0x6029A1FF;
                special=1; available=1;
            }
            break;
        case 0:
            if (D_001B189C[0] && total < D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[2]=colors[1]=colors[0]=colors[3]=0x600000FF;
                special=1; available=1;
            }
            break;
        case 1:
            if (D_001B189C[0] && total < D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[2]=colors[1]=colors[0]=colors[3]=0x60FF0000;
                special=1; available=1;
            }
            break;
        case 6: case 7:
            if (D_001B18A0[0]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 4:
            if (D_001B18A2[0]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 8:
            if (D_001B18A4[0]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 9:
            if (D_001B189C[0]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        }
        if (special) func_0028EA58(func_0028E588(D_001B18D4[D_001A8D48][i].icon,10),x+2,y+2,28,26,colors);
        color = available ? 0x80FFDE8D : 0x40808080;
        colors2[2]=colors2[1]=colors2[0]=colors2[3]=color;
        func_0028EA58(func_0028E588(D_001B18D4[D_001A8D48][i].icon,frame),x,y,30,28,colors2);
    }
    if (selectedAvailable && *(int *)(o+0x74)>=0 && *(int *)(o+0x74)<8) {
        RadialLabels labels=D_001A8E70;
        int id=labels.ids[*(int *)(o+0x74)];
        if (id==0x2F34 && D_001B189E[0]) id=0x2F35;
        label=func_00288FB8(id);
        if (label && func_001157AC(label)) {
            text *= open;
            color=func_00283D38(0x00E0C0A0,0x80E0C0A0,text);
            previous=func_00283D38(0,0x80000000,text);
            func_0027FAA8(128,(int)(D_001B23A4*200.0f+0.5f),(u64)(u32)previous,label,-1);
            func_0027FAA8(129,(int)(D_001B23A4*201.0f+0.5f),(u64)(u32)color,label,-1);
        }
    }
    return *(int *)(o+0x58);
}
