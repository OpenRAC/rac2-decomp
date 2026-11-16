#include "include_asm.h"

#include "common.h"
void part_kill(void *);
int FastDecTimer(short *);

/* Counts down the particle timer and removes the particle when it runs out. */
void part_expire_on_timer_pal(void *particle)
{
  int expired;

  expired = FastDecTimer((short *)((char *)particle + 10));
  if (expired != 0) {
    part_kill(particle);
  }
  return;
}
