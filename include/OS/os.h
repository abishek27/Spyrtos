#ifndef OS_H
#define OS_H
#include <OS/tasks.h>
#include <OS/os_cpu.h>
struct sem_data
{
	struct tcb *tcb_ptr;
	struct sem_data *next;
	struct sem_data *prev;
};

struct queue_data
{
	
	struct sem_data *mut_ptr_head;
	struct sem_data *mut_ptr_tail;
};

struct semaphore
{
	struct sem_data *sem_ptr_head;
	struct sem_data *sem_ptr_tail;
	int16_t sem_count;
};

struct mutex
{
	struct sem_data *mut_ptr_head;
	struct sem_data *mut_ptr_tail;
	struct tcb *owner_tcb;
	uint8_t highest_prio;
	uint8_t lock;
};

struct dly_data
{
	struct tcb *dly_tcb;
	struct dly_data *next;
	struct dly_data	*prev;
	uint32_t remain_time;
};
extern void os_sem_create(struct semaphore *sem, uint16_t);
extern void os_sem_wait(struct semaphore *sem);
extern void os_sem_signal(struct semaphore *sem);
extern void os_block(struct queue_data *sem);
extern void os_release(struct semaphore *sem);
extern struct sem_data *os_delete_semqueue(struct semaphore *sem);
extern void os_add_semqueue(struct semaphore *sem, struct sem_data *temp);
extern void os_dly_list_insert(struct tcb *temp,uint32_t time);
extern uint8_t os_sched_state;
extern uint32_t os_int_cntr;
extern uint32_t os_clk_cntr;
extern struct dly_data *os_dly_list_head;
extern struct dly_data *os_dly_list_tail;
extern struct semaphore os_dly_sem;
extern void os_context_switch(void);
extern void os_scheduler(void);
extern void os_init(void);
extern void os_first_task(void);
extern void os_change_prio(struct tcb *, uint8_t);
extern struct tcb *new_high_tcb;
extern struct tcb *current_tcb;
extern uint8_t os_leading_zeros(uint32_t);
extern uint8_t os_get_highest_priority(void);
extern void os_add_ready_list(struct tcb *temp);
extern void os_remove_ready_list(struct tcb *temp);
extern void os_start(void);
#endif
