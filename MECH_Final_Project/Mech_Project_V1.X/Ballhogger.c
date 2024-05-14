// This is the file where all of our functions for our Bot "BallHogger" is stored
#include <Ballhogger.h>
#include <BOARD.h>
#include <xc.h>


#include <pwm.h>
#include <serial.h>
#include <AD.h>



/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
// Pin defines for the loaction of these devices on the Pic32
// for more info look at roach.c

// Bumper sensors
#define HALL_FRONT_LEFT 
#define HALL_FRONT_RIGHT 
#define HALL_REAR_RIGHT 
#define HALL_REAR_LEFT 

#define HALL_FRONT_LEFT_TRIS 
#define HALL_FRONT_RIGHT_TRIS 
#define HALL_REAR_RIGHT_TRIS 
#define HALL_REAR_LEFT_TRIS 

// Motors
#define PINION_DIR
#define PN_DIR_INV
#define BALL_DIR
#define BALL_DIR_INV
#define LEFT_DIR 
#define LEFT_DIR_INV 
#define RIGHT_DIR 
#define RIGHT_DIR_INV 

#define PINION_DIR_TRIS 
#define PINION_DIR_INV_TRIS 
#define BALL_DIR_TRIS 
#define BALL_DIR_INV_TRIS 
#define LEFT_DIR_TRIS 
#define LEFT_DIR_INV_TRIS 
#define RIGHT_DIR_TRIS 
#define RIGHT_DIR_INV_TRIS 

#define PINION_PWM 
#define BALL_PWM 
#define LEFT_PWM 
#define RIGHT_PWM 

#define TAPE_SENSOR BALLHOGGER_TAPE_SENSOR
#define TRACK_WIRE_SENSOR 
#define ULTRASONIC_SENSOR
#define BallHogger_BAT_VOLTAGE BAT_VOLTAGE


/**
 * @Function Roach_Init(void)
 * @param None.
 * @return None.
 * @brief  Performs all the initialization necessary for the roach. this includes initializing 
 * the PWM module, the A/D converter, the data directions on some pins, and 
 * setting the initial motor directions.
 * @note  None.
 * @author Max Dunne, 2012.01.06 */
void BallHogger_Init(void)
{

    //set the control pins for the motors
    PWM_Init();
    PWM_SetFrequency(1000);
    PWM_AddPins(LEFT_PWM | RIGHT_PWM | BALL_PWM | PINION_PWM);

    PINION_DIR_TRIS = 0;
    PINION_DIR_INV_TRIS = 0;
    BALL_DIR_TRIS = 0;
    BALL_DIR_INV_TRIS = 0;
    PINION_DIR = 0;
    PINION_DIR_INV = ~PINION_DIR;
    BALL_DIR = 0;
    BALL_DIR_INV = ~BALL_DIR;
    
    LEFT_DIR_TRIS = 0;
    LEFT_DIR_INV_TRIS = 0;
    RIGHT_DIR_TRIS = 0;
    RIGHT_DIR_INV_TRIS = 0;
    LEFT_DIR = 0;
    LEFT_DIR_INV = ~LEFT_DIR;
    RIGHT_DIR = 0;
    RIGHT_DIR_INV = ~RIGHT_DIR;

    //set up the hall effect sensors
    HALL_FRONT_LEFT_TRIS = 1;
    HALL_FRONT_RIGHT_TRIS = 1;
    HALL_REAR_RIGHT_TRIS = 1;
    HALL_REAR_LEFT_TRIS = 1;


    //Initialize the sensors
    AD_Init();
    AD_AddPins(TAPE_SENSOR);
    AD_addPins()

    //enable interrupts
}

/**
 * @Function Ballhogger_LeftMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Max Dunne, 2012.01.06 */
char Ballhogger_LeftWheelMtrSpeed(char newSpeed)
{
    if ((newSpeed < -BALLHOGGER_MAX_SPEED) || (newSpeed > BALLHOGGER_MAX_SPEED)) {
        return (ERROR);
    }
    newSpeed = -newSpeed;
  
    if (newSpeed < 0) {
        LEFT_DIR = 0;
        newSpeed = newSpeed * (-1); // set speed to a positive value
    } else {
        LEFT_DIR = 1;
    }
    LEFT_DIR_INV = ~(LEFT_DIR);
    if (PWM_SetDutyCycle(LEFT_PWM, newSpeed * (MAX_PWM / BALLHOGGER_MAX_SPEED)) == ERROR) {
        //printf("ERROR: setting channel 1 speed!\n");
        return (ERROR);
    }
    return (SUCCESS);
}

/**
 * @Function Ballhogger_RightMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Max Dunne, 2012.01.06 */
