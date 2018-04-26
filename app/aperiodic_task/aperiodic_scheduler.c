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

		// task->state = TASK_RUNNING;

		// _context_restore(task->task_context, 1);
		

	}
}

void task1(void)
{
	int32_t jobs, id;
	id = hf_selfid();
	for(;;){
		jobs = hf_jobs(id);
		printf("Task Melhor esforco\n");
		//printf("\n%s (%d)[%d][%d]", hf_selfname(), id, hf_jobs(id), hf_dlm(id));
		while (jobs == hf_jobs(id));
	}
}

void task2(void)
{
	int32_t jobs, id;
	id = hf_selfid();
	for(;;){
		jobs = hf_jobs(id);
		printf("Task Aperiodica\n");
		//printf("\n%s (%d)[%d][%d]", hf_selfname(), id, hf_jobs(id), hf_dlm(id));
		while (jobs == hf_jobs(id));
	}
}

void task3(void)
{
	int32_t jobs, id;
	id = hf_selfid();
	for(;;){
		jobs = hf_jobs(id);
		printf("Task Periodica\n");
		//printf("\n%s (%d)[%d][%d]", hf_selfname(), id, hf_jobs(id), hf_dlm(id));
		while (jobs == hf_jobs(id));
	}
}

void app_main(void){
	int32_t i;
	
	
	//hf_spawn(task1, 0, 0, 0, "task1", 1024);
	hf_spawn(task2, 0, 3, 0, "task2", 1024);
	//hf_spawn(task3, 3, 1, 2, "task3", 1024);
	hf_spawn(aperiodic_scheduler, 10, 1, 10, "aperiodic_scheduler", 1024);
	
	
}

