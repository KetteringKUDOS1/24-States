#include "main.h"
#include "autons.hpp"
#include "intake.hpp"
#include "cata.hpp"
#include "flywheel.hpp"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}




///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(80, 127, true);
  chassis.wait_drive();

 pros::delay(45000);

  chassis.set_swing_pid(ez::RIGHT_SWING, -60, SWING_SPEED);
  chassis.wait_drive();

  wings.set_value(false);


  pros::delay(500);

  chassis.set_drive_pid(20, 137, true);
  chassis.wait_drive();

chassis.set_swing_pid(ez::LEFT_SWING, -90, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127, true);
  chassis.wait_drive();


  chassis.set_drive_pid(-10, 127, true);
  chassis.wait_drive();

chassis.set_drive_pid(10, 127, true);
  chassis.wait_drive();


  chassis.set_drive_pid(-10, 127, true);
  chassis.wait_drive();

  chassis.set_drive_pid(10, 127, true);
  chassis.wait_drive();
  chassis.set_drive_pid(-10, 127, true);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

void over_under_skills(){
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}


// . . .
// Make your own autonomous functions here!
// . . .

void awp(){

  intake.set_value(true);
  chassis.set_drive_pid(-70, 127, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-20, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();

  intakein(600);

  chassis.set_drive_pid(15, DRIVE_SPEED, true);
  chassis.wait_drive();

  pros::delay(250);

  chassis.set_drive_pid(-60,50,true);
  chassis.wait_drive();

  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();

  intake.set_value(false);

  intakeout(600);

  chassis.set_drive_pid(10,50,true);
  chassis.wait_drive();

  chassis.set_drive_pid(-10,50,true);
  chassis.wait_drive();
  
  chassis.set_turn_pid(0, 60);
  chassis.wait_drive();

  chassis.set_drive_pid(-40,127,true);
  chassis.wait_drive();

  intake.set_value(true);

  chassis.set_drive_pid(10,50,true);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, 60);
  chassis.wait_drive();

  intakestop();

  chassis.set_drive_pid(50,60,true);
  chassis.wait_drive();

}

void awp2(){
  intake.set_value(true);
  intakein(600);
  pros::delay(700);
  intakestop();
  chassis.set_drive_pid(-5, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(93, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(12, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(120, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(9, DRIVE_SPEED, true);
  chassis.wait_drive();
  intakeout(600);
  pros::delay(1000);
  intakestop();
  intake.set_value(false);
  pros::delay(1000);
  chassis.set_turn_pid(-60, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-10, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-50, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-4, DRIVE_SPEED+25);
  chassis.wait_drive();
  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-4, DRIVE_SPEED+25);
  chassis.wait_drive();
  chassis.set_drive_pid(8, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(28, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-130, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_drive_pid(10, 20, true);
  chassis.wait_drive();
}


void skills(){
  start_wheel();
  intake.set_value(true);
  intakein(600);

  for(int i=0; i<2; i++){
    
    intake.set_value(true);
    pros::delay(600);
    intake.set_value(false);
    pros::delay(600);
    master.rumble("-  .  -");

  }
  intakestop();
  stop_wheel();
  chassis.set_drive_pid(-24, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-45, TURN_SPEED);
    chassis.wait_drive();
    chassis.set_drive_pid(-15, DRIVE_SPEED);
  chassis.wait_drive();

  for(int i=0; i<10; i++){
    
    chassis.set_drive_pid(-15, DRIVE_SPEED);
    chassis.wait_drive();
    chassis.set_drive_pid(14, DRIVE_SPEED);
    chassis.wait_drive();
    chassis.set_drive_pid(-15, DRIVE_SPEED);
    chassis.wait_drive();
    chassis.set_drive_pid(14, DRIVE_SPEED);
    chassis.wait_drive();
    chassis.set_turn_pid(45, TURN_SPEED);
    chassis.wait_drive();
    chassis.set_drive_pid(-10, DRIVE_SPEED);
    chassis.wait_drive();
    chassis.set_turn_pid(-45, TURN_SPEED);
    chassis.wait_drive();
  }


}

