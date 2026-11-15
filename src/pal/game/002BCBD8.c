#include "common.h"
extern void FastVecAdd(void *,void *,void *),vec_scale_to_length(void *,void *,float);
extern int FastDecTimer(void *),FloatToInt(float),FastTweenColor(int,int,float);
extern void part_kill(void *);
extern float math_random_float_range(float,float);
extern char g_camera_eye_state[];
extern char *part_spawn_firework_spark(void *,void *,int,int,int,int,int,float,int,float);
extern float square_root(float), fast_vec_dist(void *,void *), IntToFloat(int);
extern void FastVecScale(void *,void *,float);
extern int vec_fast_helper_a(void *);
extern int math_random_int_range(int,int);
extern float D_001B168C MACRO_ADDR;
void func_PAL_002BCBD8(char *p)
{
    char *q=p+32;
    short *remaining;
    p[8]=(unsigned char)p[8]+1;
    if (((q[0x19]^1)&1)) {
        char *timer;
        FastVecAdd(p+16,p+16,q);
        if(q[0x19]&4) *(float *)(q+8)+=0.00392000005f;
        FastVecScale(q,q,(q[0x19]&2)?0.6f:0.8f);
        timer = p + 56;
        remaining = (short *)(p + 10);
        if(*(short *)(p+10)==FloatToInt((unsigned char)q[0x1b]*0.85f) && (unsigned char)q[0x1a]<2) {
            if(!(q[0x19]&4)) {
                int i, life, style;
                float size;
                i=4;
                do {
                    --i;
                    life=FloatToInt((unsigned char)q[0x1b]*math_random_float_range(0.9f,1.1f));
                    style=(unsigned char)q[0x18];
                    size=math_random_float_range(0.85f,1.0f);
                    part_spawn_firework_spark(p+16,q,*(int *)(q+16),*(int *)(q+20),life,style,(unsigned char)q[0x1a]+1,*(float *)(q+28),(unsigned char)q[0x19],*(float *)(q+12)*size);
                }while(i>=0);
            }
        }
        {
            if(!(q[0x19]&4)) {
                float size, duration, linear, quadratic, root, first, second, b;
                float scaled8, scaled3, y;
                size = *(float *)(q + 28);
                duration = IntToFloat((unsigned char)q[0x1b]);
scaled8 = size * 8.0f;
scaled3 = size * 3.0f;
linear = (duration * 8.0f - duration * scaled3) / (size * scaled8 + scaled8);
quadratic = duration * 3.0f;
                quadratic += linear * scaled8; quadratic /= size * -8.0f;
                duration -= IntToFloat(*(short *)(p + 10));
                duration *= 4.0f;
                y = quadratic * duration;
                root = square_root(linear * linear - y);
                first = (-linear + root) / (quadratic + quadratic);
second = (-linear - root) / (quadratic + quadratic);
*(float *)(p + 12) = first > second ? first : second;
                b=fast_vec_dist(p+16,g_camera_eye_state);
                if(b<10.0f) *(float *)(p+12)*=b*0.075f+0.25f;
            }
        }
        if(q[0x19]&2) *(int *)(p+4)=FastTweenColor(*(int *)(q+16),0x0fffffff,(float)*(short *)(p+10)/(unsigned char)q[0x1b]);
        else *(int *)(p+4)=FastTweenColor(*(int *)(q+20),*(int *)(q+16),(float)*(short *)(p+10)/(unsigned char)q[0x1b]);
        vec_fast_helper_a(timer);
        if(FastDecTimer(remaining)) {
            unsigned int flags = (unsigned char)q[0x19];
            if(flags&2) {
                float size;
                q[0x1b] = (*(short *)(p+10) = (unsigned char)q[0x1b]*3);
                q[0x19]=(q[0x19]&0xfd)|4;
                size=math_random_float_range(1.6f,2.0f);
                vec_scale_to_length(q,q,*(float *)(q+12)*size);
            } else {
                int life;
*(int *)(q+16)=*(int *)(q+20);
*(int *)(q+20)=((unsigned char)p[3]==0x48)?0:0x0f2f3f3f;
flags|=1; q[0x19]=flags;
life=math_random_int_range((unsigned char)q[0x1b]*2,(unsigned char)q[0x1b]*3);
                if(q[0x19]&8) life*=5;
                q[0x1b]=life;
                *(short *)(p+10)=(unsigned char)life;
            }
        }
    } else {
        int i, life;
        i=FloatToInt((unsigned char)q[0x1b]*0.75f)+1;
        life=FloatToInt((unsigned char)q[0x1b]*0.25f)+1;
        *(float *)(q+8)+=0.00120000001f;
        FastVecAdd(p+16,p+16,q);
        FastVecScale(q,q,0.98f);
        if(i<*(short *)(p+10)) *(int *)(p+4)=FastTweenColor(*(int *)(q+20),*(int *)(q+16),(float)(*(short *)(p+10)-i)/life);
        else if((unsigned char)p[3]==0x48) *(short *)(p+10)=0;
        else *(int *)(p+4)=(*(int *)(p+4)&0xffffff)|((*(short *)(p+10)*15/i)<<24);
        remaining = (short *)(p + 10);
        if(D_001B168C>1.0f) FastDecTimer(remaining);
        if(FastDecTimer(remaining)) part_kill(p);
    }
}


#include "common.h"
extern char *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern unsigned char *D_001F2574, *D_001F25A4;

/* func_002BC508 is in 002BC508-g8.c. */

char *func_PAL_002BD400(char *pos, int spin, int color, float spread, float low, float high, float accel, float size)
{
    char *p = part_alloc(13);
    char *q;
    if (p) {
        qcopy(p + 16, pos);
        q = p + 32;
        *(int *)(p + 4) = color;
        p[9] = FloatToInt(4.0f) + 64;
        p[3] = 0x48;
        *(float *)(p + 12) = size;
        p[1] = 0;
        p[8] = 0;
        p[2] = D_001F2574[0];
        *(float *)(p + 16) += math_random_signed_float_range(0.0f, spread);
        *(float *)(p + 20) += math_random_signed_float_range(0.0f, spread);
        *(float *)(p + 24) += math_random_signed_float_range(0.0f, spread);
        *(short *)(p + 10) = 8;
        *(int *)(q + 4) = 0;
        if (math_random_int_below(2))
            *(int *)(q + 8) = spin;
        else
            *(int *)(q + 8) = -spin;
        *(int *)(q + 20) = color & 0xffffff;
        *(float *)(q + 12) = math_random_float_range(low, high);
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
extern char g_camera_eye_state[];
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FastDecTimer(void *);
extern void part_kill(void *);

/* Particle tick: drift the position along its anchor, or fade out. */
void func_PAL_002BD698(Particle *p)
{
    float *pl = p->payload;
    p->seed += *(unsigned char *)pl;
    if (((int *)pl)[1] == 0) {
        float v[4] __attribute__((aligned(16)));
        qcopy(p->position, ((Particle *)((void **)pl)[2])->position);
        FastVecSub(v, g_camera_eye_state, p->position);
        vec_scale_to_length(v, v, 0.01f);
        FastVecAdd(p->position, p->position, v);
    } else if (FastDecTimer(&p->size)) {
        part_kill(p);
    } else {
        p->color = (FloatToInt(p->size * 25.4f) << 24) | 0xFFFFFF;
    }
}



