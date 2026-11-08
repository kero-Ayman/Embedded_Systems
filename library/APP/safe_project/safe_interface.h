/*
 * safe_interface.h
 *
 *  Created on: Nov 7, 2026
 *      Author: Kirolos
 */

#ifndef APP_SAFE_PROJECT_SAFE_INTERFACE_H_
#define APP_SAFE_PROJECT_SAFE_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

/* ---------------- Configuration ---------------- */
#define PASS_LENGTH					4		/* number of digits in the password*/
#define WRONG_INPUT					3		/* max wrong attempts before lockout*/
#define LOCKOUT_SECONDS				30		/* lockout time after too many wrong attempts */
#define LOCK_KEY					'c'		/* key that closes the safe again*/

/* ---------------- Return values ---------------- */
#define CORRECT_PASS				0
#define WRONG_PASS					1

/* ---------------- EEPROM map ---------------- */
#define MEM_CELL					0							/* password digits: cells 0..PASS_LENGTH-1 */
#define MEM_CELL_FLAG				(MEM_CELL + PASS_LENGTH)	/* "password is valid" flag, written LAST   */
#define MEM_CELL_TRIES				(MEM_CELL_FLAG + 1)			/* wrong-attempt counter (survives reset)   */

#define PASS_IS_SET					0xAA

/* ---------------- Public API ---------------- */
void safe_System_start(void);		/* call this inside while(1) in main */
void safe_NewPassword(void);
void safe_EnterPassword(void);

#endif /* APP_SAFE_PROJECT_SAFE_INTERFACE_H_ */
