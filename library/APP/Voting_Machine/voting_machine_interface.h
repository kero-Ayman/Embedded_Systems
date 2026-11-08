/*
 * voting_machine_interface.h
 *
 *  Created on: Nov 6, 2026
 *      Author: Kirolos
 */

#ifndef APP_VOTING_MACHINE_VOTING_MACHINE_INTERFACE_H_
#define APP_VOTING_MACHINE_VOTING_MACHINE_INTERFACE_H_

#define FIRST_CELL			0
#define SECOND_CELL			1
#define THIRD_CELL			2
#define FOURTH_CELL			3

void 	voting_machine_printvotes(u8 a,u8 b, u8 c,u8 d);

u8  	voting_machine_savevotes(u8 a,u8 b, u8 c,u8 d);

u8  	voting_machine_loadvotes(u8 *a,u8* b, u8* c,u8* d);

void Start_System(u8* a,u8* b, u8* c,u8* d);



#endif /* APP_VOTING_MACHINE_VOTING_MACHINE_INTERFACE_H_ */
