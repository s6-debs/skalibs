/* ISC license. */

/* MT-unsafe */

#include <errno.h>
#include <signal.h>
#include <skalibs/sysdeps.h>
#include "selfpipe-internal.h"
#include <skalibs/selfpipe.h>

#ifdef SKALIBS_HASSIGNALFD

#include <sys/signalfd.h>

int selfpipe_trap (int sig)
{
  sigset_t ss = selfpipe_caught ;
  sigset_t old ;
  if (selfpipe_fd < 0) return (errno = EBADF, -1) ;
  if ((sigaddset(&ss, sig) < 0) || (sigprocmask(SIG_BLOCK, &ss, &old) < 0))
    return -1 ;
  if (signalfd(selfpipe_fd, &ss, SFD_NONBLOCK | SFD_CLOEXEC) < 0)
  {
    int e = errno ;
    sigprocmask(SIG_SETMASK, &old, 0) ;
    errno = e ;
    return -1 ;
  }
  selfpipe_caught = ss ;
  return 0 ;
}

#else

#include <skalibs/sig.h>

int selfpipe_trap (int sig)
{
  if (selfpipe_fd < 0) return (errno = EBADF, -1) ;
  if (sig_catcha(sig, &selfpipe_ssa) < 0) return -1 ;
  if (sigprocmask(SIG_UNBLOCK, sig, 0) < 0 || sigaddset(&selfpipe_caught, sig) < 0)
  {
    int e = errno ;
    sig_restore(sig) ;
    errno = e ;
    return -1 ;
  }
  return 0 ;
}

#endif
