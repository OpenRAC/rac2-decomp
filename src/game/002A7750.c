#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

typedef float f32;

/* The campaign: call-bearing bodies reproduced by the reconstructed toolchain
   (2.9-ee + refined gas) -- sd saves in 8-byte slots,
   no sibcall, the s32 return prototype determines v0 versus v1, and || chains
   with a shared exit. Measurements and evidence: docs/build/compiler-notes.md. */

/* func_002A77E0 : random draw bounded by the argument */
extern s32 func_001163B0(void);

extern f32 func_002A7940_5(void);

extern f32 func_002A7878_10(f32, f32);

extern void func_002AF000_2(s32, f32, f32, f32);

extern float Fc3394786_FUN_002A7940(void);

extern float Fc3394786_FUN_00283180(float);

extern float Fc3394786_FUN_00283198(float);

extern f32 func_00283180_3 (f32);

struct family_27f9_object {
    unsigned char reserved[248];
    float heading;
};

extern float F27f9be8e_FUN_00283BE0(float p, float x);

extern float F27f9be8e_FUN_00282C48(float t);

extern float F27f9be8e_FUN_00283B98(float x, float y);

typedef struct { f32 x,y,z,w; } MmiPoint;

/* The 16-byte store is written through a volatile quad pointer. Without the
   qualifier the compiler moves the quad store into the return's delay slot,
   which the retail build does not do; the qualifier is what keeps the store
   ahead of the return. The alternative idiom used by the RAC1 corpus is inline
   assembly, which the candidate gate refuses. */
/* The copy itself goes through a 128-bit integer type, not the aggregate:
   the reconstructed 2.9-ee compiler reaches lq/sq only through TImode (the
   aggregate path builds ld/sd pairs or a memcpy call). Same bytes as the
   retail (`lq $v0,0($a3); sq $v0,0($a0)`). */

typedef struct { int a, b, c, d; } __attribute__((aligned(16))) Quad16;

typedef int TI128 __attribute__((mode(TI)));

#ifndef RAC2_T_V4_F5621621C
#define RAC2_T_V4_F5621621C
typedef int V4_F5621621c __attribute__((mode(TI)));
#endif

extern float F5621621c_FUN_00283248(float a, float b);

extern float F5621621c_FUN_00283180(float a);

extern float F5621621c_FUN_00283198(float a);

extern void F5621621c_FUN_002A8E20(int v, void *rec);

#ifndef RAC2_T_VEC16_F5621621C
#define RAC2_T_VEC16_F5621621C
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_F5621621c;
#endif

#ifndef RAC2_T_NODE_F5621621C
#define RAC2_T_NODE_F5621621C
typedef struct {
    char pad[16];
    float f16;
    float f20;
} Node_F5621621c;
#endif

#ifndef RAC2_T_REC_F5621621C
#define RAC2_T_REC_F5621621C
typedef struct {
    float f0;
    float f4;
    float f8;
    float f12;
    int i16;
    int i20;
    signed char b24;
    signed char b25;
    unsigned short h26;
    float f28;
    int i32;
} Rec_F5621621c;
#endif

extern float Ff454dd77_FUN_00282C48(float a);

#ifndef RAC2_T_OBJ_FF454DD77
#define RAC2_T_OBJ_FF454DD77
typedef struct {
    float f0;
} Obj_Ff454dd77;
#endif

extern void F8cb0f4c0_FUN_002AA198(float *, float);

extern float F8cb0f4c0_FUN_00282C48(float);

#ifndef RAC2_T_V4_FC6BD459E
#define RAC2_T_V4_FC6BD459E
typedef int V4_Fc6bd459e __attribute__((mode(TI)));
#endif

extern void func_00282CF0_16(float *local, void *a1, void *a0);

extern float func_00282DF0_4(float *local);

extern void func_002AA198_2(void *a2, float r, float f1, float f2, float f3);

extern void func_00282F20_12(float *local, float *local2, float v);

extern void func_00282CC0_32(void *a0, void *a0b, float *local);

extern float func_00282C48_9(float t);

