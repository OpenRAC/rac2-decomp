#include "include_asm.h"
#include "common.h"

extern unsigned char D_00139574;
extern void func_00282D30(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_0038F3D8(void *);
extern void func_L00_0038E880(void *, void *, void *);


typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139568[];
extern char *D_0018C0B0 NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L02_001AC850 __attribute__((sda));
extern int D_L02_001B3D30 __attribute__((sda)), D_L02_001B3D38 __attribute__((sda));
extern Collision D_L02_001C0940;
extern Material D_L02_00264A70[];
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_L00_0038F178(void *);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern void func_002FD1B8(int, int, int, float, float, float, float);
extern void func_00282C88(void *);
extern char *func_00312D58(void *, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_002BFB38(void *, void *, int, int);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282948(char *);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);

extern void func_00282CC0(char *, char *, char *);

extern float func_00283180(float);
extern float func_00283198(float);

extern void func_002A7750(void *, int, int);

extern void func_002A7470(void *, int, int, int);

extern int func_00282978(short *);

extern int func_L02_0032E998(char *, int, float *, char *, short, char *, char *, float, float);

extern int func_002B50E0(char *, int, float);

extern void func_002AF1D0(char *, char *, int, int);

extern void func_002B0990(char *, char *, float, int, int);

extern int func_002A8C28(char *, void *, int, float, float, float, int, int, int);

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    int x, y, z, w;
} V16;

extern void func_31E6A0(char *, int, int);

extern void func_31E3C0(char *, int, int, int);

extern void func_31E2E8(char *, int, int);

extern void func_315578(char *, int, void *);

extern void func_2F2A78(void *, void *);

extern void func_2EF388(char *, char *, char *, char *, int);

extern void func_L02_003D1ED0(char *, TI128 *);

extern void func_L02_003D2390(char *);

extern void func_3FC1B0(char *, int);

extern void func_315348(char *, char *);

extern void func_2F1CC8(char *, int, int);

extern void func_316220(char *);

extern void func_3152D0(char *, int, char *);

extern void func_31EA58(char *, float, float);

extern void func_32B068(char *, int, char *, int, float, float, float, float);

extern void func_3FC248(char *, int, int);

extern void func_40D7B8(char *, int, void *);

extern int func_L02_003D18D8(char *);

extern float func_2F2168(char *, char *, float);

extern float func_2F2648(float, float);

extern float func_2F30E8(float, float);

extern int func_31E770(int);

extern void func_332710(float, float, float, float);

extern void func_316150(char *, int, int, int);

extern void func_316180(char *, int *, int *, int *);

extern float func_0029F530(char *);

extern void func_0029FCC0(char *, int, void *);

extern void func_L00_0031BDC0(void *, void *, void *, void *);

extern void func_00282CF0(void *, void *, void *);

extern float func_00282DF0(void *);

extern int func_002E5CF8(int, int, char *);

/* Stores the quadword the caller passes into the record at +0xF0. */
/* func_L02_003CADA8 is a near miss: nonmatching/levels/func_L02_003CADA8.c */
/* func_L02_003CADA8 is matched in L02_003CADA8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* Stores the quadword the caller passes into the record at +0xB0. */
/* func_L02_003D01F0 is a near miss: nonmatching/levels/func_L02_003D01F0.c */
/* func_L02_003D01F0 is matched in L02_003D01F0.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* Callers also supply a candidate pointer; this predicate only inspects arg0. */
int func_L02_003D1880(char *arg0, void *candidate) {
    int v = 0;
    if (*(int *)(*(char **)(arg0 + 0x68) + 0x2E4) != 0) {
        unsigned char c = *(unsigned char *)(arg0 + 0x20);
        if (c == 0x13 || c == 4 || *(unsigned char *)(arg0 + 0x95) == 4 ||
            c == 0x10 || c == 0x11 || c == 0x12)
            v = 1;
    }
    return v;
}

int func_L02_003CADF0(char *self, int arg1) {
    float out;
    char *p = *(char **)(self + 0x68);
    int r = func_L02_0032E998(self + 0x10, arg1, &out, p + 0x290, *(short *)(p + 0x3B6),
                              p + 0x3B8, p + 0x3BC, 0.0f, *(float *)(p + 0x50));
    func_002B50E0(self, arg1, out);
    return r;
}

