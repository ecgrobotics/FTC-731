void drive(int pwr){
motor[motorA]=pwr;
motor[motorB]=pwr;
}
void turnLeft(){
	motor[motorA]=25;
	motor[motorB]=-25;
	wait1msec(250);
}
task main()
{
	drive(50);
	wait1Msec(3000);
	turnLeft();
	drive(100);
	wait1Msec(3000);
	drive(-100);
	wait1Msec(2000);


}
