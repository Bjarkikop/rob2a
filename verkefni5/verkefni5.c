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

/*----------------------------------------------------------------------------------------------------*\
|*                             	    - Triple Sensor Line Tracking -                                   *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program uses 3 VEX Line Follower Sensors to track a black line on a light(er) surface.       *|
|*  There is a two second pause at the beginning of the program.                                      *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  Lighting conditions, line darkness, and surface lightness change from place to place,       *|
|*        so the value of 'threshold' may need to be changed to better suit your environment.         *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor  - Port 2     rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor  - Port 3     leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Analog - Port 1     lineFollowerRIGHT   VEX Light Sensor      Front-right, facing down          *|
|*    Analog - Port 2     lineFollowerCENTER  VEX Light Sensor      Front-center, facing down         *|
|*    Analog - Port 3     lineFollowerLEFT    VEX Light Sensor      Front-left, facing down           *|
\*-----------------------------------------------------------------------------------------------4246-*/
#define TURN 3.1
#define BASEDIST 286.5

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
			motor[leftMotor] = -40;
			motor[rightMotor] = 40;
			if (TURN *deg < abs(SensorValue[rightEncoder])){
				stop_motor();
			}
		}
	}
	else if(l_r == false){
		while(TURN *deg > abs(SensorValue[leftEncoder])){
			motor[leftMotor] = 40;
			motor[rightMotor] = -40;
			if (TURN *deg < abs(SensorValue[leftEncoder])){
				stop_motor();
			}
		}
	}

};

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{

  int threshold = 1800;      /* found by taking a reading on both DARK and LIGHT    */

  while((SensorValue(touchSensor) != 1) && (vexRT[Btn8R] != 1))
  {

    // RIGHT sensor sees dark:
  	if(SensorValue(lineFollowerCENTER) > threshold)
    {
      // go straight
      motor[leftMotor]  = 40;
      motor[rightMotor] = 40;

    }

    else if(SensorValue(lineFollowerRIGHT) > threshold)
    {
      // counter-steer right:
      motor[leftMotor]  = 40;
      motor[rightMotor] = 0;

    }

    // LEFT sensor sees dark:
    else if(SensorValue(lineFollowerLEFT) > threshold)
    {
      // counter-steer left:
      motor[leftMotor]  = 0;
      motor[rightMotor] = 40;

    }
    else{
    	robot_turn(1, 90);
    	reset_encode();
    }
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
