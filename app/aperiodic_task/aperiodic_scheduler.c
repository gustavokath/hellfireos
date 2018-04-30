#include <hellfire.h>

void aperiodic_scheduler(void)
{
	int32_t rc;
	volatile int32_t status;

	struct tcb_entry* task;
	for(;;){
		
		printf("Scheduler!\n");
		task = hf_queue_remhead(krnl_aperiodic_queue);
		if(!task){
			printf("Scheduler! - No Task\n");
			hf_yield();
			continue;
		}

		if(task->apjobs == 0){
			printf("Scheduler! - No Jobs for %d\n", task->id);
			hf_kill(task->id);
			continue;
		}

		status = _di();
		task->apjobs--;
		if (hf_queue_addtail(krnl_aperiodic_queue, task))
			panic(PANIC_CANT_PLACE_APERIODIC);
		
		printf("Scheduler! - Executing %d\n", task->id);
		krnl_task = &krnl_tcb[krnl_current_task];

		rc = _context_save(krnl_task->task_context);
		if (rc){
			printf("Scheduler! Start Interruption\n");
			_ei(status);
			continue;
		}

		if (krnl_task->state == TASK_RUNNING)
			krnl_task->state = TASK_READY;
		if (krnl_task->pstack[0] != STACK_MAGIC)
			panic(PANIC_STACK_OVERFLOW);

		task->state = TASK_RUNNING;

		_context_restore(task->task_context, 1);
		

	}
}

void periodoc_task(void)
{
	int32_t jobs, id;
	id = hf_selfid();
	for(;;){
		jobs = hf_jobs(id);
		printf("\n%s (%d)[%d][%d]\n", hf_selfname(), id, hf_jobs(id), hf_dlm(id));
		while (jobs == hf_jobs(id));
	}
}

void aperiodic_task(void)
{
	int32_t jobs, id;
	id = hf_selfid();
	for(;;){
		jobs = hf_jobs(id);
		printf("\n%s (%d)[%d][%d]\n", hf_selfname(), id, hf_jobs(id), hf_dlm(id));
		while (jobs == hf_jobs(id));
	}
}

void best_effort_task(void)
{
	int32_t jobs, id;
	id = hf_selfid();
	int32_t r = 0;
	for(;;){
		hf_spawn(aperiodic_task, 0, 3, 0, "aperiodic_task " + r, 1024);
		r = ((random() % 9) + 1) * 50;
		printf("\n%s (%d)[%d][%d] Delay: %d\n", hf_selfname(), id, hf_jobs(id), hf_dlm(id), r);
		delay_ms(r);
	}
}

void app_main(void){
	int32_t i;
	
	hf_spawn(periodoc_task, 3, 1, 2, "periodoc_task 1", 1024);
	hf_spawn(periodoc_task, 5, 1, 2, "periodoc_task 2", 1024);
	hf_spawn(periodoc_task, 10, 1, 2, "periodoc_task 3", 1024);
	hf_spawn(aperiodic_scheduler, 4, 1, 10, "aperiodic_scheduler", 1024);
	
	hf_spawn(best_effort_task, 0, 0, 0, "task creator", 1024);
}

