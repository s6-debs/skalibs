/* ISC license. */

#include <skalibs/bsdsnowflake.h>
#include <errno.h>
#include <skalibs/biguint.h>

int bu_subc (uint32_t *c, unsigned int cn, uint32_t const *a, unsigned int an, uint32_t const *b, unsigned int bn, int carry)
{
  unsigned int i = 0 ;
  for (; i < cn ; i++)
  {
    uint32_t ai = (i < an) ? a[i] : 0 ;
    uint32_t bi = (i < bn) ? b[i] : 0 ;
    uint32_t ci = ai - bi - carry ;
    carry = (carry || bi) && (ci > ai) ;
    c[i] = ci ;
  }
  return carry ? (errno = EOVERFLOW, 0) : 1 ;
}
