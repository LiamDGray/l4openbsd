/*	$OpenBSD: cpufunc.h,v 1.17 2010/08/19 19:31:53 kettenis Exp $	*/
/*	$NetBSD: cpufunc.h,v 1.8 1994/10/27 04:15:59 cgd Exp $	*/

/*
 * Copyright (c) 1993 Charles Hannum.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Charles Hannum.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _I386_CPUFUNC_H_
#define	_I386_CPUFUNC_H_

#ifdef _KERNEL

/*
 * Functions to provide access to i386-specific instructions.
 */

#include <sys/cdefs.h>
#include <sys/types.h>

#include <machine/specialreg.h>

#ifdef L4

#include <sys/systm.h>
#include <sys/proc.h>
#include <machine/l4/vcpu.h>

#include <l4/sys/types.h>
#include <l4/sys/segment.h>

#define  L4XV_V(n) l4vcpu_irq_state_t n
#define  L4XV_L(n) do {	n = l4vcpu_irq_disable_save(l4x_vcpu_state(cpu_number()));\
		      } while (0)
#define  L4XV_U(n) do { if (n & L4VCPU_IRQ_STATE_ENABLED) 	\
				enable_intr(); 			\
		      } while (0)
/* tamed.c */
void l4x_global_cli(void);
void l4x_global_sti(void);

#endif	/* L4 */

static __inline void invlpg(u_int);
static __inline void lidt(void *);
static __inline void lldt(u_short);
static __inline void ltr(u_short);
static __inline void lcr0(u_int);
static __inline u_int rcr0(void);
static __inline u_int rcr2(void);
static __inline void lcr3(u_int);
static __inline u_int rcr3(void);
static __inline void lcr4(u_int);
static __inline u_int rcr4(void);
static __inline void tlbflush(void);
static __inline void tlbflushg(void);
static __inline void disable_intr(void);
static __inline void enable_intr(void);
static __inline u_int read_eflags(void);
static __inline void write_eflags(u_int);
static __inline void wbinvd(void);
static __inline void clflush(u_int32_t addr);
static __inline void mfence(void);
static __inline void wrmsr(u_int, u_int64_t);
static __inline u_int64_t rdmsr(u_int);
static __inline void breakpoint(void);

static __inline void 
invlpg(u_int addr)
{ 
#ifndef L4	/* L4 does not invalidate pages */
        __asm __volatile("invlpg (%0)" : : "r" (addr) : "memory");
#endif
}  

static __inline void
lidt(void *p)
{
#ifndef L4
	__asm __volatile("lidt (%0)" : : "r" (p) : "memory");
#endif
}

static __inline void
lldt(u_short sel)
{
#ifdef L4
//	L4XV_V(f);
//	unsigned long addr = sel;	/* very nasty conversion */
//	L4XV_L(f);
//	fiasco_ldt_set(L4_INVALID_CAP /* XXX cl */, (void *)addr,
//			NGDT * sizeof(union descriptor) - 1, 0, l4_utcb());
//	L4XV_U(f);
#else /* !L4 */
	__asm __volatile("lldt %0" : : "r" (sel));
#endif
}

static __inline void
ltr(u_short sel)
{
#ifndef L4
	__asm __volatile("ltr %0" : : "r" (sel));
#endif
}

static __inline void
lcr0(u_int val)
{
#ifndef L4
	__asm __volatile("movl %0,%%cr0" : : "r" (val));
#endif
}

static __inline u_int
rcr0(void)
{
	u_int val;
#ifdef L4
	val = 0;
#else
	__asm __volatile("movl %%cr0,%0" : "=r" (val));
#endif
	return val;
}

static __inline u_int
rcr2(void)
{
	u_int val;
#ifdef L4
	struct proc *p = curproc;
	val = p->p_md.md_pfa;
#else
	__asm __volatile("movl %%cr2,%0" : "=r" (val));
#endif
	return val;
}

static __inline void
lcr3(u_int val)
{
#ifndef L4
	__asm __volatile("movl %0,%%cr3" : : "r" (val));
#endif
}

static __inline u_int
rcr3(void)
{
	u_int val;
#ifdef L4
	val = 0;
#else
	__asm __volatile("movl %%cr3,%0" : "=r" (val));
#endif
	return val;
}

