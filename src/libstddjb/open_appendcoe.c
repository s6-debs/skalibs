/* ISC license. */

#include <skalibs/nonposix.h>
#include <fcntl.h>
#include <skalibs/djbunix.h>

int open_appendcoe (char const *fn)
{
  return open3(fn, O_WRONLY | O_NONBLOCK | O_APPEND | O_CREAT | O_CLOEXEC, 0666) ;
}