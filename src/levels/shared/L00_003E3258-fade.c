#include "common.h"

typedef struct {
    char *object;
    unsigned char rgb[4];
    int unused;
    float fade;
    void (*callback)(char *);
    int rest[3];
} FadeEntry;

extern FadeEntry D_L00_0024EFC0[];
extern int D_L00_001B2B60[] __attribute__((sda));
extern float D_L00_001B065C __attribute__((sda));
extern int D_L00_001B0648[3] __attribute__((sda));
extern char *D_L00_001B0650[] __attribute__((sda));
extern void ref_L00_003E7C88_00(float *, float, float);
extern void func_L00_003E7E40(char *, void *, float);
extern void func_L00_003E80A8(int, char *);
extern void func_002A0488(char *, int, int, int);
extern void func_0029F338(char *);

/* Fades each object in the list. When a fade ends, it restores the object and runs its finish function, or deletes it, and drops it from the list. */
void func_L00_003E7C88(void) {
    int i;
    i = 0;
    if (i < gFadingMobyCount[0]) {
        FadeEntry *base = gFadingMobyList;
        FadeEntry *prev = (FadeEntry *)((char *)base - 32);
        float zero = 0.0f;
        do {
            float *fade = (float *)((char *)base + (i * 32 + 12));
            FadeEntry *entry = &gFadingMobyList[i];
            char *fadeObject = entry->object;
            if (*fade != zero) {
                ref_L00_003E7C88_00(fade, 0.0f, D_L00_001B065C * 0.01666666753590107f);
                SpawnModelTrailParticles(fadeObject, D_L00_001B0648, *fade);
                SetFadingObjectAlphaAndColor(i, D_L00_001B0650[0]);
            } else {
                int callbacks = (int)&base->callback;
                void (**callback)(char *) = (void (**)(char *))(i * 32 + callbacks);
                if (*callback) {
                    set_moby_color(fadeObject, entry->rgb[0], entry->rgb[1], entry->rgb[2]);
                    *(unsigned char *)(fadeObject + 35) = 128;
                    *(unsigned short *)(fadeObject + 52) &= ~2;
                    (*callback)(fadeObject);
                } else MarkMobySpawned(fadeObject);
                {
                    FadeEntry *end = (FadeEntry *)(gFadingMobyCount[0] * 32 + (int)prev);
                    gFadingMobyCount[0]--;
                    gFadingMobyList[i] = *end;
                }
            }
            i++;
        } while (i < gFadingMobyCount[0]);
    }
}
