#include "common.h"
#include "include_asm.h"

extern int D_L07_001B0AE0 __attribute__((sda));

extern void func_0029F338(int);

/* Run the shared per-object pass once a level latch is set. */
void func_L07_003E61B8(int arg)
{
    if (D_L07_001B0AE0 != 0)
        func_0029F338(arg);
}

extern char *func_002AD0B0(char *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282C10(float);
extern float func_00282DB0(void *, void *);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern void func_00282F20(void *, void *, float);
extern void func_002AC9F8(void *, float);
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_002AD6F0(void *, void *, void *, void *);
extern float func_00282E80(void *, void *);
extern float D_L07_001B0C60 __attribute__((sda));
extern float D_L07_001B0C64 __attribute__((sda));
extern float D_L07_001B0C68 __attribute__((sda));
extern float D_L07_001B0C6C __attribute__((sda));
extern float D_L07_001B0C70 __attribute__((sda));
extern float D_L07_001B0C74 __attribute__((sda));
extern float D_L07_001B0C78 __attribute__((sda));
extern float D_L07_001B0C7C __attribute__((sda));
extern float D_L07_001B0C80 __attribute__((sda));
extern float D_L07_001B0C84 __attribute__((sda));
extern float D_L07_001B0C88 __attribute__((sda));

/* Steer the object's anchor toward its target (relative to the attached object when there is
   one) with a speed-limited, frame-scaled step, update the angular state, and return the
   remaining distance to the target (the caller compares it with 3.0). */
extern char *func_0029EFD0(int id);
extern void func_002B37E8(void *, void *);
extern float func_002A7940(void);
extern void func_002833F0(void *, void *);
extern void func_00282F70(void *, void *, float);
extern float func_L00_0031CDD0(float *a, float *b, float *out, float d, float e);
extern void func_00283698(void *, void *);
extern float D_L07_001B0E30 __attribute__((sda));
extern float D_L07_001B0E34 __attribute__((sda));
extern float D_L07_001B0E38 __attribute__((sda));

/* The spawned object and its state block, as far as func_L07_003F43E0 uses them. */
typedef struct {
    char pad00[0x10];
    float pos[4];          /* 0x10 */
    char pad20[0x04];
    char *pClass;          /* 0x24: class data; +0x24 is its base scale */
    char pad28[0x04];
    float scale;           /* 0x2C */
    char pad30[0x04];
    unsigned short flags;  /* 0x34 */
    char pad36[0x32];
    char *pVars;           /* 0x68 */
    char pad6C[0x54];
    float mtx[12];         /* 0xC0 */
    float rot[4];          /* 0xF0 */
} F43E0Moby;

typedef struct {
    float offset[4];       /* 0x00 */
    float vel[4];          /* 0x10 */
    char *owner;           /* 0x20 */
    char pad24[0x10];
    float x34;             /* 0x34 */
} F43E0Vars;

/* Spawn an object of class 0xE1D at POS with a random rotation and the class scale, then aim it
   at TARGET: velocity toward the target at the configured speed, with the vertical component of
   a ballistic arc under the configured gravity (both per 60 Hz frame). With an owner, the
   velocity and the offset from the owner are kept in the owner's frame. Returns the object. */
char *func_L07_003F43E0(char *a0, char *a1, char *a2, char *a3, float a4)
{
    F43E0Moby *obj = (F43E0Moby *)CreateMoby(0xE1D);

    if (obj != 0) {
        F43E0Vars *st;
        float speed, gravity;
        float buf[16];

        func_002B37E8(obj, a0);
        qcopy(obj->pos, a2);
        obj->rot[2] = func_002A7940();
        obj->rot[0] = func_002A7940();
        euler_rotation_basis(obj->mtx, obj->rot);
        obj->flags |= 0x100;
        st = (F43E0Vars *)obj->pVars;
        obj->scale = *(float *)(obj->pClass + 0x24) * D_L07_001B0E38;
        speed = D_L07_001B0E34 * (1.0f / 60.0f);
        gravity = D_L07_001B0E30 * (1.0f / 3600.0f);
        st->owner = a1;
        FastVecSub(st->vel, a3, obj->pos);
        func_00282F70(st->vel, st->vel, speed);
        st->vel[2] = func_L00_0031CDD0(obj->pos, (float *)a3, 0, speed, -gravity);
        st->vel[3] = gravity;
        st->x34 = a4;
        if (a1 != 0) {
            matrix_from_basis_rows(buf, a1 + 0xC0);
            matrix_mul_vec3(st->vel, st->vel, buf);
            FastVecSub(st->offset, obj->pos, a1 + 0x10);
            matrix_mul_vec3(st->offset, st->offset, buf);
        }
    }
    return (char *)obj;
}
