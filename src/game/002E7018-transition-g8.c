#include "common.h"
#define W(p, o)  (*(int *)((char *)(p) + (o)))
#define H(p, o)  (*(short *)((char *)(p) + (o)))
#define B(p, o)  (*(unsigned char *)((char *)(p) + (o)))
#define F(p, o)  (*(float *)((char *)(p) + (o)))

extern void game_reset_frame_counters(void);
extern void game_update_idle_frame_counters(void);
extern void snd_set_current_buffer_flag(void);
extern void snd_clear_flag_and_update(void);
extern int snd_Pump(void);
extern void func_00132A10(int, int, int, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern void update_moby_animation_state(void *);
extern void moby_transform_joint_point(void *, int, void *);
extern void func_002A0F48(void *);
extern void func_002A10E8(void *);
extern void scene_start_sequence_for_state(void);
extern char g_effect_record_table_2[];
extern void part_init_effect_table(void *);
extern s32 func_00132AC8(void);
extern int func_001163B0(void);
extern void snd_send_cmd6(int);
extern void func_00132828(void);
extern void scene_load_texture_block(void);
extern void mem_clear(void *, int, int);
extern void load_select_segment_update_world(int);
extern int cam_set_from_selected_record(void);
extern void UpdateViewContext(void);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern void UpdateEquipmentPieces(int);

typedef struct {
 char pad0[0x10]; float position[4]; char pad20[4]; char *definition;
 char pad28[4]; float scale; char pad30[2]; short draw_flags; char pad34[12];
 unsigned char key, next_key, current_anim, next_anim; float blend;
 char pad48[0x19]; unsigned char alpha, cached_frame, flags; char pad64[4];
 char *keys; char pad6c[0x29]; unsigned char opacity; char pad96[0x14]; short type;
} TransitionActor;
extern float g_screen_fade MACRO_ADDR;
typedef struct {
 char pad[0xc]; unsigned char count; char gap[0x3b]; void *animations[1];
} AnimationClass;
typedef struct { char pad[0x24]; AnimationClass *definition; } AnimationObject;
typedef struct {
 char pad[0x34]; int frame, tick, page; short duration, pad42, count;
 char pad46[0xe]; int id; char pad58[0x14]; int start, end;
 int entries[70]; char *objects[17];
} TransitionScene;
extern TransitionScene g_scene_playback_state;        /* controller state */
typedef struct {
 char pad[0x2c]; short flag; char pad2e[0x36]; int index, phase;
} TransitionMenu;
extern TransitionMenu g_hero_moby_default;        /* mode block: +0x64 index, +0x68 phase */
extern int D_001B2130_first SDATA(D_001B2130);


extern int g_scene_sound_block_a[] MACRO_ADDR __attribute__((sda));         /* [0] +0, [1] +4, [3] +0xC */
extern int g_transition_effect_list[] __attribute__((sda));
extern int D_001B2148_first[] __asm__("D_001B2148") __attribute__((sda));         /* null-terminated entity list */
typedef struct { char pad[0x24]; float scale; } ScaleClass;
typedef struct { char pad[0x24]; ScaleClass *definition; int pad28; float scale; } ScaleEntity;
extern ScaleEntity *g_equipment_pieces[];         /* null-terminated entity list */
extern int g_transition_pending_sound __attribute__((sda));
extern int g_loader_archives;
extern int D_001A7280_block[] __asm__("D_001A7280") MACRO_ADDR __attribute__((sda));
extern int g_packet_buffer_size;
typedef struct { int pad, data_offset; char gap[0x48]; int scenes[5]; } TransitionHeader;
typedef struct { int offset, size; } TransitionChunk;
typedef struct { char pad[12]; int start, end, pad14; TransitionHeader *data; } TransitionArchive;
extern TransitionArchive g_loader_memory;
extern int g_transition_sound_table[];
extern char g_transition_vec_table[];        /* 16-byte entries */
typedef struct { float x, y, z, w; } TransitionVector;
typedef struct { char pad[0xc0]; TransitionVector basis[3]; } MatrixEntity;
extern TransitionVector g_transition_vector MACRO_ADDR;
extern char g_transition_vec_a[] SDATA(D_001AC0C0);
extern char g_transition_vec_b[] SDATA(D_001AC0D0);
extern char g_transition_fade_vec[] SDATA(D_001AC120);
extern float g_transition_fov_table[] SDATA(D_001AC150);
extern float g_transition_min_fov_table[] SDATA(D_001AC168);
extern float g_transition_fov_scale MACRO_ADDR;
extern float g_transition_scale_factor __attribute__((sda));
typedef struct { char pad[0xb0]; float fov; } TransitionView;
extern TransitionView g_view_params;        /* view: +0xB0 float */

/* Runs one frame of the transition scene: moves each object along its path and starts the next scene part when one ends. */
int transition_update_scene(void)
{
    float scratch_a[4], scratch_b[4], moby_matrix[16];
    float fade_scale;
    int i, next_index;

    game_reset_frame_counters();
    {
        float new_fade = g_screen_fade - 0.25f;
        g_scene_playback_state.tick = g_scene_playback_state.tick + 1;
        g_scene_playback_state.frame = g_scene_playback_state.frame + 1;
        g_screen_fade = new_fade;
        if (new_fade < 0.0f)
            g_screen_fade = 0.0f;
    }
    if (g_scene_playback_state.frame == 1) {
        int sound_index;
        snd_set_current_buffer_flag();
        sound_index = g_hero_moby_default.index;
        func_00132A10(g_scene_sound_block_a[sound_index], 0, 0x400, 0, 0, 0, 0, (int)g_transition_sound_table + sound_index * 0x70);
        snd_clear_flag_and_update();
        snd_Pump();
    }
    if (g_scene_playback_state.frame < g_scene_playback_state.duration) {
        goto running;
    }
    /* the phase has ended */
    for (i = 0; i < g_scene_playback_state.count; i++) {
        AnimationObject *anim_object = (AnimationObject *)g_scene_playback_state.objects[i];
        if (anim_object != 0) {
            anim_object->definition->count--;
            anim_object->definition->animations[anim_object->definition->count] = 0;
            moby_mark_spawned(anim_object);
        }
    }
    if (g_transition_pending_sound != 0) {
        scene_start_sequence_for_state();
        g_transition_pending_sound = 0;
    }
    part_init_effect_table(g_effect_record_table_2);
    if (g_loader_archives < 2)
        g_hero_moby_default.phase = 0;
    if (g_hero_moby_default.phase < 2) {
        if (g_hero_moby_default.index != 2) {
            func_00132AC8();
            while (snd_Pump() != 0)
                ;
        }
        if (g_hero_moby_default.phase == 0) {
            int random_step = ((func_001163B0() >> 16) % 3) + 1;
            g_hero_moby_default.index = (g_hero_moby_default.index + random_step) & 3;
        } else {
            g_hero_moby_default.index = 4;
            snd_set_current_buffer_flag();
            snd_send_cmd6(D_001B2130_first);
            snd_send_cmd6(g_scene_sound_block_a[1]);
            snd_send_cmd6(g_scene_sound_block_a[3]);
            snd_clear_flag_and_update();
            while (snd_Pump() != 0)
                ;
            func_00132828();
            D_001A7280_block[1] = 0;
            scene_load_texture_block();
        }
        g_hero_moby_default.phase = g_hero_moby_default.phase + 1;
        qcopy(g_transition_vec_b, g_transition_vec_a);
        mem_clear(&g_scene_playback_state, 0, 0x1D0);
        {
            int workspace_offset = g_packet_buffer_size;
            TransitionHeader *header;
            TransitionChunk *chunk;
            int data_base;
            int k;
            g_scene_playback_state.start = g_loader_memory.start + workspace_offset;
            g_scene_playback_state.end = g_loader_memory.end + workspace_offset;
            header = g_loader_memory.data;
            data_base = (int)header + header->data_offset;
            chunk = (TransitionChunk *)(data_base + header->scenes[g_hero_moby_default.index]);
            for (k = 0; k < 70 && chunk->size != 0; k++) {
                int offset = chunk->offset + 0x800;
                g_scene_playback_state.entries[k] = data_base + header->scenes[g_hero_moby_default.index] + offset;
                chunk++;
            }
        }
        load_select_segment_update_world(0);
        goto after;
    } else {
        if (D_001A7280_block[1] == 0)
            return 1;
        D_001A7280_block[1] = 0;
        return 1;
    }

running:
    if (!(g_scene_playback_state.tick < 0x60)) {
        g_scene_playback_state.page = g_scene_playback_state.page + 1;
        load_select_segment_update_world(g_scene_playback_state.page);
    }
after:
    cam_set_from_selected_record();
    {
        float current = g_view_params.fov;
        float min_fov = g_transition_min_fov_table[g_hero_moby_default.index];
        if (current < min_fov)
            g_view_params.fov = min_fov;
    }
    UpdateViewContext();
    fade_scale = 1.0f;
    if (g_hero_moby_default.index == 4) {
        fade_scale = (float)(g_scene_playback_state.duration - g_scene_playback_state.frame) / (float)g_scene_playback_state.duration;
        FastVecScale(scratch_a, g_transition_fade_vec, fade_scale);
        FastVecAdd(g_transition_vec_b, g_transition_vec_b, scratch_a);
    }
    FastVecScale(&g_transition_vector, g_transition_vec_table + g_hero_moby_default.index * 16, (float)(g_scene_playback_state.frame - 0x78) * (fade_scale * 20.0f));
    g_transition_fov_scale = g_transition_fov_table[g_hero_moby_default.index];
    for (i = 0; i < g_scene_playback_state.count; i = next_index) {
        TransitionActor *actor;
        int key_index, next_key_index;
        float fraction;
        char *keys;
        key_index = g_scene_playback_state.tick >> 1;
        actor = (TransitionActor *)g_scene_playback_state.objects[i];
        next_index = i + 1;
        fraction = IntToFloat(g_scene_playback_state.tick & 1);
        next_key_index = key_index + 1;
        actor->blend = fraction * 0.5f;
        keys = (char *)actor->keys;
        FastVecScale(scratch_a, keys + key_index * 16, 1.0f - actor->blend);
        FastVecScale(scratch_b, keys + next_key_index * 16, actor->blend);
        FastVecAdd(actor->position, scratch_a, scratch_b);
        {
            char *definition = (char *)actor->definition;
            actor->current_anim = B(definition, 0xC) - 1;
            actor->next_anim = B(definition, 0xC) - 1;
            actor->key = key_index;
            actor->next_key = next_key_index;
        }
        update_moby_animation_state(actor);
        actor->draw_flags = 0x1FF;
        if (actor->type == 0xD54 /* moby class 3412 */) {
            if (D_001B2148_first[0] != 0) {
                moby_transform_joint_point(actor, 0, moby_matrix);
                {
                    int list_index = 0;
                    actor->flags = 0;
                    actor->draw_flags = 0;
                    if (D_001B2148_first[0] != 0) {
                        do {
                            int k;
                            B((char *)g_transition_effect_list[list_index], 0x63) = 0;
                            H((char *)g_transition_effect_list[list_index], 0x32) = 0x1FF;
                            qcopy((char *)g_transition_effect_list[list_index] + 0x10, actor->position);
                            for (k = 0; k < 3; k++) {
                                ((MatrixEntity *)g_transition_effect_list[list_index])->basis[k].x = moby_matrix[k * 4];
                                ((MatrixEntity *)g_transition_effect_list[list_index])->basis[k].y = moby_matrix[k * 4 + 1];
                                ((MatrixEntity *)g_transition_effect_list[list_index])->basis[k].z = moby_matrix[k * 4 + 2];
                            }
                            func_002A10E8((void *)g_transition_effect_list[list_index]);
                            list_index = list_index + 1;
                        } while (g_transition_effect_list[list_index] != 0);
                    }
                }
            } else {
                UpdateEquipmentPieces(g_scene_playback_state.id);
            }
            actor->opacity = 0xE8;
        }
        actor->cached_frame = 0xFF;
        {
            {
                actor->alpha = 0xFF;
            }
        }
        func_002A0F48(actor);
        {
            char *definition = (char *)actor->definition;
            actor->current_anim = B(definition, 0xC) - 1;
            actor->next_anim = B(definition, 0xC) - 1;
            if (g_hero_moby_default.index == 4) {
                int duration = g_scene_playback_state.duration;
                int frame = g_scene_playback_state.frame;
                if (duration - 0x28 < frame) {
                    float scale_factor = (float)(duration - frame - 4) * 0.027777778f;
                    if (scale_factor < 0.0f)
                        scale_factor = 0.0f;
                    actor->scale = F(definition, 0x24) * scale_factor;
                    g_transition_scale_factor = scale_factor;
                    if (D_001B2148_first[0] != 0) {
                        char *entity = (char *)D_001B2148_first[0];
                        F(entity, 0x2C) = F((char *)W(entity, 0x24), 0x24) * scale_factor;
                    }
                    actor->opacity = (int)(scale_factor * 232.0f);
                    if (actor->type == 0xD54 /* moby class 3412 */) {
                        if (D_001B2148_first[0] == 0) {
                            int j;
                            g_hero_moby_default.flag = 1;
                            if (g_equipment_pieces[0] != 0) {
                                j = 0;
                                do {
                                    ScaleEntity *entity = g_equipment_pieces[j];
                                    j++;
                                    entity->scale = entity->definition->scale * scale_factor;
                                } while (g_equipment_pieces[j] != 0);
                            }
                        }
                    }
                }
            }
        }
    }
    game_update_idle_frame_counters();
    return 0;
}