static __inline void
lcr4(u_int val)
{
#ifndef L4
	__asm __volatile("movl %0,%%cr4" : : "r" (val));
#endif
}

static __inline u_int
rcr4(void)
{
	u_int val;
#ifdef L4
	val = 0;
#else
	__asm __volatile("movl %%cr4,%0" : "=r" (val));
#endif
	return val;
}

/* L4BSD does not handle TLB flushing */
static __inline void
tlbflush(void)
{
#ifndef L4
	u_int val;
	__asm __volatile("movl %%cr3,%0" : "=r" (val));
	__asm __volatile("movl %0,%%cr3" : : "r" (val));
#endif
}

static __inline void
tlbflushg(void)
{
#ifndef L4
	/*
	 * Big hammer: flush all TLB entries, including ones from PTE's
	 * with the G bit set.  This should only be necessary if TLB
	 * shootdown falls far behind.
	 *
	 * Intel Architecture Software Developer's Manual, Volume 3,
	 *	System Programming, section 9.10, "Invalidating the
	 * Translation Lookaside Buffers (TLBS)":
	 * "The following operations invalidate all TLB entries, irrespective
	 * of the setting of the G flag:
	 * ...
	 * "(P6 family processors only): Writing to control register CR4 to
	 * modify the PSE, PGE, or PAE flag."
	 *
	 * (the alternatives not quoted above are not an option here.)
	 *
	 * If PGE is not in use, we reload CR3 for the benefit of
	 * pre-P6-family processors.
	 */

	if (cpu_feature & CPUID_PGE) {
		u_int cr4 = rcr4();
		lcr4(cr4 & ~CR4_PGE);
		lcr4(cr4);
	} else
		tlbflush();
#endif /* !L4 */
}

#ifdef notyet
void	setidt(int idx, /*XXX*/caddr_t func, int typ, int dpl);
#endif


/* XXXX ought to be in psl.h with spl() functions */

static __inline void
disable_intr(void)
{
#ifdef L4
	l4x_global_cli();
#else
	__asm __volatile("cli");
#endif
}

static __inline void
enable_intr(void)
{
#ifdef L4
	l4x_global_sti();
#else
	__asm __volatile("sti");
#endif
}

static __inline u_int
read_eflags(void)
{
	u_int ef;

	__asm __volatile("pushfl; popl %0" : "=r" (ef));
	return (ef);
}

static __inline void
write_eflags(u_int ef)
{
	__asm __volatile("pushl %0; popfl" : : "r" (ef));
}

static __inline void
wbinvd(void)
{
        __asm __volatile("wbinvd");
}

static __inline void
clflush(u_int32_t addr)
{
	__asm __volatile("clflush %0" : "+m" (addr));
}

static __inline void
mfence(void)
{
	__asm __volatile("mfence" : : : "memory");
}

static __inline void
wrmsr(u_int msr, u_int64_t newval)
{
#ifndef L4
        __asm __volatile("wrmsr" : : "A" (newval), "c" (msr));
#endif
}

static __inline u_int64_t
rdmsr(u_int msr)
{
        u_int64_t rv;

        __asm __volatile("rdmsr" : "=A" (rv) : "c" (msr));
        return (rv);
}

/* 
 * Some of the undocumented AMD64 MSRs need a 'passcode' to access.
 *
 * See LinuxBIOSv2: src/cpu/amd/model_fxx/model_fxx_init.c
 */

#define	OPTERON_MSR_PASSCODE	0x9c5a203a
 
static __inline u_int64_t
rdmsr_locked(u_int msr, u_int code)
{
	uint64_t rv;
	__asm volatile("rdmsr"
	    : "=A" (rv)
	    : "c" (msr), "D" (code));
	return (rv);
}

static __inline void
wrmsr_locked(u_int msr, u_int code, u_int64_t newval)
{
	__asm volatile("wrmsr"
	    :
	    : "A" (newval), "c" (msr), "D" (code));
}

/* Break into DDB/KGDB. */
static __inline void
breakpoint(void)
{
	__asm __volatile("int $3");
}

#define read_psl()	read_eflags()
#define write_psl(x)	write_eflags(x)

void amd64_errata(struct cpu_info *);

#endif /* _KERNEL */
#endif /* !_I386_CPUFUNC_H_ */
