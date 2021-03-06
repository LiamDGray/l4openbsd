/*	$OpenBSD: midi.h,v 1.9 2010/06/04 06:15:28 ratchov Exp $	*/
/*
 * Copyright (c) 2008 Alexandre Ratchov <alex@caoua.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef MIDI_H
#define MIDI_H

struct dev;

struct aproc *thru_new(char *);
struct aproc *ctl_new(char *, struct dev *);

int ctl_slotnew(struct aproc *, char *, struct ctl_ops *, void *, int);
void ctl_slotdel(struct aproc *, int);
void ctl_slotvol(struct aproc *, int, unsigned);
int  ctl_slotstart(struct aproc *, int);
void ctl_slotstop(struct aproc *, int);
void ctl_ontick(struct aproc *, int);

void ctl_stop(struct aproc *);
void ctl_start(struct aproc *);
int ctl_idle(struct aproc *);

#endif /* !defined(MIDI_H) */
