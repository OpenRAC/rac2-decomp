/* Opus G2, 1 November 2026: with -fmove-all-movables the only cause left is `mov.s $f20,$f21`, which
 * lands in the call delay slot at +0x448 where retail has a nop and keeps it at +0x544. Moving the
 * statement inside the loop tail ties. A probe of single flag and MACRO_ADDR toggles found nothing.
 * Sol-low v0327, 2026-10-28: upstream toolchain, 1480/1484 bytes, 0/27 places.
 * Carried orch/main unit with -O2 -G0 -ffunction-sections -frac2-hazard-labels
 * -fmove-all-movables. Adding qcopy/qcopy-barrier and using qcopy_nc on the final
 * independent radial copy both tie at 1480 bytes. Retail keeps the f20=f21 move
 * after the final copy; upstream moves it into the earlier call delay slot and
 * removes a nop. Old sticky-volatile-refs flag is unavailable here. Needs an
 * evidenced source lifetime that retains retail scheduling, not a volatile cast.
 */
#include "common.h"

/* Own unit: -fmove-all-movables lets loop.c hoist the second strip loop's
 * copy-destination address in its first pass (the default threshold leaves it
 * to the rerun pass), which gives retail's preheader order and allocation. */

typedef struct { float f[4]; } Vector __attribute__((aligned(16)));
typedef struct {
    Vector vertex[4];
    unsigned int color[4];
    float uv[8];
    long reserved, texture, state, flags;
} QuadPacket;
extern Vector ref_L00_003C5310_00;
extern void func_00281DE8(QuadPacket *,int,int,int);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern float func_00283CE0(int);
extern unsigned int func_00283D38(unsigned int,unsigned int,float);
extern void func_00280B90(QuadPacket *,void *,int);
extern float func_00282DF0(void *);
extern void func_00282D30(void *,void *,float);
extern void func_002FC560(unsigned int,unsigned long long);

void func_L00_003C5310(Vector *points,int count,int texture1,int texture2,
    unsigned int colorEnd1,unsigned int colorStart1,unsigned int colorEnd2,unsigned int colorStart2,
    int first,int last,int segments,float width1,float width2,float inset)
{
    QuadPacket strip, bevel;
    Vector cross, scaledCross, radial, tangent, left, right, nextRadial, previousRadial, scaledRadial, equalRadial1, equalRadial2, offset;
    float step, fraction, previousLength, nextLength;
    int current, previous, next;
    func_00281DE8(&strip,texture1,1,128);
    strip.color[0]=strip.color[1]=strip.color[2]=strip.color[3]=colorStart1;
    strip.uv[0]=0; strip.uv[1]=0; strip.uv[2]=0; strip.uv[3]=1;
    strip.uv[4]=1; strip.uv[5]=0; strip.uv[6]=1; strip.uv[7]=1;
    func_00281DE8(&bevel,texture2,1,128);
    bevel.color[0]=bevel.color[1]=bevel.color[2]=bevel.color[3]=colorStart2;
    bevel.uv[0]=0; bevel.uv[1]=0; bevel.uv[2]=0; bevel.uv[3]=1;
    bevel.uv[4]=1; bevel.uv[5]=0; bevel.uv[6]=1; bevel.uv[7]=1;
    next=(first+1)%count;
    func_00282CF0(&radial,&points[first],&ref_L00_003C5310_00);
    func_00282CF0(&tangent,&points[next],&points[first]);
    func_00282DD8(&cross,&tangent,&radial);
    func_00282F20(&cross,&cross,width1);
    func_00282CC0(&strip.vertex[0],&points[first],&cross);
    func_00282CF0(&strip.vertex[1],&points[first],&cross);
    step=1.0f/func_00283CE0(segments-1);
    fraction=step;
    current=next;
    previous=first;
    while (current!=last) {
        func_00282CF0(&radial,&points[current],&ref_L00_003C5310_00);
        func_00282CF0(&tangent,&points[current],&points[previous]);
        func_00282DD8(&cross,&tangent,&radial);
        func_00282F20(&cross,&cross,width1);
        func_00282CC0(&strip.vertex[2],&points[current],&cross);
        func_00282CF0(&strip.vertex[3],&points[current],&cross);
        strip.color[2]=strip.color[3]=func_00283D38(colorStart1,colorEnd1,fraction);
        func_00280B90(&strip,0,0);
        qcopy(&strip.vertex[0],&strip.vertex[2]);
        qcopy(&strip.vertex[1],&strip.vertex[3]);
        strip.color[0]=strip.color[1]=strip.color[2];
        fraction+=step;
        previous=current;
        current=(previous+1)%count;
    }
    func_00282CF0(&previousRadial,&points[first],&ref_L00_003C5310_00);
    previousLength=func_00282DF0(&previousRadial);
    fraction=step;
    current=next;
    while (current!=last) {
        func_00282CF0(&nextRadial,&points[current],&ref_L00_003C5310_00);
        nextLength=func_00282DF0(&nextRadial);
        if (previousLength<nextLength) {
            if (previousLength==0.0f) qcopy(&equalRadial1,&nextRadial);
            else func_00282D30(&equalRadial1,&previousRadial,nextLength/previousLength);
            func_00282CC0(&left,&ref_L00_003C5310_00,&nextRadial);
            func_00282CC0(&right,&ref_L00_003C5310_00,&equalRadial1);
        } else {
            if (nextLength==0.0f) qcopy(&equalRadial2,&previousRadial);
            else func_00282D30(&equalRadial2,&nextRadial,previousLength/nextLength);
            func_00282CC0(&left,&ref_L00_003C5310_00,&equalRadial2);
            func_00282CC0(&right,&ref_L00_003C5310_00,&previousRadial);
        }
        func_00282CF0(&tangent,&right,&left);
        func_00282D30(&offset,&tangent,inset);
        func_00282CF0(&left,&left,&offset);
        func_00282CC0(&right,&right,&offset);
        func_00282CF0(&scaledRadial,&ref_L00_003C5310_00,&left);
        func_00282DD8(&cross,&scaledRadial,&tangent);
        func_00282F20(&scaledCross,&cross,width2);
        func_00282CC0(&bevel.vertex[0],&left,&scaledCross);
        func_00282CF0(&bevel.vertex[1],&left,&scaledCross);
        func_00282CC0(&bevel.vertex[2],&right,&scaledCross);
        func_00282CF0(&bevel.vertex[3],&right,&scaledCross);
        bevel.color[2]=bevel.color[3]=func_00283D38(colorStart2,colorEnd2,fraction);
        func_00280B90(&bevel,0,0);
        qcopy(&previousRadial,&nextRadial);
        bevel.color[0]=bevel.color[1]=bevel.color[2];
        current=(current+1)%count;
        fraction+=step;
        previousLength=nextLength;
    }
    func_002FC560(0x47,0x5360b);
}
