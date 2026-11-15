#include "include_asm.h"
#include "names.h"

/* func_002A9288 needs the grouped lq/sq profile (-frac2-qcopy -frac2-qcopy-barrier):
   retail forms each copy's addresses in registers before the lq/sq pair. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    float x;
    float y;
    float z;
    float size;
    TI128 colour;
} ShadowBlob;

extern ShadowBlob D_001BA640[];
extern TI128 D_001BAFC0;
extern int D_001B163C[] __attribute__((sda));
extern float func_002A89A8(void *, int, float);
extern int func_00278E78(void);
extern float func_00282C48(float);

/* Queues a ground shadow under the object (up to 32 a frame): its position, the
   ground height just above the floor, the shadow colour and a size that shrinks
   with the height above the ground (never below a quarter of scale). */
void func_002A9288(unsigned char *object, float scale)
{
    float ground;
    float size;

    if (object[0x31] == 0)
        return;
    if (D_001B163C[0] >= 32)
        return;
    *(TI128 *)&D_001BA640[D_001B163C[0]] = *(TI128 *)(object + 0x10);
    ground = ProbeGroundHeightBelow(object + 0x10, 0, 0.5f);
    if (GetCollHitMaterial() == 0)
        return;
    D_001BA640[D_001B163C[0]].z = ground + 0.025f;
    D_001BA640[D_001B163C[0]].colour = D_001BAFC0;
    size = (8.0f - FloatAbs(*(float *)(object + 0x18) - ground)) * 0.125f;
    if (size < 0.25f)
        size = 0.25f;
    D_001BA640[D_001B163C[0]].size = scale * size;
    D_001B163C[0]++;
}
