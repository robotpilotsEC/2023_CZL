#include "can_protocol.h"

int16_t can1_send_buf[8], can2_send_buf[8];

void CAN_SendAll(void)
{
	static uint16_t i = 0;
	
	if (++i == 60000)
	{
		i = 0;
	}
	
	if (rc_sensor.work_state == DEV_OFFLINE)
	{
		memset(can1_send_buf, 0, 16);
		memset(can2_send_buf, 0, 16);
	}
	
	CAN2_Send_With_int16_to_uint8(RM_motor[FRIC_L].id.tx_id, can2_send_buf);
	if (i % 2 == 0)
	CAN1_Send_With_int16_to_uint8(RM_motor[GIM_P].id.tx_id, can1_send_buf);
	
	memset(can1_send_buf, 0, 16);
	memset(can2_send_buf, 0, 16);
}	

void CAN2_rxDataHandler(uint32_t canId, uint8_t *rxBuf)
{
	switch(canId)
	{
		case 0x201:
			RM_motor[FRIC_R].rx(&RM_motor[FRIC_R],rxBuf);
			break;
		case 0x202:
			RM_motor[FRIC_L].rx(&RM_motor[FRIC_L],rxBuf);
			break;
		case 0x203:
			RM_motor[DIAL].rx(&RM_motor[DIAL],rxBuf);
			break;
		default:
			break;
	}

}
void CAN1_rxDataHandler(uint32_t canId, uint8_t *rxBuf)
{
	switch(canId)
	{
		case 0x205:
			RM_motor[GIM_P].rx(&RM_motor[GIM_P],rxBuf);
			break;
		case 0x206:
			RM_motor[GIM_Y].rx(&RM_motor[GIM_Y],rxBuf);
			break;
		default:
			break;
	}

}
