#pragma config(Sensor, S2,     light,          sensorLightActive)
#pragma config(Motor,  motorA,          left,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          right,         tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
const int THRESH=50;
task graph(){
	while(true){
			nxtDisplayCenteredBigTextLine(0,"%d",nMotorEncoder[left]);
			nxtDisplayCenteredBigTextLine(2,"%d",nMotorEncoder[right]);
			nxtDisplayCenteredBigTextLine(4,"%d",(nMotorEncoder[left]+nMotorEncoder[right])/2);
			nxtDisplayCenteredBigTextLine(6,"%d",SensorValue[light]);
			wait1Msec(100);
	}
}
task main()
{
	nMotorEncoder[left]=0;
	nMotorEncoder[right]=0;
	StartTask(graph);
	ClearTimer(T1);
	while(time1[T1]<30000){
			if(SensorValue[light]<THRESH){//WE FOLLOW LEFT SIDE OF LINE
					motor[left]=25;
					motor[right]=5;
			}
			else{
				motor[left]=5;
				motor[right]=25;
			}
	}
	motor[left]=0;
	motor[right]=0;

}