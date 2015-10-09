#pragma systemFile
#include "hitechnic-superpro.h"
#include "C:\Users\Thomas\Documents\FTC Programs\rdpartyrobotcdr-3.3.1\drivers\hitechnic-superpro.h"
int voltsToInt(double volts){
	return (int)(310*volts);
}
int readAnalogInput(tSensors HTPB,byte port){
	return HTSPBreadADC(HTPB,port,10);
}
float readAnalogVolts(tSensors HTPB, byte port){
	int i=readAnalogInput(HTPB,port);
	return (float)i/(float)310.0;
}
bool writeAnalogFloat(tSensors HTPB,byte dac, byte mode, int freq, float volt){
	return HTSPBwriteAnalog(HTPB,dac,mode,freq,(int)(volt*310));
}
void setLED(tSensors HTPB, ubyte leds){
	HTSPB_I2CRequest[0]=3;//message size
	HTSPB_I2CRequest[1]=0x10;//PB address
	HTSPB_I2CRequest[2]=0x51;
	HTSPB_I2CRequest[3]=leds;
	writeI2C(HTPB,HTSPB_I2CRequest);
}
void setStrobe(tSensors HTPB, ubyte strobes){
	HTSPB_I2CRequest[0]=3;//message size
	HTSPB_I2CRequest[1]=0x10;//PB address
	HTSPB_I2CRequest[2]=0x50;
	HTSPB_I2CRequest[3]=strobes;
	writeI2C(HTPB,HTSPB_I2CRequest);
}
