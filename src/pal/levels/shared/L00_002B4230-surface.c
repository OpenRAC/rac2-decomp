#include "include_asm.h"

#include "common.h"
typedef struct {
    f32 x, y, z, w;
} Vec4458;
typedef struct {
    Vec4458 dir0;        
    u8 pad10[0xF0 - 0x10];
    Vec4458 velocity;    
    u8 pad100[0x270 - 0x100];
    s32 x270;
    u8 pad274[0x2290 - 0x274];
    s32 moby;            
    u8 pad2294[0x229C - 0x2294];
    s32 x229C;
    u8 pad22A0[0x22B4 - 0x22A0];
    u8 mode;             
} Hero4458;
typedef struct {
    u8 pad0[0x18];
    s32 x18;
    s32 hits;            
    u8 pad20[0x40 - 0x20];
    Vec4458 normal;      
} Hit4458;
extern Hero4458 D_00189E20;
extern Hit4458 D_L00_001BF200;
extern float func_L00_002D3A58(Vec4458 *);
extern void func_L00_002D36E0(Vec4458 *, float, float, float, int);
extern float func_00282E20(Vec4458 *);
extern void func_00282F20(Vec4458 *, Vec4458 *, float);
extern void func_L00_002D3B58(Vec4458 *, Vec4458 *, float);
extern void func_00282D30(Vec4458 *, Vec4458 *, float);
extern void func_00282CC0(Vec4458 *, Vec4458 *, Vec4458 *);
extern int func_002761F8(Vec4458 *, Vec4458 *, int, s32, int);
extern int func_00278E78(void);
extern float func_L00_002D3EA8(Vec4458 *);
extern float func_00282DB0(Vec4458 *, Vec4458 *);

/* While the hero moves, casts two short rays ahead of it (along its velocity, or along
 * the direction at +0x0 when nearly still or when forced): one from a point at the mode's
 * height, one from 0.3 of it reaching 1.4 times as far.  A slope of at least 50 degrees
 * under the first ray, or collision type 8 or 12 under the second, records the hit's word
 * at +0x18 in +0x270 and removes the part of the velocity at +0xF0 that runs into the
 * flattened surface normal. */
void func_PAL_L00_002B4380(int force)
{
    Vec4458 upper;
    Vec4458 upperEnd;
    Vec4458 lower;
    Vec4458 lowerEnd;
    float height;
    float reach;
    float slope;
    float dot;
    int type;

    if (func_L00_002D3A58(&D_00189E20.velocity) < 0.002f)
        return;
    height = 0.37f;
    reach = 0.5f;
    if ((unsigned int)(D_00189E20.x229C - 17) < 2) {
        height = 0.0f;
        reach = 0.7f;
    } else if (D_00189E20.mode == 1) {
        height = 0.35f;
        reach = 0.27f;
    }
    func_L00_002D36E0(&upper, 0.0f, 0.0f, height, 1);
    func_L00_002D36E0(&lower, 0.0f, 0.0f, height * 0.3f, 1);
    if (force || func_00282E20(&D_00189E20.velocity) < 0.01f) {
        func_00282F20(&upperEnd, &D_00189E20.dir0, reach);
        func_00282F20(&lowerEnd, &D_00189E20.dir0, reach * 1.4f);
    } else {
        func_L00_002D3B58(&upperEnd, &D_00189E20.velocity, 0.0f);
        func_00282F20(&upperEnd, &upperEnd, reach);
        func_00282D30(&lowerEnd, &upperEnd, 1.4f);
    }
    type = -1;
    func_00282CC0(&upperEnd, &upperEnd, &upper);
    func_00282CC0(&lowerEnd, &lowerEnd, &lower);
    if (func_002761F8(&lower, &lowerEnd, 2, D_00189E20.moby, 0) && D_L00_001BF200.hits > 0)
        type = func_00278E78();
    slope = 0.0f;
    if (func_002761F8(&upper, &upperEnd, 2, D_00189E20.moby, 0) && D_L00_001BF200.hits > 0)
        slope = func_L00_002D3EA8(&D_L00_001BF200.normal);
    if (slope >= 0.87266469f || type == 8 || type == 12) {
        D_00189E20.x270 = D_L00_001BF200.x18;
        func_L00_002D3B58(&D_L00_001BF200.normal, &D_L00_001BF200.normal, 0.0f);
        func_00282F20(&D_L00_001BF200.normal, &D_L00_001BF200.normal, 1.0f);
        dot = func_00282DB0(&D_L00_001BF200.normal, &D_00189E20.velocity);
        if (dot < 0.0f) {
            func_00282D30(&D_L00_001BF200.normal, &D_L00_001BF200.normal, -dot);
            func_00282CC0(&D_00189E20.velocity, &D_00189E20.velocity, &D_L00_001BF200.normal);
        }
    }
}
