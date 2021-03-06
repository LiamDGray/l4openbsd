/*
 * License:
 * This file is largely based on code from the L4Linux project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. This program is distributed in
 * the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 */

#ifndef __ASM_L4__GENERIC__VCPU_H__
#define __ASM_L4__GENERIC__VCPU_H__

/* #ifdef CONFIG_L4_VCPU */

#include <machine/cpu.h>
//#include <machine/cpufunc.h>
#include <machine/frame.h>

#include <l4/sys/types.h>
#include <l4/sys/vcpu.h>
#include <l4/sys/utcb.h>
#include <l4/vcpu/vcpu.h>

/* vCPU FPU state for each CPU */
struct l4x_arch_cpu_fpu_state {
	int enabled;
};

struct l4x_arch_cpu_fpu_state l4x_cpu_fpu_state[MAXCPUS];
struct l4x_arch_cpu_fpu_state *l4x_fpu_get(unsigned cpu);
void l4x_fpu_set(int on_off);

/* vCPU state for each CPU */
extern l4_vcpu_state_t *l4x_vcpu_states[MAXCPUS];	/* main.c */

static inline
l4_vcpu_state_t *l4x_vcpu_state(int cpu)
{
	return l4x_vcpu_states[cpu];
}

void l4x_vcpu_handle_irq(l4_vcpu_state_t *t, struct trapframe *regs);
//void l4x_vcpu_handle_ipi(struct pt_regs *regs);
int l4x_run_irq_handlers(int irq, struct trapframe *regs);

void l4x_vcpu_entry(void);	/* vCPU entry point for interrupts */
void l4x_spllower(void);	/* Xspllower() for vCPU */
void l4x_run_asts(struct trapframe *tf);
void l4x_fake_int3(void);	/* emulate int3 */
void l4x_do_vcpu_irq(l4_vcpu_state_t *);	/* emulate interrupt */
void l4x_recurse_irq_handlers(int);		/* recurse interrupts */
void *l4x_intr_establish(int, int, int, int (*)(void *), void *, const char *);

void l4x_intr_set(int irq, struct intrhand *);
void l4x_intr_clear(int irq);

void l4x_vcpu_create_user_task(struct proc *p);

static inline void l4x_vcpu_init(l4_vcpu_state_t *v)
{
	v->state     = L4_VCPU_F_EXCEPTIONS | L4_VCPU_F_PAGE_FAULTS;
	v->entry_ip  = (l4_addr_t)&l4x_vcpu_entry;
	v->user_task = L4_INVALID_CAP;
}

/* #else */
#if 0

#define  L4XV_V(n)
#define  L4XV_L(n) do {} while (0)
#define  L4XV_U(n) do {} while (0)

#endif

#endif /* ! __ASM_L4__GENERIC__VCPU_H__ */
