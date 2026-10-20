/*
 * 7_seg_interface.h
 *
 *  Created on: Oct 18, 2026
 *      Author: Kirolos
 */

#ifndef HAL_7_SEG_7_SEG_INTERFACE_H_
#define HAL_7_SEG_7_SEG_INTERFACE_H_

extern u8  s_seg_port;

void s_seg_init(u8 Copy_u8PortId);
void s_seg_print_num(u8 num);

#endif /* HAL_7_SEG_7_SEG_INTERFACE_H_ */
