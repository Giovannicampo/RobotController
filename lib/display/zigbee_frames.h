typedef struct {
    short x;
    short y;
    short deg100;
    unsigned char flags;
    unsigned char bumpers;
}  __attribute__((packed)) t_can_robot_position;

typedef struct {
    short battery_percentage;
} __attribute__((packed)) t_can_robot_battery;

// -------------- STRATEGY_COMMAND -----------------------------------
#define STRATEGY_COMMAND_CAN_ID			    0xABC
#define STRATEGY_COMMAND_ALIGN_GRANDE1		0x01
#define STRATEGY_COMMAND_ALIGN_GRANDE2		0x02
#define STRATEGY_COMMAND_ALIGN_PICCOLO		0x03
#define STRATEGY_COMMAND_ENABLE_STARTER		0x04
#define STRATEGY_COMMAND_DISABLE_STARTER	0x05
#define STRATEGY_COMMAND_START_PICCOLO		0x06
#define STRATEGY_COMMAND_START_GRANDE		0x07
#define STRATEGY_FLAG_COLOR			0x01 /* 0 = ORANGE, 1 = GREEN */
#define STRATEGY_FLAG_STGY          0x03 /* 0 = ALPHA, 1 = BETA, 2 = GAMMA, 3 = DELTA*/
#define STRATEGY_FLAG_ALIGN         0x07 /* da 1 a 5 zone*/

typedef struct
{
	unsigned char cmd;
	unsigned char flags;
	unsigned int elapsed_time;
    unsigned char stgy;
    unsigned char align;
	char padding[2];
}  __attribute__((packed)) t_can_strategy_command;

#define SCORE_CAN_ID			0x730

typedef struct
{
    unsigned char cmd;
    uint16_t score;
    unsigned char flags;
    // b0 = game end
    // b1 = robot in home
    unsigned char yellow_is_taken;
    unsigned char pink_is_taken;
    unsigned char brown_is_taken;
    unsigned char is_released;
}  __attribute__((packed)) t_can_score_data;

#define FLAGS_GAME_END_MASK   0x01
#define FLAGS_ROBOT_IN_HOME   0x02

