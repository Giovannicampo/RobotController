/*
 * bus_objects.h
 */

#ifndef __BUS_OBJECTS
#define __BUS_OBJECTS

// -------------- ROBOT POSITION ---------------------
#define ROBOT_POSITION_CAN_ID        0x3E3
#define OTHER_ROBOT_POSITION_CAN_ID  0x3E5

typedef struct {
    short x;
    short y;
    short deg100;
    unsigned char flags;
    unsigned char bumpers;
}  __attribute__((packed)) t_can_robot_position;


// UNUSED
// typedef struct {
//     float L;
//     float R;
// }  __attribute__((packed)) t_can_robot_motion;

// -------------- ROBOT VELOCITY ---------------------
#define ROBOT_VELOCITY_CAN_ID   0x3E4

typedef struct {
    short linear_speed;
    char padding[6];
}  __attribute__((packed)) t_can_robot_velocity;

// -------------- ROBOT WHEELS VELOCITY ---------------------
#define ROBOT_WHEELS_VELOCITY_CAN_ID   0x3E7

typedef struct {
    short wheel;
    short current_speed;
    short target_speed;
    short pwm;
}  __attribute__((packed)) t_can_robot_wheels_velocity;

// -------------- BATTERY PERCENTAGE --------------
#define ROBOT_BATTERY_PERCENTAGE_CAN_ID 0x3E8
#define OTHER_ROBOT_BATTERY_PERCENTAGE_CAN_ID 0x3E9

typedef struct {
    short battery_percentage;
} __attribute__((packed)) t_can_robot_battery;

// -------------- OBSTACLE_AVOIDANCE ---------------------
#define OBSTACLE_AVOIDANCE_CAN_ID   0x3D0

#define CAN_OBSTACLE_AVOIDANCE_MSG_OBSTACLEDETECTED	1
#define CAN_OBSTACLE_AVOIDANCE_MSG_OBSTACLEPROCESSED	2
#define CAN_OBSTACLE_AVOIDANCE_MSG_RESET		3
#define CAN_OBSTACLE_AVOIDANCE_MSG_ENABLE		4
#define CAN_OBSTACLE_AVOIDANCE_MSG_DISABLE		5
#define CAN_OBSTACLE_AVOIDANCE_MSG_ACKOBSTACLEPROCESSED	6
#define CAN_OBSTACLE_AVOIDANCE_MSG_SET_NEARONLY_FLAG	7
#define CAN_OBSTACLE_AVOIDANCE_MSG_CLR_NEARONLY_FLAG	8

typedef struct {
    unsigned char msg_type;
    short obstacle_direction; // [-180, 180], 0 = front
    char padding[5];
}  __attribute__((packed)) t_can_obstacle_avoidance;

// -------------- OBSTACLE_AVOIDANCE_QUERY ---------------------
#define OBSTACLE_AVOIDANCE_QUERY_CAN_ID   0x7E5

#define CAN_OBSTACLE_AVOIDANCE_QUERY_MSG_REQUEST	0
#define CAN_OBSTACLE_AVOIDANCE_QUERY_MSG_OBSTFOUND	1
#define CAN_OBSTACLE_AVOIDANCE_QUERY_MSG_OBSTNOTFOUND	2

typedef struct {
    unsigned char msg_type;
    short obstacle_direction; // [-180, 180], 0 = front
    char padding[5];
}  __attribute__((packed)) t_can_obstacle_avoidance_query;


// -------------- COLOR_SENSORS ---------------------

#define COLOR_SENSOR_CAN_COMMAND_ID             0x6ff

typedef struct {
    unsigned char sensor;
    unsigned char command;
    unsigned char parameter;
    char padding[5];
}  __attribute__((packed)) t_can_color_sensor_command;

