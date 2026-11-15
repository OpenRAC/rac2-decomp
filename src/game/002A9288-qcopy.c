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
extern float coll_probe_ground_height_below(void *, int, float);
extern int GetCollHitMaterial(void);
extern float math_fabs(float);

/* Queues a ground shadow under the object (up to 32 a frame): its position, the
   ground height just above the floor, the shadow colour and a size that shrinks
   with the height above the ground (never below a quarter of scale). */
void part_queue_ground_shadow(unsigned char *object, float scale)
{
    float ground;
    float size;

    if (object[0x31] == 0)
        return;
    if (D_001B163C[0] >= 32)
        return;
    *(TI128 *)&D_001BA640[D_001B163C[0]] = *(TI128 *)(object + 0x10);
    ground = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
    if (GetCollHitMaterial() == 0)
        return;
    D_001BA640[D_001B163C[0]].z = ground + 0.025f;
    D_001BA640[D_001B163C[0]].colour = D_001BAFC0;
    size = (8.0f - math_fabs(*(float *)(object + 0x18) - ground)) * 0.125f;
    if (size < 0.25f)
        size = 0.25f;
    D_001BA640[D_001B163C[0]].size = scale * size;
    D_001B163C[0]++;
}
