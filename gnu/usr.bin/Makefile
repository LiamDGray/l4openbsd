#	$OpenBSD: Makefile,v 1.47 2010/10/18 17:11:27 deraadt Exp $
#	$NetBSD: Makefile,v 1.35 1996/04/03 21:20:52 chuck Exp $

.include <bsd.own.mk>

.if make(obj)
SUBDIR+=	cc gcc ../egcs/gcc
.else
.  if ${COMPILER_VERSION:L} == "gcc3"
SUBDIR+=	gcc
.  elif ${COMPILER_VERSION:L} == "gcc4"
SUBDIR+=	cc
.  else
SUBDIR+=	../egcs/gcc
.  endif
.endif

SUBDIR+=	cxxfilt cvs lynx binutils

# most ports use binutils gas and ld, some do not (yet).
.if ${ELF_TOOLCHAIN:L} == "no"
SUBDIR+=	gas ld
.endif

# Do these last; texinfo builds the info 'dir' file, perl must be after binutils
SUBDIR+=	perl texinfo

.include <bsd.subdir.mk>
