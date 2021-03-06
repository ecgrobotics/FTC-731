#pragma config(Sensor, S1,     b,              sensorLightActive)
#pragma config(Sensor, S2,     f,              sensorLightActive)
#pragma config(Sensor, S3,     r,              sensorLightActive)
#pragma config(Sensor, S4,     l,              sensorLightActive)
#pragma config(Motor,  motorA,          left,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          right,         tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void turn();
void recover();
int min=500;
int max=1000;
int speed=40;
int thresh=38;//USE 40!!!!! most recently 38
volatile bool fs=true;
volatile bool bs=true;
volatile bool ls=true;
volatile bool rs=true;
bool debug=false;
task graph(){
	while(true){
		if(debug){
		nxtDisplayCenteredBigTextLine(0,"f: %d",SensorValue[f]);
		nxtDisplayCenteredBigTextLine(2,"b: %d",SensorValue[b]);
		nxtDisplayCenteredBigTextLine(4,"r: %d",SensorValue[r]);
		nxtDisplayCenteredBigTextLine(6,"l: %d",SensorValue[l]);
	}
	else{
		nxtDisplayCenteredBigTextLine(0,"HELLO!");
		nxtDisplayCenteredBigTextLine(2,"%d m %d s",time1[T4]/1000/60,time1[T4]/1000%60);
		nxtDisplayCenteredBigTextLine(4,"without");
		nxtDisplayCenteredBigTextLine(6,"accident");
	}
	//	nxtDisplayCenteredBigTextLine(2,"HELLO!");
		wait1Msec(100);
	}
}

task  sensors(){
	while(true){
		if(SensorValue[b]>=thresh)bs=true;
		else bs=false;
		if(SensorValue[r]>=thresh)rs=true;
		else rs=false;
		if(SensorValue[f]>=thresh)fs=true;
		else fs=false;
		if(SensorValue[l]>=thresh)ls=true;//TODO CHANGE THIS!!!
		else ls=false;
	}
}
bool t=true;
task main()
{
	ClearTimer(T4);
	StartTask(sensors);
	StartTask(graph);
	while(true){
		motor[left]=speed;
		motor[right]=speed;
		t=true;
		while(bs&&rs&&ls&&fs);
		/*
		motor[left]=0;
		motor[right]=0;
		nxtDisplayCenteredBigTextLine(0,"f: %d",SensorValue[f]);
		nxtDisplayCenteredBigTextLine(2,"b: %d",SensorValue[b]);
		nxtDisplayCenteredBigTextLine(4,"r: %d",SensorValue[r]);
		nxtDisplayCenteredBigTextLine(6,"l: %d",SensorValue[l]);
		wait1Msec(2000);

		if(SensorValue[b]<40){
				motor[left]=50;
				motor[right]=50;
				wait1Msec(1000);
				motor[left]=0;
				motor[right]=0;
		}
		if(SensorValue[f]<=1){
				motor[left]=-50;
				motor[right]=-50;
				wait1Msec(1000);
				motor[left]=0;
				motor[right]=0;
		}
		if(SensorValue[r]<40){
			motor[right]=-50;
			wait1Msec(250);
			motor[right]=0;
		wait1Msec(200);
				motor[left]=-50;
				motor[right]=-50;
				wait1Msec(750);
				motor[left]=0;
				motor[right]=0;
			//right back
		}
		if(SensorValue[l]<40){
				motor[left]=-50;
				wait1Msec(250);
				motor[left]=0;
					wait1Msec(200);
				motor[left]=-50;
				motor[right]=-50;
				wait1Msec(750);
				motor[left]=0;
				motor[right]=0;
		}
		*/
		recover();
		wait1Msec(500);
		if(t)turn();
		else continue;
		wait1Msec(500);
	}
}
void recover(){
	bool recovered=false;
	int post=0;//do nothing, 1=back 2=forward
	while(!recovered){
		if(!fs&&!bs&&!ls&&!rs){//ALL 4 OFF!!!!!
			motor[left]=0;
			motor[right]=0;
			PlaySound(soundException);
			ClearTimer(T4);
			wait1Msec(1000);
			post=0;
			continue;
		}
		if(!fs&&!ls&&!rs){
			motor[left]=-speed;
			motor[right]=-speed;
			post=1;
			continue;
		}
		if(!bs&&!ls&&!rs){
			motor[left]=speed;
			motor[right]=speed;
			post=2;
			continue;
		}
		if(!fs&&!bs){
			motor[left]=speed;
			motor[right]=-speed;
			post=0;
			continue;
		}
		if(!rs&&!ls){
				motor[left]=speed;
				motor[right]=speed;
				post=0;
				continue;
		}
		if(!fs&&!ls){
			motor[left]=-speed;
			motor[right]=0;
			post=1;
			continue;
		}
		if(!fs&&!rs){
			motor[left]=0;
			motor[right]=-speed;
			post=1;
			continue;
		}
		if(!bs&&!ls){
			motor[left]=speed;
			motor[right]=0;
			post=2;
			continue;
		}
		if(!bs&&!rs){
			motor[left]=0;
			motor[right]=speed;
			post=2;
			continue;
		}
		if(!ls){
			motor[left]=-speed;
			motor[right]=0;
			post=1;
			continue;
		}
		if(!rs){
			motor[left]=0;
			motor[right]=-speed;
			post=1;
			continue;
		}
		if(!fs){
			motor[left]=-speed;
			motor[right]=-speed;
			post=1;
			continue;
		}
		if(!bs){
			motor[left]=speed;
			motor[right]=speed;
			post=0;
			t=false;
		continue;//dont care
		}
		recovered=true;
	}
	switch(post){
		case 1:
			motor[left]=-speed;
			motor[right]=-speed;
			break;
		case 2:
			motor[left]=speed;
			motor[right]=speed;
			break;
		default:
			motor[left]=0;
			motor[right]=0;
			return;
	}
	ClearTimer(T1);
	while(bs&&fs&&ls&&rs&&time1[T1]<500);
	if(fs&&ls&&rs)return;
	else recover();

	motor[right]=0;
	motor[left]=0;
}
void turn(){
		int r=(rand()%2==1)?1:-1;
		motor[left]=50*r;
		motor[right]=-50*r;
		ClearTimer(T1);
		int delay=(rand() % (max-min)) + min;
		while(time1[T1]<delay&&bs&&fs&&ls&&rs);
		motor[right]=0;
		motor[left]=0;
		if(fs&&ls&&rs)return;
		else recover();
}
