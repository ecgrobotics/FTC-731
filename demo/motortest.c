#pragma config(Motor,  motorA,          m,             tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
void init(){
	nMotorEncoder[m]=0;
}
task graph(){
	while(true){
		nxtDisplayCenteredBigTextLine(2,"%d",nMotorEncoder[m]);
	}
}
task main()
{
	init();
	StartTask(graph);
while(true){
		motor[m]=10;
		while(nMotorEncoder[m]<170);
		motor[m]=-10;
		while(nMotorEncoder[m]>-120);
}


}
