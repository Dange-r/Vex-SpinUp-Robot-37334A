/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightDrive           motor_group   1, 2            
// RightMotor3          motor         4               
// LeftDrive            motor_group   9, 10           
// LeftMotor3           motor         6               
// Intake               motor         3               
// Shooter              motor         5               
// stringRight          digital_out   A               
// stringLeft           digital_out   B               
// middleString         digital_out   C               
// IntakeStopper        digital_out   D               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>
#include <cmath>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

  
  LeftDrive.setVelocity(10,pct);
  RightDrive.setVelocity(10,pct);
  Intake.setVelocity(50, pct);
  Shooter.setVelocity(600, pct);
  
  // ------------------------Left Side Roller Auton------------------------------
  LeftDrive.spinFor(reverse, .15, turns, false);
  RightDrive.spinFor(reverse, .15, turns, true);
  wait(.5, sec);
  Intake.spinFor(forward, .25, turns, true);
  wait(0.6, sec);
  
  // -------------------------Right Side Roller Auton----------------------------
  // Driving backwards to line up with roller
  /*LeftDrive.spinFor(reverse, 1.4, turns, false);
  RightDrive.spinFor(reverse, 1.4, turns, true);
  wait(0.1, sec);

  // Turning to line up with roller
  LeftDrive.spinFor(forward, 0.55, turns, false);
  RightDrive.spinFor(reverse, 0.55, turns, true);
  wait(0.2, sec);

  // Backing up to the roller face
  LeftDrive.spinFor(reverse, 0.25, turns, false);
  RightDrive.spinFor(reverse, 0.25, turns, true);
  wait(0.3, sec);

  // Spinning the roller
  Roller.spinFor(forward, 0.25, turns, true);
  wait(0.4, sec); */
  


  Intake.stop(coast);
  LeftDrive.stop(coast);
  RightDrive.stop(coast);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void setLeftDriveExpo (vex::directionType type, int percentage)
  {
    if (percentage>=0)
    {
      percentage = 1.2*pow(1.043,percentage) - 1.2 + 0.2*percentage;
    }
    else
    {
      percentage = -percentage;
      percentage = 1.2*pow(1.043,percentage) - 1.2 + 0.2*percentage;
      percentage = -percentage;
    }
    percentage=percentage-(percentage*0.3);
    
    LeftDrive.spin(type, percentage, volt);
    LeftMotor3.spin(type, percentage, volt);
  }
  

  void setRightDriveExpo (vex::directionType type, int percentage)
  {
    if (percentage>=0)
    {
      percentage = 1.2*pow(1.043,percentage) - 1.2 + 0.2*percentage;
    }
    else
    {
      percentage = -percentage;
      percentage = 1.2*pow(1.043,percentage) - 1.2 + 0.2*percentage;
      percentage = -percentage;
    }
    percentage=percentage-(percentage*0.3);
    
    RightDrive.spin(type, percentage, volt);
    RightMotor3.spin(type, percentage, volt);
  }
  
  bool toggled = true;
  bool toggleLatch = false;

  int deadband = 5; //set deadband

void usercontrol(void) {
  // User control code here, inside the loop
  Intake.setVelocity(300, pct);
  Shooter.setVelocity(80, pct);

  while (1) {

    Brain.Screen.drawCircle(240, 120, 240); // Brain screen resolution is 480x240

  // --------------------------Drive Code------------------------

    // Get the velocity percentage of the left motor. (Axis3)
    int leftMotorSpeed = Controller1.Axis3.position();
    // Get the velocity percentage of the right motor. (Axis2)
    int rightMotorSpeed = Controller1.Axis2.position();

    // Exponential Drive Functions with a deadband
    if(abs(leftMotorSpeed) > deadband) setLeftDriveExpo(fwd, leftMotorSpeed);
    else setLeftDriveExpo(fwd, 0);

    if(abs(rightMotorSpeed) > deadband) setRightDriveExpo(fwd, rightMotorSpeed);
    else setRightDriveExpo(fwd, 0);

    // -----------------------Roller Code-------------------------

    // Spinning the intake and shooter on button presses
    if(Controller1.ButtonR1.pressing())
    {
      Intake.spin(forward);
    }
    else if(Controller1.ButtonR2.pressing())
    {
      Intake.spin(reverse);
    }
    else
    {
      Intake.stop();

    }
     
    // -------------------------Disc Shooter Control--------------------------     

    if(Controller1.ButtonA.pressing()) // Janky way of toggling the boolean
    {
      Controller1.Screen.newLine();
      if(!toggleLatch){ toggled = !toggled; toggleLatch = true; }
    }
    else toggleLatch = false;

    if(toggled == true)
    {
      Brain.Screen.setFillColor(green);
      Controller1.Screen.print("Shooter Voltage: 10    ");
      if(Controller1.ButtonL1.pressing())
      {
        Shooter.spin(forward, 10, volt);
        IntakeStopper.set(false);
      }
      else 
      {
        IntakeStopper.set(true);
        Shooter.stop(coast);
      }
    }
    else{
      Brain.Screen.setFillColor(red);
      Controller1.Screen.print("Shooter Voltage: 11    ");
      if(Controller1.ButtonL1.pressing())
      {
        Shooter.spin(forward, 11, volt);
        IntakeStopper.set(false);
      }
      else 
      {
        IntakeStopper.set(true);
        Shooter.stop(coast);
      }
    }

    // ------------------------------String Shooter Control----------------------------

    if(Controller1.ButtonL2.pressing() && Controller1.ButtonUp.pressing()) 
    {
      stringRight.set(true);
      stringLeft.set(true);
      middleString.set(true);
    }
    else if(Controller1.ButtonL2.pressing() && Controller1.ButtonLeft.pressing()) //Shoot just left
    {
      stringLeft.set(true);
    }
    else if(Controller1.ButtonL2.pressing() && Controller1.ButtonRight.pressing())//Shoot just right
    {
      stringRight.set(true);
    }
    else
    {
      stringRight.set(false);
      stringLeft.set(false);
      middleString.set(false);
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
