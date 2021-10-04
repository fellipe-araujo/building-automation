#ifndef GPIO_H
#define GPIO_H

#include <wiringPi.h>

/*
  TÉRREO
    * 04 -> 07 | Lâmpada da Sala 01
    * 17 -> 0  | Lâmpada da Sala 02
    * 27 -> 02 | Luz do Corredor
    * 07 -> 11 | Ar-condicionado
    * 26 -> 25 | Sensor de Presença
    * 23 -> 04 | Sensor de Fumaça
    * 09 -> 13 | Sensor de Janela 01
    * 11 -> 14 | Sensor de Janela 02
    * 10 -> 12 | Sensor de Porta
    * 13 -> 23 | Sensor de Contagem de Entrada
    * 19 -> 24 | Sensor de Contagem de Saída
    * 16 -> 27 | Aspersor de Incêndio
  
  PRIMEIRO ANDAR
    * 22 -> 03 | Lâmpada da Sala 101
    * 25 -> 06 | Lâmpada da Sala 102
    * 08 -> 10 | Luz do Corredor
    * 12 -> 26 | Ar-condicionado
    * 18 -> 01 | Sensor de Presença
    * 24 -> 05 | Sensor de Fumaça
    * 05 -> 21 | Sensor de Janela 101
    * 06 -> 22 | Sensor de Janela 102
*/

// Ground Floor
#define LS_T01 7
#define LS_T02 0
#define LC_T 2
#define AC_T 11
#define SP_T 25
#define SF_T 4
#define SJ_T01 13
#define SJ_T02 14
#define SPo_T 12
#define SC_IN 23
#define SC_OUT 24
#define ASP 27

// First Floor
#define LS_101 3
#define LS_102 6
#define LC_1 10
#define AC_1 26
#define SP_1 1
#define SF_1 5
#define SJ_101 21
#define SJ_102 22

void gpio_setup();
int device_exist(int device);
void* gpio_handler();
void* counter_people_handler();
void change_device_state(int device, int state);
void disable_output_devices();

#endif
