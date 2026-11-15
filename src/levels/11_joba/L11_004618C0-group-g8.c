#include "common.h"

/* -G8 unit: the moby table's base is read through $gp in the first two group walks. */
typedef struct JobaGroupMoby {
    char pad00[0x10];
    float position[4];     /* 0x10 */
    unsigned char state;   /* 0x20 */
    char pad21[3];
    char *classData;       /* 0x24 */
    char pad28[0xC];
    unsigned short flags;  /* 0x34 */
    char pad36[0x32];
    int *vars;             /* 0x68 */
    char pad6C[0x29];
    unsigned char active;  /* 0x95 */
    unsigned short timer;  /* 0x96 */
    int update;            /* 0x98 */
    char pad9C[0xC];
    unsigned char slot;    /* 0xA8 */
    char padA9;
    short type;            /* 0xAA */
    char padAC[4];
    unsigned char index;   /* 0xB0 */
    char padB1[0xF];
    float target[4];       /* 0xC0 */
} JobaGroupMoby;

extern char *D_L11_001B359C MACRO_ADDR;
extern short *D_L11_001FC420[];
extern int D_001A79F0;
extern unsigned char D_0019B2E8[];
extern unsigned char D_00188660[];
extern int func_L00_00324120(void *moby);
extern int func_002B38B8(void *moby);
extern int func_002E5CF8(int sound, int mode, void *moby);
extern void func_002E59F8(int handle);
extern float *func_002AB1F0(void *moby);
extern char *func_002A9640(void *moby, int mask, int arg);
extern void func_00282F20(void *out, void *in, float length);
extern void func_002B0A68(void *moby, int a1, float f12, float f13, float f14, float f15, void *vec, int a3);
extern void func_002AC728(void *moby, float f12, float f13, void *position, int a2);
extern void func_0029F338(void *moby);

#define GROUP_MEMBER(entry) ((JobaGroupMoby *)(D_L11_001B359C + (((entry) & 0x7FFF) << 8)))

#define HIDE_MEMBER(m) { (m)->flags = ((m)->flags & 0xEFFF) | 0x43; (m)->update = 0; }

/* The class-data read sits between the two flag writes, which stay separate halfword stores. */
#define ACTIVATE_MEMBER(m)                         \
    (m)->flags = ((m)->flags & 0xFFBE) | 0x1000;   \
    {                                              \
        int update = *(int *)((m)->classData + 0x10); \
        (m)->flags &= 0xFFFD;                      \
        (m)->update = update;                      \
    }

#define HIDE_GROUP(n, type1, type2, type3)                                        \
    {                                                                             \
        short *entries, *list;                                                    \
        if (data[n] == 255 || (entries = gGroupIdLists[data[n]]) == 0) goto done; \
        list = entries;                                                           \
        do {                                                                      \
            JobaGroupMoby *m = GROUP_MEMBER(*list);                               \
            if ((signed char)m->state >= 0) {                                     \
                if (m->type == type1) { HIDE_MEMBER(m); }                         \
                else if (m->type == type2) { HIDE_MEMBER(m); }                    \
                else if (m->type == type3) { HIDE_MEMBER(m); }                    \
            }                                                                     \
        } while (*list++ >= 0);                                                   \
    }

/* A live member: the query's result is read before the member is tested. */
#define MEMBER_ALIVE(m) ((m) && (m)->state != 254 && (m)->state != 253 && health > 0.0f)

static __inline__ void FinishGroupMoby(float *vec, JobaGroupMoby *self) {
    SpawnDebrisForMaskedParts(self, 255, 3.0f, 6.0f, 3.0f, 6.0f, vec, 255);
    SpawnExplosionWithSparks(self, 1.0f, 13.0f, self->position, -1);
    MarkMobySpawned(self);
}

