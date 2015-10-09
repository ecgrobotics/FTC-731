#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S4,     HTPB,           sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     left,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     right,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    bucket,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
#include "HTPB.h"
task main()
{
	HTSPBsetupIO(HTPB,0b11000000);
	while(true){
		ubyte in=HTSPBreadIO(HTPB,0b00000001);
		switch(nNxtButtonPressed){
			case 1:motor[lift]=-50;break;
			case 2:if(in!=1)motor[lift]=50;else motor[lift]=0;break;
			default:motor[lift]=0;
		}
	}
}
