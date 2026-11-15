#include "include_asm.h"
#include "common.h"

extern long long GetEffectTextureDescriptor(int id);
extern float math_random_angle(void);
extern void FastVecScale(char *dst, char *src, float scale);
extern float mat_fast_helper_a(float x, float y);
extern float vec_distance_xy(char *p, float *v);
extern void euler_to_matrix(float *matrix, float *quat);
extern void FastVecSub(float *off, float *v, char *p);
extern void vec_scale_to_length(float *dst, float *src, float angle);
extern void draw_world_quad(char *pkt, float *matrix, int mode);
/* Camera position used by the facing-vector helpers. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} BootAimVector;

extern signed char g_active_camera[];



extern char D_00189E20_9[];

extern void func_00282C88_1(float *buf);

extern float FastVecLength(float *buf);

extern void mat_build_rotation_from_angles(void *, float *);

/* func_0031F210 is in 0031F210-ribbon.c. */


/* func_0031FC28 is in 0031F210-pickup-g8.c. */

/* func_003202E8 is in 0031F210-g8.c. */

extern void moby_set_state(unsigned char *, unsigned char, int);
extern char *CreateMoby(int);
extern void func_002A0F48(void *);
extern void group_alert_peers_type_a(char *);
extern void robot_destroy_child_cleanup(char *);
extern void vec_clear_128(void *);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern void moby_transform_joint_to_world(char *, int, void *);
extern int CollLine(void *, void *, int, char *, int);
extern float coll_probe_ground_height_below(void *, int, float);
extern void anim_start_blended(char *, int, int, int);
extern int moby_count_group_not_in_state(int, int);
extern int weapon_select_aim_target(char *, int, float, float, int, int);
extern void part_spawn_explosion_with_sparks(char *, void *, int, float, float);
extern void SetDeathBits(char *, int, int);
extern void moby_update_ground_check(char *);
extern void moby_transform_joint_point(char *, int, float *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(float *, float *, float *);
extern int moby_apply_damage_to_object(char *, void *, int);
extern float fast_vec_dist(void *, void *);
extern float D_001BAFA0[];
extern char *D_001B1C4C MACRO_ADDR;
extern char g_camera_eye_state[];
extern int D_001B1B78 MACRO_ADDR;
extern short *D_001EE5A0[];
extern char *D_001B1B5C MACRO_ADDR;
#define F(p,o) (*(float *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))
#define U(p,o) (*(unsigned char *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
/* Sets up the robot enemy on its first frame, then each frame checks hits and damage. Returns 1 when the enemy should be removed. */
int robot_init_check_health(char *object)
{
    float matrix[16];
    char *data = *(char **)(object + 0x68);
    int status, special;
    char *child;
    short *list;
    char *other;
    if (!U(object,0x20)) {
        F(object,0x2c) *= 1.1f;
        U(object,0x7e) |= 1;
        *(char **)(data+0x18)=data+0x110;
        F(data,0x284) *= 0.017453294f;
        U(data,0x48)=FloatToInt(20.0f);
        U(data,0x4a)=FloatToInt(16.0f);
        if(math_random_int_below(2)==1) H(object,0x34)|=0x8000;
        F(data,0x90)=0.5f;
        F(data,0x94)=0.5f;
        F(data,0x114)=0.5f;
        U(data,0x70)=15;
        I(data,0xa8)=5;
        U(data,0x71)=19;
        U(data,0x72)=21;
        U(data,0x76)=23;
        U(data,0x77)=24;
        F(data,0x7c)=0.10000001f;
        F(data,0x80)=1.0f/15.0f;
        F(data,0x84)=1.0f/240.0f;
        F(data,0x88)=1.0f/120.0f;
        F(data,0x8c)=1.0f/240.0f;
        F(data,0x9c)=0.4f;
        *(char *)(data+0xcc)=-1;*(char *)(data+0xcd)=-1;*(char *)(data+0xce)=-1;*(char *)(data+0xcf)=-1;*(char *)(data+0xd2)=-1;*(char *)(data+0xd3)=-1;
        I(data,0x2c0)=-1;
        F(data,0x110)=0.8f;
        F(data,0x118)=0.4f;
        F(data,0x11c)=0.4f;
        F(data,0x120)=1.134464144706726f;
        F(data,0x140)=0.52359885f;
        F(data,0x13c)=0.0055555557f;
        *(char **)(data+0x158)=data+0x3d0;
        *(char **)(data+0x15c)=data+0x450;
        moby_set_controller_speed_limits(object,0.0044444446f,1.0f/7.5f,0.0011635529808700085f,0.10471977f);
        qcopy(data+0x200,object+0x10);
        U(data,0x2e)=1;
        I(data,0x280)=0;
        F(data,0x210)=1.0f;
        F(data,0x21c)=5.0f;
        F(data,0x220)=10.0f;
        F(data,0x298)=(float)U(data,0x34);
        U(data,0x28)=3;
        moby_transform_joint_to_world(object,0,data+0x380);
        F(data,0x388)+=20.0f;
        moby_transform_joint_to_world(object,0,data+0x390);
        if(CollLine(data+0x390,data+0x380,0,object,0)) qcopy(data+0x380,D_001BAFA0);
        if(!I(data,0x27c) && I(data,0x288)==-1) {
            F(object,0x18)=coll_probe_ground_height_below(object+0x10,0,0.5f);
            moby_set_state((unsigned char *)object,1,0);
            if(U(object,0x43)) anim_start_blended(object,0,0,0);
        } else {
            moby_set_state((unsigned char *)object,3,2);
            if(U(object,0x43)!=11) anim_start_blended(object,11,0,0);
            I(object,0x98)=0;F(data,0x30)=2.5f;
            child=CreateMoby(0xab7 /* moby class 2743 */);
            *(char **)(data+0x2ac)=child;
            if(!child) return 1;
            U(child,0x30)=U(object,0x30);
            H(*(char **)(data+0x2ac),0x32)=H(object,0x32);
            U(*(char **)(data+0x2ac),0x31)=1;
            *(long long *)(*(char **)(data+0x2ac)+0x38)=*(long long *)(object+0x38);
            H(*(char **)(data+0x2ac),0x34)|=0x41;
            qcopy_nc(*(char **)(data+0x2ac)+0x10,object+0x10);
            func_002A0F48(*(char **)(data+0x2ac));
        }
        if(I(data,0x288)!=-1) {
            moby_set_state((unsigned char *)object,2,0);
            qcopy(data+0x380,D_001B1C4C+(I(data,0x288)<<7)+0x30);
            U(object,0x30)=0x80;
        }
    }
    if(U(object,0x31) && fast_vec_dist(object+0x10,g_camera_eye_state)<24.0f) {
        moby_update_ground_check(object);U(object,0x6f)=22;
    }
    moby_transform_joint_to_world(object,0,data+0x390);
    moby_transform_joint_to_world(object,1,data+0x3a0);
    moby_transform_joint_to_world(object,2,data+0x3b0);
    moby_transform_joint_point(object,3,matrix);
    vec_clear_128(data+0x3c0);
    I(data,0x3c8)=0;F(data,0x3c0)=0.25f;
    transform_vector(data+0x3c0,data+0x3c0,matrix);
    FastVecAdd((float *)(data+0x3c0),(float *)(data+0x3c0),matrix+12);
    special=0;
    if(U(data,0x2e)==2) special=1;
    status=moby_apply_damage_to_object(object,data+0x60,0);
    if(status || special) {
        F(data,0x30)=0.5f;
        if(status==5) {I(data,0xf0)=0;F(data,0xf4)=0.8377582f;}
        group_alert_peers_type_a(object);
        if((status==4 || status==5 || special) && D_001B1B78>=U(object,0x21) && moby_count_group_not_in_state(U(object,0x21),-1)>=2) {
            list=D_001EE5A0[U(object,0x21)];
            for (;;) {
                other=(char *)(D_001B1B5C+((*list & 0x7fff)<<8));
                if (*(short *)(other+0xaa)==0xb0a /* moby class 2826 */) {
                    char *d=*(char **)(other+0x68);
                    if (!I(d,0x294)) {I(d,0x294)=1;break;}
                } else if (*(short *)(other+0xaa)==0xb0b /* moby class 2827 */) {
                    char *d=*(char **)(other+0x68);
                    if (!I(d,0x294)) {
                        I(d,0x294)=1;
                        if (!I(data,0x29c)) break;
                    }
                }
                if (*list++ < 0) break;
            }
        }
    }
    I(data,0x258)=weapon_select_aim_target(object,I(data,0x250),F(data,0x268),10.0f,0,0);
        I(data,0x25c)=weapon_select_aim_target(object,I(data,0x254),F(data,0x26c),10.0f,0,0);
        if(F(object,0x18)<90.0f) {
            part_spawn_explosion_with_sparks(object,object+0x10,-1,0.5f,13.0f);
            SetDeathBits(object,0,3);return 1;
        }
    if(special) {robot_destroy_child_cleanup(object);return 1;}
    return 0;
}


extern void moby_mark_spawned(void *);
extern void group_alert_peers_type_a(char *);

/* Removes the enemy's attached child object, then runs the shared cleanup. */
void robot_destroy_child_cleanup(char *object)
{
    char *data = *(char **)(object + 0x68);
    char *child = *(char **)(data + 0x2AC);
    if (child != 0 && *(short *)(child + 0xAA) == 0xAB7 /* moby class 2743 */) {
        moby_mark_spawned(child);
        *(char **)(data + 0x2AC) = 0;
    }
    group_alert_peers_type_a(object);
}

extern void gfx_update_color_fade(char *, char *);
extern int FastDecTimer(void *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern void value_set_and_smooth(char *, char *, int, int, float);

/* Does per-frame upkeep for the enemy: counts its timers down, moves its two limb chains and adds one to its age. */
void robot_update_timers_limbs(char *object)
{
    char *data = *(char **)(object + 0x68);
    char *first;
    gfx_update_color_fade(object, data + 0x50);
    first = data + 0x3D0;
    FastDecTimer(data + 0x270);
    FastDecTimer(data + 0x272);
    moby_update_eased_node(object, first, 5, 0.03f, 0.3f);
    moby_update_eased_node(object, data + 0x450, 6, 0.03f, 0.3f);
    if (*(unsigned short *)(object + 0x96) < 65535)
        (*(unsigned short *)(object + 0x96))++;
    value_set_and_smooth(object, first, 5, 1, 2.5f);
}

/* func_00321FE0 is in the -G8 sibling. */

/* Fills in a blank square picture packet with default corners, texture coordinates and colours. */
void gfx_init_quad_packet_defaults(char *packet)
{
    *(long long *)(packet + 112) = 0LL;
    *(int *)(packet + 80) = 0;
    *(int *)(packet + 84) = 0;
    *(float *)(packet + 88) = 1.0f;
    *(int *)(packet + 92) = 0;
    *(int *)(packet + 96) = 0;
    *(float *)(packet + 100) = 1.0f;
    *(float *)(packet + 104) = 1.0f;
    *(float *)(packet + 108) = 1.0f;
    *(float *)(packet + 8) = -2.0f;
    *(float *)(packet + 24) = 2.0f;
    *(float *)(packet + 40) = -2.0f;
    *(float *)(packet + 56) = 2.0f;
    *(float *)(packet + 4) = -2.0f;
    *(float *)(packet + 36) = 2.0f;
    *(int *)(packet + 0) = 0;
    *(int *)(packet + 16) = 0;
    *(int *)(packet + 32) = 0;
    *(int *)(packet + 48) = 0;
    *(float *)(packet + 12) = 1.0f;
    *(float *)(packet + 28) = 1.0f;
    *(float *)(packet + 44) = 1.0f;
    *(long long *)(packet + 128) = 0x0000FF9000000260LL;
    *(float *)(packet + 20) = -2.0f;
    *(float *)(packet + 52) = 2.0f;
    *(float *)(packet + 60) = 1.0f;
}

/* func_00322138 is in 0031F210-q.c. */

/* Draws a flat flash facing the camera at a spot, first full size and then at half size in a second colour. */
void gfx_draw_camera_facing_flash(int unused, char *pos, int color, int first, int second, float scale)
{
    char packet[144];
    float matrix[16];
    float angles[4];
    float offset[4];
    long long texture;
    float dx, dy;

    gfx_init_quad_packet_defaults(packet);
    *(int *)(packet + 80) = 0;
    *(float *)(packet + 92) = 1.0f;
    *(float *)(packet + 96) = 1.0f;
    *(float *)(packet + 104) = 1.0f;
    *(float *)(packet + 108) = 1.0f;
    *(int *)(packet + 84) = 0;
    *(int *)(packet + 88) = 0;
    *(int *)(packet + 100) = 0;
    texture = GetEffectTextureDescriptor(11);
    *(long long *)(packet + 112) = 0;
    *(long long *)(packet + 120) = texture;
    *(long long *)(packet + 128) = 0xFF9000000260LL;
    *(long long *)(packet + 136) = 0x8000000048LL;
    dx = ((BootAimVector *)g_active_camera)->x_140 - *(float *)pos;
    dy = ((BootAimVector *)g_active_camera)->y_144 - *(float *)(pos + 4);
    *(int *)(packet + 76) = color + first;
    *(int *)(packet + 72) = color + first;
    *(int *)(packet + 68) = color + first;
    *(int *)(packet + 64) = color + first;
    angles[3] = 0;
    angles[2] = mat_fast_helper_a(dx, dy);
    angles[1] = -mat_fast_helper_a(vec_distance_xy(pos, &((BootAimVector *)g_active_camera)->x_140),
                              ((BootAimVector *)g_active_camera)->z_148 - *(float *)(pos + 8));
    angles[0] = math_random_angle();
    euler_to_matrix(matrix, angles);
    FastVecSub(offset, &((BootAimVector *)g_active_camera)->x_140, pos);
    vec_scale_to_length(offset, offset, 0.5f);
    matrix[12] = *(float *)(pos) + offset[0];
    matrix[13] = *(float *)(pos + 4) + offset[1];
    matrix[14] = *(float *)(pos + 8) + offset[2];
    matrix[15] = 1.0f;
    FastVecScale(packet, packet, scale);
    FastVecScale(packet + 16, packet + 16, scale);
    FastVecScale(packet + 32, packet + 32, scale);
    FastVecScale(packet + 48, packet + 48, scale);
    draw_world_quad(packet, matrix, 0);
    *(int *)(packet + 76) = color + second;
    *(int *)(packet + 72) = color + second;
    *(int *)(packet + 68) = color + second;
    *(int *)(packet + 64) = color + second;
    FastVecScale(packet, packet, 0.5f);
    FastVecScale(packet + 16, packet + 16, 0.5f);
    FastVecScale(packet + 32, packet + 32, 0.5f);
    FastVecScale(packet + 48, packet + 48, 0.5f);
    draw_world_quad(packet, matrix, 0);
}



typedef unsigned int JointEffectQuad __attribute__((mode(TI)));
extern void moby_transform_joint_point(char *, int, float *);
extern void FastVecAdd(float *, float *, float *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_range(int, int);
extern void vec_add_random_offset(float *, float);
/* Integer and FP arguments keep their order in the separate EE banks. */
extern int coll_sweep_from_object(char *, float *, float, int, float, float, int, int, int);
extern void *part_spawn_gravity_fade(float *, float *, float, float, float, int, int, int, int, int, int);
extern unsigned char *part_spawn_burst(float *, float *, int, int, int, int,
                                    float, float, float, float, float);
extern unsigned char *D_001F2540[];

/* Effect at an object's joint: func_002A8C28 at the joint and at two points along its axis,
   three grey func_002C65A0 particles at the joint and one func_002C16C0 particle at the near
   point, which at random takes flags 0x48 and the 0x707070 tint. */
void part_spawn_joint_hit_effects(char *object, float *position, int joint, float intensity)
{
    float matrix[16] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float base[4] __attribute__((aligned(16)));
    float near[4] __attribute__((aligned(16)));
    float far[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float drift[4] __attribute__((aligned(16)));
    int i, j;
    float start, end, gravity;
    unsigned char *particle;

    moby_transform_joint_point(object, joint, matrix);
    qcopy(axis, matrix + 4);
    FastVecSub(base, matrix + 12, (char *)position);
    vec_scale_to_length(near, axis, 0.85f);
    vec_scale_to_length(far, axis, 1.6f);
    FastVecAdd(near, near, base);
    FastVecAdd(far, far, base);
    near[2] -= 0.1f;
    far[2] -= 0.1f;
    vec_scale_to_length(velocity, matrix + 4, 0.25f);
    FastVecAdd(velocity, velocity, position);
    coll_sweep_from_object(object, base, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    coll_sweep_from_object(object, near, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    coll_sweep_from_object(object, far, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    for (i = 0; i < 3; i++) {
        vec_add_random_offset(base, 0.1f);
        start = math_random_float_range(0.2f, 0.4f) * 210000.0f;
        end = math_random_float_range(1.0f, 1.5f) * 210000.0f;
        gravity = math_random_signed_float_range(0.0f, 0.01f);
        part_spawn_gravity_fade(base, velocity, start, end, gravity, 7, 0x808080, 30, 127, 32, 0);
    }
    *(JointEffectQuad *)drift = 0;
    drift[2] = 0.1f;
    drift[3] = 1.0f;
    FastVecAdd(drift, drift, position);
    for (j = 0; j < 1; j++) {
        particle = part_spawn_burst(near, drift, 15, 60, 0x606060, 3,
                                 105000.0f, 21000.0f, 1.0f, -0.0002f, 0.0f);
        if (particle) {
            particle[2] = *D_001F2540[23];
            particle[3] = 0x44;
            if (math_random_int_range(0, 1)) {
                unsigned char *payload;
                unsigned short alpha;
                particle[3] = 0x48;
                alpha = 127;
                *(unsigned int *)(particle + 4) = 0x70707F;
                payload = particle + 0x20;
                payload[0x11] = 0x70;
                payload[0x12] = 0x70;
                payload[0x13] = 0x70;
                *(unsigned short *)(payload + 0x1E) = alpha;
            }
        }
    }
}



extern int cam_moby_update(char *);
extern void moby_set_state(unsigned char *, unsigned char, int);
/* Updates a short-lived effect: waits for its animation, then fades out and removes itself. */
void part_update_fading_debris(char *object)
{
    char *data = *(char **)(object + 0x68);
    *(float *)(data + 4) -= 1.0f / 120.0f;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (cam_moby_update(object)) {
            moby_set_state((unsigned char *)object, 1, -1);
            *(unsigned short *)(object + 0x34) |= 0x2800;
        }
        break;
    case 1:
        cam_moby_update(object);
        if (*(unsigned char *)(object + 0x23) < 2)
            moby_mark_spawned(object);
        else
            *(unsigned char *)(object + 0x23) -= 2;
        break;
    }
}

/* func_003248A8 is in 0031F210-init.c. */

extern void group_destroy_attached_parts(char *, char *);
extern void group_alert_peers_type_b(char *);

/* Removes the enemy's attached child object, then runs the shared cleanup. */
void enemy_destroy_child_cleanup_b(char *object)
{
    char *data = *(char **)(object + 0x68);
    char *child;
    group_destroy_attached_parts(object, data + 0x2A0);
    child = *(char **)(data + 0x2E0);
    if (child != 0 && *(short *)(child + 0xAA) == 0xAB7 /* moby class 2743 */) {
        moby_mark_spawned(child);
        *(char **)(data + 0x2E0) = 0;
    }
    group_alert_peers_type_b(object);
}

/* func_00325158 is in 0031F210-turn-g8.c. */

/* func_00325320 is in the -G8 sibling. */

/* Fills in a blank square picture packet with default corners, texture coordinates and colours. */
void gfx_init_quad_packet_defaults_b(char *packet)
{
    *(long long *)(packet + 112) = 0LL;
    *(int *)(packet + 80) = 0;
    *(int *)(packet + 84) = 0;
    *(float *)(packet + 88) = 1.0f;
    *(int *)(packet + 92) = 0;
    *(int *)(packet + 96) = 0;
    *(float *)(packet + 100) = 1.0f;
    *(float *)(packet + 104) = 1.0f;
    *(float *)(packet + 108) = 1.0f;
    *(float *)(packet + 8) = -2.0f;
    *(float *)(packet + 24) = 2.0f;
    *(float *)(packet + 40) = -2.0f;
    *(float *)(packet + 56) = 2.0f;
    *(float *)(packet + 4) = -2.0f;
    *(float *)(packet + 36) = 2.0f;
    *(int *)(packet + 0) = 0;
    *(int *)(packet + 16) = 0;
    *(int *)(packet + 32) = 0;
    *(int *)(packet + 48) = 0;
    *(float *)(packet + 12) = 1.0f;
    *(float *)(packet + 28) = 1.0f;
    *(float *)(packet + 44) = 1.0f;
    *(long long *)(packet + 128) = 0x0000FF9000000260LL;
    *(float *)(packet + 20) = -2.0f;
    *(float *)(packet + 52) = 2.0f;
    *(float *)(packet + 60) = 1.0f;
}


/* Draws a flat flash facing the camera at a spot, first full size and then at half size in a second colour. */
void gfx_draw_camera_facing_flash_b(int unused, char *pos, int color, int first, int second, float scale)
{
    char packet[144];
    float matrix[16];
    float angles[4];
    float offset[4];
    long long texture;
    float dx, dy;

    gfx_init_quad_packet_defaults_b(packet);
    *(int *)(packet + 80) = 0;
    *(float *)(packet + 92) = 1.0f;
    *(float *)(packet + 96) = 1.0f;
    *(float *)(packet + 104) = 1.0f;
    *(float *)(packet + 108) = 1.0f;
    *(int *)(packet + 84) = 0;
    *(int *)(packet + 88) = 0;
    *(int *)(packet + 100) = 0;
    texture = GetEffectTextureDescriptor(11);
    *(long long *)(packet + 112) = 0;
    *(long long *)(packet + 120) = texture;
    *(long long *)(packet + 128) = 0xFF9000000260LL;
    *(long long *)(packet + 136) = 0x8000000048LL;
    dx = ((BootAimVector *)g_active_camera)->x_140 - *(float *)pos;
    dy = ((BootAimVector *)g_active_camera)->y_144 - *(float *)(pos + 4);
    *(int *)(packet + 76) = color + first;
    *(int *)(packet + 72) = color + first;
    *(int *)(packet + 68) = color + first;
    *(int *)(packet + 64) = color + first;
    angles[3] = 0;
    angles[2] = mat_fast_helper_a(dx, dy);
    angles[1] = -mat_fast_helper_a(vec_distance_xy(pos, &((BootAimVector *)g_active_camera)->x_140),
                              ((BootAimVector *)g_active_camera)->z_148 - *(float *)(pos + 8));
    angles[0] = math_random_angle();
    euler_to_matrix(matrix, angles);
    FastVecSub(offset, &((BootAimVector *)g_active_camera)->x_140, pos);
    vec_scale_to_length(offset, offset, 0.5f);
    matrix[12] = *(float *)(pos) + offset[0];
    matrix[13] = *(float *)(pos + 4) + offset[1];
    matrix[14] = *(float *)(pos + 8) + offset[2];
    matrix[15] = 1.0f;
    FastVecScale(packet, packet, scale);
    FastVecScale(packet + 16, packet + 16, scale);
    FastVecScale(packet + 32, packet + 32, scale);
    FastVecScale(packet + 48, packet + 48, scale);
    draw_world_quad(packet, matrix, 0);
    *(int *)(packet + 76) = color + second;
    *(int *)(packet + 72) = color + second;
    *(int *)(packet + 68) = color + second;
    *(int *)(packet + 64) = color + second;
    FastVecScale(packet, packet, 0.5f);
    FastVecScale(packet + 16, packet + 16, 0.5f);
    FastVecScale(packet + 32, packet + 32, 0.5f);
    FastVecScale(packet + 48, packet + 48, 0.5f);
    draw_world_quad(packet, matrix, 0);
}



/* func_00325A88 (cursor bookkeeping and a 16-byte copy) is a near miss:
   nonmatching/game/func_00325A88.c */
/* Saves the enemy's current position into a ring of the four most recent positions, used for a trail. */
void enemy_record_position_trail(char *object) {
    char *state = *(char **)(object + 0x68);

    *(int *)(state + 0x2B8) = 0;
    *(int *)(state + 0x2B4) = (*(int *)(state + 0x2B4) + 1) % 4;
    if (*(int *)(state + 0x2B0) < 4)
        (*(int *)(state + 0x2B0))++;
    mat_build_rotation_from_angles(state + (*(int *)(state + 0x2B4) * 16 + 0x420), (float *)(object + 0xF0));
    qcopy(state + *(int *)(state + 0x2B4) * 16 + 0x320,
          (char *)(*(int *)(state + 0x2A4) + 0x10));
}


/* func_00325B28 is in the -G8 sibling. */

extern char *CreateMoby(int);
extern void moby_init_child_from_parent(void *, void *);
extern void moby_copy_joint_transform_to_object(void *, void *, int, int);
extern void func_002A0F48(void *);

/* Creates the two child parts of the enemy and attaches them to it. */
void enemy_spawn_child_parts(char *self, char **children, int first, int second)
{
    int i;
    for (i = 0; i < 2; i++, children++) {
        *children = CreateMoby(0xAA2 /* moby class 2722 */);
        if (*children != 0) {
            moby_init_child_from_parent(*children, self);
            *(float *)(*children + 0x2C) *= 0.75f;
            {
                char *child = *children;
                if (i != 0)
                    child[0xBC] = second;
                else
                    child[0xBC] = first;
            }
            *(unsigned short *)(*children + 0x32) = *(unsigned short *)(self + 0x32);
            moby_copy_joint_transform_to_object(self, *children, *(unsigned char *)(*children + 0xBC), 0);
            func_002A0F48(*children);
        }
    }
}


/* func_00325D30 and func_00325DA0 are in 0031F210-group-g8.c. */

/* func_00325EC0 is in 0031F210-effects-g8.c. */

/* func_00326198 is in 0031F210-state-g8.c. */





/* negates two floats read from a fixed global table, clamps each to [-1,1] into an object reached through the parameter's +104 pointer, packs the pair into a two-float stack buffer, passes it to two callees and stores the second callee's float return value at object+48 */
void pad_clamp_stick_to_vars(char *obj)
{
    float buf[2];
    char *pad_data = D_00189E20_9;
    char *vars = *(char **)(obj + 104);
    float a, b, value;

    a = -*(float *)(pad_data + 8112);
    *(float *)(vars + 20) = a;
    b = -*(float *)(pad_data + 8116);
    *(float *)(vars + 16) = b;

    if (a > 1.0f) {
        *(float *)(vars + 20) = 1.0f;
    } else if (a < -1.0f) {
        *(float *)(vars + 20) = -1.0f;
    }

    value = *(float *)(vars + 16);
    if (value > 1.0f) {
        *(float *)(vars + 16) = 1.0f;
    } else if (value < -1.0f) {
        *(float *)(vars + 16) = -1.0f;
    }
    func_00282C88_1(buf);
    buf[0] = *(float *)(vars + 16);
    buf[1] = *(float *)(vars + 20);
    *(float *)(vars + 48) = FastVecLength(buf);
}



/* func_00326EC0 is in 0031F210-basis-g8.c. */
