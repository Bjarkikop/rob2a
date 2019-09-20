#pragma config(Sensor, in1,    leftLineFollower, sensorLineFollower)
#pragma config(Sensor, in2,    centerLineFollower, sensorLineFollower)
#pragma config(Sensor, in3,    rightLineFollower, sensorLineFollower)
#pragma config(Sensor, dgtl2,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  touchSensor,    sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port6,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port7,           rightMotor,    tmotorServoContinuousRotation, openLoop)

#define TURN 3.81
void robot_turn(bool l_r,int deg){
	if(l_r){
		while(TURN *deg > SensorValue[leftEncoder]){
			motor[leftMotor] = -80;
			motor[rightMotor] = 80;
		}
	}
	else{
		while(TURN *deg > SensorValue[leftEncoder]){
			motor[leftMotor] = 80;
			motor[rightMotor] = -80;
		}
	}
};

task main()
{

	robot_turn(TRUE,90);

}
