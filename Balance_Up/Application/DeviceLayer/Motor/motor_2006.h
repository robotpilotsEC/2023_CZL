#ifndef __MOTOR_2006_H
#define __MOTOR_2006_H

#include "rp_config.h"
#include "can_protocol.h"
#include "pid.h"
#include "driver.h"

typedef struct __motor_2006_info_t
{
	  volatile uint16_t ecd;
    volatile int16_t  speed_rpm;
    volatile int16_t  given_current;
	  volatile uint8_t  temperature;
    volatile int16_t  last_ecd;
    volatile int16_t  delta_ecd;
    volatile int32_t  total_ecd;
		volatile float    angle;
  	volatile float    total_angle;
	  volatile uint8_t  offline_cnt;
	  const    uint8_t	offline_max_cnt;
} motor_2006_info_t;

typedef struct __motor_2006_t
{
	  motor_2006_info_t  *info;
	  drv_can_t          *driver;
		pid_t              *pid;
	  void					 (*init)(struct __motor_2006_t *motor);
		void           (*update)(struct __motor_2006_t *motor, uint8_t* data);
	  void           (*check)(struct __motor_2006_t *motor);	
	  void					 (*heart_beat)(struct __motor_2006_t *motor);
	  volatile dev_work_state_t   work_state;
	  volatile dev_errno_t        errno;
	  const    dev_id_t		      	id;
	
} motor_2006_t;

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern motor_2006_t dial_motor;

#endif
