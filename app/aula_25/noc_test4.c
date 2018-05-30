#include <hellfire.h>
#include <noc.h>

void t1(void){
	int32_t i;
	uint32_t crc;
	int8_t buf[1280];
	int16_t val, channel;
	
	if (hf_comm_create(hf_selfid(), 1000, 0))
		panic(0xff);
		
	delay_ms(50);

	srand(hf_cpuid());
	
	// generate a unique channel number for this CPU
	channel = hf_cpuid();
	for (i = 0; i < sizeof(buf); i++)
			buf[i] = random() % 255;
	
	//Envia t7
	val = hf_sendack(4, 7000, buf, 1280, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	//Envia t2
	val = hf_sendack(2, 2000, buf, 256, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	//Envia t3
	val = hf_sendack(3, 3000, buf, 64, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	//Envia t4
	val = hf_sendack(1, 4000, buf, 64, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	//Envia t5
	val = hf_sendack(1, 5000, buf, 64, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	while (1){
		//delay_ms(5);
	}
}

void t2(void){
	int32_t i;
	uint32_t crc;
	int8_t buf[1280];
	int16_t val, channel;
	int8_t count = 0;
	uint16_t cpu, port, size;
	
	if (hf_comm_create(hf_selfid(), 2000, 0))
		panic(0xff);
		
	delay_ms(50);

	srand(hf_cpuid());
	
	while (1){
		i = hf_recvprobe();
		if (i >= 0) {
			val = hf_recvack(&cpu, &port, buf, &size, i);
			if (val){
				printf("hf_recvack(): error %d\n", val);
			} else {
				printf("t2 - cpu %d, port %d, channel %d, size %d, crc %08x [free queue: %d]\n", cpu, port, i, size, crc, hf_queue_count(pktdrv_queue));
				if(cpu == 1){
					count++;
				}
			}
		}
		if(count == 1) break;
	}
	
	// generate a unique channel number for this CPU
	channel = hf_cpuid();
	for (i = 0; i < sizeof(buf); i++)
			buf[i] = random() % 255;
	
	//Envia t6
	val = hf_sendack(2, 6000, buf, 64, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	//Envia t7
	val = hf_sendack(4, 7000, buf, 320, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	//Envia t8
	val = hf_sendack(5, 8000, buf, 320, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	while (1){
		//delay_ms(5);
	}
}

void t3(void){
	int32_t i;
	uint32_t crc;
	int8_t buf[1280];
	int16_t val, channel;
	int8_t count = 0;
	uint16_t cpu, port, size;
	
	if (hf_comm_create(hf_selfid(), 3000, 0))
		panic(0xff);
		
	delay_ms(50);

	srand(hf_cpuid());
	
	while (1){
		i = hf_recvprobe();
		if (i >= 0) {
			val = hf_recvack(&cpu, &port, buf, &size, i);
			if (val){
				printf("hf_recvack(): error %d\n", val);
			} else {
				printf("t3 - cpu %d, port %d, channel %d, size %d, crc %08x [free queue: %d]\n", cpu, port, i, size, crc, hf_queue_count(pktdrv_queue));
				if(cpu == 1){
					count++;
				}
			}
		}
		if(count == 1) break;
	}
	
	// generate a unique channel number for this CPU
	channel = hf_cpuid();
	for (i = 0; i < sizeof(buf); i++)
			buf[i] = random() % 255;

	//Envia t7
	val = hf_sendack(4, 7000, buf, 320, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	//Envia t8
	val = hf_sendack(5, 8000, buf, 64, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	while (1){
		//delay_ms(5);
	}
}

void t4(void){
	int32_t i;
	uint32_t crc;
	int8_t buf[1280];
	int16_t val, channel;
	int8_t count = 0;
	uint16_t cpu, port, size;
	
	if (hf_comm_create(hf_selfid(), 4000, 0))
		panic(0xff);
		
	delay_ms(50);

	srand(hf_cpuid());
	
	while (1){
		i = hf_recvprobe();
		if (i >= 0) {
			val = hf_recvack(&cpu, &port, buf, &size, i);
			if (val){
				printf("hf_recvack(): error %d\n", val);
			} else {
				printf("t4 - cpu %d, port %d, channel %d, size %d, crc %08x [free queue: %d]\n", cpu, port, i, size, crc, hf_queue_count(pktdrv_queue));
				if(cpu == 1){
					count++;
				}
			}
		}
		if(count == 1) break;
	}
	
	// generate a unique channel number for this CPU
	channel = hf_cpuid();
	for (i = 0; i < sizeof(buf); i++)
			buf[i] = random() % 255;

	//Envia t8
	val = hf_sendack(5, 8000, buf, 64, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	while (1){
		//delay_ms(5);
	}
}

void t5(void){
	int32_t i;
	uint32_t crc;
	int8_t buf[1280];
	int16_t val, channel;
	int8_t count = 0;
	uint16_t cpu, port, size;
	
	if (hf_comm_create(hf_selfid(), 5000, 0))
		panic(0xff);
		
	delay_ms(50);

	srand(hf_cpuid());
	
	while (1){
		i = hf_recvprobe();
		if (i >= 0) {
			val = hf_recvack(&cpu, &port, buf, &size, i);
			if (val){
				printf("hf_recvack(): error %d\n", val);
			} else {
				printf("t5 - cpu %d, port %d, channel %d, size %d, crc %08x [free queue: %d]\n", cpu, port, i, size, crc, hf_queue_count(pktdrv_queue));
				if(cpu == 1){
					count++;
				}
			}
		}
		if(count == 1) break;
	}
	
	// generate a unique channel number for this CPU
	channel = hf_cpuid();
	for (i = 0; i < sizeof(buf); i++)
			buf[i] = random() % 255;

	//Envia t8
	val = hf_sendack(5, 8000, buf, 640, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	while (1){
		//delay_ms(5);
	}
}

void t6(void){
	int32_t i;
	uint32_t crc;
	int8_t buf[1280];
	int16_t val, channel;
	int8_t count = 0;
	uint16_t cpu, port, size;
	
	if (hf_comm_create(hf_selfid(), 6000, 0))
		panic(0xff);
		
	delay_ms(50);

	srand(hf_cpuid());
	
	while (1){
		i = hf_recvprobe();
		if (i >= 0) {
			val = hf_recvack(&cpu, &port, buf, &size, i);
			if (val){
				printf("hf_recvack(): error %d\n", val);
			} else {
				printf("t6 -cpu %d, port %d, channel %d, size %d, crc %08x [free queue: %d]\n", cpu, port, i, size, crc, hf_queue_count(pktdrv_queue));
				if(cpu == 2){
					count++;
				}
			}
		}
		if(count == 1) break;
	}
	
	// generate a unique channel number for this CPU
	channel = hf_cpuid();
	for (i = 0; i < sizeof(buf); i++)
			buf[i] = random() % 255;
	
	//Envia t9
	val = hf_sendack(0, 9000, buf, 640, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	while (1){
		//delay_ms(5);
	}
}

void t7(void){
	int32_t i;
	uint32_t crc;
	int8_t buf[1280];
	int16_t val, channel;
	int8_t count = 0;
	uint16_t cpu, port, size;
	
	if (hf_comm_create(hf_selfid(), 7000, 0))
		panic(0xff);
		
	delay_ms(50);

	srand(hf_cpuid());
	
	while (1){
		i = hf_recvprobe();
		if (i >= 0) {
			val = hf_recvack(&cpu, &port, buf, &size, i);
			if (val){
				printf("hf_recvack(): error %d\n", val);
			} else {
				printf("t7 - cpu %d, port %d, channel %d, size %d, crc %08x [free queue: %d]\n", cpu, port, i, size, crc, hf_queue_count(pktdrv_queue));
				if(cpu == 1 || cpu == 2 || cpu == 3){
					count++;
				}
			}
		}
		if(count == 3) break;
	}
	
	// generate a unique channel number for this CPU
	channel = hf_cpuid();
	for (i = 0; i < sizeof(buf); i++)
			buf[i] = random() % 255;

	//Envia t9
	val = hf_sendack(0, 9000, buf, 640, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	while (1){
		//delay_ms(5);
	}
}

void t8(void){
	int32_t i;
	uint32_t crc;
	int8_t buf[1280];
	int16_t val, channel;
	int8_t count = 0;
	uint16_t cpu, port, size;
	
	if (hf_comm_create(hf_selfid(), 8000, 0))
		panic(0xff);
		
	delay_ms(50);

	srand(hf_cpuid());
	
	while (1){
		i = hf_recvprobe();
		if (i >= 0) {
			val = hf_recvack(&cpu, &port, buf, &size, i);
			if (val){
				printf("hf_recvack(): error %d\n", val);
			} else {
				printf("t8 - cpu %d, port %d, channel %d, size %d, crc %08x [free queue: %d]\n", cpu, port, i, size, crc, hf_queue_count(pktdrv_queue));
				if(cpu == 1 || cpu == 2 || cpu == 3){
					count++;
				}
			}
		}
		if(count == 4) break;
	}
	
	// generate a unique channel number for this CPU
	channel = hf_cpuid();
	for (i = 0; i < sizeof(buf); i++)
			buf[i] = random() % 255;

	//Envia t9
	val = hf_sendack(0, 9000, buf, 640, channel, 500);
		if (val)
			printf("hf_sendack(): error %d\n", val);

	while (1){
		//delay_ms(5);
	}
}

void t9(void){
	int32_t i;
	uint32_t crc;
	int8_t buf[1280];
	int16_t val, channel;
	int8_t count = 0;
	uint16_t cpu, port, size;
	
	if (hf_comm_create(hf_selfid(), 9000, 0))
		panic(0xff);
		
	delay_ms(50);

	srand(hf_cpuid());
	
	while (1){
		i = hf_recvprobe();
		if (i >= 0) {
			val = hf_recvack(&cpu, &port, buf, &size, i);
			if (val){
				printf("hf_recvack(): error %d\n", val);
			} else {
				printf("t9 - cpu %d, port %d, channel %d, size %d, crc %08x [free queue: %d]\n", cpu, port, i, size, crc, hf_queue_count(pktdrv_queue));
				if(cpu == 2 || cpu == 4 || cpu == 5){
					count++;
				}
			}
		}
		if(count == 3) break;
	}
	
	printf("ACABOUUUUU!");

	while (1){
		//delay_ms(5);
	}
}

void app_main(void)
{
	if (hf_cpuid() == 1){
		hf_spawn(t1, 0, 0, 0, "t1", 4096);
		hf_spawn(t4, 0, 0, 0, "t4", 4096);
		hf_spawn(t5, 0, 0, 0, "t5", 4096);
	}else if(hf_cpuid() == 2){
		hf_spawn(t2, 0, 0, 0, "t2", 4096);
		hf_spawn(t6, 0, 0, 0, "t6", 4096);
	}else if(hf_cpuid() == 3){
		hf_spawn(t3, 0, 0, 0, "t3", 4096);
	}else if(hf_cpuid() == 4){
		hf_spawn(t7, 0, 0, 0, "t7", 4096);
	}else if(hf_cpuid() == 5){
		hf_spawn(t8, 0, 0, 0, "t8", 4096);
	}else if(hf_cpuid() == 0){
		hf_spawn(t9, 0, 0, 0, "t9", 4096);
	}

}