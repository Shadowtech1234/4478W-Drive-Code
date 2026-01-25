/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Theenash Muneeswaran                                      */
/*    Created:      Thu Oct 17 2024                                           */
/*    Description:  4478F Drive Code with autonomus                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// mFrontRight          motor         16              
// mMidRight            motor         3               
// mBackRight           motor         14              
// mMidLeft             motor         5               
// mFrontLeft           motor         7               
// mBackLeft            motor         4               
// mintake              motor         19              
// mfrontintake         motor         6               
// RightN               digital_out   A               
// LeftN                digital_out   C     
// cornerN              digital_out   E 
// mflipper             motor         11
// ---- END VEXCODE CONFIGURED DEVICES ----
//yougotpugged
#include "vex.h"
#include <cstdlib> 
#include <ctime>


using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

brain Brain;
controller Controller1;
motor mFrontRight = motor(PORT16, ratio18_1, true);
motor mMidRight = motor(PORT3, ratio18_1, true);
motor mBackRight = motor(PORT14, ratio18_1, true);
motor mMidLeft = motor(PORT5, ratio18_1, true);
motor mFrontLeft = motor(PORT7, ratio18_1, true);
motor mBackLeft = motor(PORT4, ratio18_1, true);
motor mintake = motor(PORT17, ratio18_1, true);
motor mfrontintake = motor(PORT6, ratio18_1, true);
motor mladybug = motor(PORT11, ratio18_1, true);
digital_out bottomN = digital_out(Brain.ThreeWirePort.A);
digital_out topN = digital_out(Brain.ThreeWirePort.C);
digital_out corner1N = digital_out(Brain.ThreeWirePort.G);
digital_out cornor2N = digital_out(Brain.ThreeWirePort.E);

void setVelo(int speed){
  mFrontLeft.setVelocity(speed, percent);
  mFrontRight.setVelocity(speed, percent);
  mMidLeft.setVelocity(speed, percent);
  mMidRight.setVelocity(speed, percent);
  mBackLeft.setVelocity(speed, percent);
  mBackRight.setVelocity(speed, percent);
}



void turnright(int waitTime){
  mFrontLeft.spinFor(forward, waitTime, degrees, false);
  mFrontRight.spinFor(forward, waitTime, degrees, false);
  mMidLeft.spinFor(forward, waitTime, degrees, false);
  mMidRight.spinFor(forward, waitTime, degrees, false);
  mBackLeft.spinFor(reverse, waitTime, degrees, false);
  mBackRight.spinFor(forward, waitTime, degrees, true);
}

void turnleft(int waitTime){
  mFrontLeft.spinFor(reverse, waitTime, degrees, false);
  mFrontRight.spinFor(reverse, waitTime, degrees, false);
  mMidLeft.spinFor(reverse, waitTime, degrees, false);
  mMidRight.spinFor(reverse, waitTime, degrees, false);
  mBackLeft.spinFor(reverse, waitTime, degrees, false);
  mBackRight.spinFor(reverse, waitTime, degrees, true);
}

void driveforward(int waitTime){
  mFrontLeft.spinFor(forward, waitTime, degrees, false);
  mFrontRight.spinFor(reverse, waitTime, degrees, false);
  mMidLeft.spinFor(forward, waitTime, degrees, false);
  mMidRight.spinFor(reverse, waitTime, degrees, false);
  mBackLeft.spinFor(forward, waitTime, degrees, false);
  mBackRight.spinFor(reverse, waitTime, degrees, true);
}

void drivereverse(int waitTime){
  mFrontLeft.spinFor(reverse, waitTime, degrees, false);
  mFrontRight.spinFor(forward, waitTime, degrees, false);
  mMidLeft.spinFor(reverse, waitTime, degrees, false);
  mMidRight.spinFor(forward, waitTime, degrees, false);
  mBackLeft.spinFor(reverse, waitTime, degrees, false);
  mBackRight.spinFor(forward, waitTime, degrees, true);
}


void intakeup(int waittime){
  mintake.spinFor(reverse, waittime, degrees, true);
}

void intakedown(int waittime){
  mintake.spinFor(forward, waittime, degrees, true);
}

void frontintakeup(int waittime){
  mfrontintake.spinFor(forward, waittime, degrees, true);
}

void frontintakedown(int waittime){
  mfrontintake.spinFor(reverse, waittime, degrees, true);
}


void bothintakeup(int waittime){
  mfrontintake.spinFor(forward, waittime, degrees, false);
  mintake.spinFor(reverse, waittime, degrees, true);
}


void bothintakedown(int waittime){
  mfrontintake.spinFor(reverse, waittime, degrees, false);
  mintake.spinFor(forward, waittime, degrees, true);
}

void bothmoveforwardintakeup(int waittime){
  mfrontintake.spinFor(forward, waittime, degrees, false);
  mFrontLeft.spinFor(forward, waittime, degrees, false);
  mFrontRight.spinFor(reverse, waittime, degrees, false);
  mMidLeft.spinFor(forward, waittime, degrees, false);
  mMidRight.spinFor(reverse, waittime, degrees, false);
  mBackLeft.spinFor(forward, waittime, degrees, false);
  mBackRight.spinFor(reverse, waittime, degrees, false);
  mintake.spinFor(reverse, waittime, degrees, true);
}


void bothmovebackwardintakeup(int waittime){
  mfrontintake.spinFor(forward, waittime, degrees, false); 
  mFrontLeft.spinFor(reverse, waittime, degrees, false);
  mFrontRight.spinFor(forward, waittime, degrees, false);
  mMidLeft.spinFor(reverse, waittime, degrees, false);
  mMidRight.spinFor(forward, waittime, degrees, false);
  mBackLeft.spinFor(reverse, waittime, degrees, false);
  mBackRight.spinFor(forward, waittime, degrees, false);
  mintake.spinFor(reverse, waittime, degrees, true);
}

void motorstop(int waitTime){
  mFrontLeft.stop(hold);
  mFrontRight.stop(hold);
  mMidLeft.stop(hold);
  mMidRight.stop(hold);
  mBackLeft.stop(hold);
  mBackRight.stop(hold);
  wait(waitTime, msec);
}

void flipperup(int waittime){
  mladybug.spinFor(reverse, waittime, degrees, true);
}

void flipperdown(int waittime){
  mladybug.spinFor(reverse, waittime, degrees, false);
}





void clamplock(){
  bottomN.set(false);
  topN.set(true);
}

void clampunlock(){
  bottomN.set(true);
  topN.set(false);
}





 bool pressedClamp = false;
 void toggleClamp(){
  pressedClamp = !pressedClamp;
  if(pressedClamp){
    bottomN.set(false);
      topN.set(true);
  }
  else if(!pressedClamp){
    bottomN.set(true);
      topN.set(false);
  }
 }

 bool pressedcorner = false;
 void toggledoinker(){
  pressedcorner = !pressedcorner;
  if(pressedcorner){
    corner1N.set(true);
    cornor2N.set(true);
  }
  else if(!pressedClamp){
    corner1N.set(false);
    cornor2N.set(false);
  }
 }


int autono = 0;
void autonSelection(){
  if (autono <= 3){
    autono++;
  }
  else{
    autono=0;
  }
  switch(autono){
    /*
    case 0:
    Brain.Screen.clearLine();
    Brain.Screen.print("AWP");
    break;
    */
    case 1:
    Brain.Screen.clearLine();
    Brain.Screen.print("red-right");
    break;
    case 2:
    Brain.Screen.clearLine();
    Brain.Screen.print("Skills");
    break;
    case 3:
    Brain.Screen.clearLine();
    Brain.Screen.print("Normal-left");
    break;

  }
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  
  Brain.Screen.pressed(autonSelection);
  /*Controller1.Screen.print("hi");
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Brain.Screen.setPenColor(red);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0, 0, 240, 120);
  Brain.Screen.setCursor(3 , 9);
  Brain.Screen.setPenColor(green);
  Brain.Screen.print("Left");
  Brain.Screen.setPenColor(blue);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(240, 0, 240, 120);
  Brain.Screen.setCursor(3, 32);
  Brain.Screen.setPenColor(yellow);
  Brain.Screen.print("Right");
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0, 120, 480, 240);
  Brain.Screen.setCursor(10, 24);
  Brain.Screen.setPenColor(white);
  Brain.Screen.print("Skills");*/
  
}



