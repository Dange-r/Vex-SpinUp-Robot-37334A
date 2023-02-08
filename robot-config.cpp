#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RightDriveMotorA = motor(PORT1, ratio18_1, false);
motor RightDriveMotorB = motor(PORT2, ratio18_1, false);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB);
motor RightMotor3 = motor(PORT4, ratio18_1, true);
motor LeftDriveMotorA = motor(PORT9, ratio18_1, true);
motor LeftDriveMotorB = motor(PORT10, ratio18_1, true);
motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB);
motor LeftMotor3 = motor(PORT6, ratio18_1, false);
motor Intake = motor(PORT3, ratio18_1, false);
motor Shooter = motor(PORT5, ratio18_1, false);
digital_out stringRight = digital_out(Brain.ThreeWirePort.A);
digital_out stringLeft = digital_out(Brain.ThreeWirePort.B);
digital_out middleString = digital_out(Brain.ThreeWirePort.C);
digital_out IntakeStopper = digital_out(Brain.ThreeWirePort.D);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
