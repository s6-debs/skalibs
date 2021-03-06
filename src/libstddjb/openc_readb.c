/* ISC license. */

#include <skalibs/djbunix.h>

int openc_readb (char const *fn)
{
  int fd = openc_read(fn) ;
  if (fd < 0) return -1 ;
  if (ndelay_off(fd) < 0)
  {
    fd_close(fd) ;
    return -1 ;
  }
  return fd ;
}