void AWP(){
  
}

void Skills(){

  setVelo(50);
  drivereverse(415);
  //motorstop(500);
  turnleft(125);
  //motorstop(500);
  clampunlock();
  setVelo(20);
  drivereverse(250);
  clamplock();
  mintake.setVelocity(100, percent);
  intakeup(490);
  drivereverse(370);
  setVelo(100);
  mintake.setVelocity(100, percent);
  mfrontintake.setVelocity(100, percent);
  driveforward(175);
  turnleft(163);
  bothmoveforwardintakeup(500);
  setVelo(10);
  bothmoveforwardintakeup(300);
  bothintakeup(2575);
  setVelo(100);
  turnright(100);
  drivereverse(520);
  turnleft(300);
  driveforward(190);
  

  

  
  clampunlock();
  drivereverse(190);
  clamplock();
  drivereverse(300);
  mintake.setVelocity(100, percent);
  mfrontintake.setVelocity(100, percent);


  /*
  turnleft(110);
  intakeup(700);
  setVelo(50);
  bothmoveforwardintakeup(900);
  bothintakeup(1100);
  drivereverse(600);

  
  drivereverse(560);
  turnleft(300);
  bothmoveforwardintakeup(900);
  intakeup(700);
  drivereverse(300);
  turnright(1000);
  drivereverse(390);
  */

}  



