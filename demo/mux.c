#pragma config(Sensor, S1,     mux,            sensorHiTechnicTouchMux)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true){
		int i=SensorValue[mux];
		nxtDisplayCenteredBigTextLine(0,(i&1)?"true":"false");
		nxtDisplayCenteredBigTextLine(2,(i&2)?"true":"false");
		nxtDisplayCenteredBigTextLine(4,(i&4)?"true":"false");
		nxtDisplayCenteredBigTextLine(6,(i&8)?"true":"false");
	}


}
