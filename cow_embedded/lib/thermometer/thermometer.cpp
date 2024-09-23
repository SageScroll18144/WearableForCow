#include <Arduino.h>
#include "thermometer.h"

float ADC_Per_Degree_Val;

void setupThermometer(void) {
    ADC_Per_Degree_Val = (ADC_Resolution/vRef)*LM35_Per_Degree_Volt;
}
int getTemperature(void) {
    float temp_adc_val = 0;
    for(int i=0;i<10;i++) temp_adc_val += analogRead(LM35);

    temp_adc_val = ((temp_adc_val / 10.0) - Zero_Deg_ADC_Value) / ADC_Per_Degree_Val;

    return temp_adc_val;
}