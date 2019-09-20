#pragma config(Sensor, in1,    leftLineFollower, sensorLineFollower)
#pragma config(Sensor, in2,    centerLineFollower, sensorLineFollower)
#pragma config(Sensor, in3,    rightLineFollower, sensorLineFollower)
#pragma config(Sensor, dgtl2,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  touchSensor,    sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port6,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port7,           rightMotor,    tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Moving Forward
This program instructs your robot to move forward at full power for three seconds.
There is a two second pause at the beginning of the program.

Robot Model(s): Squarebot

[I/O Port]          [Name]              [Type]                [Description]
Motor Port 2        rightMotor          VEX Motor             Right side motor
Motor Port 3        leftMotor           VEX Motor             Left side motor

*To run this sample program on Swervebot, be sure to Reverse Motor Port 3 in the Motors and Sensors
 Setup, and to make sure that Motor Port 2 is NOT Reversed.
----------------------------------------------------------------------------------------------------*/
// Turn formula == (40/10.5) *360 == 1371/4 == 342.75
// Formula fyrir BASEDIST 50/10*3.14) * 360
// 3.81
#define TURN 3.1
#define BASEDIST 573

void reset_encode(){
	SensorValue[rightEncoder]=0;
	SensorValue[leftEncoder]=0;
};
void stop_motor(int stop_time){
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(stop_time);
};
void robot_turn(bool l_r,int deg){
	if(l_r){
		while(TURN *deg > abs(SensorValue[rightEncoder])){
			motor[leftMotor] = -80;
			motor[rightMotor] = 80;
		}
	}
	else{
		while(TURN *deg > abs(SensorValue[leftEncoder])){
			motor[leftMotor] = 80;
			motor[rightMotor] = -80;
		}
	}
};

void drive() {
	while(BASEDIST>abs(SensorValue[rightEncoder])){
		if(abs(SensorValue[rightEncoder]) == abs(SensorValue[leftEncoder])) // If rightEncoder has counted the same amount as leftEncoder:
		{
			// Move Forward
			motor[rightMotor] = 80;		    // Right Motor is run at power level 80
			motor[leftMotor]  = 80;		    // Left Motor is run at power level 80
		}
		else if(abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder]))	// If rightEncoder has counted more encoder counts
		{
			// Turn slightly right
			motor[rightMotor] = 70;		    // Right Motor is run at power level 60
			motor[leftMotor]  = 80;		    // Left Motor is run at power level 80
		}
		else	// Only runs if leftEncoder has counted more encoder counts
		{
			// Turn slightly left
			motor[rightMotor] = 80;		    // Right Motor is run at power level 80
			motor[leftMotor]  = 70;		    // Left Motor is run at power level 60
		}

	}
};

bool turn_array[14]= {0,1,1,0,0,1,1,0,0,1,1,0,1,1};
//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
				for(int i=0;i<14;i++){
					reset_encode();
					drive();
					reset_encode();
					stop_motor(500);
					robot_turn(turn_array[i], 90);
				}



}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
