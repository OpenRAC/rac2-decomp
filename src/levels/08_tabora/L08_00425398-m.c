#include "include_asm.h"
#include "common.h"

extern float coll_find_ground_height_floor(void *position, float first, float second, float floor);
extern int GetCollHitMaterial(void);
extern float D_00189EA8;

/* Works out the ground heights under the object and keeps a floor height at least a little above a minimum. */
void moby_update_ground_probe(char *moby)
{
    float aim[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);

    qcopy(aim, moby + 0x10);
    aim[2] = aim[2] + 20.0f;
    *(float *)(vars + 0x1C4) = coll_find_ground_height_floor(aim, *(float *)(vars + 0x178) + 10.0f, *(float *)(vars + 0x178) - 3.0f, *(float *)(vars + 0x90));
    if (GetCollHitMaterial() == 0)
        *(float *)(vars + 0x1C4) = *(float *)(vars + 0x1C4) + 2.0f;
    {
        float height = *(float *)(vars + 0x1C4) + 6.5f;
        *(float *)(vars + 0x1C8) = height > D_00189EA8 ? height : D_00189EA8;
    }
}
