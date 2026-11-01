#include "common.h"


typedef int TI128 __attribute__((mode(TI)));

/* Tuning words read by func_L08_003CC4B8. */
extern float D_L08_001AFEEC __attribute__((sda));
extern float D_L08_001AFEF0 __attribute__((sda));
extern float D_L08_001AFEF4 __attribute__((sda));
extern float D_L08_001AFEF8 __attribute__((sda));
extern unsigned char D_L08_001AFEFC __attribute__((sda));
extern int D_L08_001AFF00 __attribute__((sda));
extern int D_L08_001AFF04 __attribute__((sda));
extern float D_L08_001AFF08 __attribute__((sda));
extern float D_L08_001AFF0C __attribute__((sda));
extern int D_L08_001AFF10 __attribute__((sda));
extern int D_L08_001AFF14 __attribute__((sda));
extern int D_L08_001AFF1C __attribute__((sda));
extern int D_L08_001AFF20 __attribute__((sda));
/* The frame counter: absolute loads, $gp in a delay slot. */
extern int D_L08_001B2508 MACRO_ADDR;
extern char D_L08_001B9B00[];

extern void func_0029FCC0(void *, int, void *);
extern int func_002A77E0(int);
extern void func_002A7A00(void *, float, float);
extern void func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);
extern unsigned char *func_002C2FD8(void *, int, unsigned char, int, int, int, int, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);

/* The parameter block of the shared spawn routines (func_L04_003A1A78 and its siblings). */
typedef struct {
    int kind;
    int count;
    void *table0;
    void *table1;
    void *small0;
    void *counts;
    void *table2;
    void *table3;
    void *small1;
    void *small2;
    void *owner;
    void *callback;
    void *callback2;
} L08SpawnBlock;

extern char D_00189E20[];
extern int D_L08_001B01B8[2] __attribute__((sda));
/* Kind 7 consumes seven halfwords; the full owner extent remains unknown. */
extern int D_L08_001B01D8 __attribute__((sda));
extern int D_L08_001B01DC __attribute__((sda));
extern void func_L04_003A1A78(L08SpawnBlock *);

/* Runs the shared spawn routines for the object, unless the level's player (the entity at
   D_00189E20+0x1830, kind 0x45) is alive while the mode word at +0x2294 is 0x31. The count
   is the state's +0x10 plus an entry of D_L08_001B01B8 picked by +0x18 (1 when -1); state
   0 sets the object up first and then shares state 1's step, state 2 has its own. */

/* After a one-in-four roll, spawns four particles from joint 0 whose velocity grows by a
   random step each time; then draws four rings between the moby and the point at
   D_L08_001B9B00, laid out as RAC1's update_gold_bolt_glow_rings lays out its rings: each
   ring's colour follows the frame counter, and its byte argument (the ring angle in RAC1)
   is the counter's low byte, doubled and/or inverted by the ring index. */
void func_L08_003CC4B8(char *obj)
{
    TI128 joint, velocity, step, ring, ring_step;
    int count;
    int k;
    int b;
    float t;
    float reciprocal, half, size;
    int color;

    func_0029FCC0(obj, 0, &joint);
    if (func_002A77E0(4) == 0) {
        func_002A7A00(&velocity, D_L08_001AFEEC * 0.016666668f, D_L08_001AFEF0 * 0.016666668f);
        b = D_L08_001AFEFC;
        func_002C3150(&joint, &velocity, D_L08_001AFF00, b, func_002A77E0(255), 0, D_L08_001AFF08);
        for (count = 2; count >= 0; count--) {
            func_002A7A00(&step, D_L08_001AFEF4 * 0.016666668f, D_L08_001AFEF8 * 0.016666668f);
            func_00282CC0(&velocity, &velocity, &step);
            b = D_L08_001AFEFC;
            func_002C3150(&joint, &velocity, D_L08_001AFF04, b, func_002A77E0(255), 0, D_L08_001AFF0C);
        }
    }
    func_00282CF0(&ring, D_L08_001B9B00, &joint);
    func_00282F20(&ring, &ring, -0.3f);
    func_00282F20(&ring_step, &ring, 0.1f);
    func_00282CC0(&ring, &ring, &joint);
    reciprocal = 0.003921569f;
    half = 0.5f;
    size = 3.0f;
    for (k = 0; k < 4; k++) {
        t = func_00283CE0(0xFF - ((D_L08_001B2508 + k * 20) & 0xFF));
        color = func_00283D38(D_L08_001AFF10, D_L08_001AFF14, func_00282C48(half - t * reciprocal));
        b = D_L08_001B2508 & 0xFF;
        if (k & 2)
            b = b * 2;
        if (k & 1)
            b = 0xFF - b;
        func_002C2FD8(&ring, color, b, D_L08_001AFF20, D_L08_001AFF1C, 2, 0,
                      (func_00283CE0(k) + size)
                          * (*(float *)(obj + 0x2C) / *(float *)(*(char **)(obj + 0x24) + 0x24)));
        func_00282CC0(&ring, &ring, &ring_step);
    }
}