/* Switches a moby to a new state, remembers the previous state and resets its state timer. */
void moby_set_state(u8 *moby,s32 newState,s32 subState) {
 u8 prevState=moby[0x20];moby[0x20]=(u8)newState;moby[0x94]=prevState;*(short *)(moby+0x96)=0;
 moby[0xbe]&=~1;
 if(subState!=-1){moby[0x95]=(u8)subState;moby[0xbe]&=~2;}
}

/* Measured target: byte-identical across all 27 levels. */
/* Squares a number. */
f32 math_square(f32 value) { return value * value; }

/* Eases a 0 to 1 value so it starts fast and slows down near 1. */
f32 math_ease_out_quad(f32 t) {
 return 1.0f-(1.0f-t)*(1.0f-t);
}


/* Returns a random whole number from 0 up to but not including the limit. */
s32 math_random_int_below(s32 limit) {
    return (func_001163B0() >> 16 & 0x7fff) % limit;
}

/* Returns a random whole number between low and high, both included. */
s32 math_random_int_range(s32 low, s32 high) {
    return (func_001163B0() >> 16 & 0x7fff) % ((high - low) + 1) + low;
}

/* Returns a random decimal number between low and high. */
f32 math_random_float_range(f32 low, f32 high) {
    s32 rand = func_001163B0();
    return low + (f32)(rand >> 16 & 0x7FFF) * (high - low) * 3.0517578125e-05f;
}

/* Returns a random decimal number between low and high, randomly made negative half of the time. */
f32 math_random_signed_float_range(f32 low, f32 high) {
    s32 rand = func_001163B0();
    f32 result = low + (f32)(rand >> 16 & 0xFFF) * (high - low) * 0.000244140625f;
    if ((rand >> 16 & 1) != 0) result = -result;
    return result;
}

/* Returns a random angle in radians, roughly between minus pi/2 and plus pi/2. */
f32 math_random_angle(void) {
    return (f32)((func_001163B0() >> 16 & 0xfff) - 0x800) * 0.0015339808f;
}

/* draws two bounded random angles and an interval random value from the two float arguments, then forwards the pointer, the interval draw and both angles to a fourth callee */
/* Picks two random angles and a random distance, then passes them to another function along with the target. */
void part_spawn_random_direction_effect(s32 target, f32 low, f32 high) {
    f32 x = func_002A7940_5();
    f32 y = func_002A7940_5();
    f32 z = func_002A7878_10(low, high);
    func_002AF000_2(target, z, x, y);
}

/* Writes a random direction vector with a random length between low and high. */
void vec_random_direction(float *out, float low, float high)
{
    float length = math_random_float_range(low, high);
    float yaw = Fc3394786_FUN_002A7940();
    float pitch = Fc3394786_FUN_002A7940();
    float value;

    value = Fc3394786_FUN_00283180(yaw) * Fc3394786_FUN_00283198(pitch);
    value = value * length;
    out[0] = value;
    value = Fc3394786_FUN_00283198(yaw) * Fc3394786_FUN_00283198(pitch);
    value = value * length;
    out[1] = value;
    out[2] = Fc3394786_FUN_00283180(pitch) * length;
}

float cubic_hermite_scalar(float a, float b, float c, float d, float t) {
    float p = (d - c) - (a - b);
    float q = (a - b) - p;
    float t2 = t * t;
    float t3 = t2 * t;
    return p * t3 + q * t2 + (c - a) * t + b;
}

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

