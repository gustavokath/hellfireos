#include <hellfire.h>
#include <noc.h>

void dispatcher(void){
	int32_t i;
	int8_t buf[100];
	int16_t val, channel;
	uint16_t cpu, port, size;

	if (hf_comm_create(hf_selfid(), 1000, 0))
		panic(0xff);

	srand(hf_cpuid());

	for (i = 0; i < sizeof(buf); i++)
		buf[i] = random() % 255;

	channel = hf_cpuid();
	while (1){
		i = hf_recvprobe();
		if (i >= 0) {
			size = 0;
			val = hf_recvack(&cpu, &port, buf, &size, i);
			if (size == 1){
				printf("%d - Envia problema para %d %d\n", hf_cpuid(), cpu, port);
				val = hf_sendack(cpu, port, buf, 1, i, 500);
				if (val)
					printf("hf_sendack(): error %d\n", val);
			} else {
				//Coloca resultado final
				printf("%d - Recebe resultado de %d\n", hf_cpuid(), cpu);
			}
		}
	}
}

void worker(void){
	int32_t i;
	int8_t buf[100];
	int16_t val, channel;
	uint16_t cpu, port, size;

	if (hf_comm_create(hf_selfid(), 2000, 0))
		panic(0xff);

	delay_ms(10*hf_cpuid());

	srand(hf_cpuid());

	for (i = 0; i < sizeof(buf); i++)
		buf[i] = random() % 255;

	channel = hf_cpuid();
	while (1){
		val = hf_sendack(0, 1000, buf, 1, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);
		else
			printf("%d pede novo problema \n", hf_cpuid());

		delay_ms(100);

		i = hf_recvprobe();
		if (i >= 0) {
			size = 0;
			val = hf_recvack(&cpu, &port, buf, &size, i);
			if (size == 1){
				//Nenhum problema disponivel
				printf("%d - Nenhum problema disponivel\n", hf_cpuid());
			} else {
				//Resolve puzzle
				printf("%d - Resolve Puzzle\n", hf_cpuid());
				delay_ms(50);
				// val = hf_sendack(0, 1000, buf, 2, channel, 500);
				// if (val)
				// 	printf("hf_sendack(): error %d\n", val);
			}
		}
	}
}

void app_main(void)
{
	if (hf_cpuid() == 0){
		hf_spawn(dispatcher, 0, 0, 0, "t0", 4096);
	}else{
		hf_spawn(worker, 0, 0, 0, "t"+hf_cpuid(), 4096);
	}
}