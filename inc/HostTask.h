/*
 * HostTask.h
 *
 *  Created on: Jan 30, 2021
 *      Author: 1000086162
 */

#ifndef INC_HOSTTASK_H_
#define INC_HOSTTASK_H_

#define MAX_COMMANDS 1 << 3
#define APP_STATE_BUSY 1
#define APP_IMMONLY 2

#define APP_INIT_BITS APP_STATE_BUSY | APP_IMMONLY
#define TOTAL_TASKS_IN_Q 5

// Define Global Variables
typedef union
{
    UINT16 words[7];
    struct
    {
        UINT8     opCode;    // host command Opcode
        UINT8     checksum;
        UINT16    appOpCode;  // execute Apps OpCode;
        UINT16    xferCount;
        UINT16    param1;
        UINT16    param2;
        UINT16    param3;
        UINT16    param4;
    } field;
} tCDB;

typedef struct
{
	UINT8  opCode;
	union
	{
		UINT16 words[4];
		struct
		{
			UINT16 param1;
			UINT16 param2;
			UINT16 param3;
			UINT16 rc;
		}fields;
	};
}tCommandQ;

//
//
//
typedef struct
{
    void    (*pFunc) (void);                    // s4w commands table.
    union
    {
        UINT32 word;
        struct
        {
            UINT32 busy    :1;    // 1=OK with another imm cmd
            UINT32 immOnly :1;   // 1=cmd must exec imm
            UINT32 reserved:30;
        } bits;
    } cmdOpts;
} tHostCommandTable;

// Extern functions
extern tHostCommandTable HostCommandTable[MAX_COMMANDS];
extern void HostTask(void *params);

#endif /* INC_HOSTTASK_H_ */
