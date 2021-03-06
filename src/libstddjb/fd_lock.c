/* ISC license. */

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <skalibs/error.h>
#include <skalibs/djbunix.h>

int fd_lock (int fd, int w, int nb)
{
  struct flock fl =
  {
    .l_type = w ? F_WRLCK : F_RDLCK,
    .l_whence = SEEK_SET,
    .l_start = 0,
    .l_len = 0
  } ;
  int e = errno ;
  int r ;
  do r = fcntl(fd, nb ? F_SETLK : F_SETLKW, &fl) ;
  while (r < 0 && errno == EINTR) ;
  return r >= 0 ? 1 :
    errno == EACCES || error_isagain(errno) ? (errno = e, 0) :
    -1 ;
}
