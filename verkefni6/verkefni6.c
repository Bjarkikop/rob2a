#pragma config(Sensor, in1,    lineFollowerLEFT,   sensorLineFollower)
#pragma config(Sensor, in2,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerRIGHT,    sensorLineFollower)
#pragma config(Sensor, dgtl2,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  touchSensor,    sensorTouch)
#pragma config(Sensor, in5,  sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port6,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port7,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           arMMotor,      tmotorNormal, openLoop)
#pragma config(Motor,  port3,           armMotor,      tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "header.h"

void reset_encode(){
	SensorValue[rightEncoder]=0;
	SensorValue[leftEncoder]=0;
};
void stop_motor(){
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;

};
void robot_turn(bool l_r,int deg){
	if(l_r){
		while(TURN *deg > abs(SensorValue[rightEncoder])){
			motor[leftMotor] = -POWER;
			motor[rightMotor] = POWER;
			if (TURN *deg < abs(SensorValue[rightEncoder])){
				stop_motor();
			}
		}
	}
	else if(l_r == false){
		while(TURN *deg > abs(SensorValue[leftEncoder])){
			motor[leftMotor] = POWER;
			motor[rightMotor] = -POWER;
			if (TURN *deg < abs(SensorValue[leftEncoder])){
				stop_motor();
			}
		}
	}

};

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{

  int threshold = 2000;      /* found by taking a reading on both DARK and LIGHT    */
	while(BASEDIST>abs(SensorValue[leftEncoder])){

		  	if(SensorValue(lineFollowerCENTER) > threshold && SensorValue(lineFollowerLEFT) < threshold && SensorValue(lineFollowerRIGHT) < threshold)
		    {
							motor[rightMotor] = POWER;
							motor[leftMotor]  = POWER;
		    	}

		    if(SensorValue(lineFollowerRIGHT) > threshold && SensorValue(lineFollowerLEFT) < threshold && SensorValue(lineFollowerCENTER) < threshold)
		    {
								motor[leftMotor]  = POWER;
		      			motor[rightMotor] = 0;
		    	}
		    if(SensorValue(lineFollowerLEFT) > threshold && SensorValue(lineFollowerCENTER) < threshold && SensorValue(lineFollowerRIGHT) < threshold)
		    {
		      			motor[leftMotor]  = 0;
		      			motor[rightMotor] = POWER;
		    }
	}
	stop_motor();
	wait10Msec(10);
	reset_encode();
	robot_turn(1, 90);
	reset_encode();


}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