/* Computes a point on a smooth curve through four points, using t from 0 to 1. */
void vec_catmull_rom(f32 *out, f32 *a, f32 *b, f32 *c, f32 *d, float t)
{
    f32 t2;
    f32 t3;
    f32 k1, k2, k3;

    if (t == 0.0f) {
        qcopy(out, a);
        return;
    }
    if (t == 1.0f) {
        qcopy(out, b);
        return;
    }
    t2 = t * t;
    t3 = t2 * t;
    k3 = (d[0] - b[0]) - (c[0] - a[0]);
    k2 = (c[0] - a[0]) - k3;
    k1 = b[0] - c[0];
    out[0] = k3 * t3 + k2 * t2 + k1 * t + a[0];
    k3 = (d[1] - b[1]) - (c[1] - a[1]);
    k2 = (c[1] - a[1]) - k3;
    k1 = b[1] - c[1];
    out[1] = k3 * t3 + k2 * t2 + k1 * t + a[1];
    k3 = (d[2] - b[2]) - (c[2] - a[2]);
    k2 = (c[2] - a[2]) - k3;
    k1 = b[2] - c[2];
    out[2] = k3 * t3 + k2 * t2 + k1 * t + a[2];
    out[3] = 0.0f;
}

/* Eased scalar interpolation between a and b: returns a for t==0.0, b for t==1.0, otherwise a + (b-a)*((1-cos(t*pi))*0.5). */
/* Smoothly blends between two numbers, starting and ending gently. */
f32 math_cosine_blend (f32 a, f32 b, f32 t)
{
  f32 u;
  if (t == 0.0f)
    return a;
  if (t == 1.0f)
    return b;
  u = (1.0f - func_00283180_3 (t * 3.1415927f)) * 0.5f;
  return a + (b - a) * u;
}


/* Turns a heading toward a target angle with spring-like motion and a speed limit. */
float MobySpringTurn(struct family_27f9_object *object,
                                         float *velocity,
                                         float p1, float p2, float p3, float p4)
{
    float t;
    float v;
    float oldVelocity;
    float out;

    t = F27f9be8e_FUN_00283BE0(p1, object->heading);
    v = t * 6.3661971092224121093750e+00f;
    if (v > 1.0f) {
        v = 1.0f;
    } else {
        if (v < -1.0f) {
            v = -1.0f;
        }
    }
    oldVelocity = velocity[0];
    velocity[0] = oldVelocity + (p2 * v - p3 * oldVelocity);
    if (p4 != 0.0f) {
        if (velocity[0] > p4) {
            velocity[0] = p4;
        } else {
            if (velocity[0] < -p4) {
                velocity[0] = -p4;
            }
        }
    }
    if (F27f9be8e_FUN_00282C48(t) < velocity[0]) {
        velocity[0] = F27f9be8e_FUN_00282C48(t);
    } else {
        if (velocity[0] < -F27f9be8e_FUN_00282C48(t)) {
            velocity[0] = -F27f9be8e_FUN_00282C48(t);
        }
    }
    out = F27f9be8e_FUN_00283B98(object->heading, velocity[0]);
    object->heading = out;
    return out;
}

extern float mat_fast_helper_a(float, float);
/* Turns an object toward a target position using the spring turning function. */
float moby_turn_toward_position(struct family_27f9_object *object, float *target, float *value,
                   float speed, float damping, float limit)
{
    float angle = mat_fast_helper_a(target[4] - ((float *)object)[4],
                               target[5] - ((float *)object)[5]);
    return MobySpringTurn(object, value, angle, speed, damping, limit);
}


/* func_002A7EA0 is in 002A7EA0.c. */


/* func_002A8240 is defined in 002A8240.c. */


extern unsigned short *D_001EE5A0[];
extern char *D_001B1B5C __attribute__((sda));

/* Counts the entries of the 0x7FFF-masked id list at table[index] whose class
   byte (0x20) is not value; an entry with the high bit of the id set ends the
   list, and value -1 counts every entry with a class byte below 0x80. */
/* Counts the moby entries in a group list whose state differs from a given value. */
int moby_count_group_not_in_state(int index, int value) {
    unsigned short *list;
    unsigned short *entry;
    short key;
    char *object;
    int count;
    if (index == -1)
        return 0;
    list = D_001EE5A0[index];
    count = 0;
    if (list == 0)
        return 0;
    entry = list;
    do {
        object = (char *)(((*entry & 0x7FFF) << 8) + (unsigned int)D_001B1B5C);
        if (object[0x20] >= 0) {
            if (value == -1 || (unsigned char)object[0x20] != value)
                count++;
        }
        key = *entry++;
    } while (key >= 0);
    return count;
}

