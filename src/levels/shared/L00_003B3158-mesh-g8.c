#include "include_asm.h"
/* func_L00_003B4560 needs -G8 (sda reads) and -frac2-sticky-volatile-refs:
 * retail leaves the slot of `jal func_00280328` empty because reorg's forward
 * search stops at qcopy's volatile asm, as in func_L00_002A9460 and
 * func_L00_003C5310 (see tools/compiler/README.md).
 */
#include "common.h"
typedef unsigned int MeshQuad __attribute__((mode(TI)));
typedef union { MeshQuad q; float v[4]; } MeshVector;
typedef struct { float x, y, z; } MeshPoint;
extern float D_L00_001AF9DC __attribute__((sda)), D_L00_001AF9E0 __attribute__((sda)), D_L00_001AF9E4 __attribute__((sda));
extern int D_L00_001AF9D8 __attribute__((sda)), D_L00_001AF998 __attribute__((sda)), D_L00_001AF9D0 __attribute__((sda));
extern u32 D_L00_001AF9E8 __attribute__((sda));
extern int D_L00_001AF998_1[] __attribute__((sda)), D_L00_001AF9D0_1[] __attribute__((sda));
extern signed char D_L00_001AF9E8_1[] __attribute__((sda));
extern MeshVector D_L00_001B8DC0 NOT_SDA, D_0018A0E0 NOT_SDA;
extern float D_L00_00294CA0[][3], D_L00_00295390[][3];
extern float D_L00_00295660[][2], D_L00_00295B00[][2];
extern u32 D_L00_00295CE0[], D_L00_00295F30[];
extern u64 func_0027C878(int);
extern void func_002FC560(int,u64), func_00280328(void);
extern void func_00282CF0(void *,void *,void *), func_00282F20(void *,void *,float), func_00282DD8(void *,void *,void *), func_002830C0(void *,void *,void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00281810(int,void *,int,void *,int);
static inline void MeshStorePoint(MeshPoint *point, MeshVector *value)
{
    point->x = value->v[0];
    point->y = value->v[1];
    point->z = value->v[2];
}
void func_L00_003B4560(unsigned char *object, float opacity)
{
    MeshVector transform[4];
    MeshPoint positions[148];
    float uv[148][2];
    MeshVector temp;
    int alpha;
    unsigned char *origin;
    D_L00_001AF9DC += D_L00_001AF9E0;
    if (D_L00_001AF9DC >= 7.0f) D_L00_001AF9DC -= 7.0f;
    { u64 texture = func_0027C878(D_L00_001AF9D8);
      origin = object + 0x10;
      func_002FC560(6,texture); }
    func_002FC560(0x42,0x8000000048ULL);
    func_002FC560(8,0);
    func_002FC560(0x14,0xFF9000000260ULL);
    func_00280328();
    func_00282CF0(&transform[0],&D_L00_001B8DC0,origin);
    func_00282F20(&transform[0],&transform[0],1.0f);
    func_00282DD8(&transform[1],&transform[0],&D_0018A0E0);
    func_00282F20(&transform[1],&transform[1],-1.0f);
    func_00282DD8(&transform[2],&transform[1],&transform[0]);
    qcopy(&transform[3], origin);
    {
    int i;
    for (i=0;i<148;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = D_L00_00294CA0[i][1] * D_L00_001AF9E4;
        temp.v[2] = D_L00_00294CA0[i][0] * D_L00_001AF9E4;
        temp.v[3] = 1.0f;
        func_002830C0(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = D_L00_00295660[i][1] + D_L00_001AF9DC;
        uv[i][1] = D_L00_00295660[i][0];
        if (D_L00_00295CE0[i] & 0xFF000000) {
            alpha=func_00283CF0(func_00283CE0(D_L00_001AF9E8_1[7])*opacity);
            if (alpha < 1) alpha=1;
            alpha <<= 24;
            alpha |= D_L00_001AF9E8;
            D_L00_00295CE0[i] = alpha;
        } else D_L00_00295CE0[i] = D_L00_001AF9E8;
    }
    func_00281810(D_L00_001AF998,positions,D_L00_001AF9D0,uv,1);
    }
    {
    int i;
    for (i=0;i<60;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = D_L00_00295390[i][1] * D_L00_001AF9E4;
        temp.v[2] = D_L00_00295390[i][0] * D_L00_001AF9E4;
        temp.v[3] = 1.0f;
        func_002830C0(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = D_L00_00295B00[i][1] + D_L00_001AF9DC;
        uv[i][1] = D_L00_00295B00[i][0];
        if (D_L00_00295F30[i] & 0xFF000000) {
            alpha=func_00283CF0(func_00283CE0(D_L00_001AF9E8_1[7])*opacity);
            if (alpha < 1) alpha=1;
            alpha <<= 24;
            alpha |= D_L00_001AF9E8;
            D_L00_00295F30[i] = alpha;
        } else D_L00_00295F30[i] = D_L00_001AF9E8;
    }
    func_00281810(D_L00_001AF998_1[1],positions,D_L00_001AF9D0_1[1],uv,1);
    }
    {
    int i;
    for (i=0;i<148;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = -D_L00_00294CA0[i][1] * D_L00_001AF9E4;
        temp.v[2] = D_L00_00294CA0[i][0] * D_L00_001AF9E4;
        temp.v[3] = 1.0f;
        func_002830C0(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = D_L00_00295660[i][1] + D_L00_001AF9DC;
        uv[i][1] = D_L00_00295660[i][0];
    }
    func_00281810(D_L00_001AF998,positions,D_L00_001AF9D0,uv,1);
    }
    {
    int i;
    for (i=0;i<60;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = -D_L00_00295390[i][1] * D_L00_001AF9E4;
        temp.v[2] = D_L00_00295390[i][0] * D_L00_001AF9E4;
        temp.v[3] = 1.0f;
        func_002830C0(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = D_L00_00295B00[i][1] + D_L00_001AF9DC;
        uv[i][1] = D_L00_00295B00[i][0];
    }
    func_00281810(D_L00_001AF998_1[1],positions,D_L00_001AF9D0_1[1],uv,1);
    }
    {
    int i;
    for (i=0;i<148;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = D_L00_00294CA0[i][1] * D_L00_001AF9E4;
        temp.v[2] = -D_L00_00294CA0[i][0] * D_L00_001AF9E4;
        temp.v[3] = 1.0f;
        func_002830C0(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = D_L00_00295660[i][1] + D_L00_001AF9DC;
        uv[i][1] = D_L00_00295660[i][0];
    }
    func_00281810(D_L00_001AF998,positions,D_L00_001AF9D0,uv,1);
    }
    {
    int i;
    for (i=0;i<60;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = D_L00_00295390[i][1] * D_L00_001AF9E4;
        temp.v[2] = -D_L00_00295390[i][0] * D_L00_001AF9E4;
        temp.v[3] = 1.0f;
        func_002830C0(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = D_L00_00295B00[i][1] + D_L00_001AF9DC;
        uv[i][1] = D_L00_00295B00[i][0];
    }
    func_00281810(D_L00_001AF998_1[1],positions,D_L00_001AF9D0_1[1],uv,1);
    }
    {
    int i;
    for (i=0;i<148;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = -D_L00_00294CA0[i][1] * D_L00_001AF9E4;
        temp.v[2] = -D_L00_00294CA0[i][0] * D_L00_001AF9E4;
        temp.v[3] = 1.0f;
        func_002830C0(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = D_L00_00295660[i][1] + D_L00_001AF9DC;
        uv[i][1] = D_L00_00295660[i][0];
    }
    func_00281810(D_L00_001AF998,positions,D_L00_001AF9D0,uv,1);
    }
    {
    int i;
    for (i=0;i<60;++i) {
        temp.v[0] = 0.0f;
        temp.v[1] = -D_L00_00295390[i][1] * D_L00_001AF9E4;
        temp.v[2] = -D_L00_00295390[i][0] * D_L00_001AF9E4;
        temp.v[3] = 1.0f;
        func_002830C0(&temp,&temp,transform);
        MeshStorePoint(&positions[i], &temp);
        uv[i][0] = D_L00_00295B00[i][1] + D_L00_001AF9DC;
        uv[i][1] = D_L00_00295B00[i][0];
    }
    func_00281810(D_L00_001AF998_1[1],positions,D_L00_001AF9D0_1[1],uv,1);
    }
}
