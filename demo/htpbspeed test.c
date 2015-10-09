
#pragma config(Sensor, S1,     HTPB,           sensorI2CCustom9V) !!*//

//#include "C:\Users\Thomas\Documents\FTC Programs\rdpartyrobotcdr-3.3.1\drivers\hitechnic-superpro.h"
#include "C:\Users\Thomas\Documents\FTC Programs\includes\HTPB.h"
//plug O1 to A1, read 8 consecutive data points, compare for time
task main(){
	//set O1 to 1hz
HTSPBwriteAnalog(HTPB,HTSPB_DACO0,DAC_MODE_TRIANGLEWAVE,1,1023);
		//this should set O1 (analog out) to a square wave
	/*
	HTPB_I2CRequest[0]=3;//message size
	HTPB_I2CRequest[1]=0x10;//PB address
	HTPB_I2CRequest[2]=0x52;
	HTPB_I2CRequest[3]=1;//this shoule be square wave.... if not, maybe 1 or 3...?
	//plug an led into O1 and see if blinks or fades.
	writeI2C(HTPB, HTPB_I2CRequest);//set analog mode to square wave
	HTPB_I2CRequest[2]=0x53;
	HTPB_I2CRequest[3]=0b00000000;//frequency ( this is 4Hz)
	//ignore lower 2 bits (00 for 4 hzt anyway)
	writeI2C(HTPB,HTPB_I2CRequest);//set analog out frequency to 1Hz
	HTPB_I2CRequest[2]=0x54;
	HTPB_I2CRequest[3]=0b00000001;
	writeI2C(HTPB,HTPB_I2CRequest);
	HTPB_I2CRequest[2]=0x55;
	HTPB_I2CRequest[3]=0b11111111;//1021=3.2ish volts....i think... idk...PB_
	//ignore lower 2 bits again cuz im lazy
	writeI2C(HTPB,HTPB_I2CRequest);
	*/
	/*
	wait1Msec(1000);//wait exactly 1 sec
	float values[8];
	ClearTimer(T4);
	for(int i=0;i<8;i++){
		values[i]=readAnalogVolts(HTPB,1);
	}
	int time=time1[T4];
	for(int i=0;i<8;i++){
		nxtDisplayTextLine(i,"%.3f, %.3f",values[i],(values[i]-1.65)/(4*1.68));
	}
	nxtDisplayStringAt(75,50,"(%d ms)",time);
	while(true);
	*/
	clearTimer(T4);
	 HTSPBwriteIO(HTPB,0b00000001);
		HTSPBwriteIO(HTPB,0b00000010);
		HTSPBwriteIO(HTPB,0b00000100);
		HTSPBwriteIO(HTPB,0b00001000);
		HTSPBwriteIO(HTPB,0b00010000);
		HTSPBwriteIO(HTPB,0b00100000);
		HTSPBwriteIO(HTPB,0b01000000);
		HTSPBwriteIO(HTPB,0b10000000);
		int time2=time1[T4];
		nxtDisplayCenteredBigTextLine(1,"%d",time2);
	while(true){
		HTSPBwriteIO(HTPB,0b00000001);
		HTSPBwriteIO(HTPB,0b00000010);
		HTSPBwriteIO(HTPB,0b00000100);
		HTSPBwriteIO(HTPB,0b00001000);
		HTSPBwriteIO(HTPB,0b00010000);
		HTSPBwriteIO(HTPB,0b00100000);
		HTSPBwriteIO(HTPB,0b01000000);
		HTSPBwriteIO(HTPB,0b10000000);
	}

}
