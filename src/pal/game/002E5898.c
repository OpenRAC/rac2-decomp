#include "include_asm.h"

#include "common.h"
typedef union { float f[4]; } Vec4 __attribute__((aligned(16)));
typedef struct {
    u8 pad00[0x18];
    u8 source_state;
    u8 attenuation_flags;
    s16 sound_index;
    s32 bank_handle;
} VoiceDefinition_DD68;
typedef struct {
    u8 pad00[0x10];
    Vec4 position;
    u8 state;
    u8 pad21[0x9F];
    Vec4 rotation;
} VoiceMoby_DD68;
typedef struct {
    u32 handle;                          
    u8 state;                            
    u8 flags;                            
    u8 pad06[2];
    VoiceDefinition_DD68 *definition;    
    s32 pad0C;
    s16 volume;
    u16 occlusion_history_position;
    s32 pitch_bend;                      
    VoiceMoby_DD68 *moby;                
    s32 owner_context;                   
    Vec4 position;           
    Vec4 position_offset;    
    f32 angle;                           
    u8 occlusion_history[36];            
    u8 pad68[8];
} VoiceSlot_DD68;
typedef struct {
    Vec4 listener_history[4];    
    s32 listener_history_position;           
    s32 pad44;
    s32 group_0_volume;                      
    s32 group_1_volume;
    s32 group_2_volume;
    s32 group_3_volume;
    s32 group_4_volume;
    s32 group_5_volume;
    s32 pad60;
    s32 reverb_depth;                        
    u8 reverb_type;
    u8 reverb_delay;
    u8 reverb_feedback;
    u8 reverb_commands;
    s32 pending_commands;                    
    VoiceSlot_DD68 voices[52];               
    s32 padD90[2];
    s32 occlusion_frame;                     
    s32 padD9C;
    Vec4 occlusion_samples[6];
    s32 banks[6];
    s16 fade_state;
    s16 fade_timer;
} VoiceRuntimeState_DD68;
extern VoiceRuntimeState_DD68 g_sound_state;
extern f32 g_water_height[];
extern s32 g_underwater_flag[] NOT_SDA;
extern u8 g_camera_l00_position[];
extern s32 g_current_game_mode MACRO_ADDR;
extern s32 g_menu_panel_active MACRO_ADDR;
extern s32 g_game_time MACRO_ADDR;
extern char g_hero_velocity[];
extern short g_transition_mode;
extern int g_sound_fade_mode MACRO_ADDR;
extern s32 FastCountChars(u8 *, s32);
extern int snd_get_doppler_pitch_mod(int);
extern void mem_clear(void *, s32, s32);
extern void snd_set_current_buffer_flag(void);
extern s32 snd_Pump(void);
extern void snd_send_cmd9(s32, s32);
extern void snd_send_cmd11_six_values_callback();
extern void snd_send_cmd15(s32);
extern void snd_send_cmd25_with_settings();
extern void snd_send_cmd21_callback();
extern void snd_clear_flag_and_update();
extern void snd_send_cmd50_five_values(s32, s32, s32, s32, s32);
extern void snd_send_cmd10(s32, s32, s32, s32);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, f32);
extern f32 FastVecDot(void *, void *);
extern f32 FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void matrix_mul_vec3(void *, void *, void *);
extern f32 IntToFloat(s32);
extern s32 FloatToInt(f32);
extern void snd_update_music_system_pal();
extern void snd_probe_listener_occlusion_point(void *);
extern u8 snd_test_occlusion(VoiceSlot_DD68 *, void *);
extern s32 snd_compute_voice_volume_from_distance(VoiceSlot_DD68 *, Vec4 *);
extern s32 snd_compute_voice_pan(VoiceSlot_DD68 *, Vec4 *);
extern void snd_voice_started_callback();
extern void voice_update_callback();

