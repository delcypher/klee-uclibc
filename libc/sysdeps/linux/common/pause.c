/* vi: set sw=4 ts=4: */
/*
 * pause() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#define __UCLIBC_HIDE_DEPRECATED__
#include <sys/syscall.h>
#include <unistd.h>
#include <sysdep-cancel.h>
#include <signal.h>
/* libc_hidden_proto(__sigpause) */
/* libc_hidden_proto(sigblock) */

/* Suspend the process until a signal arrives.
   This always returns -1 and sets errno to EINTR.  */
int
__libc_pause (void)
{
  sigset_t set;

  __sigemptyset (&set);
  sigprocmask (SIG_BLOCK, NULL, &set);

  /* pause is a cancellation point, but so is sigsuspend.
     So no need for anything special here.  */

  return sigsuspend (&set);
}
weak_alias (__libc_pause, pause)

LIBC_CANCEL_HANDLED ();		/* sigsuspend handles our cancellation.  */
