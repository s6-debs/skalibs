/* ISC license. */

#include <skalibs/bsdsnowflake.h>
#include <errno.h>
#include <skalibs/bitarray.h>
#include <skalibs/biguint.h>

int bu_scan (char const *s, size_t len, uint32_t *x, unsigned int xn, size_t zeron)
{
  size_t n = bitarray_div8(zeron) ;
  if (xn < n) return (errno = EOVERFLOW, 0) ;
  bu_scan_internal(s, len, x) ;
  bu_zero(x + n, xn - n) ;
  return 1 ;
}
