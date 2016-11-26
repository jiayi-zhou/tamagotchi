
#include <stdint.h>
#include <stdbool.h>

#include  "LaunchPad.h"
#include  "OrbitBoosterPackDefs.h"

#include  "OrbitOled.h"
#include  "OrbitOledGrph.h"
#include  "OrbitOledChar.h"
#include  "FillPat.h"

#include  "delay.h"

void DeviceInit(void) {

  /*
   * First, Set Up the Clock.
   * Main OSC       -> SYSCTL_OSC_MAIN
   * Runs off 16MHz clock -> SYSCTL_XTAL_16MHZ
   * Use PLL        -> SYSCTL_USE_PLL
   * Divide by 4      -> SYSCTL_SYSDIV_4
   */
  SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_4);

  /*
   * Enable and Power On All GPIO Ports
   */
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA);
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB);
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOC);
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOD);
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE);
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);


  /*
   * Pad Configure.. Setting as per the Button Pullups on
   * the Launch pad (active low).. changing to pulldowns for Orbit
   */
  GPIOPadConfigSet(SWTPort, SWT1 | SWT2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(BTN1Port, BTN1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(BTN2Port, BTN2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(LED1Port, LED1, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED2Port, LED2, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED3Port, LED3, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED4Port, LED4, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);

  /*
   * Initialize Switches as Input
   */
  GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);

  /*
   * Initialize Buttons as Input
   */
  GPIOPinTypeGPIOInput(BTN1Port, BTN1);
  GPIOPinTypeGPIOInput(BTN2Port, BTN2);

  /*
   * Initialize LEDs as Output
   */
  GPIOPinTypeGPIOOutput(LED1Port, LED1);
  GPIOPinTypeGPIOOutput(LED2Port, LED2);
  GPIOPinTypeGPIOOutput(LED3Port, LED3);
  GPIOPinTypeGPIOOutput(LED4Port, LED4);

  /*
   * Enable ADC Periph
   */
  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

  GPIOPinTypeADC(AINPort, AIN);

  /*
   * Enable ADC with this Sequence
   * 1. ADCSequenceConfigure()
   * 2. ADCSequenceStepConfigure()
   * 3. ADCSequenceEnable()
   * 4. ADCProcessorTrigger();
   * 5. Wait for sample sequence ADCIntStatus();
   * 6. Read From ADC
   */
  ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
  ADCSequenceEnable(ADC0_BASE, 0);

  /*
   * Initialize the OLED
   */

}

void potentiometer(){
  unsigned long ulAIN0;
  char      szAIN[6] = {0};
  char      cMSB = 0x00;
  char      cMIDB = 0x00;
  char      cLSB = 0x00;

  ADCProcessorTrigger(ADC0_BASE, 0);

  while(!ADCIntStatus(ADC0_BASE, 0, false));

  ADCSequenceDataGet(ADC0_BASE, 0, &ulAIN0);

  /*
   * Process data
   */
  cMSB = (0xF00 & ulAIN0) >> 8;
  cMIDB = (0x0F0 & ulAIN0) >> 4;
  cLSB = (0x00F & ulAIN0);

  szAIN[0] = '0';
  szAIN[1] = 'x';
  szAIN[2] = (cMSB > 9) ? 'A' + (cMSB - 10) : '0' + cMSB;
  szAIN[3] = (cMIDB > 9) ? 'A' + (cMIDB - 10) : '0' + cMIDB;
  szAIN[4] = (cLSB > 9) ? 'A' + (cLSB - 10) : '0' + cLSB;
  szAIN[5] = '\0';
  OrbitOledSetCursor(8, 4);
  if(szAIN[2] >= '0' && szAIN[2] < '3'){
    OrbitOledPutString("Feeding");
    
  }
  else if(szAIN[2] >= '3' && szAIN[2] < '5'){
    OrbitOledPutString("Cleaning");
  }
  else if(szAIN[2] >= '5' && szAIN[2] < '7'){
    OrbitOledPutString("Games");
  }
  else if(szAIN[2] >= '7' && szAIN[2] < '9'){
    OrbitOledPutString("Stats");
  }
  else if(szAIN[2] >= '9' && szAIN[2] < 'B'){
    OrbitOledPutString("Medicine");
  }
  else if(szAIN[2] >= 'B' && szAIN[2] < 'D'){
    OrbitOledPutString("6");
  }
  else if(szAIN[2] >= 'D' && szAIN[2] <= 'F'){
    OrbitOledPutString("7");
  }
}
