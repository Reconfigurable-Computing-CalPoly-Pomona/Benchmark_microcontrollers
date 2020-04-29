//uses 1562 bytes of Program Memory

//for PIC32MC230F064B
 #include <p32mx230f064b.h>
 #include <xc.h>             /* contains Vector Name/Number Macros */
 #include <sys/attribs.h>    /* contains __ISR() Macros */
 #pragma config FWDTEN = OFF //disables watchdog timer
 #pragma config POSCMOD = XT             // Primary Oscillator Configuration (XT osc mode)
 #define TIMER_MAX 0xFFFF
 #define IO_Output PORTAbits.RA0
 #define TIMER_CONTROL  T1CONbits.TON
 #define TIMER_START = 1
 #define TIMER_STOP = 0
 #define TIMER_FLAG  IFS0bits.T1IF
 #define OSC_SpeedM = ???
 
 
//--------------Values for all devices---------------//
 
// To retrieve the benchmark results, we use the IDE to watch our variable values after the benchmark has been completed.
// We will not be using any external hardware other than what is require to program the MC (no 7segment or LCD).
// The variables shown below are the ones we need to retrieve after the benchmark is complete.
 
unsigned int TimeOverFlowCount = 0; //keeps track of all timer overflows
 
unsigned int PingIO_Cycles = 0; //keeps track of time taken by processor to complete specific operation
unsigned int PingIO_OverFlow = 0; //keeps track if any overflow occurs during specific operation
unsigned int FPadd_Cycles = 0;
unsigned int FPadd_OverFlow = 0;
unsigned int FPmult_Cycles = 0;
unsigned int FPmult_OverFlow = 0;
unsigned int FPdiv_Cycles = 0;
unsigned int FPdiv_OverFlow = 0;
unsigned int FPArrayMath_Cycles = 0;
unsigned int FPArrayMath_OverFlow = 0;
unsigned int Shift_Cycles = 0;
unsigned int Shift_OverFlow = 0;

 
//-------------------------------------------------//
unsigned int Cycles_Temp = 0;
unsigned int OverFlow_Temp = 0;
float C = 0;
int F = 0;
float Array_A [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float Array_C [5][5] = {
{1,2,3,4,5}, {1,2,3,4,5},
{1,2,3,4,5}, {1,2,3,4,5},
{1,2,3,4,5}};
 
 
void initilaizeMC();
void TIMER_RESET();
void __ISR() ISR(void);
void PingIO();
void FPadd(float A, float B);
void FPmult(float A, float B);
void FPdiv(float A, float B);
void Shift(int A, int B);
void FPArrayMath(float A);
unsigned int TimerCurrent();
 
//NEEDS YOUR REGISTERS//
void initializeMC(){ //sets MC Ports and Registers to proper values
    OSCCONbits.PBDIV = 0;
    ANSELA = 0;
    TRISA = 0x00; //selects PORTA as output
    PORTA = 0x00; //clears PORTA //we will be using PORTA, Pin 0 [A0] for IO Test
    TMR1 = 0x00000000; //set up the timer for the idle count up to 65,535?
    PR1 = 65535;              // Load period register
    T1CONbits.TCS = 0;
    T1CONbits.TCKPS = 0;
    // Reset the Timer 1 interrupt flag
    IFS0bits.T1IF = 0;
    // Enable interrupts from Timer 1
    IEC0bits.T1IE = 1;
}
 
void TIMER_RESET(){
 
    TMR1 = 0x00000000;
}
 
//MAY NEED CHANGE//
void __ISR(_TIMER_1_VECTOR, IPL7SOFT) ISR(void) {  //interrupt service routine. Counts the number over timer overflows to keep track of instruction cycle count
    TIMER_CONTROL = 0; //stops timer to prevent ISR from affecting results
    TIMER_FLAG = 0;             //resets interrupt flag
 
    TimeOverFlowCount += 1;     //increments overflow count
 
    TIMER_RESET();              //resets timer
    TIMER_CONTROL = 1; //starts timer
}
 
 
unsigned int TimerCurrent(){
       unsigned int timerValue = TMR1; //adds both registers to make single value
       return timerValue;
}
 
//----------------------does not need change--------------------------//
 
void PingIO(){ //tests I/O time
   Cycles_Temp = TimerCurrent();
   OverFlow_Temp = TimeOverFlowCount;
   TIMER_CONTROL = 1; //starts timer
 
   IO_Output = 1;
   IO_Output = 0;
 
   TIMER_CONTROL = 0; //stops timer
   PingIO_Cycles += (TimerCurrent() - Cycles_Temp);
   PingIO_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}
 
void FPadd(float A, float B){
    Cycles_Temp = TimerCurrent();
    OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = 1; //starts timer

    C = A + B;

    TIMER_CONTROL = 0; //stops timer
    FPadd_Cycles += (TimerCurrent() - Cycles_Temp);
    FPadd_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void FPmult(float A, float B){
    Cycles_Temp = TimerCurrent();
    OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = 1; //starts timer

    C = A * B;

    TIMER_CONTROL = 0; //stops timer
    FPmult_Cycles += (TimerCurrent() - Cycles_Temp);
    FPmult_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void FPdiv(float A, float B){
    Cycles_Temp = TimerCurrent();
    OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = 1; //starts timer

    C = B/A;

    TIMER_CONTROL = 0; //stops timer
    FPdiv_Cycles += (TimerCurrent() - Cycles_Temp);
    FPdiv_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void Shift(int A, int B){
    Cycles_Temp = TimerCurrent();
    OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = 1; //starts timer

    F = B << A;

    TIMER_CONTROL = 0; //stops timer
    Shift_Cycles += (TimerCurrent() - Cycles_Temp);
    Shift_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void FPArrayMath(float A){
    Cycles_Temp = TimerCurrent();
    OverFlow_Temp = TimeOverFlowCount;
    int i, j;
    TIMER_CONTROL = 1; //starts timer
    for ( i = 0; i < 10; i++){ //populate Arrays
        Array_A [i] = A - i;
    }
        
    for ( i = 0; i < 10; i ++){  //search array, find middle, toggle LED
        if(Array_A[i] == (A - 5)){
            break;
        }
    }

   for ( i = 0; i < 5; i++){ //cross the values
           for( j = 0; j < 5;  j++){
               C = Array_C[i][j];
               Array_C[i][j] = Array_C[j][i];
               Array_C[j][i] = C;
           }
   }
    TIMER_CONTROL = 0; //stops timer
    FPArrayMath_Cycles += (TimerCurrent() - Cycles_Temp);
    FPArrayMath_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

//----------------------does not need change--------------------------//

void main(){ //benchmark
    float A = 5.05, B = 255.0255;
    int D = 5, E = 255;
    initializeMC();

    PingIO();
    FPadd(A, B);
    FPmult(A, B);
    FPdiv(A, B);
    Shift(D, E);
    FPArrayMath(A);

    while(1);
}