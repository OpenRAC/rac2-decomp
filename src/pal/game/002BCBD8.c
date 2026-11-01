#include "common.h"
extern void func_00282CC0(void *,void *,void *),func_00282F20(void *,void *,float);
extern int func_00282978(void *),func_00283CF0(float),func_00283D38(int,int,float);
extern void func_002B9180(void *);
extern float func_002A7878(float,float);
extern char D_001B5340[];
extern char *func_002BBCB0(void *,void *,int,int,int,int,int,float,int,float);
extern float func_00282C10(float), func_00282E48(void *,void *), func_00283CE0(int);
extern void func_00282D30(void *,void *,float), func_002829A8(void *);
extern int func_002A7820(int,int);
extern float D_001B168C MACRO_ADDR;
void func_PAL_002BCBD8(char *p)
{
    char *q=p+32;
    short *remaining;
    p[8]=(unsigned char)p[8]+1;
    if (((q[0x19]^1)&1)) {
        char *timer;
        func_00282CC0(p+16,p+16,q);
        if(q[0x19]&4) *(float *)(q+8)+=0.00392000005f;
        func_00282D30(q,q,(q[0x19]&2)?0.6f:0.8f);
        timer = p + 56;
        remaining = (short *)(p + 10);
        if(*(short *)(p+10)==func_00283CF0((unsigned char)q[0x1b]*0.85f) && (unsigned char)q[0x1a]<2) {
            if(!(q[0x19]&4)) {
                int i, life, style;
                float size;
                i=4;
                do {
                    --i;
                    life=func_00283CF0((unsigned char)q[0x1b]*func_002A7878(0.9f,1.1f));
                    style=(unsigned char)q[0x18];
                    size=func_002A7878(0.85f,1.0f);
                    func_002BBCB0(p+16,q,*(int *)(q+16),*(int *)(q+20),life,style,(unsigned char)q[0x1a]+1,*(float *)(q+28),(unsigned char)q[0x19],*(float *)(q+12)*size);
                }while(i>=0);
            }
        }
        {
            if(!(q[0x19]&4)) {
                float size, duration, linear, quadratic, root, first, second, b;
                float scaled8, scaled3, y;
                size = *(float *)(q + 28);
                duration = func_00283CE0((unsigned char)q[0x1b]);
scaled8 = size * 8.0f;
scaled3 = size * 3.0f;
linear = (duration * 8.0f - duration * scaled3) / (size * scaled8 + scaled8);
quadratic = duration * 3.0f;
                quadratic += linear * scaled8; quadratic /= size * -8.0f;
                duration -= func_00283CE0(*(short *)(p + 10));
                duration *= 4.0f;
                y = quadratic * duration;
                root = func_00282C10(linear * linear - y);
                first = (-linear + root) / (quadratic + quadratic);
second = (-linear - root) / (quadratic + quadratic);
*(float *)(p + 12) = first > second ? first : second;
                b=func_00282E48(p+16,D_001B5340);
                if(b<10.0f) *(float *)(p+12)*=b*0.075f+0.25f;
            }
        }
        if(q[0x19]&2) *(int *)(p+4)=func_00283D38(*(int *)(q+16),0x0fffffff,(float)*(short *)(p+10)/(unsigned char)q[0x1b]);
        else *(int *)(p+4)=func_00283D38(*(int *)(q+20),*(int *)(q+16),(float)*(short *)(p+10)/(unsigned char)q[0x1b]);
        func_002829A8(timer);
        if(func_00282978(remaining)) {
            unsigned int flags = (unsigned char)q[0x19];
            if(flags&2) {
                float size;
                q[0x1b] = (*(short *)(p+10) = (unsigned char)q[0x1b]*3);
                q[0x19]=(q[0x19]&0xfd)|4;
                size=func_002A7878(1.6f,2.0f);
                func_00282F20(q,q,*(float *)(q+12)*size);
            } else {
                int life;
*(int *)(q+16)=*(int *)(q+20);
*(int *)(q+20)=((unsigned char)p[3]==0x48)?0:0x0f2f3f3f;
flags|=1; q[0x19]=flags;
life=func_002A7820((unsigned char)q[0x1b]*2,(unsigned char)q[0x1b]*3);
                if(q[0x19]&8) life*=5;
                q[0x1b]=life;
                *(short *)(p+10)=(unsigned char)life;
            }
        }
    } else {
        int i, life;
        i=func_00283CF0((unsigned char)q[0x1b]*0.75f)+1;
        life=func_00283CF0((unsigned char)q[0x1b]*0.25f)+1;
        *(float *)(q+8)+=0.00120000001f;
        func_00282CC0(p+16,p+16,q);
        func_00282D30(q,q,0.98f);
        if(i<*(short *)(p+10)) *(int *)(p+4)=func_00283D38(*(int *)(q+20),*(int *)(q+16),(float)(*(short *)(p+10)-i)/life);
        else if((unsigned char)p[3]==0x48) *(short *)(p+10)=0;
        else *(int *)(p+4)=(*(int *)(p+4)&0xffffff)|((*(short *)(p+10)*15/i)<<24);
        remaining = (short *)(p + 10);
        if(D_001B168C>1.0f) func_00282978(remaining);
        if(func_00282978(remaining)) func_002B9180(p);
    }
}


