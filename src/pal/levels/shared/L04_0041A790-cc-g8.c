/* func_PAL_L04_0041A790, the PAL copy of func_L04_00416018: the same C. */

typedef unsigned char u8;
typedef short s16;

/* Collects the racers, sorts their recorded times, and records each rank and
   the next racer in the ordered list. */
typedef unsigned int u32;

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

/* Eight-sample trail records; the retail loop visits 140 entries of stride 0x150. */
typedef struct Trail416018 {
    float points[8][4];
    float velocities[8][4];
    float origin[4];
    float *offset, *impulse;
    short ages[8], landed[8];
    int count, lifetime;
    u32 colour;
    int active;
    char *owner;
    int tail;
} Trail416018;
extern Trail416018 D_L04_00254E10[] __attribute__((sda));
extern unsigned char D_00189E20[];
extern int D_L04_001B08F0 __attribute__((sda));
extern void *D_L04_001B0914 __attribute__((sda));
extern void func_00282CC0(float *, float *, float *);
extern void func_00282D30(float *, float *, float);
extern void func_00283098(float *, float *, char *);
extern int func_00282948(int *);
extern int func_00283D38(int, int, float);
extern void func_L04_00415E28(void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
void func_PAL_L04_0041A790(void)
{
    float local[4] __attribute__((aligned(16)));
    float floorZ, scale;
    Trail416018 *trail;
    float *point, *velocity;
    float gravity;
    short *age;
    int i, j, count;
    char *owner;
    for (i = 0; i < 140; i++) {
        trail = &D_L04_00254E10[i];
        if (!trail->active)
            continue;
        owner = trail->owner;
        count = trail->count;
        if (*(short *)(owner + 0xaa) == 0xbbc) {
            /* Through a pointer, as retail keeps the hero base in a register. */
            unsigned char *hero = D_00189E20;
            floorZ = *(float *)(hero + 0x318) + 0.1f;
        } else {
            floorZ = *(float *)(owner + 0x18) - 0.25f;
        }
        for (j = 0; j < count; j++) {
            float widthStep = 0.0009f;
            gravity = 0.0028000001f;
            point = trail->points[j];
            age = &trail->ages[j];
            velocity = trail->velocities[j];
            /* velocities[j][2], addressed from the point as retail does. */
            if ((*age)++ > 8)
                ((float *)((char *)point + 0x80))[2] -= gravity;
            scale = 1.0f;
            scale -= (*age - 4) * 0.01f;
            func_00282CC0(point, point, velocity);
            func_00282D30(local, trail->impulse, scale);
            func_00282CC0(point, point, local);
            if (point[2] < floorZ) {
                point[2] = floorZ;
                trail->landed[j] = 1;
            }
            point[3] = trail->ages[0] * widthStep + 0.01f + *age * widthStep;
        }
        if (count < 8 &&
            ((*(short *)(trail->owner + 0xaa) == 0xbbc && D_L04_001B08F0) ||
             (*(short *)(trail->owner + 0xaa) == 0xb2d &&
              *(int *)(*(char **)(trail->owner + 0x68) + 0x244)))) {
            if (trail->ages[count - 1] < 3)
                continue;
            point = trail->points[count];
            func_00283098(local, trail->origin, trail->owner + 0xc0);
            func_00282CC0(point, trail->offset, local);
            func_00282CC0(point, point, trail->impulse);
            qcopy(trail->velocities[count], local);
            point[3] = 0.005f;
            trail->ages[count] = 0;
            trail->count++;
        } else if (trail->landed[count - 1] == 1) {
            if (func_00282948(&trail->lifetime)) {
                trail->active = 0;
            } else {
                trail->colour = func_00283D38(0x00858585, 0x80858585,
                    trail->lifetime * 0.04f);
            }
        }
    }
    func_L00_002E6CF0(func_L04_00415E28, D_L04_001B0914);
}
