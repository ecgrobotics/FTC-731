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
#include "HTPB.h"
task main()
{
	while(true){
		nxtDisplayCenteredBigTextLine(1,"%d",readAnalogInput(HTPB,2));
		wait1Msec(100);
	}
}
