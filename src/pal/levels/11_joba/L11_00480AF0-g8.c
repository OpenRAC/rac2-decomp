#include "include_asm.h"

#include "common.h"
typedef struct JobaGroupMoby {
    char pad00[0x10];
    float position[4];      
    unsigned char state;    
    char pad21[3];
    char *classData;        
    char pad28[0xC];
    unsigned short flags;   
    char pad36[0x32];
    int *vars;              
    char pad6C[0x29];
    unsigned char active;   
    unsigned short timer;   
    int update;             
    char pad9C[0xC];
    unsigned char slot;     
    char padA9;
    short type;             
    char padAC[4];
    unsigned char index;    
    char padB1[0xF];
    float target[4];        
} JobaGroupMoby;
extern char *g_moby_l11_table MACRO_ADDR;
extern short *g_group_id_lists[];
extern int g_current_map_index;
extern unsigned char g_moby_group_flags[];
extern unsigned char g_sound_state[];
extern int hero_is_current_selected_id(void *moby);
extern int flag_is_third_pending_set(void *moby);
extern int PlayMobySound(int sound, int mode, void *moby);
extern void snd_stop_voice(int handle);
extern float *moby_get_private_value_0(void *moby);
extern char *part_find_owned_effect_slot(void *moby, int mask, int arg);
extern void vec_scale_to_length(void *out, void *in, float length);
extern void part_spawn_masked_debris_pal(void *moby, int a1, float f12, float f13, float f14, float f15, void *vec, int a3);
extern void part_spawn_explosion_with_sparks_pal(void *moby, float f12, float f13, void *position, int a2);
extern void moby_mark_spawned(void *moby);
#define GROUP_MEMBER(entry) ((JobaGroupMoby *)(D_L11_001B359C + (((entry) & 0x7FFF) << 8)))
#define HIDE_MEMBER(m) { (m)->flags = ((m)->flags & 0xEFFF) | 0x43; (m)->update = 0; }
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
        if (data[n] == 255 || (entries = D_L11_001FC420[data[n]]) == 0) goto done; \
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
#define MEMBER_ALIVE(m) ((m) && (m)->state != 254 && (m)->state != 253 && health > 0.0f)
/* Fades out the group controller with a burst of sparks and removes it. */
static __inline__ void FinishGroupMoby(float *vec, JobaGroupMoby *self) {
    part_spawn_masked_debris_pal(self, 255, 3.0f, 6.0f, 3.0f, 6.0f, vec, 255);
    part_spawn_explosion_with_sparks_pal(self, 1.0f, 13.0f, self->position, -1);
    moby_mark_spawned(self);
}