char Ballhogger_RightWheelMtrSpeed(char newSpeed)
{
    if ((newSpeed < -BALLHOGGER_MAX_SPEED) || (newSpeed > BALLHOGGER_MAX_SPEED)) {
        return (ERROR);
    }
    if (newSpeed < 0) {
        RIGHT_DIR = 0;
        newSpeed = newSpeed * (-1); // set speed to a positive value
    } else {
        RIGHT_DIR = 1;
    }
    RIGHT_DIR_INV = ~(RIGHT_DIR);
    if (PWM_SetDutyCycle(RIGHT_PWM, newSpeed * (MAX_PWM / BALLHOGGER_MAX_SPEED)) == ERROR) {
        //puts("\aERROR: setting channel 1 speed!\n");
        return (ERROR);
    }
    return (SUCCESS);
}

/**
 * @Function Ballhogger_BallMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Max Dunne, 2012.01.06 */
char Ballhogger_BallMtrSpeed(char newSpeed)
{
    if ((newSpeed < -BALLHOGGER_MAX_SPEED) || (newSpeed > BALLHOGGER_MAX_SPEED)) {
        return (ERROR);
    }
    if (newSpeed < 0) {
        BALL_DIR = 0;
        newSpeed = newSpeed * (-1); // set speed to a positive value
    } else {
        BALL_DIR = 1;
    }
    BALL_DIR_INV = ~(BALL_DIR);
    if (PWM_SetDutyCycle(BALL_PWM, newSpeed * (MAX_PWM / BALLHOGGER_MAX_SPEED)) == ERROR) {
        //puts("\aERROR: setting channel 1 speed!\n");
        return (ERROR);
    }
    return (SUCCESS);
}

/**
 * @Function Ballhogger_PinionMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Max Dunne, 2012.01.06 */
char Ballhogger_PinionMtrSpeed(char newSpeed)
{
    if ((newSpeed < -BALLHOGGER_MAX_SPEED) || (newSpeed > BALLHOGGER_MAX_SPEED)) {
        return (ERROR);
    }
    if (newSpeed < 0) {
        PINION_DIR = 0;
        newSpeed = newSpeed * (-1); // set speed to a positive value
    } else {
        PINION_DIR = 1;
    }
    PINION_DIR_INV = ~(PINION_DIR);
    if (PWM_SetDutyCycle(PINION_PWM, newSpeed * (MAX_PWM / BALLHOGGER_MAX_SPEED)) == ERROR) {
        //puts("\aERROR: setting channel 1 speed!\n");
        return (ERROR);
    }
    return (SUCCESS);
}

/**
 * @Function Ballhogger_TapeSensor(void)
 * @param None.
 * @return a 10-bit value corresponding to the amount of light received.
 * @brief  Returns the current light level. A higher value means less light is detected.
 * @author Max, 2012.01.06 */
unsigned int Ballhogger_TapeSensor(void)
{
    return AD_ReadADPin(TAPE_SENSOR);
}

/**
 * @Function Ballhogger_TrackWireSensor(void)
 * @param None.
 * @return a 10-bit value corresponding to the amount of light received.
 * @brief  Returns the current light level. A higher value means less light is detected.
 * @author Max Dunne, 2012.01.06 */
unsigned int Ballhogger_TrackWireSensor(void)
{
    return AD_ReadADPin(TRACK_WIRE_SENSOR);
}

/**
 * @Function Ballhogger_UltraSonicSensor(void)
 * @param None.
 * @return a 10-bit value corresponding to the amount of light received.
 * @brief  Returns the current light level. A higher value means less light is detected.
 * @author Max Dunne, 2012.01.06 */
unsigned int Ballhogger_UltraSonicSensor(void)
{
    return AD_ReadADPin(ULTRASONIC_SENSOR);
}

/**
 * @Function Ballhogger_ReadBumpers(void)
 * @param None.
 * @return 4-bit value representing all four bumpers in following order: front left,front right, rear left, rear right
 * @brief  Returns the state of all 4 bumpers
 * @author Max Dunne, 2012.01.06 */
unsigned char Ballhogger_ReadBumpers(void)
{
    //unsigned char bump_state;
    //bump_state = (!HALL_FRONT_LEFT + ((!HALL_FRONT_RIGHT) << 1)+((!HALL_REAR_LEFT) << 2)+((!HALL_REAR_RIGHT) << 3));
    return (!HALL_FRONT_LEFT + ((!HALL_FRONT_RIGHT) << 1)+((!HALL_REAR_LEFT) << 2)+((!HALL_REAR_RIGHT) << 3));
}




/**
 * @Function Roach_ReadBumpers(void)
 * @param None.
 * @return 4-bit value representing all four bumpers in following order: front left,front right, rear left, rear right
 * @brief  Returns the state of all 4 bumpers
 * @author Max Dunne, 2012.01.06 */
unsigned char Ballhogger_ReadBumpers(void)
{
    //unsigned char bump_state;
    //bump_state = (!HALL_FRONT_LEFT + ((!HALL_FRONT_RIGHT) << 1)+((!HALL_REAR_LEFT) << 2)+((!HALL_REAR_RIGHT) << 3));
    return (!HALL_FRONT_LEFT + ((!HALL_FRONT_RIGHT) << 1)+((!HALL_REAR_LEFT) << 2)+((!HALL_REAR_RIGHT) << 3));
}