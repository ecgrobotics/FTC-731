#pragma systemFile
#include "HTPB.h"
const int NXTOK=8500;
const int NXTBAD=8000;
const int TETRIXOK=11500;
const int TETRIXBAD=10000;

void clock(tSensors HTPB);
//update battery lights
int out=0;
void batteryUpdate(tSensors HTPB){

	int nxt=nImmediateBatteryLevel;
	int tet=externalBattery;

	//tetrix: ryg
	HTSPBwriteIO(HTPB,out=(tet<=TETRIXBAD)?0b10000000:0b00000000);
	clock(HTPB);
	HTSPBwriteIO(HTPB,out=(tet<=TETRIXOK&&tet>TETRIXBAD)?0b10000000:0b00000000);
	clock(HTPB);
	HTSPBwriteIO(HTPB,out=(tet>TETRIXOK)?0b10000000:0b00000000);
	clock(HTPB);
	//empty output
	HTSPBwriteIO(HTPB,out=0b00000000);
	clock(HTPB);
	//Nxt ryg
	HTSPBwriteIO(HTPB,out=(nxt<=NXTBAD)?0b10000000:0b00000000);
	clock(HTPB);
	HTSPBwriteIO(HTPB,out=(nxt<=NXTOK && nxt>NXTBAD)?0b10000000:0b00000000);
	clock(HTPB);
	HTSPBwriteIO(HTPB,out=(nxt>NXTOK)?0b10000000:0b00000000);
	clock(HTPB);
	//empty
	HTSPBwriteIO(HTPB,out=0b00000000);
	clock(HTPB);
	//latch
	HTSPBwriteIO(HTPB,0b01000000);
}
void clock(tSensors HTPB){
	HTSPBwriteIO(HTPB,out | 0b00100000);
}
