#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void *part_alloc(int);

extern void moby_transform_joint_to_world(void *, int, void *);

extern void FastVecSub(void *, void *, void *);

extern void vec_scale_to_length(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern int FloatToInt(float);

extern int func_001163B0(void);

extern char D_L01_001B94C0[];

extern char *D_L01_001FF19C;

typedef struct {
    /* Retail stores and then reloads this pointer before querying the joint. */
    void *volatile f20;
    char pad3[2];
    short f26;
    void *f28;
} L01_00333FA8_TAIL;

typedef struct {
    char pad0[1];
    char f01;
    char f02;
    char f03;
    int f04;
    char f08;
    char f09;
    char pad2[2];
    float f0C;
    TI128 f10;
    L01_00333FA8_TAIL tail;
} L01_00333FA8_OBJ;

typedef struct {
    char pad[0x32];
    unsigned short group;
} L01_00333FA8_PARENT;

extern int D_L01_001A79F0 __attribute__((sda));

extern int D_L01_001BD1F4;

extern char D_L01_001BD1C0[];

extern void func_2E3738(void *, void *, float);

extern void func_2E3470(void *, void *, void *);

extern void func_2E2608(void *, int, int, unsigned int, int);

/* Builds the four-slice trail mesh for the ship's current colour. */
void ship_build_trail_mesh(char *trail_source) {
    char buffer[0x40];
    char end[0x10];
    int kind;
    int i;
    int offset;
    char *dest;
    char *state;

    if (D_L01_001A79F0 != 1)
        return;
    kind = -1;
    if ((unsigned)(D_L01_001BD1F4 - 0x2A0) < 0xB5)
        kind = 0x44;
    else if ((unsigned)(D_L01_001BD1F4 - 0x355) <= 0xBC)
        kind = 0x43;
    if (kind == -1)
        return;
    func_2E3738(end, trail_source + 0xC0, 0.05000000074505806f);
    offset = 0x30;
    dest = buffer;
    state = D_L01_001BD1C0;
    for (i = 3; i >= 0; i--) {
        qcopy(dest, (void *)(offset + *(int *)(state + 0x50) + 0x20));
        func_2E3470(dest, dest, end);
        offset -= 16;
        dest += 16;
    }
    func_2E2608(buffer, kind, 2, 0xFF808080u, 0);
}

/* func_L01_002F2570 is defined in L01_002F2570-g8.c. */

ASM_FUNC("asm/levels", func_L01_003042AC);

/* Spawns a small effect object tied to a parent object and places it at the parent or at one of its joints. */
void *CreateAttachedType57Effect(L01_00333FA8_PARENT *parent, void *owner, int joint_index, float size)
{
    L01_00333FA8_OBJ *obj;
    char buf0[16];
    char buf1[16];
    L01_00333FA8_TAIL *tail_part;
    int random_value;
    int group_bits;

    obj = part_alloc(0x57);
    if (obj != 0) {
        tail_part = &obj->tail;
        tail_part->f20 = parent;
        tail_part->f26 = joint_index;
        tail_part->f28 = owner;
        if ((short)joint_index == -1) {
            qcopy(&obj->f10, (char *)parent + 0x10);
        } else {
            moby_transform_joint_to_world(obj->tail.f20, (short)joint_index, buf0);
            FastVecSub(buf1, D_L01_001B94C0, buf0);
            vec_scale_to_length(buf1, buf1, 0.4f);
            FastVecAdd(&obj->f10, buf0, buf1);
        }
        obj->f08 = (char)func_001163B0();
        obj->f04 = (int)owner;
        random_value = FloatToInt(4.0f);
        group_bits = ((short)parent->group >> 5) * 16;
        obj->f03 = 0x48;
        obj->f01 = 0;
        *(float *)((char *)obj + 0xC) = size;
        obj->f09 = (char)(group_bits + random_value);
        obj->f02 = *D_L01_001FF19C;
    }
    return obj;
}


/* func_L01_002F2098 is defined in L01_002BEB90-g8.c (it needs a $gp-relative address). */

/* func_L01_00378A80 is defined in L01_002BEB90-g8.c (this unit has no $gp access for it). */
