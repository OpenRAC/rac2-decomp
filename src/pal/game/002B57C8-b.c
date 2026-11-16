#include "include_asm.h"
#include "names.h"
typedef unsigned char QwenRecovery_84e23fd54f9f_AbiByte16;
extern int moby_step_controller(QwenRecovery_84e23fd54f9f_AbiByte16 *owner, QwenRecovery_84e23fd54f9f_AbiByte16 *input, float factor);

/* Steps the moby controller toward the moby's own position with the given factor (PAL). */
int moby_step_at_own_position_factor_pal(QwenRecovery_84e23fd54f9f_AbiByte16 *moby, float factor)
{
    return moby_step_controller(moby, moby + 0x10, factor);
}
