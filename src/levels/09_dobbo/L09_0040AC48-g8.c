#include "common.h"
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern void func_L09_0040B008(char *);
extern void func_L09_0040B0C8(char *);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_002AA548(float *, float *, float, float, float, float);
extern float D_L09_001B15A8 __attribute__((sda));
extern float D_L09_001B15AC __attribute__((sda));
extern char D_00188660[];
typedef struct { float value[2]; float rate[2]; } DobboDoorMotion;
/* Per-frame update of the sliding double door (moby class 3680): it opens, stays open for a while and closes again. */
void func_L09_0040AC48(char *obj) {
    char *data = *(char **)(obj+0x68);
    int next, next4, sound, ticks;
    float speed, accel, speed4, accel4;
    char *entry;
    switch (*(unsigned char *)(obj+0x20)) {
    case 0:
        *(int *)(obj+0x98) = 0;
        *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) | 0x2141) & 0xEFFF;
        SetMobyState(obj,1,-1);
        break;
    case 1:
        if (*(unsigned char *)(obj+0xBC)) SetMobyState(obj,2,-1);
        else {
            *(int *)(obj+0x98) = 0;
            *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) | 0x41) & 0xEFFF;
        }
        break;
    case 2:
        if (SetFirstPendingFlag(obj)) {
            *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) & 0xFFBE) | 0x1000;
            *(int *)(obj+0x98) = *(int *)(*(char **)(obj+0x24)+0x10);
            InitSlidingDoorMotion(obj);
            *(int *)(data+0x1C) = PlayMobySound(0,4,obj);
        }
        next = (*(int *)(data+0x14)+1)&1;
        speed = D_L09_001B15A8 * 0.000277777785f;
        accel = D_L09_001B15AC * 0.000277777785f;
        if (((DobboDoorMotion *)data)->value[*(int *)(data+0x14)] < 1.0f)
            StepValueTowardTarget(&((DobboDoorMotion *)data)->value[*(int *)(data+0x14)],(float *)(data+8)+*(int *)(data+0x14),1.0f,speed,accel,1.0f);
        if (((DobboDoorMotion *)data)->value[*(int *)(data+0x14)] > 0.6f)
            StepValueTowardTarget(&((DobboDoorMotion *)data)->value[next],(float *)(data+8)+next,1.0f,speed,accel,1.0f);
        UpdateSpinningDirection(obj);
        if (((DobboDoorMotion *)data)->value[next] >= 1.0f) SetMobyState(obj,3,-1);
        break;
    case 3:
        if (SetFirstPendingFlag(obj)) *(int *)(data+0x18) = 240;
        ticks = *(unsigned short *)(obj+0x96);
        *(unsigned short *)(obj+0x96) = ticks + 1;
        if ((float)ticks > (*(float *)(data+0x20)+*(float *)(data+0x24))*60.0f)
            SetMobyState(obj,4,-1);
        UpdateSpinningDirection(obj);
        break;
    case 4:
        next4 = (*(int *)(data+0x14)+1)&1;
        speed4 = D_L09_001B15A8 * 0.000277777785f;
        accel4 = D_L09_001B15AC * 0.000277777785f;
        if (((DobboDoorMotion *)data)->value[next4] > 0.2f)
            StepValueTowardTarget(&((DobboDoorMotion *)data)->value[next4],(float *)(data+8)+*(int *)(data+0x14),0.2f,speed4,accel4,1.0f);
        if (((DobboDoorMotion *)data)->value[next4] < 0.6f)
            StepValueTowardTarget(&((DobboDoorMotion *)data)->value[*(int *)(data+0x14)],(float *)(data+8)+next4,0.2f,speed4,accel4,1.0f);
        UpdateSpinningDirection(obj);
        if (((DobboDoorMotion *)data)->value[*(int *)(data+0x14)] <= 0.2f) {
            obj[0xBC] = 0;
            *(int *)(obj+0x98) = 0;
            *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) | 0x41) & 0xEFFF;
            SetMobyState(obj,1,-1);
            sound = *(int *)(data+0x1C);
            if (sound != -1) {
                entry = gSoundState + sound*0x70;
                if (*(char **)(entry+0x88) == obj && *(unsigned char *)(entry+0x74)) StopSoundVoice(sound);
            }
            *(int *)(data+0x1C) = -1;
        }
        break;
    }
}