void func_L02_003D14F8(char *self) {
    char *p = *(char **)(self + 0x68);
    if (*(int *)(p + 0x2E4) != 0) {
        func_002A7750(self, 4, 2);
        if (*(unsigned char *)(self + 0x43) != 0)
            func_002A7470(self, 0, 0, 0xA);
    } else {
        func_002A7750(self, 5, 2);
        if (*(unsigned char *)(self + 0x43) != 1)
            func_002A7470(self, 1, 0, 0xA);
    }
}

void func_L02_003D1430(char *self) {
    char *p = *(char **)(self + 0x68);
    func_00282978((short *)(p + 0x2F4));
    if (*(unsigned short *)(self + 0x96) < 0xFFFF)
        (*(unsigned short *)(self + 0x96))++;
    if (*(int *)(p + 0x2E4) != 0) {
        func_002AF1D0(self, *(char **)(p + 0x2E4), 2, 0);
        *(unsigned short *)(*(char **)(p + 0x2E4) + 0x34) &= 0xFFFD;
    }
    func_002B0990(self, p + 0x210, 3.5f, 4, 1);
    func_002A8C28(self, self + 0x10, 0x4000000, 1.5f, 1.0f, 1.0f, 0, 1, 0);
}

extern void *func_0029EFD0(int);

extern void func_002A0F48(char *);

void func_L02_003D1E40(char *self) {
    char *p = *(char **)(self + 0x68);
    *(char **)(p + 0x2E4) = func_0029EFD0(0x9D8);
    if (*(char **)(p + 0x2E4) != 0) {
        *(unsigned char *)(*(char **)(p + 0x2E4) + 0x30) = *(unsigned char *)(self + 0x30);
        *(unsigned short *)(*(char **)(p + 0x2E4) + 0x32) = *(unsigned short *)(self + 0x32);
        *(unsigned char *)(*(char **)(p + 0x2E4) + 0x31) = 1;
        *(unsigned long long *)(*(char **)(p + 0x2E4) + 0x38) =
            *(unsigned long long *)(self + 0x38);
        func_002A0F48(*(char **)(p + 0x2E4));
        *(int *)(*(char **)(p + 0x2E4) + 0x98) = 0;
        *(int *)(*(char **)(*(char **)(p + 0x2E4) + 0x68) + 0x3C) = 1;
    }
}

typedef struct {
    float x, y, z, w;
    float pad[4];
} L02_Record20;

typedef struct {
    float x, y, z, w;
    float pad[12];
} L02_Record40;

/* sda in this -G0 unit gives retail's macro load (`lui $r,%hi ; lw $r,%lo($r)`, one register); a plain
   declaration splits it into two registers and interleaves the loads. */
extern L02_Record20 *D_L02_001B3C14 __attribute__((sda));

extern L02_Record20 *D_L02_001B3C18 __attribute__((sda));

extern L02_Record40 *D_L02_001B3BD0 __attribute__((sda));

extern int D_L02_001B3BD4 __attribute__((sda));

/* Walks the two record tables and shifts each record's x by one period (2000, and 2048000 for the
   second table, whose limit is scaled by 1024): down while x > 0 for the records on the flagged side
   of the limit (z below it when flag is set), up while x < 0 for the others. */
void func_L02_002ED7B0(int flag, float limit) {
    L02_Record20 *p;
    int i;

    for (p = D_L02_001B3C14; p != D_L02_001B3C18; p++) {
        int sel = p->z < limit ? flag : !flag;

        if (sel) {
            if (p->x > 0.0f)
                p->x -= 2000.0f;
        } else {
            if (p->x < 0.0f)
                p->x += 2000.0f;
        }
    }
    limit *= 1024.0f;
    for (i = 0; i < D_L02_001B3BD4; i++) {
        L02_Record40 *q = &D_L02_001B3BD0[i];
        int sel = q->z < limit ? flag : !flag;

        if (sel) {
            if (q->x > 0.0f)
                q->x -= 2048000.0f;
        } else {
            if (q->x < 0.0f)
                q->x += 2048000.0f;
        }
    }
}