void Normalleft(){

  setVelo(50);
  drivereverse(415);
  //motorstop(500);
  turnright(125);
  //motorstop(500);
  clampunlock();
  setVelo(20);
  drivereverse(250);
  clamplock();
  mintake.setVelocity(100, percent);
  intakeup(490);
  drivereverse(370);
  setVelo(100);
  mintake.setVelocity(100, percent);
  mfrontintake.setVelocity(100, percent);
  driveforward(175);
  turnright(163);
  bothmoveforwardintakeup(500);
  setVelo(10);
  bothmoveforwardintakeup(300);
  bothintakeup(2575);
  setVelo(100);
  turnleft(100);
  drivereverse(520);
  turnright(300);


}   



void redright(){

  setVelo(50);
  drivereverse(415);
  //motorstop(500);
  turnleft(125);
  //motorstop(500);
  clampunlock();
  setVelo(20);
  drivereverse(250);
  clamplock();
  mintake.setVelocity(100, percent);
  intakeup(490);
  drivereverse(370);
  setVelo(100);
  mintake.setVelocity(100, percent);
  mfrontintake.setVelocity(100, percent);
  driveforward(175);
  turnleft(163);
  bothmoveforwardintakeup(500);
  setVelo(10);
  bothmoveforwardintakeup(300);
  bothintakeup(2575);
  setVelo(100);
  turnright(100);
  drivereverse(520);
  turnleft(300);
  driveforward(190);




  /*
  clampunlock();
  drivereverse(190);
  clamplock();
  drivereverse(300);
  mintake.setVelocity(100, percent);
  mfrontintake.setVelocity(100, percent);
  
  turnleft(110);
  intakeup(700);
  setVelo(50);
  bothmoveforwardintakeup(900);
  bothintakeup(1100);
  drivereverse(600);

  
  drivereverse(560);
  turnleft(300);
  bothmoveforwardintakeup(900);
  intakeup(700);
  drivereverse(300);
  turnright(1000);
  drivereverse(390);
  */

}

void autonomous(void) {
  switch(autono){
    /*
    case 0:
    AWP();
    break;
    */
    case 1:
    redright();
    break;
    case 2:
    Skills();
    break;
    case 3:
    Normalleft();
    break;
  }

}

controller::button buttons[] = {Controller1.ButtonA, Controller1.ButtonB, Controller1.ButtonX, Controller1.ButtonY, Controller1.ButtonUp, Controller1.ButtonDown, Controller1.ButtonLeft, Controller1.ButtonRight, Controller1.ButtonL1, Controller1.ButtonL2, Controller1.ButtonR1, Controller1.ButtonR2};
controller::button* correctButton;

void usercontrol(void) {
  // User control code here, inside the loop
  //drivetrain

  srand(time(0));
  correctButton = &buttons[rand() % 12];


  while (1) {

    Controller1.Screen.print("Let's play a Game...");
    Controller1.Screen.newLine();
    // Controller1.Screen.print("You think you can cuss me out, well NUH UH");
    // Controller1.Screen.newLine();
    Controller1.Screen.print("Press a button, if your right, your program will run...");
    Controller1.Screen.newLine();
    Controller1.Screen.print("If it's wrong, your precious program won't run :)");
    Controller1.Screen.newLine();
    Controller1.Screen.print("Have fun...");
    if (correctButton->pressing()) {
      mFrontRight.spin(reverse, (Controller1.Axis2.position(pct)), pct);
      mMidRight.spin(reverse, (Controller1.Axis2.position(pct)), pct);
      mBackRight.spin(reverse, (Controller1.Axis2.position(pct)), pct);
      mMidLeft.spin(forward, (Controller1.Axis3.position(pct)), pct);
      mFrontLeft.spin(forward, (Controller1.Axis3.position(pct)), pct);
      mBackLeft.spin(forward, (Controller1.Axis3.position(pct)), pct);
  
    //intake system
      if (Controller1.ButtonL1.pressing()) {
        mfrontintake.spin(forward, 100, percent);
        mintake.spin(reverse, 100, percent);
      }
      else if (Controller1.ButtonL2.pressing()) {
        mfrontintake.spin(reverse, 100, percent);
        mintake.spin(forward, 100, percent);
      }
      else{
        mfrontintake.stop(hold);
        mintake.stop(hold);
      }
  
      if (Controller1.ButtonR1.pressing()) {
        mladybug.spin(forward, 100, percent);
      }
      else if (Controller1.ButtonR2.pressing()) {
        mladybug.spin(reverse, 100, percent);
      }
      else{
        mladybug.stop(hold);
      }
    
    
  
  
  
    //clamp
      Controller1.ButtonX.pressed(toggleClamp);
  
  
    //doinker
      Controller1.ButtonB.pressed(toggledoinker);
  
    }
    



    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec); 
  }
}