
task main()
{
		nMotorEncoder[motorB]=0;
	nMotorEncoder[motorA]=0;
	//B
	//set motors to 50;
	while(nMotorEncoder[motorA]<1800 && nMotorEncoder[motorB]<1800){
		nxtDisplayCenteredBigTextLine(0,"%d",nMotorEncoder[motorA]);
		nxtDisplayCenteredBigTextLine(2,"%d",nMotorEncoder[motorB]);
	}
//stop


}