#define MACRO_ADDR __attribute__((section(".sdata")))

extern unsigned short *r1_D_L01_001ABFC0[];

extern char *r1_D_L01_00160058 MACRO_ADDR;

/* rac1-decomp src/overlays/shared/mobyutil_0026E8E0.c: func_L01_0026F040 */
// Set byte 0xBC of each entry in a negative-terminated index list.
/* Sets one byte on every moby in a group list. */
void moby_set_byte_on_group(int group, int value) {
    unsigned short *list = r1_D_L01_001ABFC0[group];
    unsigned short *p;
    if (list != 0) {
        p = list;
        do {
            r1_D_L01_00160058[(*p & 0x7FFF) * 256 + 0xBC] = value;
        } while (*(short *)p++ >= 0);
    }
}


extern unsigned char *D_001B1D40 MACRO_ADDR;
extern unsigned short *D_001B1D38 MACRO_ADDR;
extern short D_001B1D3C MACRO_ADDR;
extern int D_001B1B78 MACRO_ADDR;
extern int GetNextMobyInGroup(int *out, unsigned char *m, int includeInactive, int onlyInactive);

/* rac1-decomp src/overlays/shared/moby_ground_collision.c: get_first_moby_in_group */
// Starts the group cursor at the first moby of a group; when the state filter
// rejects it, advances to the next accepted moby.
/* Starts looping over the mobys of a group and returns the first one that passes the filter. */
int GetFirstMobyInGroup(int *out, int group, int includeInactive, int onlyInactive) {
    unsigned short *entry;
    unsigned char *m;
    int index;
    int inactive;

    if (group < 0 || D_001B1B78 < group) {
        *out = 0;
        return -1;
    }
    *out = 0;
    D_001B1D40 = 0;
    entry = D_001EE5A0[group];
    D_001B1D38 = entry;
    if (entry == 0) {
        return -1;
    }
    index = *entry & 0x7FFF;
    D_001B1D3C = index;
    m = (unsigned char *)D_001B1B5C + (index << 8);
    D_001B1D40 = m;
    *out = (int)m;
    inactive = (signed char)D_001B1D40[0x20] < 0;
    if (!includeInactive) {
        if (!onlyInactive && !inactive) goto found;
    } else if (!onlyInactive || inactive) {
        goto found;
    }
    return GetNextMobyInGroup(out, D_001B1D40, includeInactive, onlyInactive);
found:
    return 0;
}




/* Subtracts from the top byte of a packed number, stopping at 0, and says whether it reached 0. */
int moby_decrement_top_byte(int *packed, int amount) {
    int word = *packed;
    int count = (word >> 24) - amount;
    if (count < 0) count = 0;
    *packed = (word & 0xFFFFFF) | (count << 24);
    return count == 0;
}




extern float coll_probe_ground_height_below(void *, int, float);

/* Looks up the ground height under an object. */
float coll_get_ground_height_under_object(void *object) {
    return coll_probe_ground_height_below(object, 32, 0.5f);
}


/* Checks a point against a convex shape and returns the number of the first edge it lies outside, or 0 if inside. */
s32 coll_find_outside_edge_index(const f32 *point,const MmiPoint *poly,s32 count) {
    s32 i;
    for(i=0;i<count;i++) {
        f32 x=poly[i].x,y=poly[i].y;
        if((poly[(i+1)%count].x-x)*(point[1]-y)-(poly[(i+1)%count].y-y)*(point[0]-x)>0.0f) return i+1;
    }
    return 0;
}

/* Tells whether a point lies inside a flat polygon. */
int point_in_path_xy(float *point, float *verts, int count) {
    int inside = 0;
    int next = 0;
    int k;
    for (k = 0; k < count; k++) {
        float y1 = verts[k * 4 + 1];
        next++;
        if (next == count) next = 0;
        if ((y1 < point[1] && point[1] <= verts[next * 4 + 1]) || (verts[next * 4 + 1] < point[1] && point[1] <= y1)) {
            if (verts[k * 4] + (point[1] - verts[k * 4 + 1]) / (verts[next * 4 + 1] - verts[k * 4 + 1]) * (verts[next * 4] - verts[k * 4]) < point[0]) {
                inside = !inside;
            }
        }
    }
    return inside;
}