ASM_FUNC("asm/levels", func_L02_002F2B88);

/* func_L02_003007D8 is matched in L02_003007D8-g8.c (built with -G8 and -g). */

typedef struct {
    u8 pad00[0x34];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    u32 p68;
    u8 pad6C[0xAA - 0x6C];
    s16 type;
} L02_Mob;

typedef struct {
    u8 pad00[0x30];
    s32 mode;
    u8 pad34[0x44 - 0x34];
    s16 count;
    u8 pad46[0x18C - 0x46];
    L02_Mob *mobs[1];
} L02_MobList;

extern L02_MobList D_L02_001BE200;

/* sda in this -G0 unit gives the bare-symbol load: retail has it as `lui`/`lw` after the loop and,
   as the filler of the first branch's delay slot, as the one-instruction `$gp` form gas makes of
   it there. */
extern int D_001A79F0 __attribute__((sda));

extern void func_L00_002FC980(void);

extern void func_002E64A0(void *);

extern void func_L00_00326048(void *, void *, int, int, float);

extern void func_L00_002E6CF0(void *, void *);

extern void func_L02_003007D8(void *);

/* Walks the level's list of mobs (the same walk as func_L04_0031D630): the ones of type 0xE29 get
   the 0x800 flag, the ones of type 0xD54 are handed to func_002E64A0 and the ones of type 0xFA0
   that hold a 0x68 pointer give that pointer's block (from +0xC) to func_L00_00326048; the 0xD54
   test reads the type without the null check, as retail does. When the game state is 2 and the
   list's word at +0x30 is 2 as well, it then queues func_L02_003007D8. */
