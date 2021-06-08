/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */
#include "main.h"
#include "Display_MGR.h"
#include "Mode_MGR.h"
#include "util/delay.h"
#include "Calibrator_Resistor.h"
#include "KeyPad.h"
#include "Temp_MGR.h"



int main(void) {
    config();
    _delay_ms(1500);
    uint8 oldCurrTemp = currentTemp;
    uint8 oldSetTemp = setTemp;
    while (1) {
        if (machineState != ERROR){
            if (machineState != STANDBY){
                if ((currentTemp != oldCurrTemp) || (setTemp != oldSetTemp)){
                    if (((currentTemp > setTemp) && ((currentTemp - setTemp) <= 5)) || ((setTemp > currentTemp) && ((setTemp - currentTemp) <= 5))){
                        write_State(NORMAL);
                        SetMachineState(NORMAL);
                    } else{
                        write_State(OPERATIONAL);
                        SetMachineState(OPERATIONAL);
                    }
                    if ((currentTemp > setTemp) && ((currentTemp - setTemp) > 10)){
                        write_State(ERROR);
                        SetMachineState(ERROR);
                    }
                    write_CRT_Temp(currentTemp);
                    oldSetTemp = setTemp;
                    oldCurrTemp = currentTemp;
                }
            }
            if (KeyPad_Get_Hash()){
                if (machineState == STANDBY){
                    write_State(OPERATIONAL);
                    SetMachineState(OPERATIONAL);
                } else {
                    write_State(STANDBY);
                    SetMachineState(STANDBY);
                }
            }
        }
    }
}

void config(){
    Activate_LCD();
    display_Welcome_screen(1);
    InitCalibrator();
    SystemPeriodicity_Init();
    KeyPad_Init();
}

