#include "common.h"

typedef struct { u8 data[256]; } AttachObject;
extern AttachObject *D_L01_001B255C __attribute__((sda));
extern u8 *D_L01_001FE180[] NOT_SDA;
extern f32 func_00282E80(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282FB8(void *, void *, f32);
extern s32 func_002A8AF0(void *, void *, s32);
extern f32 func_002A7878(f32,f32);
extern f32 func_00283248(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern f32 func_00283B98(f32, f32);
extern void func_0029FCC0(void *, s32, void *);
extern void func_002AF000(void *, f32, f32, f32);
extern s32 func_002A8C28(void *, void *, f32, s32, f32, f32, s32, s32, s32);
extern s32 func_L01_003120A8(void *, void *, void *, f32, s32, f32, s32, s32, s32);
extern s32 func_001163B0(void);
extern s32 func_00283CF0(f32);
extern u8 *func_002BAA28(void *, void *, void *, u32, u32, s32, s32, s32, s32);


extern void func_L01_003DC8B8(u8 *, void *, void *);
extern void func_L01_003DC9E0(void *, void *);
extern void func_L01_003DC9A8(void **, s32 *);
extern s32 func_L01_00321178(void *, void *);
extern void func_L01_00318638(void *, void *, void *);

extern s32 func_310648();

extern f32 func_310580(f32 x, f32 y);

extern s32 func_310528(s32 a, s32 b);

extern f32 func_2E3A48(f32 x);

extern f32 func_2E3A60(f32 x);

extern void func_2E3470(void *a, void *b, void *c);

extern void func_32EF38(void *buf, s32 a1, s32 a2, s32 a3, f32 x, f32 y);

extern void func_00115484(void *buf, s32 value, s32 count);

extern s32 func_00277F48(f32 radius, void *pos, s32 flag, void *obj, s32 arg);

/* The level's table of the records the spawner looks through. */
extern u32 D_L01_001C3980[];

/* func_L01_003DA740 is in L01_003DA740-particles-g8.c. */

/* func_L01_003DAB98 is in L01_003DAB98-g8.c. */

/* func_L01_003DAE58 is in L01_003DAE58.c. */

/* Scatters the measured primitive around the object, a1 times. */

/* func_L01_003DBCB8 is defined in L01_003DBCB8-qcopy-barrier.c. */

/* func_L01_003DBF38 is defined in L01_003DBF38-qcopy-barrier.c. */

void func_L01_003DC078(u8 *obj, s32 skip) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 end[4] __attribute__((aligned(16)));
    f32 tmp[4] __attribute__((aligned(16)));
    f32 velocity[4] __attribute__((aligned(16)));
    f32 acceleration[4] __attribute__((aligned(16)));
    f32 particlePos[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    f32 angle, yaw, distance, height;
    u8 *particle;

    distance = func_00282E80(obj + 0x10, *(u8 **)(state + 0x2F0) + 0x10);
    height = *(f32 *)(*(u8 **)(state + 0x2F0) + 0x18) - *(f32 *)(obj + 0x18);
    angle = func_00283BE0(func_00283248(distance, height), *(f32 *)(obj + 0xF4));
    if (angle > 0.3490659f) angle = 0.3490659f;
    else if (angle < -0.3490659f) angle = -0.3490659f;
    angle = func_00283B98(angle, *(f32 *)(obj + 0xF4));
    yaw = *(f32 *)(obj + 0xF8);

    func_0029FCC0(obj, 0, pos);
    func_00282F20(tmp, obj + 0xC0, -0.4f);
    func_00282CC0(pos, pos, tmp);
    func_00282F20(tmp, obj + 0xE0, 0.3f);
    func_00282CC0(pos, pos, tmp);

    if (*(s16 *)(*(u8 **)(state + 0x2F0) + 0xAA) == 0xB1A) {
        func_002A8C28(obj, pos, 1.0f, 0x4000001, (f32)state[0x34], 1.0f, 0, 1, 0);
        return;
    }

    particle = *(u8 **)(state + 0x3F0);
    if (particle) {
        if (particle[0] == 2 && particle[1] != 0x80) {
            distance = func_00282E80(pos, particle + 0x10);
            if (*(f32 *)(state + 0x3F4) < distance) *(f32 *)(state + 0x3F4) = distance;
        } else {
            *(u8 **)(state + 0x3F0) = 0;
            *(f32 *)(state + 0x3F4) = 3.0f;
        }
        func_002AF000(end, *(f32 *)(state + 0x3F4), yaw, angle);
        func_00282CC0(end, end, pos);
        func_L01_003120A8(obj, pos, end, (f32)state[0x34], 0x4000001, 1.0f, 0, 1, 0);
        func_002A8C28(obj, end, 0.3f, 0x4000001, (f32)state[0x34], 1.0f, 0, 1, 0);
    }
    if (skip) return;

    {
        s32 i, count = 2, variant, life, size, duration;
        u32 color1, color2;
        u8 *spawned;

        velocity[3] = 0.2f;
        acceleration[3] = 1.0f;
        for (i = 0; i < count; i++) {
            variant = func_001163B0() & 1;
            color1 = 0x50608040;
            color2 = 0x10608040;
            if (!variant && (func_001163B0() & 1)) {
                color1 = 0x30304020;
                color2 = 0x30304020;
            }
            qcopy(particlePos, pos);
            particlePos[0] += func_002A7878(-0.18f, 0.18f);
            particlePos[1] += func_002A7878(-0.18f, 0.18f);
            particlePos[2] += func_002A7878(-0.18f, 0.18f);
            func_002AF000(velocity, 0.15f, yaw, angle);
            velocity[2] += func_002A7878(0.0075000003f, 0.009166667f);
            func_002AF000(acceleration, 0.008333334f,
                          func_00283B98(yaw, func_002A7878(-9.0f, 9.0f) * 0.017453294f), angle);
            acceleration[2] += func_002A7878(-0.030000001f, -0.03666667f);
            life = func_00283CF0(func_002A7878(2.0f, 4.0f));
            size = func_00283CF0(func_002A7878(20.0f, 24.0f));
            duration = func_00283CF0(func_002A7878(30.0f, 36.0f));
            spawned = func_002BAA28(particlePos, velocity, acceleration, color1, color2,
                                    life, size, duration, -1);
            if (spawned) {
                if (!*(u8 **)(state + 0x3F0)) *(u8 **)(state + 0x3F0) = spawned;
                if (variant) spawned[3] = 0x48;
            }
        }
    }
    {
        s32 i, count = 3, variant, life, size, duration;
        u32 color1, color2;
        u8 *spawned = 0;

        velocity[3] = 0.05f;
        acceleration[3] = 0.09f;
        for (i = 0; i < count; i++) {
            variant = func_001163B0() & 1;
            color1 = 0x8050FF30;
            color2 = 0x3050FF30;
            if (!variant && (func_001163B0() & 1)) {
                color1 = 0x80306000;
                color2 = 0x30304000;
            }
            qcopy(particlePos, pos);
            particlePos[0] += func_002A7878(-0.24f, 0.24f);
            particlePos[1] += func_002A7878(-0.24f, 0.24f);
            particlePos[2] += func_002A7878(-0.24f, 0.24f);
            func_002AF000(velocity, 0.16666667f,
                          func_00283B98(yaw, func_002A7878(-18.0f, 18.0f) * 0.017453294f), angle);
            velocity[2] += func_002A7878(0.0058333334f, 0.012500001f);
            func_002AF000(acceleration, 0.008333334f,
                          func_00283B98(yaw, func_002A7878(-4.0f, 4.0f) * 0.017453294f), angle);
            acceleration[2] += func_002A7878(-0.014f, -0.030000001f);
            life = func_00283CF0(func_002A7878(2.0f, 4.0f));
            size = func_00283CF0(func_002A7878(20.0f, 24.0f));
            duration = func_00283CF0(func_002A7878(100.0f, 120.00001f));
            spawned = func_002BAA28(particlePos, velocity, acceleration, color1, color2,
                                    life, size, duration, -1);
            if (spawned && variant) spawned[3] = 0x48;
        }
    }
}

/* func_L01_003DC838 is defined in L01_003DA740-g8.c (this unit has no $gp access for it). */

/* Marks the records of type 0xA26 the object finds and collects them in a1. */
void func_L01_003DC8B8(u8 *a0, void *a1, void *a2) {
    s32 i;
    s32 n;
    u32 **out = a1;
    s32 *count = a2;

    func_00115484(out, 0, 4);
    *count = 0;
    n = func_00277F48(3.0f, a0 + 0x10, 1, a0, 0);
    if (n <= 0)
        return;
    for (i = 0; i < n; i++) {
        if (D_L01_001C3980[i] == 0)
            continue;
        if (*(s16 *)(D_L01_001C3980[i] + 0xAA) != 0xA26)
            continue;
        *(s32 *)(D_L01_001C3980[i] + 0x9C) = 1;
        *(u8 *)(D_L01_001C3980[i] + 0xBC) = 1;
        out[*count] = D_L01_001C3980[i];
        *count = *count + 1;
        if (*count >= 16)
            return;
    }
}

void func_L01_003DC9A8(void **a0, s32 *a1) {
    s32 i;

    for (i = 0; i < *a1; i++) {
        *(s32 *)((u8 *)*a0 + 0x9C) = 0;
        a0++;
    }
}


void func_L01_003DC9E0(void *arg, void *fallback) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 matrix[16] __attribute__((aligned(16)));
    u8 *obj = arg;
    u8 *state = *(u8 **)(obj+0x68);
    u8 *target;
    u8 *path;
    s32 index = *(s32 *)(state+0x410);
    if (index != -1) {
        target = (u8 *)&D_L01_001B255C[index];
        if (!target) return;
        if (*(s16 *)(target+0xAA) == 0xA56) {
            if (func_00282E80(obj+0x10,target+0x10)>1.0f) {
                func_00282CF0(delta,obj+0x10,target+0x10);
                func_00282F20(delta,delta,1.0f);
                func_00282CC0(pos,target+0x10,delta);
            } else qcopy(pos,obj+0x10);
            if (pos[2] < *(f32 *)(target+0x18)+0.01f)
                pos[2] = *(f32 *)(target+0x18)+0.011f;
        } else if (*(s16 *)(target+0xAA) == 0xA53) {
            func_00283698(matrix,target+0xC0);
            func_00282CF0(delta,obj+0x10,target+0x10);
            func_002830C0(delta,delta,matrix);
            if (delta[0]>2.0f) delta[0]=2.0f;
            else if (delta[0]<-2.0f) delta[0]=-2.0f;
            if (delta[1]>5.0f) delta[1]=5.0f;
            else if(delta[1]<-5.0f) delta[1]=-5.0f;
            if (delta[2]<0.01f) delta[2]=0.01f;
            func_00283098(delta,delta,target+0xC0);
            func_00282CC0(pos,target+0x10,delta);
        } else qcopy(pos,obj+0x10);
        func_00282CF0(delta,pos,obj+0x10);
        func_00282FB8(delta,delta,0.10000000894069671631f);
        func_00282CC0(obj+0x10,obj+0x10,delta);
        if (*(f32 *)(obj+0x18)<pos[2]) *(f32 *)(obj+0x18)=pos[2]+0.001f;
    } else {
        s32 pathIndex=*(s32 *)(state+0x1FC);
        if(pathIndex!=-1) {
            path=D_L01_001FE180[pathIndex];
            if(path && !func_002A8AF0(obj+0x10,path+0x10,*(s32 *)path)) qcopy(obj+0x10,fallback);
        }
        {
            u8 *other = *(u8 **)(state + 0x248);
            if (other && (*(s16 *)(other + 0xAA) == 0xA56 ||
                          *(s16 *)(other + 0xAA) == 0xA53))
                *(s32 *)(state + 0x410) = (AttachObject *)other - D_L01_001B255C;
        }
    }
}





INCLUDE_ASM("asm/levels", func_L01_003DCF40);

/* func_L01_003DD3A0 is in L01_003DD3A0.c. */

/* func_L01_003DD6A8 */
extern void func_002AB8C0(void *, void *);

extern void func_00282978(void *);

extern s32 func_00282948(void *);

extern void func_002B0990(void *, void *, s32, s32, f32);

void func_L01_003DD6A8(u8 *a0)
{
    u32 v;
    u8 *p = *(u8 **)(a0 + 0x68);

    func_002AB8C0(a0, p + 0x100);
    v = *(u16 *)(a0 + 0x96);
    if (v <= 0xFFFE) {
        *(u16 *)(a0 + 0x96) = v + 1;
    }
    func_00282978(p + 0x3D8);
    func_00282948(p + 0x404);
    func_00282978(p + 0x3D6);
    v = *(s16 *)(p + 0x3DA);
    if (v != 0) {
        *(u16 *)(p + 0x3D6) = 0x168;
        *(s16 *)(p + 0x3DA) = 0;
    }
    func_002B0990(a0, p + 0x300, 1, 1, 1.8f);
}

/* func_L01_003E8ED8 is in L01_003E8ED8-g8.c. */

/* func_L01_003EC0C0 and func_L01_00405300 (L01_003DA740-pose.c): the moby
   eases from the pose it had when it started to entry `index` of the
   D_L01_001B264C table (0x80-byte entries). Struct (not cast) accesses matter:
   GCC only lets the table pointer's load pass the store of an angle when that
   store is a structure field, as retail's loads are scheduled. */
typedef struct {
    unsigned char pad00[0x30];
    float position[4];              /* 0x30 */
    unsigned char pad40[0x30];
    float rotation[4];              /* 0x70 */
} PoseRecord;
typedef struct {
    unsigned char pad00[0x20];
    float track[4];                 /* 0x20 */
    unsigned char pad30[0x2C];
    int flags;                      /* 0x5C */
    float start_position[4];        /* 0x60 */
    float start_rotation[4];        /* 0x70 */
    int index;                      /* 0x80 */
    float duration;                 /* 0x84 */
    float t;                        /* 0x88 */
    int link;                       /* 0x8C */
    int sound;                      /* 0x90 */
} PoseMotion;
typedef struct {
    unsigned char pad00[0x10];
    float position[4];              /* 0x10 */
    unsigned char state;            /* 0x20 */
    unsigned char pad21[0x13];
    unsigned short flags;           /* 0x34 */
    unsigned char pad36[0x32];
    PoseMotion *vars;               /* 0x68 */
    unsigned char pad6C[0x3C];
    unsigned char hit_slot;         /* 0xA8 */
    unsigned char padA9[0x13];
    unsigned char command;          /* 0xBC */
    unsigned char padBD[0x33];
    float rotation[4];              /* 0xF0 */
} PoseMoby;
extern PoseRecord *D_L01_001B264C MACRO_ADDR;
extern unsigned char D_00188660[];
extern float func_00283180(float);
extern void func_00282D30(void *, void *, float);
extern float func_002AA150(float, float, float);
extern void func_002A7750(void *, int, int);
extern void func_002AD6F0(void *, void *, void *, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);

/* Waits for its command byte, then starts its sound 0 with flag 4 (the slot
   kept in `sound`) and eases into its table pose; at the end stops that sound
   if the slot still belongs to it and plays its sound 1. */
void func_L01_003EC0C0(PoseMoby *m)
{
    float position[4], rotation[4], delta[4];
    PoseMotion *p = m->vars;
    float blend;

    qcopy(position, m->position);
    qcopy(rotation, m->rotation);
    switch (m->state) {
    case 0:
        p->sound = -1;
        p->t = 0.0f;
        p->flags |= 1;
        qcopy(p->start_position, m->position);
        qcopy(p->start_rotation, m->rotation);
        func_002A7750(m, 1, -1);
        break;
    case 1:
        if (m->command) {
            p->sound = func_002E5CF8(0, 4, m);
            func_002A7750(m, 2, -1);
        }
        m->hit_slot = 255;
        break;
    case 2:
        p->t += 1.0f / p->duration;
        if (p->t > 1.0f) p->t = 1.0f;
        blend = (1.0f - func_00283180(p->t * 3.1415927f)) * 0.5f;
        func_00282CF0(delta, D_L01_001B264C[p->index].position, p->start_position);
        func_00282D30(delta, delta, blend);
        func_00282CC0(m->position, p->start_position, delta);
        m->rotation[2] = func_002AA150(p->start_rotation[2], D_L01_001B264C[p->index].rotation[2], blend);
        m->rotation[1] = func_002AA150(p->start_rotation[1], D_L01_001B264C[p->index].rotation[1], blend);
        m->rotation[0] = func_002AA150(p->start_rotation[0], D_L01_001B264C[p->index].rotation[0], blend);
        if (p->t >= 1.0f) {
            int handle = p->sound;
            if (handle != -1) {
                unsigned char *slot = D_00188660 + handle * 0x70;
                if (*(void **)(slot + 0x88) == m && slot[0x74])
                    func_002E59F8(handle);
                p->sound = -1;
            }
            func_002E5CF8(1, 0, m);
            func_002A7750(m, 3, -1);
        }
        break;
    }
    if (m->state < 3) {
        func_00282CF0(delta, m->position, position);
        func_002AD6F0(p->track, delta, rotation, m->rotation);
    }
}

/* func_L01_003ECCF8 */
extern f32 func_00283B98(f32, f32);
extern void func_0029FCC0(void *, s32, void *);
extern f32 func_00283198(f32);
extern s32 func_00283CF0(f32);
extern s32 func_002E5DA0(s32, s32, void *, s32);
typedef struct { u8 pad[0x80]; f32 pos[4]; u8 pad90[0x2AC]; u8 *object; s32 active; } PlayerECC;
extern PlayerECC D_00189E20;
extern s32 D_001A79F0[] __attribute__((sda));
extern u8 D_0019B4A8[];
typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;
extern LevelSaveState D_L01_0021E4B0;

/* Pulses the object's grey colour until the player touches it (save nibble counter at
   D_0019B4A8) or its id is already collected; then marks it and its linked record active
   and plays sound 0x8A1 once. */
void func_L01_003ECCF8(u8 *obj) {
    f32 pos[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    f32 dist;
    s32 shade;
    u16 id;
    u32 color;
    if (!state) return;
    *(f32 *)(state + 4) = func_00283B98(*(f32 *)(state + 4), 0.10471977293491364f);
    if (obj[0x20] == 0) {
        func_0029FCC0(obj, 0, pos);
        dist = func_00282E80(D_00189E20.pos, pos);
        *(s32 *)(state + 8) = 0;
        if (D_00189E20.object == obj && D_00189E20.active && dist < 0.5f) {
            u16 objectId;
            objectId = *(u16 *)(obj + 0xB2);
            if (objectId & 1) {
                if (((D_0019B4A8[((s16)objectId >> 1) + (D_001A79F0[0] << 10)] >> 4) & 7) != 7)
                    D_0019B4A8[((s16)objectId >> 1) + (D_001A79F0[0] << 10)] += 16;
            } else {
                if ((D_0019B4A8[((s16)objectId >> 1) + (D_001A79F0[0] << 10)] & 7) != 7)
                    D_0019B4A8[((s16)objectId >> 1) + (D_001A79F0[0] << 10)] += 1;
            }
        }
        if (obj[0xB0] != 255) {
            s32 nibble;
            id = *(u16 *)(obj + 0xB2);
            if (D_L01_0021E4B0.collected[(s16)id] != 0) goto activate;
            nibble = D_0019B4A8[((s16)id >> 1) + (D_001A79F0[0] << 10)];
            if ((id & 1) ? ((nibble >> 4) & 7) : (nibble & 7)) {
activate:
                obj[0x20] = 1;
                obj[0xBC] = 1;
                if (*(s32 *)state != -1) D_L01_001B255C[*(s32 *)state].data[0xBC] = 1;
            }
        }
        shade = func_00283CF0((func_00283198(*(f32 *)(state + 4)) * 4.0f - 3.0f) * 128.0f);
        if (shade > 128) shade = 128;
        else if (shade < 32) shade = 32;
        color = (shade << 8) | 0x80000000;
        *(u32 *)(obj + 0x78) = (shade << 16) | color | shade;
    } else {
        if (!*(s32 *)(state + 8)) {
            func_002E5DA0(0, 0, obj, 0x8A1);
            *(s32 *)(state + 8) = 1;
        }
        *(u32 *)(obj + 0x78) = 0x80208010;
    }
}

/* func_L01_00405300 is in L01_003DA740-pose.c. */

/* func_L01_0040EED0 is in L01_0040EED0-g8.c. */

/* func_L01_0040F118 is in L01_0040F118-g8.c. */

void func_L01_0040F340(u8 *a0) {
    if (*(u8 *)(a0 + 0x20) == 0) {
        *(u8 *)(a0 + 0x30) = 0xFF;
        *(u8 *)(a0 + 0x20) = 1;
    }
}

/* func_L01_0040F360 is in L01_0040F360-g8.c. */

INCLUDE_ASM("asm/levels", func_L01_0040F5A8);

/* func_L01_0040F958 is in L01_003DA740-destruct.c. */

/* func_L01_00410AD0 is in L01_003DA740-f7-g8.c. */

/* func_L01_00412E00 is defined in L01_00412E00-flags-g8.c. */

/* func_L01_00412F18 is defined in L01_00412F18-g8.c. */

/* func_L01_00416440 is in L01_00416440-g8.c. */



/* func_L01_00416C08 is in L01_003DA740-rings-g8.c. */

/* func_L01_00416E78 is in L01_00416E78-camera.c. */

/* func_L01_004171C8 is in L01_004171C8-g8.c. */

void func_L01_0041C960(u8 *a0) {
    *(u16 *)(a0 + 0x34) |= 0x802;
}

INCLUDE_ASM("asm/levels", func_L01_0041C970);

INCLUDE_ASM("asm/levels", func_L01_0042C450);

INCLUDE_ASM("asm/levels", func_L01_0042C540);

INCLUDE_ASM("asm/levels", func_L01_0042C8D8);

/* func_L01_0042CE78 */
typedef struct L01_0042CE78_ENTRY {
    char pad0[0x38];
    u8 f38;
    u8 f39;
} L01_0042CE78_ENTRY;

typedef struct L01_0042CE78_OBJ {
    char pad0[0x84];
    s16 f84;
} L01_0042CE78_OBJ;

extern u8 *D_L01_001B1F04 __attribute__((sda));

extern s32 func_L00_004290C0(void *);

s32 func_L01_0042CE78(L01_0042CE78_OBJ *a0, u8 *a1)
{
    L01_0042CE78_ENTRY *e = *(L01_0042CE78_ENTRY **)(D_L01_001B1F04 + a0->f84 * 0x20 + 0x1C);
    s32 r;

    if (e->f39 != 0) {
        r = -1;
    } else if (e->f38 != 0) {
        r = 1;
    } else if (a1 != 0 && *(s16 *)(a1 + 0x7E) == 0) {
        r = 0;
    } else {
        if (func_L00_004290C0(a0) != 0) {
            goto one;
        }
        goto zero;
    one:
        r = 1;
        return r;
    zero:
        r = 0;
        return r;
    }
    return r;
}
