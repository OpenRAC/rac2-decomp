#include "common.h"

/* func_PAL_L09_0040FD68: the PAL copy of func_L09_0040AC48 (src/levels/09_dobbo/L09_0040AC48-g8.c),
   a Dobbo door, with its rates and timings for 50 Hz: the 1/3600 rate is 0.0004, the 240-frame
   wait is 200, and case 3's timeout is ((open + hold) * 300 + 2) / 6 frames, v1.01's 60 Hz
   count converted as (n * 5 + 2) / 6.

   Case 3 compares a copy of the frame counter, t, made after the incremented counter is stored.
   Retail allocates the counter as if that copy were kept and tied to it: the counter takes $v0
   ahead of counter + 1, and its conversion is scheduled after the 1/6 constant, taking $f3
   ahead of 2.0f. Built with -frac2-keep-user-copies, which keeps the copy through cse and
   combine (tools/compiler/transformers/keep_user_copies.py); the copy then costs no instruction.
   func_PAL_L00_003B9E80 has the same counter copy. */
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
void func_PAL_L09_0040FD68(char *obj) {
    char *data = *(char **)(obj+0x68);
    int next, next4, sound, ticks;
    float speed, accel, speed4, accel4;
    char *entry;
    switch (*(unsigned char *)(obj+0x20)) {
    case 0:
        *(int *)(obj+0x98) = 0;
        *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) | 0x2141) & 0xEFFF;
        func_002A7750(obj,1,-1);
        break;
    case 1:
        if (*(unsigned char *)(obj+0xBC)) func_002A7750(obj,2,-1);
        else {
            *(int *)(obj+0x98) = 0;
            *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) | 0x41) & 0xEFFF;
        }
        break;
    case 2:
        if (func_002B3868(obj)) {
            *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) & 0xFFBE) | 0x1000;
            *(int *)(obj+0x98) = *(int *)(*(char **)(obj+0x24)+0x10);
            func_L09_0040B008(obj);
            *(int *)(data+0x1C) = func_002E5CF8(0,4,obj);
        }
        next = (*(int *)(data+0x14)+1)&1;
        speed = D_L09_001B15A8 * 0.00040000002f;
        accel = D_L09_001B15AC * 0.00040000002f;
        if (((DobboDoorMotion *)data)->value[*(int *)(data+0x14)] < 1.0f)
            func_002AA548(&((DobboDoorMotion *)data)->value[*(int *)(data+0x14)],(float *)(data+8)+*(int *)(data+0x14),1.0f,speed,accel,1.0f);
        if (((DobboDoorMotion *)data)->value[*(int *)(data+0x14)] > 0.6f)
            func_002AA548(&((DobboDoorMotion *)data)->value[next],(float *)(data+8)+next,1.0f,speed,accel,1.0f);
        func_L09_0040B0C8(obj);
        if (((DobboDoorMotion *)data)->value[next] >= 1.0f) func_002A7750(obj,3,-1);
        break;
    case 3:
        if (func_002B3868(obj)) *(int *)(data+0x18) = 200;
        {
            int t;

            ticks = *(unsigned short *)(obj+0x96);
            *(unsigned short *)(obj+0x96) = ticks + 1;
            t = ticks;
            if ((float)t > ((*(float *)(data+0x20)+*(float *)(data+0x24))*300.0f + 2.0f)*0.16666667f)
                func_002A7750(obj,4,-1);
        }
        func_L09_0040B0C8(obj);
        break;
    case 4:
        next4 = (*(int *)(data+0x14)+1)&1;
        speed4 = D_L09_001B15A8 * 0.00040000002f;
        accel4 = D_L09_001B15AC * 0.00040000002f;
        if (((DobboDoorMotion *)data)->value[next4] > 0.2f)
            func_002AA548(&((DobboDoorMotion *)data)->value[next4],(float *)(data+8)+*(int *)(data+0x14),0.2f,speed4,accel4,1.0f);
        if (((DobboDoorMotion *)data)->value[next4] < 0.6f)
            func_002AA548(&((DobboDoorMotion *)data)->value[*(int *)(data+0x14)],(float *)(data+8)+next4,0.2f,speed4,accel4,1.0f);
        func_L09_0040B0C8(obj);
        if (((DobboDoorMotion *)data)->value[*(int *)(data+0x14)] <= 0.2f) {
            obj[0xBC] = 0;
            *(int *)(obj+0x98) = 0;
            *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) | 0x41) & 0xEFFF;
            func_002A7750(obj,1,-1);
            sound = *(int *)(data+0x1C);
            if (sound != -1) {
                entry = D_00188660 + sound*0x70;
                if (*(char **)(entry+0x88) == obj && *(unsigned char *)(entry+0x74)) func_002E59F8(sound);
            }
            *(int *)(data+0x1C) = -1;
        }
        break;
    }
}
