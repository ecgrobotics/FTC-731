#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     HTPB,           sensorI2CCustom9V)
#pragma config(Sensor, S3,     light,          sensorLightActive)
#pragma config(Sensor, S4,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     left,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     right,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     arm,           tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     flag,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    latch,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
volatile int batterydelay=1000;
volatile bool useScreen=false;
#include "constants.h"
task batteryTask()
{
	while(true){
		ubyte write=0b00000000;
		if(useScreen){
			nxtDisplayCenteredTextLine(0,"NXT Battery (mV):");
			nxtDisplayCenteredBigTextLine(1,"%d",nImmediateBatteryLevel);
			nxtDisplayCenteredTextLine(2,"TETRIX Battery (mV):");
			nxtDisplayCenteredBigTextLine(4,"%d",externalBattery);
	  }
		if(nAvgBatteryLevel<NXTWARNING){
			if(nAvgBatteryLevel<NXTLOW){
				write+=0b10000000;
			}
			else{
				write+=0b01000000;
			}
		}
		if(externalBatteryAvg<TETRIXWARNING){
			if(externalBatteryAvg<TETRIXLOW){
				write+=0b00100000;
			}
			else{
				write+=0b00010000;
			}
		}
		HTSPBwriteIO(HTPB,write);
		wait1Msec(batterydelay);
	}
}
void writeBattery(){
		ubyte write=0b00000000;
		nxtDisplayCenteredTextLine(0,"NXT Battery (mV):");
		nxtDisplayCenteredBigTextLine(1,"%d",nImmediateBatteryLevel);
		nxtDisplayCenteredTextLine(2,"TETRIX Battery (mV):");
		nxtDisplayCenteredBigTextLine(4,"%d",externalBattery);
		if(nAvgBatteryLevel<NXTWARNING){
			if(nAvgBatteryLevel<NXTLOW){
				write+=0b10000000;
			}
			else{
				write+=0b01000000;
			}
		}
		if(externalBatteryAvg<TETRIXWARNING){
			if(externalBatteryAvg<TETRIXLOW){
				write+=0b00100000;
			}
			else{
				write+=0b00010000;
			}
		}
		HTSPBwriteIO(HTPB,write);
}
