#include <PIC12F1822.h> //include necessary header
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC	INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (OFF	Brown-out Reset disabled)
// CONFIG2
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (LO	Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (OFF	High-voltage on MCLR/VPP must be used for programming)
#pragma config PLLEN = ON
#pragma interrupt ISR   //initializes the interrupt
#define TIMER_MAX  0xFFFF //holds max value of microcontroller timer before overflow. This will be used to determine the counter max. This is not used in the benchmark but will be used in the report and hand calculations
#define IO_Output  PORTAbits.RA0 //using PORTA, pin A0 for IO
//we use the timer to count the number of cycles that have passed during the completion of an operation.
#define TIMER_CONTROL  T1CONbits.TMR1ON //this is the register to control the timer on/off
#define TIMER_START  1 //this is the value to load into the register to turn the timer on
#define TIMER_STOP  0 //this is the value to load into the register to turn the timer off
#define TIMER_FLAG  PIR1bits.TMR1IF //this is the interrupt flag raised whenever the timer has overflowed. If the timer has overflowed, this means the microcontroller has taken more than TIMER_MAX cycles to complete the benchmark
#define OSC_SpeedM 32 //in Megahertz (if 500kHz -> 0.5; if 5GHz, 5000) this is not used in the benchmark but will be used in the report and hand calculations
// Definitions
#define _XTAL_FREQ 32000000        // this is used by the __delay_ms(xx) and __delay_us(xx) functions

unsigned int TimeOverFlowCount = 0; //keeps track of all timer overflows
 
unsigned int PingIO_Cycles = 0; //keeps track of time taken by processor to complete specific operation
//unsigned int PingIO_OverFlow = 0; //keeps track if any overflow occurs during specific operation
unsigned int add_Cycles = 0;
//unsigned int add_OverFlow = 0;
unsigned int mult_Cycles = 0;
//unsigned int mult_OverFlow = 0;
unsigned int div_Cycles = 0;
//unsigned int div_OverFlow = 0;
unsigned int ArrayMath_Cycles = 0;
//unsigned int ArrayMath_OverFlow = 0;
unsigned int Shift_Cycles = 0;
//unsigned int Shift_OverFlow = 0;
 
//-------------------------------------------------//
unsigned int Cycles_Temp = 0;
//unsigned int OverFlow_Temp = 0;
int C = 0;
//int Array_A [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Array_C [5][5] = {
{1,2,3,4,5}, {1,2,3,4,5},
{1,2,3,4,5}, {1,2,3,4,5},
{1,2,3,4,5}};
 
 
void initializeMC();
void TIMER_RESET();
void __interrupt() ISR(void);
void PingIO();
void add(int A, int B);
void mult(int A, int B);
void div(int A, int B);
void Shift(int A, int B);
void ArrayMath(int A);
unsigned int TimerCurrent();
 
void initializeMC(){ //sets MC Ports and Registers to proper values
    // //for PIC12F1822
    ADCON1 = 0x00; //sets PORTA as digital input (on all PICs, some PORTA pins accept Analog input. Needs disable.)
    TRISA = 0x00; //selects PORTA as output
    PORTA = 0x00; //clears PORTA //we will be using PORTA, Pin 0 [A0] for IO Test
    TMR1H = 0x00; //set up the timer for the idle count up to 65,535?
    TMR1L = 0x00;
    T1CONbits.TMR1CS = 1;  //sets timer1 to count every instruction cycle
    INTCONbits.GIE = 1; //enables global interrupts, all interrupts enabled
    INTCONbits.PEIE = 1;    // enables peripheral interrupt
    PIE1 = 0x01; //enables timer1 interrupt flag
    PIR1bits.TMR1IF=0;      // Clears the interrupt flag for Timer 1
}

//NEEDS YOUR REGISTERS//
void TIMER_RESET(){
    // //for PIC12F1822
    TMR1H = 0x00;  // reset timer values back to 0
    TMR1L = 0x00;
}

//MAY NEED CHANGE//
void __interrupt() ISR(void) {  //interrupt service routine. Counts the number over timer overflows to keep track of instruction cycle count
    TIMER_CONTROL = TIMER_STOP; //stops timer to prevent ISR from affecting results
    TIMER_FLAG = 0;             //resets interrupt flag

    TimeOverFlowCount += 1;     //increments overflow count

    TIMER_RESET();              //resets timer
    TIMER_CONTROL = TIMER_START; //starts timer
}

//NEEDS YOUR REGISTERS//
unsigned int TimerCurrent(){
    // //for PIC12F1822
    unsigned int timerValue = {(TMR1H<<8)| TMR1L}; //adds both registers to make single value // retrieve timer values, concatenate
    return timerValue;
}

//----------------------does not need change--------------------------//
 
void PingIO(){ //tests I/O time
   Cycles_Temp = TimerCurrent();
   //OverFlow_Temp = TimeOverFlowCount;
   TIMER_CONTROL = 1; //starts timer
 
   //IO_Output = 1;
   //IO_Output = 0;
 
   TIMER_CONTROL = 0; //stops timer
   PingIO_Cycles += (TimerCurrent() - Cycles_Temp);
   //PingIO_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}
 
void add(int A, int B){
    Cycles_Temp = TimerCurrent();
    //OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = 1; //starts timer
 
    C = A + B;
 
    TIMER_CONTROL = 0; //stops timer
    add_Cycles += (TimerCurrent() - Cycles_Temp);
    //add_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}
 
void mult(int A, int B){
    Cycles_Temp = TimerCurrent();
    //OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = 1; //starts timer
 
    C = A * B;
 
    TIMER_CONTROL = 0; //stops timer
    mult_Cycles += (TimerCurrent() - Cycles_Temp);
    //mult_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}
 
void div_p32 (int A, int B){
    Cycles_Temp = TimerCurrent();
    //OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = 1; //starts timer
 
    C = B/A;
 
    TIMER_CONTROL = 0; //stops timer
    div_Cycles += (TimerCurrent() - Cycles_Temp);
    //div_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}
 
void Shift(int A, int B){
    Cycles_Temp = TimerCurrent();
    //OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = 1; //starts timer
 
    C = B << A;
 
    TIMER_CONTROL = 0; //stops timer
    Shift_Cycles += (TimerCurrent() - Cycles_Temp);
    //Shift_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}
 
void ArrayMath(int A){
    Cycles_Temp = TimerCurrent();
    //OverFlow_Temp = TimeOverFlowCount;
    //int i, j;
    
    TIMER_CONTROL = 1; //starts timer
    for (int i = 0; i < 10; i++){ //populate Arrays
        Array_C [i][0] = A - i;
    }
        
    for (int i = 0; i < 10; i ++){  //search array, find middle, toggle LED
        if(Array_C[i][0] == (A - 5)){
            break;
        }
    }
 
   for (int i = 0; i < 5; i++){ //cross the values
           for(int j = 0; j < 5;  j++){
               C = Array_C[i][j];
               Array_C[i][j] = Array_C[j][i];
               Array_C[j][i] = C;
           }
   }
    TIMER_CONTROL = 0; //stops timer
    ArrayMath_Cycles += (TimerCurrent() - Cycles_Temp);
    //ArrayMath_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}
 
//----------------------does not need change--------------------------//
 
void main(){ //benchmark
    int A = 5, B = 255;
    initializeMC();
 
    PingIO();
    add(A, B);
    mult(A, B);
    div_p32(A, B);
    Shift(A, B);
    ArrayMath(A);
 
    while(1);
}