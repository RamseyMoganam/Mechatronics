#include <BOARD.h>


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/
#define BUMPER_TRIPPED 1
#define BUMPER_NOT_TRIPPED 0

#define BALLHOGGER_MAX_SPEED 100 
#define BALLHOGGER_Ball_MAX_SPEED 50 

void BallHogger_Init(void);


unsigned int Roach_BatteryVoltage(void);


char Ballhogger_LeftWheelMtrSpeed(char newSpeed);

char Ballhogger_RightWheelMtrSpeed(char newSpeed);

char Ballhogger_BallMtrSpeed(char newSpeed);

char Ballhogger_PinionMtrSpeed(char newSpeed);

unsigned int Ballhogger_TapeSensor(void);

unsigned int Ballhogger_TrackWireSensor(void);

unsigned int Ballhogger_UltraSonicSensor(void);

unsigned char Ballhogger_ReadBumpers(void);