/* Updates every sound voice each frame: volume, pan, pitch, occlusion and group volume fades. */
s32 UpdateSoundVoices_pal(void) {
    VoiceSlot_DD68 *voices;
    Vec4 listener_occlusion_position;
    Vec4 listener_velocity;
    Vec4 relative_velocity;
    s32 flags[52];
    s32 voice_volumes[52];
    f32 radial_velocities[52];
    Vec4 direction;
    s32 slot_index;
    s32 underwater;
    s32 *voice_flags;
    s32 *volumes;
    f32 *velocities;
    VoiceMoby_DD68 *moby;
    f32 water_height;
    f32 listener_speed;
    s32 history_index;
    s32 divisor;
    s32 current_index;
    s32 previous_history_index;
    s32 listener_sample_count;
    s32 group_volume;
    s32 history_offset;
    s32 sample_index;
    s32 repeat_index;
    s32 owner_removed;
    s32 distance_volume;
    s32 occluded_samples;
    s32 parameter_mask;
    s32 pan;
    s32 pitch_modifier;
    s32 pitch_bend;
    s32 handle;
    s32 command_flags;

    underwater = g_underwater_flag[0];
    water_height = 0.0f;
    if (underwater != 0) {
        water_height = g_water_height[0];
    }
    snd_Pump();

    if (g_sound_state.reverb_commands & 8) {
        snd_send_cmd50_five_values(2, 0, 0, 0, 0);
    } else if (g_sound_state.reverb_commands & 0x13) {
        snd_send_cmd50_five_values(2, g_sound_state.reverb_type, g_sound_state.reverb_depth,
                             g_sound_state.reverb_delay, g_sound_state.reverb_feedback);
    } else if (g_sound_state.reverb_commands & 4) {
        snd_send_cmd10(2, g_sound_state.reverb_depth, 0xC, 3);
    }
    g_sound_state.reverb_commands = 0;

    if ((g_current_game_mode == 0 || g_current_game_mode == 2) && g_menu_panel_active == 0) {
        snd_probe_listener_occlusion_point(&listener_occlusion_position);
    }

    qzero_nc(&listener_velocity);
    history_index = g_sound_state.listener_history_position + 1;
    history_index %= 4;
    g_sound_state.listener_history_position = history_index;
    qcopy(&g_sound_state.listener_history[history_index], g_camera_l00_position);

    listener_speed = FastVecLength(g_hero_velocity);
    listener_sample_count = 0;
    divisor = 18;
    current_index = g_sound_state.listener_history_position;
    previous_history_index = (current_index + 3) % 4;
    if (previous_history_index != current_index) {
        do {
            FastVecSub(&relative_velocity, &g_sound_state.listener_history[current_index],
                            &g_sound_state.listener_history[previous_history_index]);
            if (!(FastVecLength(&relative_velocity) < listener_speed + 1.2f)) {
                break;
            }
            listener_sample_count++;
            FastVecAdd(&listener_velocity, &listener_velocity, &relative_velocity);
            current_index = previous_history_index;
            previous_history_index = (current_index + 3) % 4;
        } while (previous_history_index != g_sound_state.listener_history_position);
    }
    if (listener_sample_count >= 2) {
        FastVecScale(&listener_velocity, &listener_velocity,
                          1.0f / IntToFloat(listener_sample_count));
    }

    if (g_sound_fade_mode != 0 || g_sound_state.fade_state > 0) {
        float scale = 1.0f;
        float volume = g_sound_state.group_0_volume;
        if (!g_sound_fade_mode) {
            if (g_sound_state.fade_state == 2) {
                g_sound_state.fade_state = 3;
                g_sound_state.fade_timer = 25;
            }
        } else if (!g_sound_state.fade_state) {
            if (g_sound_fade_mode == 2) {
                g_sound_state.fade_state = 2;
            } else {
                g_sound_state.fade_state = 1;
                g_sound_state.fade_timer = 25;
            }
        }
        --g_sound_state.fade_timer;
        switch (g_sound_state.fade_state) {
        case 3:
            scale = g_sound_state.fade_timer * 0.12f + 1.0f;
            if (g_sound_state.fade_timer <= 0) g_sound_state.fade_state = 0;
            break;
        case 1:
            scale = (1.0f - g_sound_state.fade_timer * (0.04f)) * 3.0f + 1.0f;
            if (g_sound_state.fade_timer <= 0) g_sound_state.fade_state = 2;
            break;
        case 2: scale = 4.0f; break;
        }
        volume /= scale;
        {
            s32 faded_volume = volume;
            snd_send_cmd9(0, faded_volume);
            snd_send_cmd9(3, faded_volume);
        }
    } else if (g_current_game_mode == 2 || (g_current_game_mode == 6 && (g_transition_mode == 3 || g_transition_mode == 0))) {
        snd_send_cmd9(1, 0);
        snd_send_cmd9(0, g_sound_state.group_0_volume / 2);
        snd_send_cmd9(3, g_sound_state.group_3_volume / 2);
    } else {
        group_volume = g_sound_state.group_1_volume;
        if (underwater) {
            group_volume = group_volume * 3 / 5;
        }
        snd_send_cmd9(1, group_volume);
        snd_send_cmd9(0, g_sound_state.group_0_volume);
        snd_send_cmd9(3, g_sound_state.group_3_volume);
    }
    snd_send_cmd9(2, g_sound_state.group_2_volume);
    snd_send_cmd9(5, g_sound_state.group_5_volume);
    snd_send_cmd9(6, g_sound_state.group_2_volume);

    voice_flags = flags;
    volumes = voice_volumes;
    velocities = radial_velocities;
    mem_clear(voice_flags, 0, 0xD0);
    mem_clear(volumes, 0, 0xD0);
    mem_clear(velocities, 0, 0xD0);

    for (slot_index = 0; slot_index < 52; slot_index++) {
        {
            s32 state = g_sound_state.voices[slot_index].state;
            if (state != 7) {
                if (g_sound_state.voices[slot_index].handle == 0) {
                    continue;
                }
                if (g_sound_state.voices[slot_index].handle == -1) {
                    continue;
                }
            }
        }
        moby = g_sound_state.voices[slot_index].moby;
        owner_removed = 0;
        if (moby != 0) {
            u8 owner_state = moby->state;
            if (owner_state == 0xFE)
                goto owner_removed_label;
            if (owner_state != 0xFD)
                goto owner_checked_label;
        owner_removed_label:
            owner_removed = 1;
        owner_checked_label:;
        }
        if (owner_removed) {
            g_sound_state.voices[slot_index].moby = 0;
        }
        {
            s32 state = g_sound_state.voices[slot_index].state;
            if (state == 4 ||
                (state != 6 && owner_removed &&
                 g_sound_state.voices[slot_index].definition->source_state != 0)) {
                flags[slot_index] = 0x20;
                continue;
            }
        }
        if (g_current_game_mode != 0 && g_current_game_mode != 2 && g_current_game_mode != 6) {
            s32 state = g_sound_state.voices[slot_index].state;
            if (state != 7) {
                voice_flags[slot_index] = 0x10;
                continue;
            }
        }

        if (g_sound_state.voices[slot_index].moby != 0 &&
            !(g_sound_state.voices[slot_index].flags & 8)) {
            if (g_sound_state.voices[slot_index].flags & 0x40) {
                matrix_mul_vec3(&direction, &g_sound_state.voices[slot_index].position_offset,
                                      &moby->rotation);
                FastVecAdd(&direction, &direction, &moby->position);
                {
                    Vec4 *position = &g_sound_state.voices[slot_index].position;
                    FastVecSub(&relative_velocity, &direction, position);
                    qcopy(position, &direction);
                }
            } else {
                g_sound_state.voices[slot_index].position.f[2] -= 1.0f;
                {
                    Vec4 *position = &g_sound_state.voices[slot_index].position;
                    FastVecSub(&relative_velocity,
                                  &g_sound_state.voices[slot_index].moby->position, position);
                    qcopy(position, &g_sound_state.voices[slot_index].moby->position);
                }
                g_sound_state.voices[slot_index].position.f[2] += 1.0f;
            }
        } else {
            qzero_nc(&relative_velocity);
        }
        FastVecSub(&relative_velocity, &relative_velocity, &listener_velocity);
        FastVecSub(&direction, g_camera_l00_position, &g_sound_state.voices[slot_index].position);
        vec_scale_to_length(&direction, &direction, 1.0f);
        radial_velocities[slot_index] = FastVecDot(&direction, &relative_velocity);

        if (!(g_sound_state.voices[slot_index].flags & 0x10)) {
            distance_volume = snd_compute_voice_volume_from_distance(&g_sound_state.voices[slot_index],
                                                           &g_sound_state.voices[slot_index].position);
            volumes[slot_index] = distance_volume * g_sound_state.voices[slot_index].volume / 1024;
            {
                s32 attenuation = g_sound_state.voices[slot_index].definition->attenuation_flags;
                if (!(attenuation & 2)) {
                    voice_flags[slot_index] |= 8;
                }
            }
        } else {
            distance_volume = 0x400;
            voice_volumes[slot_index] = g_sound_state.voices[slot_index].volume;
        }
        if (underwater && !(g_sound_state.voices[slot_index].definition->attenuation_flags & 4) &&
            water_height < g_sound_state.voices[slot_index].position.f[2]) {
            volumes[slot_index] /= 2;
        }
        voice_flags[slot_index] |= 1;
        if (distance_volume < 0x20 && voice_volumes[slot_index] < 0x20 &&
            (g_sound_state.voices[slot_index].flags & 4)) {
            voice_flags[slot_index] = 0x20;
            continue;
        }
        {
            s32 voice_flags_byte = g_sound_state.voices[slot_index].flags;
            if ((voice_flags_byte ^ 1) & 1) {
                voice_flags[slot_index] |= 2;
                if (!(g_sound_state.voices[slot_index].flags & 0x20)) {
                    s32 attenuation = g_sound_state.voices[slot_index].definition->attenuation_flags;
                    if (!(attenuation & 0x10)) {
                        voice_flags[slot_index] |= 4;
                    }
                }
            }
        }
    }

    voices = g_sound_state.voices;
    for (slot_index = 0; slot_index < 52; slot_index++) {
        if (!(flags[slot_index] & 8)) {
            continue;
        }
        {
            if (g_sound_state.voices[slot_index].state == 7) {
                if ((g_current_game_mode != 0 && g_current_game_mode != 2) || g_menu_panel_active != 0) {
                    continue;
                }
                occluded_samples = 0;
                if (g_game_time != g_sound_state.occlusion_frame) {
                    {
                        s32 i;
                        Vec4 *sample = g_sound_state.occlusion_samples;
                        for (i = 5; i >= 0; i--, sample++) {
                            snd_probe_listener_occlusion_point(sample);
                        }
                    }
                    g_sound_state.occlusion_frame = g_game_time;
                }
                for (history_offset = 0, sample_index = 0; history_offset < 36;
                     history_offset += 6, sample_index++) {
                    g_sound_state.voices[slot_index].occlusion_history[history_offset] =
                        snd_test_occlusion(&g_sound_state.voices[slot_index],
                                            &g_sound_state.occlusion_samples[sample_index]);
                    {
                        /* Byte offset of this voice's occlusion_history within D_00188660. */
                        s32 voice_base = slot_index * 0x70 + 0xB4;
                        s32 copy_offset = history_offset + voice_base;
                        for (repeat_index = 1; repeat_index < 6; repeat_index++) {
                            ((u8 *)&g_sound_state)[copy_offset + repeat_index] =
                                g_sound_state.voices[slot_index].occlusion_history[history_offset];
                        }
                    }
                    if (g_sound_state.voices[slot_index].occlusion_history[history_offset]) {
                        occluded_samples += 6;
                    }
                }
                if (occluded_samples >= 36) {
                    voice_volumes[slot_index] = 0;
                } else if (occluded_samples >= 19) {
                    voice_volumes[slot_index] = (36 - occluded_samples) * voice_volumes[slot_index] / divisor;
                }
            } else {
                if ((g_current_game_mode == 0 || g_current_game_mode == 2) && g_menu_panel_active == 0) {
                    g_sound_state.voices[slot_index].occlusion_history_position =
                        (g_sound_state.voices[slot_index].occlusion_history_position + 1) % 36;
                    /* Active sources test every other frame; other voices every fourth. */
                    {
                        s32 test_now = (slot_index ^ g_game_time) & 1;
                        if (!(g_sound_state.voices[slot_index].flags & 4)) {
                            test_now = (slot_index & 3) == (g_game_time & 3);
                        }
                        if (test_now) {
                            g_sound_state.voices[slot_index].occlusion_history
                                [g_sound_state.voices[slot_index].occlusion_history_position] =
                                snd_test_occlusion(&g_sound_state.voices[slot_index],
                                                    &listener_occlusion_position);
                        } else {
                            g_sound_state.voices[slot_index].occlusion_history
                                [g_sound_state.voices[slot_index].occlusion_history_position] =
                                g_sound_state.voices[slot_index].occlusion_history
                                    [(g_sound_state.voices[slot_index].occlusion_history_position + 35) % 36];
                        }
                    }
                }
                {
                    s32 occluded =
                        FastCountChars(voices[slot_index].occlusion_history, 36);
                    if (occluded >= 36) {
                        voice_volumes[slot_index] = 0;
                    } else if (occluded >= 19) {
                        voice_volumes[slot_index] = (36 - occluded) * voice_volumes[slot_index] / divisor;
                    }
                }
            }
        }
    }

    
    for (slot_index = 0; slot_index < 52; slot_index++) {
        command_flags = flags[slot_index];
        if (command_flags == 0) {
            continue;
        }
        handle = g_sound_state.voices[slot_index].handle;
        g_sound_state.voices[slot_index].handle = -1;
        if (command_flags & 0x20) {
            {
                if (g_sound_state.voices[slot_index].state == 7) {
                    g_sound_state.voices[slot_index].moby = 0;
                    g_sound_state.voices[slot_index].owner_context = 0;
                    g_sound_state.voices[slot_index].state = 0;
                } else {
                    snd_send_cmd15(handle);
                    g_sound_state.voices[slot_index].state = 6;
                    snd_send_cmd25_with_settings(handle, voice_update_callback,
                                                 &g_sound_state.voices[slot_index]);
                }
            }
        } else if (command_flags & 0x10) {
            snd_send_cmd25_with_settings(handle, voice_update_callback,
                                         &g_sound_state.voices[slot_index]);
        } else {
            pitch_bend = g_sound_state.voices[slot_index].pitch_bend;
            parameter_mask = pitch_bend ? 0x11 : 1;
            pan = 0;
            pitch_modifier = 0;
            if (command_flags & 2) {
                pan = snd_compute_voice_pan(&g_sound_state.voices[slot_index],
                                            &g_sound_state.voices[slot_index].position);
                parameter_mask |= 6;
            }
            if (voice_flags[slot_index] & 4) {
                parameter_mask |= 8;
                pitch_modifier = snd_get_doppler_pitch_mod(
                    FloatToInt(radial_velocities[slot_index] * ((g_sound_state.voices[slot_index].flags & 2) ? 500.0f : 3e+02f)));
            }
            if (underwater && !(g_sound_state.voices[slot_index].definition->attenuation_flags & 8)) {
                parameter_mask |= 8;
                pitch_modifier -= 0x5F4;
            }
            {
                if (g_sound_state.voices[slot_index].state != 7) {
                    snd_send_cmd21_callback(handle, parameter_mask, voice_volumes[slot_index], pan,
                                            pitch_modifier, pitch_bend, voice_update_callback,
                                            &g_sound_state.voices[slot_index]);
                } else {
                    if (g_sound_state.voices[slot_index].definition == 0 ||
                        g_sound_state.banks[g_sound_state.voices[slot_index].definition->bank_handle] == -1 ||
                        g_sound_state.banks[g_sound_state.voices[slot_index].definition->bank_handle] == 0) {
                        g_sound_state.voices[slot_index].moby = 0;
                        g_sound_state.voices[slot_index].owner_context = 0;
                        g_sound_state.voices[slot_index].state = 0;
                        continue;
                    }
                    g_sound_state.voices[slot_index].state = 1;
                    snd_send_cmd11_six_values_callback(g_sound_state.banks[g_sound_state.voices[slot_index].definition->bank_handle],
                                                 g_sound_state.voices[slot_index].definition->sound_index,
                                                voice_volumes[slot_index], pan, pitch_modifier, pitch_bend,
                                                snd_voice_started_callback, &g_sound_state.voices[slot_index]);
                }
            }
        }
    }

    snd_update_music_system_pal();
    snd_clear_flag_and_update();
    snd_Pump();
    snd_set_current_buffer_flag();
    g_sound_state.pending_commands = 0;
    return 0;
}

