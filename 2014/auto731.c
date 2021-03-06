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

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//TODO account for forward IR bias on 1 and 2 and backward ir bias for 3 and 4....
//yes its bs. the damned ir beacons arent centered under the baskets

/* PROTOTYPE BOARD VOLTAGE CONVERSIONS
 *HTPB:	310/V=.310/mV;
 *Gyro: 7mV/degree/s=.007V/degree/s
 *Gyro with resistors:  (2/3) everything, 4.66666mV/degree/s = .0046666V/degree/s
 *NXT: 1.446/2 /degree/sec   idk where the /2 cam from, but it works....
 */

//NOTE: if compilation and running fails, set general preference for multi-robot to false
#include "HTPB.h"
#include "batteryinclude.h"
#include "JoystickDriver.c"
void drive(int pwr);
void rotateRight(int degrees, int pwr);
void rotateLeft(int degrees, int pwr);
void forwardFromWall();
void driveUntilIR(int pwr);
void dump();
void driveForwardToWall(int pwr);
void driveBackwardToWall(int pwr);
void driveToLine(int pwr);
void driveOntoRamp(int pwr);
void adjust();
task gyroThread;
task graphicsThread;

volatile float theta=0;
volatile int updateTime=5;
volatile int sonar1;
volatile int sonar2;
volatile int sonar3;
int stationaryVoltage=515;
const int SONAR_ERROR=4;
const float valueDegreeSecond=1.446/2;//for gyro analog conversion...//changed from 1.449 to 1.446: previous value would cause it to be off by .6 degrees/second/second
const int colorThreshold=55;
const int sonar1Stage1=18;
const int sonar2Stage3B=19;
const int sonar3Stage3A=19;
const int sonar2Basket2=35;
const int sonar2Basket1=18;
const int sonar3Basket2=0;//NEED
const int sonar3Basket1=0;//NEED
const int sonar2Threshold1=20;
const int sonar2Threshold2=36;
const int sonar3Threshold1=0;//NEED
const int sonar3Threshold2=0;//NEED
//IMPORTANT: TEST WITH IR IN POS 3
//COLLECT CONSTANTS:
bool data=false;//if collecting sonar data
bool useLight=true;
bool useSonars=false;//for data collect code
bool useSonars3=true;
int path=PRIMARY_ROUTE;
int position=PRIMARY_POSITION;
int sample[3][10];
int sonardata[100];
void init(){
		 HTSPBsetupIO(HTPB,0b11111000);
		 bDisplayDiagnostics=false;
		 writeBattery();
	   clearDebugStream();
	   if(HTSPBreadIO(HTPB,0b00000001)!=0)path=SECONDARY_ROUTE;//determine if we need to run backup path.
	   if(HTSPBreadIO(HTPB,0b00000010)!=0)position=SECONDARY_ROUTE;//determine starting position based on a switch
	 		nxtDisplayCenteredBigTextLine(6,"PATH: %d",path);
		 nxtDisplayCenteredBigTextLine(3,"POS: %d",position);
	  	nMotorEncoder[arm]=0;
			int sum=0;
			for(int i=0;i<5;i++){
					sum+=readAnalogInput(HTPB,0);
					wait1Msec(100);
			}
			stationaryVoltage=sum/5;
}
//sorts the sample array
void sort( int s, int count ){
    int i, j;
    double temp;
    do{
        j = 0;
        for (i = 0;i<count-1;i++){
                if (sample[s][i] > sample[s][i+1]){
                    j = 1;
                    temp = sample[s][i];
                    sample[s][i] = sample[s][i+1];
                    sample[s][i+1] = temp;
                }
            }
    } while (j == 1);
}
task main()
{
		init();
	//	waitForStart();
	//	batterydelay=10000;
	//	StartTask(batteryTask);
		wait1Msec(250);
		StartTask(gyroThread);

		servo[latch]=0;
		wait1Msec(2000);
		servo[latch]=90;
		wait1Msec(2000);
		servo[latch]=180;
		wait1Msec(2000);servo[latch]=255;



	//	dump();
		wait1Msec(1000000);
		forwardFromWall();
		if(data){
			writeDebugStreamLine("SONAR 1");
			for(int i=0;i<44;i++){
				writeDebugStreamLine("%d",sonardata[i]);
			}
			writeDebugStreamLine("AFTER BEACON PART");
		}
		wait1Msec(50);
		if(position==SECONDARY_POSITION){
				rotateRight(135,35);
				wait1Msec(100);
				driveUntilIR(-20);
				goto linedup;
		}
		rotateRight(45,40);
		wait1Msec(100);
		if(SensorValue[ir]==5)goto foundIR;
		driveUntilIR(20);
		foundIR:
		//collect 10 data points from each sonar
		for(int i=0;i<10;i++){
			int v=0;
			sample[0][i]=HTSPBreadADC(HTPB,1,10);
			sample[1][i]=HTSPBreadADC(HTPB,2,10);
			sample[2][i]=HTSPBreadADC(HTPB,3,10);
		}
		//sort the data numerically from least to greates
		sort(0,10);
		sort(1,10);
		sort(2,10);
		adjust();
		wait1Msec(500);
		linedup:
		dump();
		wait1Msec(250);
		if(path==PRIMARY_ROUTE){
				driveForwardToWall(30);
				if(data){
					writeDebugStreamLine("SONAR 3");
					for(int i=0;i<100;i++){
						writeDebugStreamLine("%d",sonardata[i]);
					}
				}
				wait1Msec(250);
				rotateLeft(90,40);
				wait1Msec(250);
				driveToLine(30);
				wait1Msec(500);
				rotateLeft(100,40);
				wait1Msec(500);
				driveOntoRamp(50);
		}
		else if(path==SECONDARY_ROUTE){
				driveBackwardToWall(30);
				wait1Msec(500);
				rotateLeft(90,40);
				wait1Msec(250);
				driveToLine(30);
				wait1Msec(500);
				rotateRight(90,40);
				wait1Msec(500);
				driveOntoRamp(50);
		}
		while(true){}
}
void adjust(){
		int s1=sample[0][5];
		int s2=sample[1][5];
		int s3=sample[2][5];
		hogCPU();
		if(s2<sonar2Threshold1){
			//TODO check that s3 is not in range for basket 2,3,4. (>?)
				eraseDisplay();
				nxtDisplayCenteredBigTextLine(1,"%d",1);
				nxtDisplayCenteredBigTextLine(4,"%d",s2);
				wait1Msec(500);
				int consec=0;
				drive(30);
				while(consec<3){
						int d=readAnalogInput(HTPB,2);
						if (d>40)continue;
						if(d>=sonar2Basket1)consec++;
						else consec=0;
				}
				drive(-50);
				wait1Msec(100);
				drive(0);
		}
		else if(s2<sonar2Threshold2){
			//TODO make sure that s3 is IN range for basket 2 (not 3,4), dont worry bout 1...
				eraseDisplay();
				nxtDisplayCenteredBigTextLine(1,"%d",2);
				nxtDisplayCenteredBigTextLine(4,"%d",s2);
				wait1Msec(500);
				int consec=0;
				drive(30);
				while(consec<3){
							int d=readAnalogInput(HTPB,2);
							if (d>55)continue;
							if(d>=sonar2Basket2)consec++;
							else consec=0;
				}
				drive(-50);
				wait1Msec(100);
				drive(0);
		}
		else{
			releaseCPU();
			return;
		}
		releaseCPU();
}
void drive(int pwr){
	motor[right]=-pwr;
	motor[left]=pwr;
}
void forwardFromWall(){
	//TODO SONAR 1
		drive(40);
	/*	if(useSonars){
			wait1Msec(200);
			while(readAnalogInput(HTPB,1)<sonar1Stage1);
  	}
  	*/
  	ClearTimer(T3);
  	if(data){
  		hogCPU();//prevent other threads from accessing sonar (basically a way of putting a lock without using locks/semaphores)
  		for(int i=0;time1[T3]<420;i++){
  			int d=readAnalogInput(HTPB,1);
  	  	if(d<100)sonardata[i]= d;
  	  	else i--;
  			while(time1[T3]%10 !=0 );
  		}
  		releaseCPU();
  	}
		else wait1Msec(420);
		drive(-40);
		wait1Msec(200);
		drive(0);
}
void driveUntilIR(int pwr){
		drive(pwr);
		while(SensorValue[ir]!=5);
		drive(-30);
		wait1Msec(175);
		drive(0);
		//TODO analyze sonars
}
void dump(){
		motor[arm]=30;
		while(nMotorEncoder[arm]<1700){
			nxtDisplayCenteredBigTextLine(3,"%d", nMotorEncoder[arm]);
		}//TODO check this
		motor[arm]=-15;
	//	int starts=ServoValue[latch];
		wait1Msec(50);
		motor[arm]=0;
		wait1Msec(1000);
		servo[latch]=0;
		wait1Msec(5000);
		servo[latch]=255;
		wait1Msec(250);
		wait1Msec(5000);
		servo[latch]=255;
		motor[arm]=-25;
		while(nMotorEncoder[arm]>100);
		motor[arm]=15;
		wait1Msec(50);
		motor[arm]=0;
		servo[latch]=185;
		/*servo[latch]=255;
		motor[arm]=20;
		while(nMotorEncoder[arm]<-30);
		motor[arm]=0;
		*/
}
void driveForwardToWall(int pwr){
		drive(pwr);
		int consec=0;
	//	if(useSonars3){
			while(consec<3){
				int d=readAnalogInput(HTPB,3);
				if (d>100)continue;
				if(d<sonar3Stage3A)consec++;
				else consec=0;
			}/*
		}
		else{
			if(data){
				ClearTimer(T3);
				for(int i=0;time1[T3]<1300;i++){
					int d=readAnalogInput(HTPB,3);
					if(d<400)sonardata[0]=d;
					else i--;
					while(time1[T3]%10!=0);
				}
			}
			else{
				wait1Msec(1300);
			}
		}
		*/
		drive(-50);
		wait1Msec(100);
		drive(0);
}
void driveBackwardToWall(int pwr){
		drive(-pwr);
	//	if(useSonars)while(readAnalogInput(HTPB,2)>sonar2Stage3B);
	//	else wait1Msec(2000);
			int consec=0;
			while(consec<3){
				int d=readAnalogInput(HTPB,2);
				if (d>100)continue;
				if(d<sonar2Stage3B)consec++;
				else consec=0;
			}
			drive(50);
		wait1Msec(100);
		drive(0);
}
void driveToLine(int pwr){
		drive(pwr);
		if(useLight){
			//while(SensorValue[light]<colorThreshold);
		while(readAnalogInput(HTPB,1)<3);
		}
		else wait1Msec(1300);
		drive(-50);
		wait1Msec(75);
		drive(0);
}
void driveOntoRamp(int pwr){
		drive(pwr);
		wait1Msec(1700);
		drive(0);
}
//TODO improve this and use better motors on drive train to prevent drift
void rotateRight(int degrees, int pwr){
		float itheta=theta;
		hi:
		motor[left]=pwr;
		motor[right]=pwr;
		while(theta-itheta<degrees-10);
		motor[left]=0;
		motor[right]=0;
		wait1Msec(200);
	//	if(theta-itheta<degrees)goto hi;
		motor[left]=-20;
		motor[right]=-20;
		while(theta-itheta>degrees);
		motor[left]=0;
		motor[right]=0;
}
void rotateLeft(int degrees, int pwr){
		float itheta=theta;
		hi:
		motor[left]=-pwr;
		motor[right]=-pwr;
		while(itheta-theta<degrees-10);
		motor[left]=0;
		motor[right]=0;
		wait1Msec(200);
		//if(itheta-theta<degrees)goto hi;
		motor[left]=20;
		motor[right]=20;
		while(itheta-theta>degrees);
		motor[left]=0;
		motor[right]=0;
}
void rotateRightv2(int degrees){
		float itheta=theta;
		motor[left]=35;
		motor[right]=35;
		while(theta-itheta<degrees-10);
		motor[left]=0;
		motor[right]=0;
		goto check;
		moreleft:
			motor[left]=-20;
			motor[right]=-20;
			while(theta-itheta>degrees+ERROR);
			motor[left]=0;
			motor[right]=0;
			goto check;
		moreright:
			motor[left]=20;
			motor[right]=20;
			while(theta-itheta<degrees-ERROR);
			motor[left]=0;
			motor[right]=0;
			goto check;
		check:
			wait1Msec(100);
			if(theta-itheta>degrees+ERROR)goto moreleft;
			if(theta-itheta<degrees-ERROR)goto moreright;
			motor[left]=0;
			motor[right]=0;
}
volatile int gyrovolts=0;
task graphicsThread(){
		while(true){
				if(data){
					nxtDisplayCenteredBigTextLine(0,"IR: %d",SensorValue[ir]);
					if(sonar1!=0)nxtDisplayCenteredBigTextLine(2,"%d",sonar1);
					if(sonar2!=0)nxtDisplayCenteredBigTextLine(4,"%d",sonar2);
					if(sonar3!=0)nxtDisplayCenteredBigTextLine(6,"%d",sonar3);
				}
				else{
					nxtDisplayCenteredBigTextLine(0,"%d, %d",theta, gyrovolts);
					nxtDisplayCenteredBigTextLine(2,"%d ms",updateTime);

					nxtDisplayCenteredBigTextLine(4,"L: %d",sonar1);
					nxtDisplayCenteredBigTextLine(6,"path: %d",path);

				}
				wait1Msec(100);
		}
}

task gyroThread(){
		StartTask(graphicsThread);
		ClearTimer(T4);
		while(true){
				int v=0;
			if(data)	HTSPBreadAllADC(HTPB,v,sonar1,sonar2,sonar3,10);
			else{
				v=readAnalogInput(HTPB,0);
				sonar1=readAnalogInput(HTPB,1);
			}
			/*	sonar1=readAnalogInput(HTPB,1);
				sonar2=readAnalogInput(HTPB,2);
				sonar3=readAnalogInput(HTPB,3);
			*/
			gyrovolts=v;
				float dv=v-stationaryVoltage;
				float dtheta=dv*valueDegreeSecond;
				theta+=dtheta*time1[T4]*.001;
				updateTime=time1[T4];
				ClearTimer(T4);
				wait1Msec(2);
		}
}
