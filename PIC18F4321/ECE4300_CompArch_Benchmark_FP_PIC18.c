//uses 5660 bytes of Program Memory

//for PIC18F4321
#include <PIC18F4321.h> //include necessary header
#pragma config OSC = INTIO2 //selects default oscillator, use the fastest one at the fastest setting
#pragma config WDT = OFF //disables watchdog timer. Needs to be done to prevent controller from ending loop early
#pragma config LVP = OFF //disables Low Voltage Protection (may not be in your microcontroller)
#pragma config BOR = OFF //disables Brown Out Reset (may not be in your microcontroller)
#pragma interrupt ISR   //initializes the interrupt
#define TIMER_MAX  0xFFFF //holds max value of microcontroller timer before overflow. This will be used to determine the counter max. This is not used in the benchmark but will be used in the report and hand calculations
#define IO_Output  PORTAbits.RA0 //using PORTA, pin A0 for IO
//we use the timer to count the number of cycles that have passed during the completion of an operation.
#define TIMER_CONTROL  T1CONbits.TMR1ON //this is the register to control the timer on/off
#define TIMER_START  1 //this is the value to load into the register to turn the timer on
#define TIMER_STOP  0 //this is the value to load into the register to turn the timer off
#define TIMER_FLAG  PIR1bits.TMR1IF //this is the interrupt flag raised whenever the timer has overflowed. If the timer has overflowed, this means the microcontroller has taken more than TIMER_MAX cycles to complete the benchmark
#define OSC_SpeedM 8 //in Megahertz (if 500kHz -> 0.5; if 5GHz, 5000) this is not used in the benchmark but will be used in the report and hand calculations

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
void __interrupt() ISR(void);
void PingIO();
void FPadd(float A, float B);
void FPmult(float A, float B);
void FPdiv(float A, float B);
void Shift(int A, int B);
void FPArrayMath(float A);
unsigned int TimerCurrent();

//NEEDS YOUR REGISTERS//
void initializeMC(){ //sets MC Ports and Registers to proper values
    //for PIC18F4321
    ADCON1 = 0x0F; //sets PORTA as digital input (on all PICs, some PORTA pins accept Analog input. Needs disable.)
    TRISA = 0x00; //selects PORTA as output
    PORTA = 0x00; //clears PORTA //we will be using PORTA, Pin 0 [A0] for IO Test
    TMR1H = 0x00; //set up the timer for the idle count up to 65,535?
    TMR1L = 0x00;
    T1CONbits.TMR1CS = 0; //sets timer1 to count every instruction cycle [we may need to change the timer to increment at an external clock source. find the control register for this as well but do not enable]
    INTCONbits.GIE = 1; //enables global interrupts, all interrupts enabled
    INTCONbits.PEIE = 1;    // enables peripheral interrupt 
    PIE1 = 0x01; //enables timer1 interrupt flag
    PIR1bits.TMR1IF=0;      // Clears the interrupt flag for Timer 1
}

//NEEDS YOUR REGISTERS//
void TIMER_RESET(){
    //for PIC18F4321
    TMR1H = 0x00;
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
    //for PIC18F4321
    unsigned int timerValue = {(TMR1H<<8)| TMR1L}; //adds both registers to make single value

    return timerValue;
}

//----------------------does not need change--------------------------//

void PingIO(){ //tests I/O time
   Cycles_Temp = TimerCurrent();
   OverFlow_Temp = TimeOverFlowCount;
   TIMER_CONTROL = TIMER_START; //starts timer

   IO_Output = 1; //toggles output
   IO_Output = 0;

   TIMER_CONTROL = TIMER_STOP; //stops timer
   PingIO_Cycles += (TimerCurrent() - Cycles_Temp);
   PingIO_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void FPadd(float A, float B){
    Cycles_Temp = TimerCurrent();
    OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = TIMER_START; //starts timer

    C = A + B;

    TIMER_CONTROL = TIMER_STOP; //stops timer
    FPadd_Cycles += (TimerCurrent() - Cycles_Temp);
    FPadd_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void FPmult(float A, float B){
    Cycles_Temp = TimerCurrent();
    OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = TIMER_START; //starts timer

    C = A * B;

    TIMER_CONTROL = TIMER_STOP; //stops timer
    FPmult_Cycles += (TimerCurrent() - Cycles_Temp);
    FPmult_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void FPdiv(float A, float B){
    Cycles_Temp = TimerCurrent();
    OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = TIMER_START; //starts timer

    C = B/A;

    TIMER_CONTROL = TIMER_STOP; //stops timer
    FPdiv_Cycles += (TimerCurrent() - Cycles_Temp);
    FPdiv_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void Shift(int A, int B){
    Cycles_Temp = TimerCurrent();
    OverFlow_Temp = TimeOverFlowCount;
    TIMER_CONTROL = TIMER_START; //starts timer

    F = B << A;

    TIMER_CONTROL = TIMER_STOP; //stops timer
    Shift_Cycles += (TimerCurrent() - Cycles_Temp);
    Shift_OverFlow += (TimeOverFlowCount - OverFlow_Temp);
}

void FPArrayMath(float A){
    Cycles_Temp = TimerCurrent();
    OverFlow_Temp = TimeOverFlowCount;
    
    TIMER_CONTROL = TIMER_START; //starts timer
    for (int i = 0; i < 10; i++){ //populate Arrays
        Array_A [i] = A - i;
    }
        
    for (int i = 0; i < 10; i ++){  //search array, find middle, toggle LED
        if(Array_A[i] == (A - 5)){
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
    TIMER_CONTROL = TIMER_STOP; //stops timer
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