/* Fills in an effect record with two numbers and a scale, then resets it. */
void part_init_effect_record(char *record, int valueA, int valueB, float scale) { extern void vec_clear_128(void *); *(int *)(record + 0x10) = valueA; *(int *)(record + 0x14) = valueB; *(float *)(record + 0x1C) = scale; *(int *)(record + 0x20) = 0; vec_clear_128(record); }

/* Fills in an effect record with two numbers, a scale and a position copied from a source. */
void make_hit_descriptor(char *record, int valueA, int valueB, float scale, Quad16 *source) {
    *(int *)(record + 0x10) = valueA;
    *(int *)(record + 0x14) = valueB;
    *(float *)(record + 0x1C) = scale;
    *(int *)(record + 0x20) = 1;
    *(volatile TI128 *)record = *(TI128 *)source;
}


extern void moby_transform_joint_to_world(void *, int, float *);
extern int coll_sweep_from_object(void *, float, float *, int, float, float, int, int, int);

/* Reads the position of a bone on an object and uses it to run a hit test. */
int coll_test_hit_at_bone(float x, float y, float z, void *object, int bone, int mode, int first, int second, int third)
{
    float vector[4];
    moby_transform_joint_to_world(object, bone, vector);
    return coll_sweep_from_object(object, x, vector, mode, y, z, first, second, third);
}


typedef struct {
    u8 pad0[0x10];
    f32 pos[4];
    s32 i20;
    s32 flags;
    u8 b28;
    u8 b29;
    unsigned short h2A;
    f32 f2C;
    s32 i30;
    f32 f34;
    u8 *owner;
    s32 i3C;
} L_A8E20Entry;

typedef struct {
    f32 pos[4];
    s32 i10;
    s32 flags;
    u8 b18;
    u8 b19;
    unsigned short h1A;
    f32 f1C;
    s32 i20;
    f32 f24;
} L_A8E20Req;

extern void vec_clear_128(void *);
extern s32 g_collision_hit[];
extern L_A8E20Entry D_001BF200[];

/* Adds a hit effect to the queue for a moby, merging with its existing one if it is stronger. */
void QueueMobyImpact(u8 *moby, L_A8E20Req *request)
{
    s32 idx = g_collision_hit[5];
    s32 flags = 0;
    L_A8E20Entry *entry;

    if (moby[0xA8] != 0xFF) {
        L_A8E20Entry *oldEntry = &D_001BF200[moby[0xA8]];

        if (oldEntry->owner == moby) {
            if (oldEntry->f2C > request->f1C) {
                oldEntry->flags = oldEntry->flags | request->flags;
                return;
            }
            flags = oldEntry->flags;
        }
    }
    entry = &D_001BF200[idx];
    vec_clear_128(entry);
    qcopy(D_001BF200[idx].pos, request->pos);
    entry->flags = request->flags | flags;
    entry->i20 = request->i10;
    entry->b28 = request->b18;
    entry->b29 = request->b19;
    entry->h2A = request->h1A;
    entry->f2C = request->f1C;
    entry->f34 = request->f24;
    entry->i30 = request->i20;
    entry->owner = moby;
    entry->i3C = 0;
    moby[0xA8] = idx;
    g_collision_hit[5] = (idx + 1) & 0x3F;
}

/* func_002A8F70 is in 002A7750-records.c. */



extern int D_001B22D8 __attribute__((sda));
extern int D_001B22DC __attribute__((sda));
typedef struct { float x, y, height, radius; } HeightPlane;
extern HeightPlane D_001B22E0 __attribute__((sda));
extern int SampleSurfaceHeightMap(float *, float, float, float);
extern float math_fabs(float);
extern float vec_distance_xy(void *, void *);
extern void vec_copy_helper_a(void *);

