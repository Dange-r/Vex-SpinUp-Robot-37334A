using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group RightDrive;
extern motor RightMotor3;
extern motor_group LeftDrive;
extern motor LeftMotor3;
extern motor Intake;
extern motor Shooter;
extern digital_out stringRight;
extern digital_out stringLeft;
extern digital_out middleString;
extern digital_out IntakeStopper;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
