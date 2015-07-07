#pragma config(Sensor, in1,    pot,            sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  solenoid,       sensorDigitalOut)
#pragma config(Sensor, dgtl9,  redCloseBut,    sensorTouch)
#pragma config(Sensor, dgtl10, redFarBut,      sensorTouch)
#pragma config(Sensor, dgtl11, blueCloseBut,   sensorTouch)
#pragma config(Sensor, dgtl12, blueFarBut,     sensorTouch)
#pragma config(Motor,  port1,           hangRight,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           armRight,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           backRight,     tmotorVex393_MC29, openLoop, reversed, encoderPort, dgtl1)
#pragma config(Motor,  port5,           intakeRight,   tmotorVex393_MC29, openLoop, encoderPort, dgtl3)
#pragma config(Motor,  port6,           intakeLeft,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           armLeft,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           frontLeft,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          hangLeft,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(200)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
int phase = 0; //Values are 0-3, 0 = wait, 1 = left, 2 = right, 3 = pick up sack, return home.
int upperArmPosition = 1600;
int lowerArmPosition = 80;
int middleArmPosition = 1000;
int scoringArmPosition = 1400; //CHANGE THIS
#define REDC 1
#define REDF 2
#define BLUEC 3
#define BLUEF 4



void stahp(){
	motor[frontLeft] = 0;
	motor[backLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;

}

void goForward(int rotations){//rotations = negative
	while(SensorValue(leftEncoder) > rotations){
		if(SensorValue[leftEncoder] < SensorValue[rightEncoder]){ //left wheels further than right wheels, slow down left
			motor[frontLeft] = 100;
			motor[backLeft] = 100;
			motor[frontRight] = 127;
			motor[backRight] = 127;
		}
		if(SensorValue[rightEncoder] < SensorValue[leftEncoder]){ //right wheels further than left wheels, slow down right
			motor[frontLeft] = 127;
			motor[backLeft] = 127;

			motor[frontRight] = 100;
			motor[backRight] = 100;
		}
		if(SensorValue[leftEncoder] == SensorValue[rightEncoder]){
			motor[frontLeft] = 127;
			motor[backLeft] = 127;
			motor[frontRight] = 127;
			motor[backRight] = 127;
		}
	}
}

void goBackward(int rotations){//rotations = positive
	while(SensorValue(leftEncoder) < rotations){
		if(SensorValue[leftEncoder] < SensorValue[rightEncoder]){ //left wheels further than right wheels, slow down left
			motor[frontLeft] = -100;
			motor[backLeft] = -100;
			motor[frontRight] = -127;
			motor[backRight] = -127;
		}
		if(SensorValue[rightEncoder] < SensorValue[leftEncoder]){ //right wheels further than left wheels, slow down right
			motor[frontLeft] = -127;
			motor[backLeft] = -127;
			motor[frontRight] = -100;
			motor[backRight] = -100;
		}
		if(SensorValue[leftEncoder] == SensorValue[rightEncoder]){
			motor[frontLeft] = -127;
			motor[backLeft] = -127;
			motor[frontRight] = -127;
			motor[backRight] = -127;
		}

	}
}
void turnRight(int rotations){//rotations = negative
	while(SensorValue(leftEncoder) > rotations){
		motor[frontLeft] = 127;
		motor[backLeft] = 127;
		motor[frontRight] = -127;
		motor[backRight] = -127;
	}
}

void turnLeft(int rotations){//rotations = negative
	while(SensorValue(rightEncoder) > rotations){
		motor[frontLeft] = -127;
		motor[backLeft] = -127;
		motor[frontRight] = 127;
		motor[backRight] = 127;
	}
}

void leftPivot(int rotations){//rotations = negative
	while(SensorValue(rightEncoder) > rotations){
		motor[frontLeft] = 0;
		motor[backLeft] = 0;
		motor[frontRight] = 127;
		motor[backRight] = 127;
	}
}

void rightPivot(int rotations){//rotations = negative
	while(SensorValue(leftEncoder) > rotations){
		motor[frontLeft] = 127;
		motor[backLeft] = 127;
		motor[frontRight] = 0;
		motor[backRight] = 0;
	}
}

void resetEncoder(){
	SensorValue(leftEncoder) = 0;
	SensorValue(rightEncoder) = 0;
}


void resetPot(){
	SensorValue(pot) = 0;
}
void armUpTo(int position){
	while(SensorValue(pot) < position){
		motor[armLeft] = 127;
		motor[armRight] = 127;
	}
}
void armUp(){
	while(SensorValue(pot) < upperArmPosition){
		motor[armLeft] = 127;
		motor[armRight] = 127;
	}
}

void armHalfUp(){
	while(SensorValue(pot) < (middleArmPosition)){
		motor[armLeft] = 100;
		motor[armRight] = 100;
	}
}

void keepArmUp(){
	motor[armLeft] = 50;
	motor[armRight] = 50;
}

void armDown(){
	while(SensorValue(pot) > lowerArmPosition){
		motor[armLeft] = -127;
		motor[armRight] = -127;
	}
}

void stahpArm(){
	motor[armLeft] = 0;
	motor[armRight] = 0;
}

void intakeDown(){

	armUp();
	armDown();
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton() {
	phase = 0;
	motor[port2]=0;
	motor[port3]=0;
	motor[port4]=0;
	motor[port5]=0;
	motor[port6]=0;
	motor[port7]=0;
	motor[port8]=0;
	motor[port9]=0;

	if(SensorValue(redCloseBut) == 1){
		phase = 1;
	}
	else if(SensorValue(redFarBut) == 1){
		phase = 2;
	}


	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous(){
	while(true){
		if(SensorValue(redCloseBut) == 1){
			phase = REDC;
		}
		else if (SensorValue(redFarBut) == 1){
			phase = REDF;
		}
		else if (SensorValue(blueCloseBut) == 1){
			phase = BLUEC;
		}
		else if (SensorValue(blueFarBut) == 1){
			phase = BLUEF;
		}

		if(phase == REDF){
			resetEncoder();
			resetPot();

			armUp();
			resetPot();
			armDown();
			resetPot();

			armHalfUp();
			motor[armLeft] = 25;
			motor[armRight] = 25;

			goForward(-740);
			stahp();
			resetEncoder();

			wait(.5);

			goBackward(540);
			stahp();
			resetEncoder();

			wait(3); //reposition bot

			goForward(-850);
			stahp();
			resetEncoder();

			wait(.5);

			goBackward(850);
			stahp();
			resetEncoder();

			armDown();
			stahpArm();
			resetPot();

			break;

			}else if(phase == BLUEC){ //go for high goal with preload
			resetEncoder();
			resetPot();

			armUp();
			armDown();

			startMotor(intakeLeft);
			startMotor(intakeRight);

			goForward(-370);
			resetEncoder();
			wait(1);
			goBackward(370);
			resetEncoder();
			wait(1);

			stopMotor(intakeLeft);
			stopMotor(intakeRight);

			goForward(-10);
			resetEncoder();
			goBackward(-10);
			resetEncoder();
			goForward(-10);
			resetEncoder();
			goBackward(-10);
			resetEncoder();
			stahp();

			goForward(-80);
			stahp();
			resetEncoder();

			wait(.5);

			rightPivot(-760); //u-turn
			stahp();
			resetEncoder();

			wait(.5);

			goForward(-240);
			stahp();
			resetEncoder();

			goBackward(100);
			stahp();
			resetEncoder();

			turnRight(-125);
			stahp();
			resetEncoder();

			goForward(-250);
			stahp();
			resetEncoder();

			wait(.5);

			goBackward(180);
			stahp();
			resetEncoder();

			turnLeft(-150);
			stahp();
			resetEncoder();

			goForward(-790);
			stahp();
			resetEncoder();

			turnRight(-360);
			stahp();
			resetEncoder();

			goForward(-360);
			stahp();
			resetEncoder();

			motor[intakeLeft] = -127;
			motor[intakeRight] = -127;

			break;
		}
		else if (phase == REDC){
			resetEncoder();
			resetPot();

			armUp();
			armDown();

			startMotor(intakeLeft);
			startMotor(intakeRight);

			goForward(-370);
			resetEncoder();
			wait(.5);
			goBackward(370);
			resetEncoder();
			wait(.1);

			stopMotor(intakeLeft);
			stopMotor(intakeRight);

			goForward(-10);
			resetEncoder();
			goBackward(-10);
			resetEncoder();
			goForward(-10);
			resetEncoder();
			goBackward(-10);
			resetEncoder();
			stahp();

			goForward(-80);
			stahp();
			resetEncoder();

			wait(.5);

			leftPivot(-760); //u-turn
			stahp();
			resetEncoder();

			wait(.5);

			goForward(-240);
			stahp();
			resetEncoder();

			goBackward(100);
			stahp();
			resetEncoder();

			turnLeft(-125);
			stahp();
			resetEncoder();

			goForward(-250);
			stahp();
			resetEncoder();

			wait(.5);

			goBackward(180);
			stahp();
			resetEncoder();

			turnRight(-150);//100
			stahp();
			resetEncoder();

			goForward(-790);
			stahp();
			resetEncoder();

			turnLeft(-360);
			stahp();
			resetEncoder();

			goForward(-360);
			stahp();
			resetEncoder();

			//should work....

			motor[intakeLeft] = -127;
			motor[intakeRight] = -127;

			break;
		}
		if (phase == BLUEF){
			resetEncoder();
			resetPot();

			armUp();
			resetPot();
			armDown();
			resetPot();

			armHalfUp();
			motor[armLeft] = 25;
			motor[armRight] = 25;

			goForward(-740);
			stahp();
			resetEncoder();

			wait(.5);

			goBackward(540);
			stahp();
			resetEncoder();

			wait(3); //reposition bot

			goForward(-850);
			stahp();
			resetEncoder();

			wait(.5);

			goBackward(850);
			stahp();
			resetEncoder();

			armDown();
			stahpArm();
			resetPot();

			wait(3);
			goForward(-1000);
			stahp();
			resetEncoder();

			armUp();
			motor[armLeft] = 25;
			motor[armRight] = 25;


			goForward(-300);
			resetEncoder();
			stahp();

			motor[intakeLeft] = -127;
			motor[intakeRight] = -127;
			wait(1);

			goBackward(300);
			stahp();
			resetEncoder();
			armDown();
			resetPot();
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//z
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol(){
	while (true){
		motor[frontRight] = vexRT[Ch2];  //C1 joystick down = backward, up = forward
		motor[backRight] = vexRT[Ch2];
		motor[frontLeft] = vexRT[Ch3];
		motor[backLeft] = vexRT[Ch3];
		motor[armLeft] = vexRT[Ch2Xmtr2];  //right joy stick arm up and down
		motor[armRight] = vexRT[Ch2Xmtr2];

		if(vexRT[Btn8U]){
			motor[hangLeft] = 127;
			motor[hangRight] = 127;
			}else if(vexRT[Btn7L]){
			motor[hangLeft] = -127;
			motor[hangRight] = -127;
		}
		else{
			motor[hangLeft] = 0;
			motor[hangRight] = 0;
		}
		// 2nd Controller
		/*-------------------TESTING------------------------------------------- */


/*		if(vexRT[Ch2Xmtr2] > 0)
		{
			if (SensorValue(pot) < 1600)
			{
				motor[armLeft] = vexRT[Ch2Xmtr2];
				motor[armRight] = vexRT[Ch2Xmtr2];
			}
			else
			{
				motor[armLeft] = 50;
				motor[armRight] = 50;
			}
		}
		else if (vexRT[Ch2Xmtr2] < 0)
		{
			if (SensorValue(pot) > lowerArmPosition)
			{
				motor[armLeft] = vexRT[Ch2Xmtr2];
				motor[armRight] = vexRT[Ch2Xmtr2];
			}
			else
			{
				motor[armLeft] = 0;
				motor[armRight] = 0;
			}
		}
		else
		{
			motor[armLeft] = 0;
			motor[armRight] = 0;
		}
		else {
			motor[armLeft] = vexRT[Ch2Xmtr2];
			motor[armRight] = vexRT[Ch2Xmtr2];
		}*/
		/*----------------------------------------------------------------------*/


		if(vexRT[Btn5UXmtr2]){ //backward intake
			motor[intakeLeft] = -127;
			motor[intakeRight] = -127;
		}
		else if(vexRT[Btn5DXmtr2]){ //forward intake
			motor[intakeLeft] = 127; // used to be 75
			motor[intakeRight] = 127;
		}
		else{
			motor[intakeLeft] = 0;
			motor[intakeRight] = 0;
		}

	if (vexRT[Btn7UXmtr2]){
		SensorValue[solenoid] = 1;
	}
}
}