#include "common.h"
extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern unsigned char *D_001F2574, *D_001F25A4;

/* func_002BC508 is in 002BC508-g8.c. */

char *func_PAL_002BD400(char *pos, int spin, int color, float spread, float low, float high, float accel, float size)
{
    char *p = func_002B9030(13);
    char *q;
    if (p) {
        qcopy(p + 16, pos);
        q = p + 32;
        *(int *)(p + 4) = color;
        p[9] = func_00283CF0(4.0f) + 64;
        p[3] = 0x48;
        *(float *)(p + 12) = size;
        p[1] = 0;
        p[8] = 0;
        p[2] = D_001F2574[0];
        *(float *)(p + 16) += func_002A78D8(0.0f, spread);
        *(float *)(p + 20) += func_002A78D8(0.0f, spread);
        *(float *)(p + 24) += func_002A78D8(0.0f, spread);
        *(short *)(p + 10) = 8;
        *(int *)(q + 4) = 0;
        if (func_002A77E0(2))
            *(int *)(q + 8) = spin;
        else
            *(int *)(q + 8) = -spin;
        *(int *)(q + 20) = color & 0xffffff;
        *(float *)(q + 12) = func_002A7878(low, high);
        *(float *)(q + 16) = accel;
    }
    return p;
}


extern int Fd1c348f5_FUN_00282978(char *p);
extern int Fd1c348f5_FUN_00283CF0(float v);
extern void Fd1c348f5_FUN_002B9180(char *p);

void func_PAL_002BD580(char *p)
{
    char *q = p + 32;
    int r;
    int v;
    float f;

    *(unsigned char *)(p + 8) = *(unsigned char *)(p + 8) + *(unsigned char *)(q + 8);
    *(float *)(p + 24) = *(float *)(p + 24) + *(float *)(q + 16);
    *(float *)(p + 12) = *(float *)(p + 12) * *(float *)(q + 12);
    if (*(int *)(q + 4) == 0) {
        r = Fd1c348f5_FUN_00282978(p + 10);
        if (r != 0) {
            *(int *)(q + 4) = 1;
            *(short *)(p + 10) = 25;
            *(int *)(p + 4) = *(int *)(q + 20) | 0x7f000000;
        } else {
            f = (float)(8 - *(short *)(p + 10)) * 12.0f;
            v = Fd1c348f5_FUN_00283CF0(f);
            *(int *)(p + 4) = ((v + 32) << 24) | *(int *)(q + 20);
        }
    } else {
        r = Fd1c348f5_FUN_00282978(p + 10);
        if (r != 0) {
            Fd1c348f5_FUN_002B9180(p);
        } else {
            f = (float)*(short *)(p + 10) * 5.08f;
            v = Fd1c348f5_FUN_00283CF0(f);
            *(int *)(p + 4) = (v << 24) | *(int *)(q + 20);
        }
    }
}


typedef struct {
    unsigned char b0, b1, b2, b3;
    int color;
    unsigned char seed, alpha;
    short size;
    float life;
    float position[4];
    float payload[8];
} Particle;
extern char D_001B5340[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00282978(void *);
extern void func_002B9180(void *);

/* Particle tick: drift the position along its anchor, or fade out. */
void func_PAL_002BD698(Particle *p)
{
    float *pl = p->payload;
    p->seed += *(unsigned char *)pl;
    if (((int *)pl)[1] == 0) {
        float v[4] __attribute__((aligned(16)));
        qcopy(p->position, ((Particle *)((void **)pl)[2])->position);
        func_00282CF0(v, D_001B5340, p->position);
        func_00282F20(v, v, 0.01f);
        func_00282CC0(p->position, p->position, v);
    } else if (func_00282978(&p->size)) {
        func_002B9180(p);
    } else {
        p->color = (func_00283CF0(p->size * 25.4f) << 24) | 0xFFFFFF;
    }
}



