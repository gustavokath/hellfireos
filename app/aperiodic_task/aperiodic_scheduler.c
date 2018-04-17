#include <hellfire.h>

void aperiodic_scheduler(void)
{
	tcb_entry* task;
	for(;;){
		task = hf_queue_remhead(krnl_aperiodic_queue);
		if(!task){
			hf_yield();
			continue;
		}

		if(task->apjobs == 0){
			hf_kill(task->id);
			continue;
		}

		task->apjobs--;
		if (hf_queue_addtail(krnl_aperiodic_queue, task))
			panic(PANIC_CANT_PLACE_APERIODIC);
		
		//Executa
	}
}

static tcb_entry* aperiodic_queue_next()
{
	return 
}

void app_main(void){
	int32_t i;
	
	for (i = 0; i < 20; i++)
		hf_spawn(thread, 0, 0, 0, "thread", 1024);
}