#define COLOR_SENSOR_COMMAND_SAMPLE             0x01
//Added by Alessando
#define COLOR_SENSOR_COMMAND_START_PERIODIC_SAMPLING            0x02
#define COLOR_SENSOR_COMMAND_STOP_PERIODIC_SAMPLING             0x03
#define COLOR_SENSOR_COMMAND_CALIBRATE                          0x10
//

#define COLOR_FORMAT_RGB        0x01
#define COLOR_FORMAT_HSV        0x02

#define COLOR_SENSOR_CAN_DATA_ID                0x6fe

typedef struct {
    unsigned char sensor;
    unsigned short red;
    unsigned short green;
    unsigned short blue;
    unsigned char format;
}  __attribute__((packed)) t_can_color_sensor_data;



// -------------- DISTANCE_SENSORS ---------------------

#define DISTANCE_SENSOR_CAN_COMMAND_ID             0x67f

typedef struct {
    unsigned char sensor;
    unsigned char command;
    unsigned short front_sensor_bitmap;
    unsigned short rear_sensor_bitmap;
    unsigned char threshold_cm;
    unsigned char threshold_count;
}  __attribute__((packed)) t_can_distance_sensor_command;

#define DISTANCE_SENSOR_COMMAND_SAMPLE                         0x01
#define DISTANCE_SENSOR_COMMAND_START_PERIODIC_SAMPLING        0x02
#define DISTANCE_SENSOR_COMMAND_STOP_PERIODIC_SAMPLING         0x03

#define DISTANCE_SENSOR_CAN_DATA_ID                0x67e
#define NEAR_OBJECT_CAN_DATA_ID                    0x67d

typedef struct {
    unsigned char sensor;
    unsigned short distance;
    char padding[5];
}  __attribute__((packed)) t_can_distance_sensor_data;


// -------------- OBSTACLE_MAP ---------------------

#define OBSTACLE_MAP_CAN_COMMAND_ID             0x70f

typedef struct {
    unsigned char obstacle_number;
    unsigned char valid;
    short angle_start;
    short angle_end;
    short distance;
}  __attribute__((packed)) t_can_obstacle_map;


// -------------- STRATEGY_COMMAND -----------------------------------
#define STRATEGY_COMMAND_CAN_ID			0x710
#define STRATEGY_COMMAND_ALIGN_GRANDE1		0x01
#define STRATEGY_COMMAND_ALIGN_GRANDE2		0x02
#define STRATEGY_COMMAND_ALIGN_PICCOLO		0x03
#define STRATEGY_COMMAND_ENABLE_STARTER		0x04
#define STRATEGY_COMMAND_DISABLE_STARTER	0x05
#define STRATEGY_COMMAND_START_PICCOLO		0x06
#define STRATEGY_COMMAND_START_GRANDE		0x07
#define STRATEGY_FLAG_COLOR			0x01 /* 0 = ORANGE, 1 = GREEN */
#define STRATEGY_FLAG_STGY          0x03 /* 0 = ALPHA, 1 = BETA, 2 = GAMMA, 3 = DELTA*/

typedef struct
{
	unsigned char cmd;
	unsigned char flags;
	unsigned int elapsed_time;
	char padding[4]; // da aggiungere strategy e config align
}  __attribute__((packed)) t_can_strategy_command;

// -------------- SCORE_COMMAND -----------------------------------
#define SCORE_CAN_ID			0x730

typedef struct
{
    unsigned char cmd;
    uint32_t score;
    unsigned char statuette_placed;
    unsigned char experiment;
    char padding;
}  __attribute__((packed)) t_can_score_data;

// -------------- ROBOT STATUS UPDATE ---------------------
#define ROBOT_STATUS_UPDATE_CAN_ID        0x402

typedef enum
{
	CAN_ROBOT_STATUS_UPDATE_ROBOT_GRANDE,
	CAN_ROBOT_STATUS_UPDATE_ROBOT_PICCOLO
} t_can_robot_status_update_robot;

