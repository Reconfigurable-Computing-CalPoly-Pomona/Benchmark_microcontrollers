//Using framework created by Dr. Pong P. Chu

#include "chu_init.h"
#include "adder_core.h"
#include "shifter_core.h"
#include "multiplier_core.h"
#include "FPadder_core.h"
#include "FPmultiplier_core.h"
#include "RAM_core.h"
#include "gpio_cores.h"

TimerCore timer(get_slot_addr(BRIDGE_BASE, S0_SYS_TIMER));
GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
AdderCore INTADD(get_slot_addr(BRIDGE_BASE, S4_ADD));
MultCore INTMULT (get_slot_addr(BRIDGE_BASE, S5_MULT));
ShifterCore SHFT (get_slot_addr(BRIDGE_BASE, S7_SHFT));
FPAdderCore FPADD (get_slot_addr(BRIDGE_BASE, S10_FPA));
FPMultCore FPMULT (get_slot_addr(BRIDGE_BASE, S11_FPM));
RAMCore RAM1(get_slot_addr(BRIDGE_BASE, S8_RAM1));
RAMCore RAM2(get_slot_addr(BRIDGE_BASE, S9_RAM2));


int PingIO_Cycles = 0; //keeps track of time taken by processor to complete specific operation
//unsigned int PingIO_OverFlow = 0; //keeps track if any overflow occurs during specific operation
int add_Cycles = 0;
//unsigned int add_OverFlow = 0;
int mult_Cycles = 0;
//unsigned int mult_OverFlow = 0;
int div_Cycles = 0;
//unsigned int div_OverFlow = 0;
int ArrayMath_Cycles = 0;
//unsigned int ArrayMath_OverFlow = 0;
int Shift_Cycles = 0;
//unsigned int Shift_OverFlow = 0;

//-------------------------------------------------//
uint32_t Cycles_Temp = 0;
//unsigned int OverFlow_Temp = 0;
uint32_t Array_A [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32_t Array_C [5][5] = {
{1,2,3,4,5}, {1,2,3,4,5},
{1,2,3,4,5}, {1,2,3,4,5},
{1,2,3,4,5}};


//void initilaizeMC();
void TIMER_RESET();
uint64_t TimerCurrent();
void PingIO();
void add(uint32_t A, uint32_t B);
void mult(uint32_t A, uint32_t B);
void div(uint32_t A, uint32_t B);
void Shift(uint32_t A, uint32_t B);
void ArrayMath(uint32_t A);


void initializeMC(){ //sets MC Ports and Registers to proper values
	for(uint32_t i = 0; i < 10; i++){
		RAM1.Store(i, Array_A[i]);
	}

	for(uint32_t i = 0; i < 5; i++){
		for(uint32_t j = 0; j < 5; j++){
				RAM2.Store((INTADD.Add((INTMULT.Mult(j, 5)), i)), Array_C[j][i]);
			}
	}
}


void TIMER_RESET(){
	timer.clear();
}


uint64_t TimerCurrent(){
    return timer.read_tick();
}

//----------------------does not need change--------------------------//

void PingIO(){ //tests I/O time
   Cycles_Temp = TimerCurrent();
   //OverFlow_Temp = TimeOverFlowCount;
   timer.go(); //starts timer

   led.write(1);
   led.write(0);

   timer.pause(); //stops timer
   PingIO_Cycles += (TimerCurrent() - Cycles_Temp);
   //PingIO_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void add(uint32_t A, uint32_t B){
    Cycles_Temp = TimerCurrent();
    //OverFlow_Temp = TimeOverFlowCount;
    timer.go(); //starts timer

    RAM1.Store(31, INTADD.Add(A, B));

    timer.pause(); //stops timer
    add_Cycles += (TimerCurrent() - Cycles_Temp);
    //add_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void mult(uint32_t A, uint32_t B){
    Cycles_Temp = TimerCurrent();
   // OverFlow_Temp = TimeOverFlowCount;
    timer.go(); //starts timer

    RAM1.Store(31, INTMULT.Mult(A, B));

    timer.pause(); //stops timer
    mult_Cycles += (TimerCurrent() - Cycles_Temp);
   // mult_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

//void div(int A, int B){
//    Cycles_Temp = TimerCurrent();
//    //OverFlow_Temp = TimeOverFlowCount;
//    timer.go(); //starts timer
//
//    C = B/A;
//
//    timer.pause(); //stops timer
//    div_Cycles += (TimerCurrent() - Cycles_Temp);
//    //div_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
//}

void Shift(uint32_t A, uint32_t B){
    Cycles_Temp = TimerCurrent();
    //OverFlow_Temp = TimeOverFlowCount;
    timer.go(); //starts timer

    RAM1.Store(31, SHFT.Shift(B, A));

    timer.pause(); //stops timer
    Shift_Cycles += (TimerCurrent() - Cycles_Temp);
    //Shift_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void ArrayMath(uint32_t A){
    Cycles_Temp = TimerCurrent();
    //OverFlow_Temp = TimeOverFlowCount;
    timer.go(); //starts timer

    for (uint32_t i = 0; i < 10; i++){ //populate Arrays
        RAM1.Store(i, (INTADD.Add(A, i)));
    }

    for (uint32_t i = 0; i < 10; i ++){  //search array, find middle, toggle LED
        if(RAM1.Load(i) == (INTADD.Add(A, 5))){
            break;
        }
    }

   for (uint32_t i = 0; i < 5; i++){ //cross the values
           for(uint32_t j = 0; j < 5;  j++){
               RAM1.Store(31, RAM2.Load((INTADD.Add((INTMULT.Mult(j, 5)), i)))); //C = val1
               RAM2.Store((INTADD.Add((INTMULT.Mult(i, 5)), j)), RAM2.Load(INTADD.Add((INTMULT.Mult(j, 5)), i))); //val1 = val2
               RAM2.Store((INTADD.Add((INTMULT.Mult(j, 5)), i)), RAM1.Load(31));// = RAM1.Load(31); //val2 = val1

           }
   }
    timer.pause(); //stops timer
    ArrayMath_Cycles += (TimerCurrent() - Cycles_Temp);
    //ArrayMath_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}


//----------------------does not need change--------------------------//

int main(){ //benchmark

	uint32_t A = 0x00000005, B = 0x000000FF; //int 5 and int 255
    initializeMC();

    PingIO();
    add(A, B);
    mult(A, B);
    Shift(A, B);
    ArrayMath(A);

//To see output, create UART terminal, BAUD 9600

    uart.disp(PingIO_Cycles);
    uart.disp(", ");
    uart.disp(Shift_Cycles);
    uart.disp(", ");
    uart.disp(add_Cycles);
    uart.disp(", ");
    uart.disp(mult_Cycles);
    uart.disp(", ");
    uart.disp(ArrayMath_Cycles);

    while(1);
}