/* Parent moby in vars[0], two member groups in vars[1] and vars[2], sound handle in vars[5]. */
void moby_group_trigger_update_pal(JobaGroupMoby *self) {
    float vec[4];
    int *data = self->vars;
    JobaGroupMoby *parent = (JobaGroupMoby *)(g_moby_l11_table + (data[0] << 8));
    short *list;
    char *event;
    float health;

    if (self->state == 0) {
        self->state = 1;
        self->flags |= 0x800;
        parent->flags |= 0x41;
        HIDE_GROUP(1, 0xCF5, 0xCF6, 0xD07)
        HIDE_GROUP(2, 0xD07, 0xCF6, 0xCF5)
    }
    if (self->state == 1) {
        if (hero_is_current_selected_id(parent) || flag_is_third_pending_set(parent) ||
            (g_moby_group_flags[self->index + (g_current_map_index << 4)] & 0x80)) {
            self->timer = 0;
            self->state = 2;
            PlayMobySound(1, 0, self);
            {
                unsigned char *record = g_sound_state + data[5] * 0x70;
                if (*(JobaGroupMoby **)(record + 0x88) != self || record[0x74] == 0) {
                    data[5] = PlayMobySound(2, 4, self);
                }
            }
            {
                short *entries;
                if (data[1] == 255 || (entries = g_group_id_lists[data[1]]) == 0) goto done;
                list = entries;
                do {
                    JobaGroupMoby *m = GROUP_MEMBER(*list);
                    health = *moby_get_private_value_0(m);
                    if (MEMBER_ALIVE(m) && m->type == 0xCF5) { m->active = 1; ACTIVATE_MEMBER(m); }
                    else if (MEMBER_ALIVE(m) && m->type == 0xCF6) { m->active = 1; ACTIVATE_MEMBER(m); }
                    else if (MEMBER_ALIVE(m) && m->type == 0xD07) { m->active = 1; ACTIVATE_MEMBER(m); }
                } while (*list++ >= 0);
            }
            {
                short *entries;
                if (data[2] == 255 || (entries = g_group_id_lists[data[2]]) == 0) goto done;
                list = entries;
                do {
                    JobaGroupMoby *m = GROUP_MEMBER(*list);
                    if ((signed char)m->state >= 0) {
                        if (m->type == 0xD07) { m->active = 1; ACTIVATE_MEMBER(m); }
                        else if (m->type == 0xCF6) { m->active = 1; ACTIVATE_MEMBER(m); }
                        else if (m->type == 0xCF5) { m->active = 1; ACTIVATE_MEMBER(m); }
                    }
                } while (*list++ >= 0);
            }
        }
        event = part_find_owned_effect_slot(self, 0x10000, 0);
        if (event) {
            vec_scale_to_length(vec, self->target, 0.50000006f);
            if ((*(JobaGroupMoby **)(event + 0x20))->type == 0xDD9) {
                short *entries, *list;
                PlayMobySound(0, 0, self);
                self->timer = 0;
                self->slot = 255;
                /* Each exit writes its calls out: jump2 shares only the last call between them. */
                if (data[1] == 255) { FinishGroupMoby(vec, self); return; }
                entries = g_group_id_lists[data[1]];
                if (entries == 0) { FinishGroupMoby(vec, self); return; }
                list = entries;
                do {
                    JobaGroupMoby *m = GROUP_MEMBER(*list);
                    if ((signed char)m->state >= 0) {
                        if (m->type == 0xCF5) { ACTIVATE_MEMBER(m); m->active = 1; }
                        else if (m->type == 0xCF6) { ACTIVATE_MEMBER(m); m->active = 1; }
                        else if (m->type == 0xD07) { ACTIVATE_MEMBER(m); m->active = 1; }
                    }
                } while (*list++ >= 0);
                if (data[2] == 255) { FinishGroupMoby(vec, self); return; }
                entries = g_group_id_lists[data[2]];
                if (entries == 0) { FinishGroupMoby(vec, self); return; }
                list = entries;
                do {
                    JobaGroupMoby *m = GROUP_MEMBER(*list);
                    if ((signed char)m->state >= 0) {
                        if (m->type == 0xD07) { ACTIVATE_MEMBER(m); m->active = 1; }
                        else if (m->type == 0xCF6) { ACTIVATE_MEMBER(m); m->active = 1; }
                        else if (m->type == 0xCF5) { ACTIVATE_MEMBER(m); m->active = 1; }
                    }
                } while (*list++ >= 0);
                part_spawn_explosion_with_sparks_pal(self, 1.0f, 13.0f, self->position, -1);
                part_spawn_masked_debris_pal(self, 255, 3.0f, 6.0f, 3.0f, 6.0f, vec, 255);
                moby_mark_spawned(self);
                return;
            }
            self->slot = 255;
        }
        self->slot = 255;
    }
    if (self->state == 2) {
        self->position[2] += 0.18f;
        if (++self->timer > 60) {
            if (data[5] != -1) {
                unsigned char *record = g_sound_state + data[5] * 0x70;
                if (*(JobaGroupMoby **)(record + 0x88) == self && record[0x74]) {
                    snd_stop_voice(data[5]);
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
