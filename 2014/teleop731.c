#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTPB,           sensorI2CCustom9V)
#pragma config(Sensor, S3,     light,          sensorLightActive)
#pragma config(Sensor, S4,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     left,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     right,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     arm,           tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     flag,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     up,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     down,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    latch,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    pivot,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    base,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "HTPB.h"
//#include "batteryinclude.h"
#include "JoystickDriver.c"
const int FLAG_POWER=50;
const int ARM_POWER=4;
void init(){
	HTSPBsetupIO(HTPB,0b11111000);
}
task main()
{
	init();
	waitForStart();
//	batterydelay=10000;
//	StartTask(batteryTask);
	while(true)
	{
		getJoystickSettings(joystick);

		if(abs(joystick.joy1_y1) > 5){
			motor[left] = joystick.joy1_y1;
		}
		else{
			motor[left] = 0;
		}

		if(abs(joystick.joy1_y2) > 5){
			motor[right] = -joystick.joy1_y2;
		}
		else{
			motor[right] = 0;
		}
		if(abs(joystick.joy2_y1) > 5){
			motor[up] = joystick.joy2_y1/2;
		}
		else{
			motor[up] = 0;
		}

		if(abs(joystick.joy2_y2) > 5){
			motor[down] = -joystick.joy2_y2/2;
		}
		else{
			motor[down] = 0;
		}
	if(joy1Btn(4)==1){
	  	servo[base]=ServoValue[base]+1;
	}
	else if(joy1Btn(2)==1){
		servo[base]=ServoValue[base]-1;
	}
	if(ServoValue[base]>255)servo[base]=255;
	if(ServoValue[base]<0)servo[base]=0;
		/**		if(joy1Btn(6) == 1){
		motor[arm] = ARM_POWER;
		}
		else if(joy1Btn(8) == 1){
		motor[arm] = ARM_POWER;
		}
		else{
		motor[arm] = 0;
		}**/

		if(joy1Btn(5) == 1){
			motor[flag] = FLAG_POWER;
		}
		else if(joy1Btn(7) == 1){
			motor[flag] = -FLAG_POWER;
		}
		else{
			motor[flag] = 0;
		}

	}


}