/* Finds the ground height at a position, using the level floor or a special flat area. */
float coll_get_ground_height_at_position(float *position, void *direction)
{
    float result;
    if (D_001B22D8 != 0) {
        result = position[2];
        if (SampleSurfaceHeightMap(&result, position[0], position[1], position[2]) != 0)
            return result;
    }
    if (D_001B22DC != 0 && math_fabs(position[2] - D_001B22E0.height) < 0.5f &&
        vec_distance_xy(position, &D_001B22E0) < D_001B22E0.radius) {
        if (direction != 0)
            vec_copy_helper_a(direction);
        return D_001B22E0.height;
    }
    if (direction != 0)
        vec_copy_helper_a(direction);
    return position[2];
}

extern void multiply_quaternions(void *, void *, void *);
extern void build_axis_rotation_quaternion(void *, int, float);

/* Builds a rotation from three axis angles and combines them into one. */
void mat_build_rotation_from_angles(void *out, float *angles) {
    float rotZ[4];
    float rotY[4];
    float rotX[4];
    build_axis_rotation_quaternion(rotX, 0, angles[0]);
    build_axis_rotation_quaternion(rotY, 1, angles[1]);
    build_axis_rotation_quaternion(rotZ, 2, angles[2]);
    multiply_quaternions(out, rotX, rotY);
    multiply_quaternions(out, out, rotZ);
}

/* func_002A9288 uses the quadword-copy profile in 002A9288-qcopy.c. */

extern int D_001A8CA0[] __attribute__((sda));
extern float D_001BAFA0[];
extern float D_001BAFA8;
extern void scale_vector(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern int CollLine(void *, void *, int, void *, void *);

/* Checks the ground below a moby and sets its ground height and slide values. */
void moby_update_ground_check(char *moby)
{
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));

    if (D_001A8CA0[0] == 0) {
        if (*(float *)(moby + 0xE8) < 0.9f) {
            *(float *)(moby + 0x70) = 0.0f;
            *(float *)(moby + 0x74) = 0.0f;
            return;
        }
        qcopy(start, moby + 0x10);
        start[2] = start[2] - 16.0f;
        if (start[2] < 0.5f)
            start[2] = 0.5f;
        qcopy(end, moby + 0x10);
        end[2] = end[2] + 0.5f;
        if (CollLine(end, start, 0x22, 0, 0) != 0) {
            *(float *)(moby + 0x70) = D_001BAFA8 - *(float *)(moby + 0x18);
            *(float *)(moby + 0x74) = *(float *)(moby + 0xC) * 0.000244140625f;
        } else {
            *(float *)(moby + 0x70) = 0.0f;
            *(float *)(moby + 0x74) = 0.0f;
        }
    } else {
        scale_vector(start, moby, 0.0009765625f);
        FastVecScale(end, moby + 0xE0, -8.0f);
        FastVecAdd(end, start, end);
        if (CollLine(start, end, 0x22, 0, 0) != 0) {
            FastVecSub(normal, D_001BAFA0, moby + 0x10);
            *(float *)(moby + 0x70) = FastVecDot(normal, moby + 0xE0);
            *(float *)(moby + 0x74) = 0.2f;
            *(unsigned char *)(moby + 0xBD) = 0xFF;
        } else {
            *(float *)(moby + 0x70) = 0.0f;
            *(float *)(moby + 0x74) = 0.0f;
        }
    }
}

/* Runs the ground check for an object. */
void moby_run_ground_check(void *object) {
    moby_update_ground_check(object);
}

extern int FastTweenColor(int, int, float);

/* Calls another function with two values and an amount and returns its result. */
int moby_forward_two_values_and_amount(int first, int second, float amount) {
    return FastTweenColor(first, second, amount);
}





typedef struct Rec_002A96A0 {
    char pad0[4];
    short s4;
    char pad6[0x11];
    u8 b17;
    u8 *p18;
    short s1C;
} Rec_002A96A0;

typedef struct Src_002A96A0 {
    char pad0[0x20];
    u8 *p20;
    int f24;
    u8 b28;
    float f2C;
} Src_002A96A0;

