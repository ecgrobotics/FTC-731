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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
task main()
{

	nMotorEncoder[lift]=0;
	waitForStart();
while(true)
{getJoystickSettings(joystick);
	motor[left]=joystick.joy1_y1;
	motor[right]=-joystick.joy1_y2;
	if (joy1Btn(4)==1&&nMotorEncoder[lift]<12000)
		motor[lift]=75;
else if (joy1Btn(2)==1)
	motor[lift]=-75;
else motor[lift]=0;
if (joy1Btn(3)==1)
		motor[flag]=100;
else if (joy1Btn(1)==1)
	motor[flag]=-100;
else motor[flag]=0;
nxtDisplayCenteredBigTextLine(1,"%d",nMotorEncoder[lift]);
//14830


}


}
