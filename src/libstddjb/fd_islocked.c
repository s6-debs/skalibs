/* ISC license. */

#include <fcntl.h>
#include <unistd.h>

#include <skalibs/djbunix.h>

int fd_islocked (int fd)
{
  struct flock fl =
  {
    .l_type = F_RDLCK,
    .l_whence = SEEK_SET,
    .l_start = 0,
    .l_len = 0
  } ;
  return fcntl(fd, F_GETLK, &fl) < 0 ? -1 : fl.l_type != F_UNLCK ;
}
