#include "include_asm.h"
#include "names.h"
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;
extern void func_002FDBD8_2(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void moby_apply_active_effect_pal(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_2(1.0f, context, context->vector_10, 0);
    }
}

#include "common.h"
extern void BuildObjectAttachmentTransforms();
extern void moby_update_attached_transforms(unsigned char *, unsigned char *);
extern float FastAddRotations(float, float);

/* Per-frame update of an object that follows attached transforms and spins about one axis (PAL: 50 Hz rate). */
void tracked_state_update_pal(unsigned char *moby) {
    unsigned char *self = moby;
    unsigned char *state = *(unsigned char **)(self + 0x68);
    switch (self[0x20]) {
    case 0:
        if (*(long long *)state == -1) {
            break;
        }
        {
            unsigned char stamp = 0xFF;
            *(unsigned char *)(self + 0x30) = stamp;
        }
        BuildObjectAttachmentTransforms(self, state + 0x30, 0x64, *(int *)(state + 4), *(int *)state, -1, 7, 0);
        state[0xC5A] = 1;
        self[0x20] = 1;
        break;
    case 1:
        *(float *)(self + 0xF4) = FastAddRotations(
            *(float *)(self + 0xF4), *(float *)(state + 8) * 0.0003490659f);
        moby_update_attached_transforms(self, state + 0x30);
        break;
    }
}
