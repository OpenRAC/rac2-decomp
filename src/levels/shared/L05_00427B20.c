#include "include_asm.h"
#include "names.h"
typedef int Quad __attribute__((mode(TI)));
extern Quad D_L05_001BFB30;
/* Retail holds this table base and reads its texture pointer at+0x184. */
extern unsigned char D_L05_001FF240[];
extern void func_00282CC0(char *, char *, char *);
extern int func_00282948(int *);
extern int func_00278E78(void);
/* Bank contract matches the qualified declaration in 00274128.c:142 and Barlow 00422240.
 * Original C parameter order is unknown; a0/a1/a2/f12 inputs are unchanged. */
extern int func_00277258(char *, int, float, char *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_L05_00427E10(char *);
extern void func_0029F338(void *);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282D30(char *, char *, float);
extern float func_002A7940(void);
extern void func_002AF000(float *, float, float, float);
extern char *func_002BD8B0(char *, char *, unsigned int, unsigned int, int, int, float);

/* Move a directed effect, resolve contact and leave paired trail particles. */
void func_L05_00427B20(char *object) {
    struct { Quad previous, point, step, velocity; } local;
    char *state = *(char **)(object + 0x68);
    char *particle;
    unsigned char *textures;
    float size, limit, first, second;
    int i, contact;
    local.previous = *(Quad *)(object + 16);
    FastVecAdd(object + 16, object + 16, state);
    size = *(float *)(object + 0x2C) + 0.07f;
    *(float *)(object + 0x2C) = size;
    limit = *(float *)(*(char **)(object + 0x24) + 0x24);
    if (limit < size) *(float *)(object + 0x2C) = limit;
    if (!FastFloatHelperD((int *)(state + 0x18)) &&
        !(*(float *)(object + 16) < 2.0f) && !(1021.0f < *(float *)(object + 16)) &&
        !(*(float *)(object + 20) < 2.0f) && !(1021.0f < *(float *)(object + 20)) &&
        !(*(float *)(object + 24) < 2.0f) && !(1021.0f < *(float *)(object + 24))) {
        if (!FastFloatHelperD((int *)(state + 0x28))) {
            if (GetCollHitMaterial() == 6) goto trail;
            contact = 0;
            if (TestPointAgainstCollision(object + 16, 16, 1.0f, *(char **)(state + 0x20))) {
                contact = 1;
                *(Quad *)(object + 16) = D_L05_001BFB30;
            }
            if (!contact && !CollLine(&local.previous, object + 16, 16, *(char **)(state + 0x20), 0)) goto trail;

        }
        ExplodeAndDamageNearbyObjects(object);
    }
    MarkMobySpawned(object);
    return;
trail:
    local.point = local.previous;
    FastVecSub((char *)&local.step, object + 16, (char *)&local.previous);
    FastVecScale((char *)&local.step, (char *)&local.step, 0.333f);
    textures = D_L05_001FF240;
    i = 3;
    do {
        FastVecAdd((char *)&local.point, (char *)&local.point, (char *)&local.step);
        first = RandomAngle();
        second = RandomAngle();
        BuildSphericalOffset((float *)&local.velocity, 0.012500001f, first, second);
        particle = SpawnTrailingSparkParticle((char *)&local.point, (char *)&local.velocity, 0x4FFF0000, 0x1FFF0000, 10, 1, 80000.0f);
        if (particle) particle[2] = (*(unsigned char **)(textures + 0x184))[7];
        particle = SpawnTrailingSparkParticle((char *)&local.point, (char *)&local.velocity, 0x4FFF1010, 0x1FFF1010, 10, 1, 60000.0f);
        if (particle) particle[2] = (*(unsigned char **)(textures + 0x184))[7];
        i--;
    } while (i >= 0);
}
