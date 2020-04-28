/*****************************************************************//**
 *
 * @brief Basic test of nexys4 ddr mmio cores
 *
 * @author p chu
 * @version v1.0: initial release
 *********************************************************************/

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


//unsigned int TimeOverFlowCount = 0; //keeps track of all timer overflows

int PingIO_Cycles = 0; //keeps track of time taken by processor to complete specific operation
//unsigned int PingIO_OverFlow = 0; //keeps track if any overflow occurs during specific operation
int FPadd_Cycles = 0;
//unsigned int add_OverFlow = 0;
int FPmult_Cycles = 0;
//unsigned int mult_OverFlow = 0;
//int FPdiv_Cycles = 0;
//unsigned int div_OverFlow = 0;
int FPArrayMath_Cycles = 0;
//unsigned int ArrayMath_OverFlow = 0;
int Shift_Cycles = 0;
//unsigned int Shift_OverFlow = 0;

//-------------------------------------------------//
unsigned int Cycles_Temp = 0;
//unsigned int OverFlow_Temp = 0;
//float C = 0;
//int F = 0;
uint32_t Array_A [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32_t Array_C [5][5] = {
{1,2,3,4,5}, {1,2,3,4,5},
{1,2,3,4,5}, {1,2,3,4,5},
{1,2,3,4,5}};


//void initilaizeMC();
void TIMER_RESET();
uint64_t TimerCurrent();
void PingIO();
void FPadd(uint32_t A, uint32_t B);
void FPmult(uint32_t A, uint32_t B);
//void div(int A, int B);
//void FPdiv(float A, float B);
void FPArrayMath(uint32_t A);


void initializeMC(){ //sets MC Ports and Registers to proper values
	for(int i = 0; i < 10; i++){
		RAM1.FPStore(i, Array_A[i]);
	}

	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
				RAM2.FPStore((INTADD.Add((INTMULT.Mult(j, 5)), i)), Array_C[j][i]);
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

void FPadd(uint32_t A, uint32_t B){
    Cycles_Temp = TimerCurrent();
    //OverFlow_Temp = TimeOverFlowCount;
    timer.go(); //starts timer

    RAM1.FPStore(31, FPADD.Add(A, B));

    timer.pause(); //stops timer
    FPadd_Cycles += (TimerCurrent() - Cycles_Temp);
    //add_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void FPmult(uint32_t A, uint32_t B){
    Cycles_Temp = TimerCurrent();
   // OverFlow_Temp = TimeOverFlowCount;
    timer.go(); //starts timer

    RAM1.FPStore(31, FPMULT.FPMult(A, B));

    timer.pause(); //stops timer
    FPmult_Cycles += (TimerCurrent() - Cycles_Temp);
   // mult_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

//FPvoid div(int A, int B){
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

void Shift(int A, int B){
    Cycles_Temp = TimerCurrent();
    //OverFlow_Temp = TimeOverFlowCount;
    timer.go(); //starts timer

    RAM1.Store(31, SHFT.Shift(B, A));

    timer.pause(); //stops timer
    Shift_Cycles += (TimerCurrent() - Cycles_Temp);
    //Shift_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void FPArrayMath(uint32_t A){
    Cycles_Temp = TimerCurrent();
    //OverFlow_Temp = TimeOverFlowCount;
    timer.go(); //starts timer

    for (uint32_t i = 0; i < 10; i++){ //populate Arrays
        RAM1.FPStore(i, (FPADD.Add(A, i)));
    }

    for (uint32_t i = 0; i < 10; i ++){  //search array, find middle, toggle LED
        if(RAM1.FPLoad(i) == (FPADD.Add(A, 5))){
            break;
        }
    }

   for (uint32_t i = 0; i < 5; i++){ //cross the values
           for(uint32_t j = 0; j < 5;  j++){
               RAM1.FPStore(31, RAM2.FPLoad((INTADD.Add((INTMULT.Mult(j, 5)), i)))); //C = val1
               RAM2.FPStore((INTADD.Add((INTMULT.Mult(i, 5)), j)), RAM2.FPLoad(INTADD.Add((INTMULT.Mult(j, 5)), i))); //val1 = val2
               RAM2.FPStore((INTADD.Add((INTMULT.Mult(j, 5)), i)), RAM1.FPLoad(31));// = RAM1.Load(31); //val2 = val1

           }
   }
    timer.pause(); //stops timer
    FPArrayMath_Cycles += (TimerCurrent() - Cycles_Temp);
    //ArrayMath_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}


//----------------------does not need change--------------------------//

int main(){ //benchmark
	uint32_t A = 0x40a1999a, B = 0x437f0687; //hex rep of float values 5.05, 255.0255

    initializeMC();

    PingIO();
    FPadd(A, B);
    FPmult(A, B);
    Shift(A, B);
    FPArrayMath(A);

    uart.disp(PingIO_Cycles);
    uart.disp(", ");
    uart.disp(Shift_Cycles);
    uart.disp(", ");
    uart.disp(FPadd_Cycles);
    uart.disp(", ");
    uart.disp(FPmult_Cycles);
    uart.disp(", ");
    uart.disp(FPArrayMath_Cycles);

    while(1);
}