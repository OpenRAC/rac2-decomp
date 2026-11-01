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
extern VoiceRuntimeState_DD68 D_00188660;
extern f32 D_0018A150[];
extern s32 D_001B5600[] NOT_SDA;
extern u8 D_L00_001B8DC0[];
extern s32 D_001A8BB0 MACRO_ADDR;
extern s32 D_001A8C88 MACRO_ADDR;
extern s32 D_001B1688 MACRO_ADDR;
extern char D_00189F70[];
extern short D_00152C20;
extern int D_001A8B80 MACRO_ADDR;
extern s32 func_00283150(u8 *, s32);
extern int func_00133988(int);
extern void func_00282A60(void *, s32, s32);
extern void func_00133220(void);
extern s32 func_00132028(void);
extern void func_00132888(s32, s32);
extern void func_001329F0();
extern void func_00132A58(s32);
extern void func_00132B58();
extern void func_00132B88();
extern void func_00133230();
extern void func_00133700(s32, s32, s32, s32, s32);
extern void func_00133788(s32, s32, s32, s32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern f32 func_00282DB0(void *, void *);
extern f32 func_00282DF0(void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00283098(void *, void *, void *);
extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);
extern void func_PAL_002B8130();
extern void func_002E4478(void *);
extern u8 func_002E4528(VoiceSlot_DD68 *, void *);
extern s32 func_002E46C0(VoiceSlot_DD68 *, Vec4 *);
extern s32 func_002E4708(VoiceSlot_DD68 *, Vec4 *);
extern void func_002E60A0();
extern void func_002E60E8();

s32 func_PAL_002E5898(void) {
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

    underwater = D_001B5600[0];
    water_height = 0.0f;
    if (underwater != 0) {
        water_height = D_0018A150[0];
    }
    func_00132028();

    if (D_00188660.reverb_commands & 8) {
        func_00133700(2, 0, 0, 0, 0);
    } else if (D_00188660.reverb_commands & 0x13) {
        func_00133700(2, D_00188660.reverb_type, D_00188660.reverb_depth,
                             D_00188660.reverb_delay, D_00188660.reverb_feedback);
    } else if (D_00188660.reverb_commands & 4) {
        func_00133788(2, D_00188660.reverb_depth, 0xC, 3);
    }
    D_00188660.reverb_commands = 0;

    if ((D_001A8BB0 == 0 || D_001A8BB0 == 2) && D_001A8C88 == 0) {
        func_002E4478(&listener_occlusion_position);
    }

    qzero_nc(&listener_velocity);
    history_index = D_00188660.listener_history_position + 1;
    history_index %= 4;
    D_00188660.listener_history_position = history_index;
    qcopy(&D_00188660.listener_history[history_index], D_L00_001B8DC0);

    listener_speed = func_00282DF0(D_00189F70);
    listener_sample_count = 0;
    divisor = 18;
    current_index = D_00188660.listener_history_position;
    previous_history_index = (current_index + 3) % 4;
    if (previous_history_index != current_index) {
        do {
            func_00282CF0(&relative_velocity, &D_00188660.listener_history[current_index],
                            &D_00188660.listener_history[previous_history_index]);
            if (!(func_00282DF0(&relative_velocity) < listener_speed + 1.2f)) {
                break;
            }
            listener_sample_count++;
            func_00282CC0(&listener_velocity, &listener_velocity, &relative_velocity);
            current_index = previous_history_index;
            previous_history_index = (current_index + 3) % 4;
        } while (previous_history_index != D_00188660.listener_history_position);
    }
    if (listener_sample_count >= 2) {
        func_00282D30(&listener_velocity, &listener_velocity,
                          1.0f / func_00283CE0(listener_sample_count));
    }

    if (D_001A8B80 != 0 || D_00188660.fade_state > 0) {
        float scale = 1.0f;
        float volume = D_00188660.group_0_volume;
        if (!D_001A8B80) {
            if (D_00188660.fade_state == 2) {
                D_00188660.fade_state = 3;
                D_00188660.fade_timer = 25;
            }
        } else if (!D_00188660.fade_state) {
            if (D_001A8B80 == 2) {
                D_00188660.fade_state = 2;
            } else {
                D_00188660.fade_state = 1;
                D_00188660.fade_timer = 25;
            }
        }
        --D_00188660.fade_timer;
        switch (D_00188660.fade_state) {
        case 3:
            scale = D_00188660.fade_timer * 0.12f + 1.0f;
            if (D_00188660.fade_timer <= 0) D_00188660.fade_state = 0;
            break;
        case 1:
            scale = (1.0f - D_00188660.fade_timer * (0.04f)) * 3.0f + 1.0f;
            if (D_00188660.fade_timer <= 0) D_00188660.fade_state = 2;
            break;
        case 2: scale = 4.0f; break;
        }
        volume /= scale;
        {
            s32 faded_volume = volume;
            func_00132888(0, faded_volume);
            func_00132888(3, faded_volume);
        }
    } else if (D_001A8BB0 == 2 || (D_001A8BB0 == 6 && (D_00152C20 == 3 || D_00152C20 == 0))) {
        func_00132888(1, 0);
        func_00132888(0, D_00188660.group_0_volume / 2);
        func_00132888(3, D_00188660.group_3_volume / 2);
    } else {
        group_volume = D_00188660.group_1_volume;
        if (underwater) {
            group_volume = group_volume * 3 / 5;
        }
        func_00132888(1, group_volume);
        func_00132888(0, D_00188660.group_0_volume);
        func_00132888(3, D_00188660.group_3_volume);
    }
    func_00132888(2, D_00188660.group_2_volume);
    func_00132888(5, D_00188660.group_5_volume);
    func_00132888(6, D_00188660.group_2_volume);

    voice_flags = flags;
    volumes = voice_volumes;
    velocities = radial_velocities;
    func_00282A60(voice_flags, 0, 0xD0);
    func_00282A60(volumes, 0, 0xD0);
    func_00282A60(velocities, 0, 0xD0);

    for (slot_index = 0; slot_index < 52; slot_index++) {
        {
            s32 state = D_00188660.voices[slot_index].state;
            if (state != 7) {
                if (D_00188660.voices[slot_index].handle == 0) {
                    continue;
                }
                if (D_00188660.voices[slot_index].handle == -1) {
                    continue;
                }
            }
        }
        moby = D_00188660.voices[slot_index].moby;
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
            D_00188660.voices[slot_index].moby = 0;
        }
        {
            s32 state = D_00188660.voices[slot_index].state;
            if (state == 4 ||
                (state != 6 && owner_removed &&
                 D_00188660.voices[slot_index].definition->source_state != 0)) {
                flags[slot_index] = 0x20;
                continue;
            }
        }
        if (D_001A8BB0 != 0 && D_001A8BB0 != 2 && D_001A8BB0 != 6) {
            s32 state = D_00188660.voices[slot_index].state;
            if (state != 7) {
                voice_flags[slot_index] = 0x10;
                continue;
            }
        }

        if (D_00188660.voices[slot_index].moby != 0 &&
            !(D_00188660.voices[slot_index].flags & 8)) {
            if (D_00188660.voices[slot_index].flags & 0x40) {
                func_00283098(&direction, &D_00188660.voices[slot_index].position_offset,
                                      &moby->rotation);
                func_00282CC0(&direction, &direction, &moby->position);
                {
                    Vec4 *position = &D_00188660.voices[slot_index].position;
                    func_00282CF0(&relative_velocity, &direction, position);
                    qcopy(position, &direction);
                }
            } else {
                D_00188660.voices[slot_index].position.f[2] -= 1.0f;
                {
                    Vec4 *position = &D_00188660.voices[slot_index].position;
                    func_00282CF0(&relative_velocity,
                                  &D_00188660.voices[slot_index].moby->position, position);
                    qcopy(position, &D_00188660.voices[slot_index].moby->position);
                }
                D_00188660.voices[slot_index].position.f[2] += 1.0f;
            }
        } else {
            qzero_nc(&relative_velocity);
        }
        func_00282CF0(&relative_velocity, &relative_velocity, &listener_velocity);
        func_00282CF0(&direction, D_L00_001B8DC0, &D_00188660.voices[slot_index].position);
        func_00282F20(&direction, &direction, 1.0f);
        radial_velocities[slot_index] = func_00282DB0(&direction, &relative_velocity);

        if (!(D_00188660.voices[slot_index].flags & 0x10)) {
            distance_volume = func_002E46C0(&D_00188660.voices[slot_index],
                                                           &D_00188660.voices[slot_index].position);
            volumes[slot_index] = distance_volume * D_00188660.voices[slot_index].volume / 1024;
            {
                s32 attenuation = D_00188660.voices[slot_index].definition->attenuation_flags;
                if (!(attenuation & 2)) {
                    voice_flags[slot_index] |= 8;
                }
            }
        } else {
            distance_volume = 0x400;
            voice_volumes[slot_index] = D_00188660.voices[slot_index].volume;
        }
        if (underwater && !(D_00188660.voices[slot_index].definition->attenuation_flags & 4) &&
            water_height < D_00188660.voices[slot_index].position.f[2]) {
            volumes[slot_index] /= 2;
        }
        voice_flags[slot_index] |= 1;
        if (distance_volume < 0x20 && voice_volumes[slot_index] < 0x20 &&
            (D_00188660.voices[slot_index].flags & 4)) {
            voice_flags[slot_index] = 0x20;
            continue;
        }
        {
            s32 voice_flags_byte = D_00188660.voices[slot_index].flags;
            if ((voice_flags_byte ^ 1) & 1) {
                voice_flags[slot_index] |= 2;
                if (!(D_00188660.voices[slot_index].flags & 0x20)) {
                    s32 attenuation = D_00188660.voices[slot_index].definition->attenuation_flags;
                    if (!(attenuation & 0x10)) {
                        voice_flags[slot_index] |= 4;
                    }
                }
            }
        }
    }

    voices = D_00188660.voices;
    for (slot_index = 0; slot_index < 52; slot_index++) {
        if (!(flags[slot_index] & 8)) {
            continue;
        }
        {
            if (D_00188660.voices[slot_index].state == 7) {
                if ((D_001A8BB0 != 0 && D_001A8BB0 != 2) || D_001A8C88 != 0) {
                    continue;
                }
                occluded_samples = 0;
                if (D_001B1688 != D_00188660.occlusion_frame) {
                    {
                        s32 i;
                        Vec4 *sample = D_00188660.occlusion_samples;
                        for (i = 5; i >= 0; i--, sample++) {
                            func_002E4478(sample);
                        }
                    }
                    D_00188660.occlusion_frame = D_001B1688;
                }
                for (history_offset = 0, sample_index = 0; history_offset < 36;
                     history_offset += 6, sample_index++) {
                    D_00188660.voices[slot_index].occlusion_history[history_offset] =
                        func_002E4528(&D_00188660.voices[slot_index],
                                            &D_00188660.occlusion_samples[sample_index]);
                    {
                        /* Byte offset of this voice's occlusion_history within D_00188660. */
                        s32 voice_base = slot_index * 0x70 + 0xB4;
                        s32 copy_offset = history_offset + voice_base;
                        for (repeat_index = 1; repeat_index < 6; repeat_index++) {
                            ((u8 *)&D_00188660)[copy_offset + repeat_index] =
                                D_00188660.voices[slot_index].occlusion_history[history_offset];
                        }
                    }
                    if (D_00188660.voices[slot_index].occlusion_history[history_offset]) {
                        occluded_samples += 6;
                    }
                }
                if (occluded_samples >= 36) {
                    voice_volumes[slot_index] = 0;
                } else if (occluded_samples >= 19) {
                    voice_volumes[slot_index] = (36 - occluded_samples) * voice_volumes[slot_index] / divisor;
                }
            } else {
                if ((D_001A8BB0 == 0 || D_001A8BB0 == 2) && D_001A8C88 == 0) {
                    D_00188660.voices[slot_index].occlusion_history_position =
                        (D_00188660.voices[slot_index].occlusion_history_position + 1) % 36;
                    /* Active sources test every other frame; other voices every fourth. */
                    {
                        s32 test_now = (slot_index ^ D_001B1688) & 1;
                        if (!(D_00188660.voices[slot_index].flags & 4)) {
                            test_now = (slot_index & 3) == (D_001B1688 & 3);
                        }
                        if (test_now) {
                            D_00188660.voices[slot_index].occlusion_history
                                [D_00188660.voices[slot_index].occlusion_history_position] =
                                func_002E4528(&D_00188660.voices[slot_index],
                                                    &listener_occlusion_position);
                        } else {
                            D_00188660.voices[slot_index].occlusion_history
                                [D_00188660.voices[slot_index].occlusion_history_position] =
                                D_00188660.voices[slot_index].occlusion_history
                                    [(D_00188660.voices[slot_index].occlusion_history_position + 35) % 36];
                        }
                    }
                }
                {
                    s32 occluded =
                        func_00283150(voices[slot_index].occlusion_history, 36);
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
        handle = D_00188660.voices[slot_index].handle;
        D_00188660.voices[slot_index].handle = -1;
        if (command_flags & 0x20) {
            {
                if (D_00188660.voices[slot_index].state == 7) {
                    D_00188660.voices[slot_index].moby = 0;
                    D_00188660.voices[slot_index].owner_context = 0;
                    D_00188660.voices[slot_index].state = 0;
                } else {
                    func_00132A58(handle);
                    D_00188660.voices[slot_index].state = 6;
                    func_00132B58(handle, func_002E60E8,
                                                 &D_00188660.voices[slot_index]);
                }
            }
        } else if (command_flags & 0x10) {
            func_00132B58(handle, func_002E60E8,
                                         &D_00188660.voices[slot_index]);
        } else {
            pitch_bend = D_00188660.voices[slot_index].pitch_bend;
            parameter_mask = pitch_bend ? 0x11 : 1;
            pan = 0;
            pitch_modifier = 0;
            if (command_flags & 2) {
                pan = func_002E4708(&D_00188660.voices[slot_index],
                                            &D_00188660.voices[slot_index].position);
                parameter_mask |= 6;
            }
            if (voice_flags[slot_index] & 4) {
                parameter_mask |= 8;
                pitch_modifier = func_00133988(
                    func_00283CF0(radial_velocities[slot_index] * ((D_00188660.voices[slot_index].flags & 2) ? 500.0f : 3e+02f)));
            }
            if (underwater && !(D_00188660.voices[slot_index].definition->attenuation_flags & 8)) {
                parameter_mask |= 8;
                pitch_modifier -= 0x5F4;
            }
            {
                if (D_00188660.voices[slot_index].state != 7) {
                    func_00132B88(handle, parameter_mask, voice_volumes[slot_index], pan,
                                            pitch_modifier, pitch_bend, func_002E60E8,
                                            &D_00188660.voices[slot_index]);
                } else {
                    if (D_00188660.voices[slot_index].definition == 0 ||
                        D_00188660.banks[D_00188660.voices[slot_index].definition->bank_handle] == -1 ||
                        D_00188660.banks[D_00188660.voices[slot_index].definition->bank_handle] == 0) {
                        D_00188660.voices[slot_index].moby = 0;
                        D_00188660.voices[slot_index].owner_context = 0;
                        D_00188660.voices[slot_index].state = 0;
                        continue;
                    }
                    D_00188660.voices[slot_index].state = 1;
                    func_001329F0(D_00188660.banks[D_00188660.voices[slot_index].definition->bank_handle],
                                                 D_00188660.voices[slot_index].definition->sound_index,
                                                voice_volumes[slot_index], pan, pitch_modifier, pitch_bend,
                                                func_002E60A0, &D_00188660.voices[slot_index]);
                }
            }
        }
    }

    func_PAL_002B8130();
    func_00133230();
    func_00132028();
    func_00133220();
    D_00188660.pending_commands = 0;
    return 0;
}

