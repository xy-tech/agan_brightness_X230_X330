#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hidapi/hidapi.h"

#define VENDOR_ID	0x10C4
#define PRODUCT_ID	0x83CE
#define SERIAL		NULL
#define READ		4
#define WRITE		6
#define BUFFER_LENGTH	2
#define MULTIPLIER	16

//write to 0x06, followed by the value of brightness
//read from 0x04, followed by the actual value of brightness
//value to write is in multiples of 16
//value to read is just 0 to 15

//error handling of res in case there's any issues reading/writing
int err_handling(int err, unsigned char rw)
{
	if (err == -1) //hid api would return -1 to res if something is wrong
	{
		if (rw == READ) //if mode is READ
		{
			printf("Unable to read from adapter. Something is wrong?\n");
		}
		else //if mode is WRITE
		{
			printf("Unable to write to adapter. Something is wrong?\n");
		}
		return 1;
	}
	return 0;
}

int main (int argc, char *argv[])
{
	if (argc > 2)
	{
		printf("Too many arguments\n");
		return 1;
	}
	
	//initialise the HID device
	int res;
	hid_device *handle;
	
	res = hid_init();
	
	handle = hid_open(VENDOR_ID, PRODUCT_ID, SERIAL);
	
	//detecting if HID device exists
	if (handle == NULL) //nothing opened
	{
		printf("Unable to open device\n");
		return 1;
	}
	else
	{
		printf("Device open!\n");
	}
	
	//buf[0] is the register to set read/write and buf[1] is the value to write or value to store read
	//int buflen = 2;
	unsigned char buf[2];
	buf[0] = WRITE; //set initial mode to write

	if (argc == 1) //no argument, default to max brightness
	{	
		buf[1] = 240; //max brightness 15*16=240
		
		printf("\nBrightness adjustment script for agan X230 FHD/2K adapter boards\n");
		printf("\nOptions:\n");
		printf("\n		<int>\n");
		printf("\n		Brightness value in integer, from 0 to 15\n");
		printf("\n		Example:\n");
		printf("\n				sudo ./script 15 //brightness changed to 15 (highest brightness)\n");
		printf("\n				sudo ./script 0 //brightness changed to 0 (lowest brightness)\n");
		printf("\n				sudo ./script 5 //brightness changed to 5\n");
		printf("\n				sudo ./script //brightness defaults to 15 (max brightness)\n");
		printf("\n				sudo ./script -1 //brightness reduces by 1 level for any input <= -1\n");
		printf("\n				sudo ./script 16 //brightness increases by 1 level for any input >= 16\n");
	}
	
	else
	{
		int b_val = atoi(argv[1]); //store arg as brightness value
		
		//if input is any string or character (evaluated as 0)
		//if input is any number is below 1 or higher than 16
		//this is for incrementing or decrementing the brightness
		if (b_val < 1 || b_val > MULTIPLIER)
		{
			buf[0] = READ; //change buffer to read mode
			res = hid_get_feature_report(handle, buf, BUFFER_LENGTH); //read and store value in buf[1]
			
			//error handling
			if (err_handling(res, buf[0]) == 1)
			{
				return 1;
			}
			
			printf("Previous brightness = %i\n", buf[1]); //print current brightness from buf[1]
			
			//if brightness is minimum or maximum, do not adjust brightness
			if ((buf[1] == 0 && b_val < 1) || (buf[1] == 15 && b_val > MULTIPLIER))
			{
				printf("Not adjusting brightness\n");
				return 0;
			}
			
			//if brightness is lowered
			if (b_val < 1)
			{
				buf[1] = (buf[1] - 1) * MULTIPLIER; //decrement current buf[1] by 1 to write
			}
			
			else	
			{
				buf[1] = (buf[1] + 1) * MULTIPLIER; //increment current buf[1] by 1 to write
			}
			
			printf("Adjusted brightness to %i\n", buf[1]/MULTIPLIER); //print brightness to write
			buf[0] = WRITE; //change mode to write
		}
		
		//if number is within 1 and 16, adjust brightness accordingly
		else
		{
			buf[1] = (b_val - 1) * MULTIPLIER;
			printf("Adjusted brightness to %i\n", b_val);
		}
	}
	
	//write the results if applicable
	res = hid_write(handle, buf, BUFFER_LENGTH);
	//error handling
	if (err_handling(res, buf[0]) == 1)
	{
		return 1;
	}
	return 0;
}