void func_L02_00300CE8(void) {
    int i;

    func_L00_002FC980();
    for (i = 0; i < D_L02_001BE200.count; i++) {
        L02_Mob *mob = D_L02_001BE200.mobs[i];

        if (mob != 0 && mob->type == 0xE29)
            mob->flags |= 0x800;
        if (mob->type == 0xD54)
            func_002E64A0(mob);
        if (mob != 0 && mob->type == 0xFA0 && mob->p68 != 0)
            func_L00_00326048(mob, (u8 *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.0610865355f);
    }
    if (D_001A79F0 == 2 && D_L02_001BE200.mode == 2)
        func_L00_002E6CF0(func_L02_003007D8, 0);
}

/* func_L02_0033C760 is matched in L02_0033C760.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_0033C8B8 is matched in L02_0033C8B8-g.c (built with -g). */

INCLUDE_ASM("asm/levels", func_L02_0035BD60);

/* func_L02_00363D78 is defined in L02_00363D78.c. */

ASM_FUNC("asm/levels", func_L02_00364A18);

ASM_FUNC("asm/levels", func_L02_00364D3C);

void func_L02_00397D10(unsigned char *obj) {
    struct {
        Vec old, velocity, normal;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
        Vec position, spread;
    } frame;
    char *ctx = *(char **)(obj + 0x68), *position = (char *)obj + 0x10;
    int i, lifetime;
    float angle, speed;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, ctx, position);
    func_002FEE70(*(int *)(ctx + 0x1C), ctx, 0);
    func_00300190(position, position);
    func_00300248(ctx, ctx);
    func_002FE880(position, ctx, 0.0030555557f);
    func_L00_0038F178(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)D_L02_00264A70 + D_00139568[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        if (!func_00278E78() && *(float *)(ctx + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            func_002FD1B8(D_L02_001B3D30, D_L02_001B3D38, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            func_00282C88(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = D_L02_001C0940.point.f[2];
            effect = func_00312D58(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                angle = func_002A7940();
                speed = func_002A7878(0.0f, 0.050000004f);
                frame.spread.f[0] = func_00283180(angle) * speed;
                frame.spread.f[1] = func_00283198(angle) * speed;
                frame.spread.f[2] = func_002A7878(0.050000004f, 0.10833334f);
                lifetime = func_002A7820(90, 120);
                func_002BFB38(&frame.position, spread, func_002A77E0(2), lifetime);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &D_L02_001C0940;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &D_L02_001C0940;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L02_001AC850 && *(short *)(model + 0xAA) != 0x336)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                func_00283028(&frame.velocity, ctx, &reread->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
                func_00282F20(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                func_00283028(&frame.velocity, ctx, &collision->normal);
                func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
                func_00282F20(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (obj[0xBC]) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        func_L00_0038DE70(obj, &frame.velocity, &frame.normal);
    }
}



void func_L02_00398128(char *obj) {
    struct {
        Vec velocity, normal, old, surface;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, position, ctx);
    func_002AFFD8(position, &frame.surface, 0);
    func_00282D30(&frame.surface, &frame.surface, 0.0003055556f);
    func_L00_0038F3D8(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L02_00264A70)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L02_001C0940;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L02_001C0940;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L02_001AC850 && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            func_00283028(&frame.velocity, ctx, &reread->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L02_001C0940;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            func_00283028(&frame.velocity, ctx, &collision->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 20)
            func_L00_0038DE70(obj, &frame.velocity, &frame.normal);
        else
            func_L00_0038E880(obj, &frame.velocity, &frame.normal);
    }
}



/* func_L02_003CA4A8 is defined in L02_003CA4A8-g8.c. */

/* func_L02_003CAE68 is matched in L02_003CAE68.c (built with -frac2-qcopy). */

/* func_L02_003CB090 is matched in L02_003CB090.c (built with -mno-split-addresses). */


extern u16 *D_L02_001FC060[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
extern u8 *D_L02_001B359C[] __attribute__((sda));
extern int D_L02_001B35B8[] __attribute__((sda));

/* Returns the first entity of the group's id list whose state byte is 0x17, or 0. */
u8 *func_L02_003CD5B0(int group) {
    u16 *p;
    u8 *e;

    for (p = D_L02_001FC060[group];
         (u8)group != 0xFF && group <= D_L02_001B35B8[0] && p != 0 &&
         ((s16)p[-1] >= 0 || p == D_L02_001FC060[group]);
         p++) {
        e = D_L02_001B359C[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] == 0x17)
            return e;
    }
    return 0;
}

/* Resets the actor's aim record and hands its descriptor to the object system. */
/* func_L02_003CD668 is defined in L02_003CD668.c. */



INCLUDE_ASM("asm/levels", func_L02_003D0408);

extern int func_00283CF0(float);

extern float func_002A7878(float, float);

extern float func_00282E48(void *, void *);

extern void func_002A93B0(char *);

extern void *func_002A9640(char *, int, int);

extern void func_002B0ED8(char *, char *, int);

extern void func_L02_003D1FA0(char *, int);

extern void func_L02_003D2488(char *, int, int);

extern void func_L02_003D1998(char *);

extern char D_L02_001BA500;

extern int func_002A77E0(int);


extern float func_00282E80(char *, char *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern int func_002A77E0(int);

/* Picks the idle variant the actor should play, from its distance and heading. */
int func_L02_003D1698(char *object) {
    char *state = *(char **)(object + 0x68);
    float dist;
    float ang;

    if (func_L02_003D18D8(object) != 0)
        return 0;
    dist = 100.0f;
    ang = 1.0f;
    if (*(char **)(state + 0x2E0) != 0) {
        dist = func_00282E80(object + 0x10, *(char **)(state + 0x2E0) + 0x10);
        ang = func_00283248(*(float *)(*(char **)(state + 0x2E0) + 0x10) - *(float *)(object + 0x10),
                            *(float *)(*(char **)(state + 0x2E0) + 0x14) - *(float *)(object + 0x14));
    }
    if (dist < 4.0f) {
        if (func_00283C80(ang, *(float *)(object + 0xF8)) < 0.26179942f) {
            if (func_002A77E0(5) == 0) {
                func_002A7750(object, 0xC, 5);
                if (*(u8 *)(object + 0x43) != 7)
                    func_002A7470(object, 7, 0, 0xA);
            } else if (*(int *)(state + 0x2E4) != 0) {
                func_002A7750(object, 0x12, 6);
                if (*(u8 *)(object + 0x43) != 0xD)
                    func_002A7470(object, 0xD, 8, 0xF);
            } else {
                func_002A7750(object, 0xF, 6);
                if (*(u8 *)(object + 0x43) != 0xA)
                    func_002A7470(object, 0xA, 8, 0xF);
            }
            return 1;
        }
    }
    return 0;
}

/* func_L02_003D18D8 is defined in L02_002ED7B0-g8.c (it reaches D_L02_001B359C through $gp). */

/* func_L02_003D1998 is matched in L02_002ED7B0-g8.c (built with -G8: it reads D_L02_001B35B8
   through $gp). */

/* Chooses the variant the actor plays from how far along the path it has come. */
void func_L02_003D1C38(char *object) {
    float start[4], end[4], closest[4], remaining[4], span[4];
    char *state;
    float time, fraction;

    time = func_0029F530(object);
    state = *(char **)(object + 0x68);
    if (19.0f <= time && time <= 31.0f) {
        func_0029FCC0(object, 0, start);
        func_0029FCC0(object, 1, end);
        func_L00_0031BDC0(closest, start, end, *(char **)(state + 0x2E0) + 0x10);
        func_00282CF0(remaining, closest, end);
        func_00282CF0(span, start, end);
        fraction = func_00282DF0(remaining);
        fraction /= func_00282DF0(span);
        if (fraction < 0.0f)
            fraction = 0.0f;
        if (fraction > 1.0f)
            fraction = 1.0f;
        if (func_002A8C28(object, closest, 0x10001, fraction * 0.35f + 0.15f,
                          (float)*(unsigned char *)(state + 0x34), 1.0f, 0, 1, 0) &&
            *(short *)(state + 0x2F8) == 0) {
            func_002E5CF8(5, 0, object);
            *(short *)(state + 0x2F8) = 1;
        }
        func_002A8C28(object, end, 0x10001, 0.5f,
                      (float)*(unsigned char *)(state + 0x34), 1.0f, 0, 1, 0);
    }
}

extern void func_002F1F70(void *, void *, void *);

extern void func_0032B468(char *, int, char *, char *, int, int, float *, void *, void *, float);

extern void func_003144D8(char *);

/* `sda` on an array of unknown size: each use is a fresh absolute `lui`/`addiu`, as retail has
   it, where a plain declaration is kept in a saved register across the calls. */
extern char D_L02_001A8F20[] __attribute__((sda));

/* When the actor is drawn and still holds its sub-object, builds a vector from 0.1 and 1/6,
   offsets it by the vector at D_L02_001A8F20 and passes both to func_0032B468 with the
   sub-object's +0x10 and +0xF0 records; then releases the sub-object in every case. The
   caller's quadword is copied to the stack (as retail does) and not read again. */
void func_L02_003D1ED0(char *self, TI128 *pos) {
    char *state = *(char **)(self + 0x68);
    float copy[4];
    float vec[4];

    *(TI128 *)copy = *pos;
    if (*(unsigned char *)(self + 0x31) != 0 && *(char **)(state + 0x2E4) != 0) {
        func_31EA58((char *)vec, 0.10000000894069672f, 0.16666667163372040f);
        func_002F1F70(vec, vec, D_L02_001A8F20);
        func_0032B468(self, 0x9D8, *(char **)(state + 0x2E4) + 0x10, *(char **)(state + 0x2E4) + 0xF0,
                    0, 0, vec, D_L02_001A8F20, D_L02_001A8F20, 0.0027777778450399637f);
    }
    func_003144D8(*(char **)(state + 0x2E4));
    *(char **)(state + 0x2E4) = 0;
}

/* Brings the actor into its armed state and re-registers its sub-object. */
void func_L02_003D2248(char *arg0, int arg1) {
    char *p = *(char **)(arg0 + 0x68);

    *(short *)(p + 0x2F6) = 0;
    *(float *)(p + 0x20) = (float)*(short *)(p + 0x24);
    func_332710(0.0055555556900799274f, 0.10333333909511566f, 0.0034906589426100254f,
                0.41887909173965454f);
    func_31E6A0(arg0, 3, 1);
    if (*(unsigned char *)(arg0 + 0x43) != 0)
        func_31E3C0(arg0, 0, 0, 0xA);
    *(int *)(arg0 + 0x98) = *(int *)(*(char **)(arg0 + 0x24) + 0x10);
    *(unsigned char *)(p + 0x6A) = 0;
    *(unsigned char *)(p + 0x2E) = 1;
    *(unsigned char *)(arg0 + 0x7F) = 0;
    *(unsigned char *)(arg0 + 0x31) = 1;
    *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) | 0x1000) & 0xFFB8;
    func_L02_003D1E40(arg0);
    *(short *)(p + 0x2FC) = arg1;
    *(short *)(p + 0x88) = 0;
    if (*(short *)(p + 0x50) != 0) {
        *(short *)(p + 0x50) = 0;
        func_316150(arg0, *(unsigned char *)(p + 0x54), *(unsigned char *)(p + 0x55),
                    *(unsigned char *)(p + 0x56));
        *(short *)(p + 0x52) = 1;
    }
    if (*(char **)(p + 0x2E4) != 0) {
        int a, b, c;

        func_316180(arg0, &a, &b, &c);
        func_316150(*(char **)(p + 0x2E4), a, b, c);
    }
}

extern void func_00282A60(char *, int, int);

extern void func_0029F978(char *, int, char *);

extern void func_002A7A00(char *, float, float);

extern void func_002B0A68(char *, int, char *, float, float, float, float, int);

extern void func_L02_003FC248(char *, int, int);

extern void func_L01_003E9CF8(char *, int, void *);

/* Re-arms the actor: passes a copy of its sub-object's +0x10 quadword to func_L02_003D1ED0 and,
   while the effect record at +0x290 is not yet set up (byte +0x291 clear), resets and registers
   it, scales it by 0.0001 and starts the effect; then clears the word at +0x98. A clear flag1
   also calls func_L02_003FC248; a clear flag2 hands func_L02_003D2390 to func_L01_003E9CF8,
   otherwise func_L02_003D2390 runs at once. */
void func_L02_003D2488(char *self, int flag1, int flag2) {
    char *state = *(char **)(self + 0x68);
    float vec[4];

    if (*(char **)(state + 0x2E4) != 0) {
        *(TI128 *)vec = *(TI128 *)(*(char **)(state + 0x2E4) + 0x10);
        func_L02_003D1ED0(self, (TI128 *)vec);
    }
    if (*(unsigned char *)(state + 0x291) == 0) {
        func_00282A60(state + 0x290, 0, 0x40);
        func_0029F978(self, 3, state + 0x290);
        *(float *)(state + 0x2B0) = *(float *)(state + 0x2B4) = *(float *)(state + 0x2B8) = 0.0001f;
        *(unsigned char *)(state + 0x292) = 1;
        func_002A7A00((char *)vec, 0.016666668f, 0.050000004f);
        func_002B0A68(self, 0x20, (char *)vec, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    *(int *)(self + 0x98) = 0;
    if (flag1 == 0)
        func_L02_003FC248(self, 0, -1);
    if (flag2 == 0)
        func_L01_003E9CF8(self, 0, func_L02_003D2390);
    else
        func_L02_003D2390(self);
}

extern float func_00283180(float);
extern float func_00283198(float);

/* Same body as func_L02_003F1A88, with this function's own callees. */
void func_L02_003D25C8(char *arg0, char *arg1) {
    char *state;
    float angle;
    float radius;

    angle = func_00283248(*(float *)(arg0 + 0x10) - *(float *)arg1,
                          *(float *)(arg0 + 0x14) - *(float *)(arg1 + 4));
    angle += func_002A7878(-0.78539824f, 0.78539824f);
    radius = func_002A7878(-2.0f, 2.0f) + 8.0f;
    state = *(char **)(arg0 + 0x68);
    qcopy(state + 0x2D0, arg1);
    *(float *)(state + 0x2D0) += radius * func_00283180(angle);
    *(float *)(state + 0x2D4) += radius * func_00283198(angle);
}