extern Rec_002A96A0 *moby_get_private_value_0(s32);
extern char *moby_get_private_value_4(s32);
extern u8 moby_get_kind_slot(u8 *);

/* Tracks which target the player is aiming at and returns an updated strength value, with a short delay before switching. */
f32 moby_update_aim_target_strength(s32 id, Src_002A96A0 *src) {
    Rec_002A96A0 *rec = moby_get_private_value_0(id);
    f32 result = 0.0f;
    if (rec != 0) {
        u8 *target = rec->p18;
        if (target != 0) {
            u8 targetState = target[0x20];
            if (targetState != 0xFE) {
                if (targetState == 0xFD) {
                    rec->s1C = 0;
                    rec->p18 = 0;
                }
            } else {
                rec->s1C = 0;
                rec->p18 = 0;
            }
        }
        {
            short timer = rec->s1C;
            if (timer != 0) {
                rec->s1C = (unsigned short)rec->s1C + 1;
                if (timer >= 0x79) {
                    rec->p18 = 0;
                    rec->s1C = 0;
                }
            }
        }
        if (src != 0) {
            u8 *newTarget = src->p20;
            result = src->f2C;
            if (newTarget != 0) {
                if (rec->p18 != newTarget) {
                    rec->p18 = newTarget;
                    rec->b17 = moby_get_kind_slot(src->p20);
                    rec->s1C = 1;
                } else {
                    if (src->b28 == 9) {
                        if (rec->s1C < 0x3C) result = 0.0f;
                        else rec->s1C = 1;
                    } else {
                        if (rec->s1C < 10) result = 0.0f;
                        rec->s1C = 1;
                    }
                }
            }
            if ((f32)rec->s4 <= 1.0f && result > 0.0f && result < 1.0f) result = 1.0f;
            if (src->f24 & 0x100000) {
                u8 *slot = moby_get_private_value_4(id);
                if (slot != 0) slot[0x18] = 1;
            } else {
                u8 *slot = moby_get_private_value_4(id);
                if (slot != 0) slot[0x18] = 0;
            }
        }
    }
    return result;
}

/* Queues a hit effect for each object in a list, pushing each one away from a point. */
void moby_queue_knockback_for_nodes(void *owner, Vec16_F5621621c *src, int *nodes, int count,
                                        int t0, int t1, int t2, int t3,
                                        float f1, float f2, float f3)
{
    Vec16_F5621621c vec;
    Vec16_F5621621c *vp = &vec;
    Rec_F5621621c rec;
    int i;
    int *nodePtr;

    *(V4_F5621621c *)&vec = *(V4_F5621621c *)src;
    if (count <= 0) return;
    for (nodePtr = nodes, i = count; i != 0; i--, nodePtr++) {
        Node_F5621621c *node = (Node_F5621621c *)*nodePtr;
        float angle;
        if ((int)*nodePtr == t0) continue;
        rec.i16 = (int)owner;
        rec.h26 = *(unsigned short *)((char *)owner + 170);
        rec.i20 = t1;
        rec.f28 = f1;
        rec.i32 = t1;
        rec.b24 = t2;
        rec.b25 = t3;
        angle = F5621621c_FUN_00283248(node->f16 - vp->x, node->f20 - vp->y);
        rec.f0 = F5621621c_FUN_00283180(angle) * f2;
        rec.f4 = F5621621c_FUN_00283198(angle) * f2;
        rec.f8 = f3;
        rec.f12 = 5.6279248046875000000000e3f;
        F5621621c_FUN_002A8E20(*nodePtr, &rec);
    }
}

/* func_002A99A0 is in 002A99A0.c. */


/* Blends linearly between two numbers. */
f32 math_lerp_float(f32 a, f32 b, f32 t) { return a + (b - a) * t; }

/* Moves an angle part of the way toward a target angle. */
float math_move_angle_toward_target(float angle, float target, float factor)
{
    return F27f9be8e_FUN_00283B98(angle,
            F27f9be8e_FUN_00283BE0(target, angle) * factor);
}

