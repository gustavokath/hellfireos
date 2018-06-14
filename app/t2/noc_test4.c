#include <hellfire.h>
#include <noc.h>

void dispatcher(void){
	int32_t i;
	int8_t buf[100];
	int16_t val;
	uint16_t cpu, port, size;
	int8_t status[50];
	int8_t tasks[50];
	int8_t cpus[50];
	int8_t next = 0;
	int8_t temp;

	if (hf_comm_create(hf_selfid(), 100, 0))
		panic(0xff);

	srand(hf_cpuid());

	for (i = 0; i < sizeof(status); i++)
		status[i] = tasks[i] = cpus[i] = 0;

	

	while (1){
		 i = hf_recvprobe();
		 if (i >= 0) {
		 	size = 0;
		 	val = hf_recv(&cpu, &port, buf, &size, i);
			if (size == 10){
				printf("%d - Envia problema para %d %d\n", hf_cpuid(), cpu, port);
				if(next < 50){
					cpus[cpu] = next;
					status[next] = 1;
					val = hf_send(cpu, cpu * 1000, tasks[next], sizeof(tasks[next]), i * 100);
					if (val)
						printf("hf_sendack(): error %d\n", val);
					next++;
				}else{
					val = hf_send(cpu, cpu * 1000, buf, 10, i * 100);
					if (val)
						printf("hf_sendack(): error %d\n", val);
				}
			} else {
				//Coloca resultado final
				temp = cpus[cpu];
				status[temp] = 2;
				tasks[temp] = buf;
				
				//Resolve puzzle
				for (i = 0; i < size; i++)
					printf("%02x ", buf[i]);
				printf(" -> ");

				printf("%d - Recebe resultado de %d\n", hf_cpuid(), cpu);
			}
		}
	}
}

void worker(void){
	int32_t i;
	int8_t buf[100];
	int8_t waiting;
	int16_t val, channel;
	uint16_t cpu, port, size;

	if (hf_comm_create(hf_selfid(), hf_cpuid() * 1000, 0))
		panic(0xff);

	delay_ms(10*hf_cpuid());

	srand(hf_cpuid());

	for (i = 0; i < sizeof(buf); i++)
		buf[i] = random() % 255;

	channel = hf_cpuid();
	waiting = 0;
	while (1){
		if (!waiting){
			val = hf_send(0, 100, buf, 10, channel);
			if (val)
				printf("hf_sendack(): error %d\n", val);
			else
				printf("%d pede novo problema \n", hf_cpuid());
			waiting = 1;
		}

		i = hf_recvprobe();
		if (i >= 0) {
			size = 0;
			val = hf_recv(&cpu, &port, buf, &size, i);
			if (size == 10){
				//Nenhum problema disponivel
				printf("%d - Nenhum problema disponivel\n", hf_cpuid());
				delay_ms(100);
			} else {
				//Resolve puzzle
				for (i = 0; i < size; i++)
					printf("%02x ", buf[i]);
				printf("\n");

				for (i = 0; i < size; i++)
					buf[i] = 1;

				printf("%d - Resolve Puzzle\n", hf_cpuid());
				delay_ms(50);
				val = hf_send(0, 100, buf, size, channel * 10);
				if (val)
					printf("hf_sendack(): error %d\n", val);
			}
			waiting = 0;
		}
	}
}

void app_main(void)
{
	if (hf_cpuid() == 0){
		hf_spawn(dispatcher, 0, 0, 0, "t0", 4096);
	}else{
//		hf_spawn(worker, 0, 0, 0, "t"+hf_cpuid(), 4096);
		hf_spawn(worker, 0, 0, 0, "t800", 4096);
	}
}