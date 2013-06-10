/**
 *	I2C Bus Devices for the BitThunder device manager.
 *
 **/

#ifndef _BT_I2C_H_
#define _BT_I2C_H_

#include "bt_types.h"
#include <collections/bt_linked_list.h>

typedef struct _BT_I2C_BOARD_INFO {
	BT_i8 		   *name;			///< Device/driver matching name.
	BT_RESOURCE	   *pResources;		///< Pointer to fundamental resource table.
	BT_u32			ulResources;	///< Total resources.
	BT_u16			addr;			///< I2C bus address.
} BT_I2C_BOARD_INFO;

typedef struct _BT_I2C_CLIENT {
	BT_LIST_ITEM 	oItem;
	BT_HANDLE	 	hBus;
	BT_u32		 	flags;
	BT_u16		 	addr;
} BT_I2C_CLIENT;

typedef struct _BT_I2C_MESSAGE {
	BT_u16 	addr;
	BT_u16	flags;
    #define BT_I2C_M_TEN						0x0010				///< Use 10-bit addressing mode.
    #define BT_I2C_M_RD							0x0001				///< Flag a read request.
	#define BT_I2C_M_STOP						0x8000
	#define BT_I2C_M_NOSTART					0x4000
	#define BT_I2C_M_REV_DIR_ADDR				0x2000
	#define BT_I2C_M_IGNORE_NAK					0x1000
	#define BT_I2C_M_NO_RD_ACK					0x0800
	#define BT_I2C_M_RECV_LEN					0x0400
	BT_u8  *buf;
	BT_u16 	len;
} BT_I2C_MESSAGE;

BT_ERROR BT_I2C_RegisterBusWithID(BT_HANDLE hBus, BT_u32 ulBusID, BT_I2C_BOARD_INFO *pInfo, BT_u32 ulNum);
BT_ERROR BT_I2C_RegisterDevices(BT_u32 ulBusID, BT_I2C_BOARD_INFO *pInfo, BT_u32 ulNum);

#endif