/* Updates a spring speed value, clamping it to limits. */
void math_update_spring_velocity(Obj_Ff454dd77 *spring, float a, float b, float c, float d)
{
    if (Ff454dd77_FUN_00282C48(a) < spring->f0)
        spring->f0 = Ff454dd77_FUN_00282C48(a);
    else if (spring->f0 < -Ff454dd77_FUN_00282C48(a))
        spring->f0 = -Ff454dd77_FUN_00282C48(a);

    spring->f0 = spring->f0 + (b * a - c * spring->f0);
    if (0.0f < d) {
        if (d < spring->f0)
            spring->f0 = d;
        else if (spring->f0 < -d)
            spring->f0 = -d;
    }

    if (Ff454dd77_FUN_00282C48(a) < spring->f0)
        spring->f0 = Ff454dd77_FUN_00282C48(a);
    else if (spring->f0 < -Ff454dd77_FUN_00282C48(a))
        spring->f0 = -Ff454dd77_FUN_00282C48(a);
}

/* Moves a number toward a target by at most one step and returns the remaining distance. */
f32 ApproachValue(f32 *value, f32 target, f32 step) {
    f32 diff = target - *value;
    if (step < diff) diff = step;
    else if (diff < -step) diff = -step;
    *value = *value + diff;
    return Ff454dd77_FUN_00282C48(target - *value);
}

/* Moves a whole number toward a target by at most one step and returns the remaining distance. */
f32 math_step_int_toward_target(s32 *number, s32 target, s32 maxStep)
{
    s32 value;
    s32 step = target - *number;
    if (maxStep < step)
        step = maxStep;
    else if (step < -maxStep)
        step = -maxStep;
    value = *(volatile s32 *)number + step;
    *number = value;
    return (f32)subtract_integer_with_clamp(target - value);
}


/* Moves a value toward a goal with spring motion and snaps to it when close. */
float math_spring_float_to_goal(float *value, float *velocity, float f1, float f2,
                                         float f3, float f4)
{
    float goal = f1;
    float threshold = f4;
    float error;
    float absError;

    F8cb0f4c0_FUN_002AA198(velocity, goal - value[0]);
    error = goal - (value[0] + velocity[0]);
    value[0] = value[0] + velocity[0];
    absError = F8cb0f4c0_FUN_00282C48(error);
    threshold = threshold * 0.01f;
    if (absError < threshold) {
        value[0] = goal;
        velocity[0] = 0.0f;
        return velocity[0];
    }
    return error;
}

/* shared native family */
/* Moves a position toward a target with spring motion and snaps to it when close. */
float vec_spring_to_target(void *pos, void *target, void *speed, float f1, float f2, float f3)
{
    float delta[4];
    float dist;
    float absDist;

    func_00282CF0_16(delta, target, pos);
    dist = func_00282DF0_4(delta);
    func_002AA198_2(speed, dist, f1, f2, f3);
    func_00282F20_12(delta, delta, *(float *)speed);
    func_00282CC0_32(pos, pos, delta);
    dist = dist - *(float *)speed;
    absDist = func_00282C48_9(dist);
    if (!(absDist < f3 * 0.01f))
        return dist;
    *(V4_Fc6bd459e *)pos = *(V4_Fc6bd459e *)target;
    *(float *)speed = 0.0f;
    return *(float *)speed;
}

/* func_002AA548 is implemented in 002AA548.c. */

extern float fast_subtract_rotations(float, float);
extern float math_fabs(float);

/* Gives the shortest turn between two angles, going a chosen direction when asked. */
f32 math_shortest_angle_delta(float from, s32 direction, float to)
{
    f32 base = fast_subtract_rotations(from, to);

    if (direction == 0 || base * (f32)direction > 0.0f)
        return base;
    {
        f32 zero = 0.0f;

        if (math_fabs(base) <= 0.001745329471305012702941895f)
            return zero;
        if (base > zero)
            return base - 6.2831859588623046875f;
        return base + 6.2831859588623046875f;
    }
}
