/* ISC license. */

#include <time.h>

int main (void)
{
  struct timespec ts ;
  if (clock_gettime(CLOCK_BOOTTIME, &ts) < 0) return 111 ;
  return 0 ;
}
