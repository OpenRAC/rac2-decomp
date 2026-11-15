#include "common.h"

/* -ffast-math gives retail's min.s for the radius; D_001B0954 is reached through $gp. */
typedef int DamageQuad __attribute__((mode(TI)));
typedef union { DamageQuad quad; float f[4]; } DamageVector;

typedef struct {
    DamageVector vector;
    char pad10[8];
    unsigned char type;
    unsigned char subtype;
    unsigned short id;
    int pad1C;
    int flag;
    char pad24[12];
} Damage330CA0;

typedef struct {
    char pad0[0x2290];
    char *owner;
} DamageHero;

typedef struct {
    char pad0[0x70];
    float value;
    char pad74[0x6C];
} DamageData;

extern float D_001B0954 __attribute__((sda));
extern char *D_001BF000[];
extern char g_hero_state[];
extern unsigned char g_item_slot_to_record[];
extern DamageData g_weapon_table[];

extern int coll_process_hit(float, void *, int, void *, int);
extern int moby_get_private_value_0(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern void StartAttachedEffect(void *, int, int);

/* Hurts every enemy and breakable thing near the object, pushing it away from the blast. It skips the player's own vehicle. */
void QueueRadialMobyImpacts(char *object)
{
    DamageVector delta;
    Damage330CA0 damage;
    int count;
    int i;
    char *target;
    float radius = *(float *)(*(char **)(object + 0x68) + 0x64);

    count = coll_process_hit(radius < D_001B0954 ? radius : D_001B0954, object + 0x10, 0, object, 0);
    for (i = 0; i < count; i++) {
        target = D_001BF000[i];
        if ((moby_get_private_value_0(target) || (*(unsigned short *)(target + 0x34) & 0x4000))
            && target != ((DamageHero *)g_hero_state)->owner) {
            FastVecSub(&delta, target + 0x10, object + 0x10);
            vec_scale_to_length(&delta, &delta, 1.0f);
            vec_scale_to_length(&damage, &damage, 1.0f);
            make_hit_descriptor(&damage, object, 0x810000, &delta, (g_weapon_table + g_item_slot_to_record[0x20])->value);
            damage.flag = 1;
            damage.vector.quad = delta.quad;
            damage.vector.f[3] = 5627.925f;
            damage.type = 5;
            damage.subtype = 3;
            damage.id = *(unsigned short *)(target + 0xAA);
            QueueMobyImpact(target, &damage);
            StartAttachedEffect(target, 0x4E, *(int *)(object + 0xB8));
        }
    }
}
