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
/* Updates a firework shell. It rises, splits into sparks near the end of its life, then flares and fades out. */
void part_update_firework(char *particle)
{
    char *motion=particle+32;
    short *remaining;
    particle[8]=(unsigned char)particle[8]+1;
    if (((motion[0x19]^1)&1)) {
        char *timer;
        FastVecAdd(particle+16,particle+16,motion);
        if(motion[0x19]&4) *(float *)(motion+8)+=0.00272222236f;
        FastVecScale(motion,motion,(motion[0x19]&2)?0.6f:0.8f);
        timer = particle + 56;
        remaining = (short *)(particle + 10);
        if(*(short *)(particle+10)==FloatToInt((unsigned char)motion[0x1b]*0.85f) && (unsigned char)motion[0x1a]<2) {
            if(!(motion[0x19]&4)) {
                int i, life, style;
                float size;
                i=4;
                do {
                    --i;
                    life=FloatToInt((unsigned char)motion[0x1b]*math_random_float_range(0.9f,1.1f));
                    style=(unsigned char)motion[0x18];
                    size=math_random_float_range(0.85f,1.0f);
                    part_spawn_firework_spark(particle+16,motion,*(int *)(motion+16),*(int *)(motion+20),life,style,(unsigned char)motion[0x1a]+1,*(float *)(motion+28),(unsigned char)motion[0x19],*(float *)(motion+12)*size);
                }while(i>=0);
            }
        }
        {
            if(!(motion[0x19]&4)) {
                float size, duration, linear, quadratic, root, first, second, distance;
                float scaled8, scaled3, y;
                size = *(float *)(motion + 28);
                duration = IntToFloat((unsigned char)motion[0x1b]);
scaled8 = size * 8.0f;
scaled3 = size * 3.0f;
linear = (duration * 8.0f - duration * scaled3) / (size * scaled8 + scaled8);
quadratic = duration * 3.0f;
                quadratic += linear * scaled8; quadratic /= size * -8.0f;
                duration -= IntToFloat(*(short *)(particle + 10));
                duration *= 4.0f;
                y = quadratic * duration;
                root = square_root(linear * linear - y);
                first = (-linear + root) / (quadratic + quadratic);
second = (-linear - root) / (quadratic + quadratic);
*(float *)(particle + 12) = first > second ? first : second;
                distance=fast_vec_dist(particle+16,g_camera_eye_state);
                if(distance<10.0f) *(float *)(particle+12)*=distance*0.075f+0.25f;
            }
        }
        if(motion[0x19]&2) *(int *)(particle+4)=FastTweenColor(*(int *)(motion+16),0x0fffffff,(float)*(short *)(particle+10)/(unsigned char)motion[0x1b]);
        else *(int *)(particle+4)=FastTweenColor(*(int *)(motion+20),*(int *)(motion+16),(float)*(short *)(particle+10)/(unsigned char)motion[0x1b]);
        vec_fast_helper_a(timer);
        if(FastDecTimer(remaining)) {
            unsigned int flags = (unsigned char)motion[0x19];
            if(flags&2) {
                float size;
                motion[0x1b] = (*(short *)(particle+10) = (unsigned char)motion[0x1b]*3);
                motion[0x19]=(motion[0x19]&0xfd)|4;
                size=math_random_float_range(1.6f,2.0f);
                vec_scale_to_length(motion,motion,*(float *)(motion+12)*size);
            } else {
                int life;
*(int *)(motion+16)=*(int *)(motion+20);
*(int *)(motion+20)=((unsigned char)particle[3]==0x48)?0:0x0f2f3f3f;
flags|=1; motion[0x19]=flags;
life=math_random_int_range((unsigned char)motion[0x1b]*2,(unsigned char)motion[0x1b]*3);
                if(motion[0x19]&8) life*=5;
                motion[0x1b]=life;
                *(short *)(particle+10)=(unsigned char)life;
            }
        }
    } else {
        int i, life;
        i=FloatToInt((unsigned char)motion[0x1b]*0.75f)+1;
        life=FloatToInt((unsigned char)motion[0x1b]*0.25f)+1;
        *(float *)(motion+8)+=0.000833333354f;
        FastVecAdd(particle+16,particle+16,motion);
        FastVecScale(motion,motion,0.98f);
        if(i<*(short *)(particle+10)) *(int *)(particle+4)=FastTweenColor(*(int *)(motion+20),*(int *)(motion+16),(float)(*(short *)(particle+10)-i)/life);
        else if((unsigned char)particle[3]==0x48) *(short *)(particle+10)=0;
        else *(int *)(particle+4)=(*(int *)(particle+4)&0xffffff)|((*(short *)(particle+10)*15/i)<<24);
        remaining = (short *)(particle + 10);
        if(D_001B168C>1.0f) FastDecTimer(remaining);
        if(FastDecTimer(remaining)) part_kill(particle);
    }
}

