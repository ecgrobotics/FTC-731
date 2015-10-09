#pragma config(Sensor, S1,     lu,             sensorTouch)
#pragma config(Sensor, S2,     ld,             sensorTouch)
#pragma config(Sensor, S3,     ru,             sensorTouch)
#pragma config(Sensor, S4,     rd,             sensorTouch)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "circle.c"
#include "vector.c"
#include "includes/rect.c"
volatile rect left;
volatile rect right;
volatile circle ball;
int lp;
int rp;
volatile int mode=2;//0=game, 1=pause, 2=score, 3=game over
volatile bool physicsActive=true;
volatile bool graphicsActive=true;
const int physicsDelay=50;
const int inputDelay=50;
vector ds;
bool rightStart=true;
task input(){
	while(physicsActive){
		if(SensorValue[lu]==1)left.y++;
		if(SensorValue[ld]==1)left.y--;
		if(sensorValue[ru]==1)right.y++;
		if(sensorValue[rd]==1)right.y--;
		wait1Msec(inputDelay);
	}
}
task physics(){
	while(PhysicsActive){
		if(mode==0){
			if(ds.x==0&&ds.y==0){//start ball
				ball.x=49;
				ball.y=31;
				int deg=rand()%120-60;
				ds.x=cosDegrees(deg);
				ds.y=sinDegrees(deg);
				if(!rightStart)ds.x*=-1;
				normalizeVector(ds);//need this? need &?
			}
			ball.x+=ds.x;
			ball.y+=ds.y;
			if(ball.y+ball.radius>=63 || ball.y-ball.radius<=0){
				ds.y*=-1;
			}
			//TODO Collisions


			if(ball.x+ball.radius>=99){
				lp++;
				mode=2;
				rightStart=true;
				nullifyVector(ds);
			}
			if(ball.x-ball.radius<=0){
				rp++;
				rightStart=false;
				mode=2;
				nullifyVector(ds);
			}
		}
		wait1Msec(physicsDelay);
	}
}
task graphics(){
	int time=29;
	while(graphicsActive){
		eraseDisplay();

		switch(mode){
				case 0:
						drawRect(left);
						drawRect(right);
						drawCircle(ball);
						nxtDrawLine(49,0,49,63);
						break;
				case 1:
					nxtDisplayCenteredBigTextLine(3,"PAUSED");
					break;
				case 2:
					nxtDisplayCenteredBigTextLine(1,"%d    %d",lp,rp);
					nxtDisplayCenteredBigTextLine(4,"%d",time/10+1);
					time--;
					if(time==0){
						mode=0;
						time=29;
					}
					break;
				case 3:
					nxtDisplayCenteredBigTextLine(0,"GAME OVER!");
					nxtDisplayCenteredBigTextLine(2,(lp>rp)?"LEFT WINS!":"RIGHT WINS!");
					nxtDisplayCenteredBigTextLine(1,"%d    %d",lp,rp);
					nxtDisplayCenteredTextLine(7,"Press a button to exit");
					physicsActive=false;
					while(SensorValue[lu]+SensorValue[ld]+SensorValue[ru]+SensorValue[rd]+nNxtButtonPressed<0);//should be -1 if all unpressed
					graphicsActive=false;

		}
		wait1Msec(100);
	}
}
task main()
{
	left.x=2;
	left.w=3;
	left.h=8;
	left.y=35;
	right.x=96;
	right.w=3;
	right.h=8;
	right.y=35;
	ball.radius=3;
	ds.x=0;
	ds.y=0;
	StartTask(graphics);
	StartTask(physics);
	StartTask(input);
	while(graphicsActive);
}