typedef enum
{
	CAN_ROBOT_STATUS_UPDATE_STATUS_NO_INFO,
	CAN_ROBOT_STATUS_UPDATE_STATUS_IDLE,
	CAN_ROBOT_STATUS_UPDATE_STATUS_ALIGNING,
	CAN_ROBOT_STATUS_UPDATE_STATUS_WAIT_STARTER_IN,
	CAN_ROBOT_STATUS_UPDATE_STATUS_WAIT_STARTER_OUT,
	CAN_ROBOT_STATUS_UPDATE_STATUS_RUNNING
} t_can_robot_status_update_status;

typedef struct {
	int robot_selected;
	int status_display;
	char padding[4];
}  __attribute__((packed)) t_can_robot_status_update;

// -------------- MOTION_COMMAND -----------------------------------
#define MOTION_COMMAND_CAN_ID			0x7F0

typedef struct
{
    unsigned char cmd;
    int16_t param1;
    int16_t param2;
    int16_t param3;
    char flags;
}  __attribute__((packed)) t_motion_command;

#define MC_STOP                         0x82
#define MC_BRAKE                        0x83
#define MC_SET_POSTION                  0x84
#define MC_FORWARD_TO_DISTANCE          0x85
#define MC_ROTATE_RELATIVE              0x88
#define MC_CRUISE_SPEED                 0x8C

// -------------- ALIVE_COMMAND -----------------------------------
#define SERVO_CAN_ID			0x72F

#define RCSERVO_TYPE    1
#define AX12SERVO_TYPE  2

typedef struct
{
    uint8_t number;
    uint8_t type;
    uint16_t position;
    char padding[5];
}  __attribute__((packed)) t_servo_command;

// -------------- ALIVE_COMMAND -----------------------------------
#define ROBOT_ALIVE_CAN_ID			0x7FE

typedef struct
{
    uint32_t counter1;
    uint32_t counter2;
}  __attribute__((packed)) t_alive_command;

// --------------- SIMPLE_VAR_OUTPUT ----------------------
#define SIMPLE_VAR_OUTPUT_ID		0x200 // priorità alta, per non perdere troppo tempo nell'invio

// Ad eccezione del tipo speciale "FLUSH", i seguenti codici corrispondo a quelli
// del modulo python struct
#define SIMPLE_VAR_TYPE_FLUSH		'\0'
#define SIMPLE_VAR_TYPE_NULL		'x'
#define SIMPLE_VAR_TYPE_CHAR		'c'
#define SIMPLE_VAR_TYPE_INT8		'b'
#define SIMPLE_VAR_TYPE_UINT8		'B'
#define SIMPLE_VAR_TYPE_BOOL		'?'
#define SIMPLE_VAR_TYPE_INT16		'h'
#define SIMPLE_VAR_TYPE_UINT16		'H'
#define SIMPLE_VAR_TYPE_INT32		'i'
#define SIMPLE_VAR_TYPE_UINT32		'I'
#define SIMPLE_VAR_TYPE_FLOAT		'f'
#define SIMPLE_VAR_TYPE_STRING		'p'

typedef struct {
	char type, ctr;
	char data[6];
}  __attribute__((packed)) t_can_simple_var_packet;


// -------------- RESISTOR_MEASURE ---------------------

#define RESISTOR_MEASURE_COMMAND_CAN_COMMAND_ID             0x7fc
#define RESISTOR_MEASURE_VALUE_CAN_COMMAND_ID               0x7f8

typedef struct {
    unsigned char command;
    char padding[7];
}  __attribute__((packed)) t_can_resistor_command;

#define RESISTOR_MEASURE_COMMAND_SAMPLE_STOP               0x00
#define RESISTOR_MEASURE_COMMAND_SAMPLE_START              0x01

typedef struct {
    int16_t voltage;
    int16_t resistor;
    char padding[4];
}  __attribute__((packed)) t_can_resistor_value;

#endif
