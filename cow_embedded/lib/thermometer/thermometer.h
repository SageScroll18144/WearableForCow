#ifndef THERMOMETER_H
#define THERMOMETER_H

#define LM35 A0
#define vRef 3.30
#define ADC_Resolution 4095
#define LM35_Per_Degree_Volt 0.01
#define Zero_Deg_ADC_Value 879.00

void setupThermometer(void);
int getTemperature(void);

#endif