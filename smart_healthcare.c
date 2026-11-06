/*Cauã Brylkowski dos Santos, Clara Miyamoto Yajima, Turma 4A*/
#include "contiki.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

PROCESS(freq_cardiaca, "Frequência Cardíaca");
PROCESS(sat_sanguinea, "Saturação Sanguínea");
PROCESS(temperatura, "Temperatura");
PROCESS(monitor, "Monitor de saúde");

AUTOSTART_PROCESSES(&freq_cardiaca, &sat_sanguinea, &temperatura, &monitor);



PROCESS_THREAD(freq_cardiaca, ev, data) {

    static struct etimer timer;

    PROCESS_BEGIN();

    etimer_set(&timer, CLOCK_SECOND * 3);

    srand(time(NULL));

    int min = 40;
    int max = 120;

    while(1){

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

        int frequencia_cardiaca = (rand() % (max - min + 1)) + min;

        if(frequencia_cardiaca <= 50){
            process_post(&monitor, PROCESS_EVENT_MSG, (void*) "Frequencia Cardiaca baixa: Bradicardia");
        }else if(frequencia_cardiaca > 110){
            process_post(&monitor, PROCESS_EVENT_MSG, (void*) "Frequencia Cardiaca alta: Taquicardia");
        }

        etimer_reset(&timer);
    }
    PROCESS_END();
}

PROCESS_THREAD(sat_sanguinea, ev, data){

    static struct etimer timer;

    PROCESS_BEGIN();

    etimer_set(&timer, CLOCK_SECOND * 3);

    srand(time(NULL));
    
    int min = 80; 
    int max = 100;
    
    while(1){

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

        int saturacao = (rand() % (max - min + 1) ) + min;

        if(saturacao < 90){
            process_post(&monitor, PROCESS_EVENT_MSG, (void*) "Saturação baixa");
        }else if(saturacao >= 90 && saturacao < 95){
            process_post(&monitor, PROCESS_EVENT_MSG, (void*) "Atenção ao nível de saturação");
        }

        etimer_reset(&timer);
    }
    PROCESS_END();
}

PROCESS_THREAD(temperatura, ev, data){

    static struct etimer timer;

    PROCESS_BEGIN();

    etimer_set(&timer, CLOCK_SECOND * 3);

    srand(time(NULL));

    int min = 25;
    int max = 45;

    while(1){

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

        float temperatura = (rand() % (max - min + 1)) + min;

        if(temperatura > 37){
            process_post(&monitor, PROCESS_EVENT_MSG, (void*) "Febre");
        }else if (temperatura < 35.5){
            process_post(&monitor, PROCESS_EVENT_MSG, (void*) "Hipotermia");
        }

        etimer_reset(&timer);
    }
    PROCESS_END();
}


PROCESS_THREAD(monitor, ev, data){


    PROCESS_BEGIN();
    
    while(1){
        PROCESS_WAIT_EVENT();
        if (ev == PROCESS_EVENT_MSG){
            printf("Alerta emitido: %s\n", (char*) data); 
        }
    }
    PROCESS_END();
}