/* Parent moby in vars[0], two member groups in vars[1] and vars[2], sound handle in vars[5]. */
/* Updates a group controller: when the hero is near, it wakes up its tribesmen and saur-beasts, plays its sound, and fades out when hit. */
void func_L11_0047A310(JobaGroupMoby *self) {
    float vec[4];
    int *data = self->vars;
    JobaGroupMoby *parent = (JobaGroupMoby *)(gMobyTable_L11 + (data[0] << 8));
    short *list;
    char *event;
    float health;

    if (self->state == 0) {
        self->state = 1;
        self->flags |= 0x800;
        parent->flags |= 0x41;
        HIDE_GROUP(1, 0xCF5 /* Joba Tribesman */, 0xCF6 /* moby class 3318 */, 0xD07 /* Jobian Saur-Beast */)
        HIDE_GROUP(2, 0xD07 /* Jobian Saur-Beast */, 0xCF6 /* moby class 3318 */, 0xCF5 /* Joba Tribesman */)
    }
    if (self->state == 1) {
        if (IsCurrentSelectedId(parent) || IsThirdPendingFlagSet(parent) ||
            (D_0019B2E8[self->index + (gCurrentMapIndex << 4)] & 0x80)) {
            self->timer = 0;
            self->state = 2;
            PlayMobySound(1, 0, self);
            {
                unsigned char *record = gSoundState + data[5] * 0x70;
                if (*(JobaGroupMoby **)(record + 0x88) != self || record[0x74] == 0) {
                    data[5] = PlayMobySound(2, 4, self);
                }
            }
            {
                short *entries;
                if (data[1] == 255 || (entries = gGroupIdLists[data[1]]) == 0) goto done;
                list = entries;
                do {
                    JobaGroupMoby *m = GROUP_MEMBER(*list);
                    health = *GetMobyPrivateValue0(m);
                    if (MEMBER_ALIVE(m) && m->type == 0xCF5 /* Joba Tribesman */) { m->active = 1; ACTIVATE_MEMBER(m); }
                    else if (MEMBER_ALIVE(m) && m->type == 0xCF6 /* moby class 3318 */) { m->active = 1; ACTIVATE_MEMBER(m); }
                    else if (MEMBER_ALIVE(m) && m->type == 0xD07 /* Jobian Saur-Beast */) { m->active = 1; ACTIVATE_MEMBER(m); }
                } while (*list++ >= 0);
            }
            {
                short *entries;
                if (data[2] == 255 || (entries = gGroupIdLists[data[2]]) == 0) goto done;
                list = entries;
                do {
                    JobaGroupMoby *m = GROUP_MEMBER(*list);
                    if ((signed char)m->state >= 0) {
                        if (m->type == 0xD07 /* Jobian Saur-Beast */) { m->active = 1; ACTIVATE_MEMBER(m); }
                        else if (m->type == 0xCF6 /* moby class 3318 */) { m->active = 1; ACTIVATE_MEMBER(m); }
                        else if (m->type == 0xCF5 /* Joba Tribesman */) { m->active = 1; ACTIVATE_MEMBER(m); }
                    }
                } while (*list++ >= 0);
            }
        }
        event = FindOwnedEffectSlot(self, 0x10000, 0);
        if (event) {
            vec_scale_to_length(vec, self->target, 0.4166666865f);
            if ((*(JobaGroupMoby **)(event + 0x20))->type == 0xDD9 /* moby class 3545 */) {
                short *entries, *list;
                PlayMobySound(0, 0, self);
                self->timer = 0;
                self->slot = 255;
                /* Each exit writes its calls out: jump2 shares only the last call between them. */
                if (data[1] == 255) { FinishGroupMoby(vec, self); return; }
                entries = gGroupIdLists[data[1]];
                if (entries == 0) { FinishGroupMoby(vec, self); return; }
                list = entries;
                do {
                    JobaGroupMoby *m = GROUP_MEMBER(*list);
                    if ((signed char)m->state >= 0) {
                        if (m->type == 0xCF5 /* Joba Tribesman */) { ACTIVATE_MEMBER(m); m->active = 1; }
                        else if (m->type == 0xCF6 /* moby class 3318 */) { ACTIVATE_MEMBER(m); m->active = 1; }
                        else if (m->type == 0xD07 /* Jobian Saur-Beast */) { ACTIVATE_MEMBER(m); m->active = 1; }
                    }
                } while (*list++ >= 0);
                if (data[2] == 255) { FinishGroupMoby(vec, self); return; }
                entries = gGroupIdLists[data[2]];
                if (entries == 0) { FinishGroupMoby(vec, self); return; }
                list = entries;
                do {
                    JobaGroupMoby *m = GROUP_MEMBER(*list);
                    if ((signed char)m->state >= 0) {
                        if (m->type == 0xD07 /* Jobian Saur-Beast */) { ACTIVATE_MEMBER(m); m->active = 1; }
                        else if (m->type == 0xCF6 /* moby class 3318 */) { ACTIVATE_MEMBER(m); m->active = 1; }
                        else if (m->type == 0xCF5 /* Joba Tribesman */) { ACTIVATE_MEMBER(m); m->active = 1; }
                    }
                } while (*list++ >= 0);
                SpawnExplosionWithSparks(self, 1.0f, 13.0f, self->position, -1);
                SpawnDebrisForMaskedParts(self, 255, 3.0f, 6.0f, 3.0f, 6.0f, vec, 255);
                MarkMobySpawned(self);
                return;
            }
            self->slot = 255;
        }
        self->slot = 255;
    }
    if (self->state == 2) {
        self->position[2] += 0.15f;
        if (++self->timer > 60) {
            if (data[5] != -1) {
                unsigned char *record = gSoundState + data[5] * 0x70;
                if (*(JobaGroupMoby **)(record + 0x88) == self && record[0x74]) {
                    StopSoundVoice(data[5]);
                }
            }
            data[5] = -1;
            self->state = 3;
            self->update = 0;
            self->flags = (self->flags | 0x41) & 0xEFFF;
        }
    }
done:
    return;
}
