#include "names.h"
/* func_PAL_L00_003F9B90, the PAL copy of func_L00_003F5750: the same C, where 0.016666668f becomes
   0.020000001f. */
#include "include_asm.h"
#include "common.h"

extern char *level_get_slot_body(int a0, int a1);

extern void vaporizer_set_chain_joint_offset(char *rec, int index);

extern float IntToFloat(int);
extern float math_wrap_angle_to_pi(float);
extern float math_random_float_range(float,float);
extern float math_random_signed_float_range(float,float);
extern float g_vaporizer_joint_angle_min __attribute__((sda));
extern float g_vaporizer_joint_angle_max __attribute__((sda));
extern float g_vaporizer_joint_angle_step __attribute__((sda));
extern float g_vaporizer_joint_length __attribute__((sda));
extern float g_vaporizer_joint_spin_min __attribute__((sda));
extern float g_vaporizer_joint_spin_max __attribute__((sda));

typedef struct {
    float offset[4];
    float position[4];
    float angle;
    float length;
    float f28;
    float f2c;
} L00Joint;

/* Places one joint of a table entry's chain at `position`: its angle, length and two
   rates come from level tuning values, then func_L00_003F5870 lays out its offset and
   the entry's joint count advances. The record offset is computed once and added to the
   reloaded chain pointer at every store, as retail's addu order shows. */
void vaporizer_add_chain_joint_pal(char *object, char *position)
{
    char *state = *(char **)(object + 0x68);
    char **table = (char **)level_get_slot_body(0xc04, *(short *)(state + 0x1a));
    short index = *(short *)(state + 0x20);
    char **entry;
    int offset = index * 0x30;
    entry = (char **)((*(short *)(state + 0x18) << 2) + (int)table);
    qcopy(((L00Joint *)(offset + (int)*entry))->position, position);
    ((L00Joint *)(offset + (int)*entry))->angle = math_wrap_angle_to_pi(IntToFloat(index) * 0.017453294f * g_vaporizer_joint_angle_step);
    ((L00Joint *)(offset + (int)*entry))->f28 = math_random_float_range(g_vaporizer_joint_angle_min, g_vaporizer_joint_angle_max) * 0.017453294f;
    ((L00Joint *)(offset + (int)*entry))->length = g_vaporizer_joint_length;
    ((L00Joint *)(offset + (int)*entry))->f2c = math_random_signed_float_range(g_vaporizer_joint_spin_min, g_vaporizer_joint_spin_max) * 0.020000001f;
    vaporizer_set_chain_joint_offset(*entry, index);
    (*(unsigned short *)(state + 0x20))++;
}
