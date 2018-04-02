#include <hellfire.h>

#define N_POMBOS	1
#define N_USERS		30
#define REQ_MSG		20

sem_t mtx_rc, mtx_wc, mtx, w_db, r_db;
sem_t enchendo, mutex, cheia;
int32_t rc = 0, wc = 0, reads = 0, writes = 0;
int32_t contaPostIt = 0;
int32_t* mochila;


void levaMochila(){
	int32_t i;
	for(i=0;i<REQ_MSG;i++){
		mochila[i] = 0;
	}
	contaPostIt = 0;	
}

void addMsgNaMochila(int32_t msg, int32_t user){
	mochila[contaPostIt] = msg;
	contaPostIt++;
	printf("User %d Add MSG: %d\n", user, msg);
}

void usuario(void){
	int32_t t = hf_selfid();
	while(1){
		printf("Usuario %d - Espera para colocar\n", t);
		hf_semwait(&enchendo);
		printf("Usuario %d - Enchendo\n", t);
		hf_semwait(&mutex);
		printf("Usuario %d - Lock mutex\n", t);
		addMsgNaMochila(contaPostIt, t);		
		if (contaPostIt==REQ_MSG){
			printf("Usuario %d - Mochila Cheia\n", t);
			hf_sempost(&cheia);
		}
		hf_sempost(&mutex);
	}
}

void pombo(void){
        mochila = (int32_t*) malloc(REQ_MSG * sizeof(int32_t));
	int32_t i;
	while(1){
		printf("Pombo - Espera Cheia\n");
		hf_semwait(&cheia);
		printf("Pombo - Espera Mutex\n");
		hf_semwait(&mutex);
		printf("Pombo - Leva Mochila\n");
		levaMochila();
		contaPostIt=0;
		for(i=0;i<REQ_MSG;i++)
			hf_sempost(&enchendo);
		hf_sempost(&mutex);
	}
}


void app_main(void){
	int32_t i;

	hf_seminit(&cheia, 0);
	hf_seminit(&mutex, 1);	
	hf_seminit(&enchendo, 20);

	for(i = 0; i < N_POMBOS; i++)
		hf_spawn(pombo, 0, 0, 0, "pombo", 2048);

	for(i = 0; i < N_USERS; i++)
		hf_spawn(usuario, 0, 0, 0, "usuario", 2048);

}

