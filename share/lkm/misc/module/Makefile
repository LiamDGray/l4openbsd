#	$OpenBSD: Makefile,v 1.3 2000/03/02 14:46:36 todd Exp $
#
# Makefile for miscmod
#
# 05 Jun 93	Terry Lambert		Original
#
# Copyright (c) 1993 Terrence R. Lambert.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#      This product includes software developed by Terrence R. Lambert.
# 4. The name Terrence R. Lambert may not be used to endorse or promote
#    products derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY TERRENCE R. LAMBERT ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE TERRENCE R. LAMBERT BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
#

SRCS=miscmod.c
OBJS=$(SRCS:.c=.o)

KSRCS=misccall.c
KOBJS=misccall.o

MODOBJ=combined.o

KMOD=miscmod
CFLAGS+= -D_KERNEL -I/sys

all:	$(MODOBJ)

clean:
	rm -f $(OBJS) $(KOBJS) $(MODOBJ) $(KMOD)

load:
	modload -o $(KMOD) -e$(KMOD) $(MODOBJ)

unload:
	modunload -n $(KMOD)

$(MODOBJ): $(OBJS) $(KOBJS)
	$(LD) -r -o $(MODOBJ) $(OBJS) $(KOBJS)

#
# EOF -- This file has not been truncated
#
