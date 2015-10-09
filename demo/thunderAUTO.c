#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     flag,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     right,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     left,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    Tili,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
#include "JoystickDriver.c"
task main()
{
	waitForStart();

	while(true){
	}



}
