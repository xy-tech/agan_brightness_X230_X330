#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hidapi/hidapi.h"

int main (int argc, char *argv[])
{
	if (argc > 2)
	{
		printf("Too many arguments\n");
		return 1;
	}

	int res;
	hid_device *handle;
	
	res = hid_init();
	
	handle = hid_open(0x10C4, 0x83CE, NULL);

	if (handle == NULL)
	{
		printf("Unable to open device\n");
		return 1;
	}
	else
	{
		printf("Device open!\n");
	}
	
		
	//write to 0x06, followed by the value of brightness
	//read from 0x04, followed by the actual value of brightness
	//value to write is in multiples of 16
	//value to read is just 0 to 15
	
	int buflen = 2;
	unsigned char buf[2];
	buf[0] = 6;

	if (argc == 1) //no argument, default to max brightness
	{	
		buf[1] = 240;
		printf("INSTRUCTIONS TO USE: \n");
		printf("sudo ./script [BRIGHTNESS VALUE IN INTEGERS]\n");
		printf("[BRIGHTNESS VALUE IN INTEGERS] can be between 1 to 16.\n");
		printf("Any value below 1 reduces brightness by 1 and any value above 16 increases brightness by 1\n");
		printf("Max brightness\n");
	}
	else
	{
		int b_val = atoi(argv[1]);
		if (b_val < 1 || b_val > 16)
		{
			buf[0] = 4;
			res = hid_get_feature_report(handle, buf, buflen);
			printf("Current brightness = %i\n", buf[1]);
			if ((buf[1] == 0 && b_val < 1) || (buf[1] == 15 && b_val > 16))
			{
				printf("Not adjusting brightness\n");
				return 0;
			}
			else if (b_val < 1)
			{
				buf[1] = (buf[1] - 1) * 16;
			}
			else	
			{
				buf[1] = (buf[1] + 1) * 16;
			}
			printf("Adjust brightness to %i\n", buf[1]);
			buf[0] = 6;
		}
		else
		{
			buf[1] = (b_val - 1) * 16;
			printf("Adjust brightness to %i\n", b_val);
		}
	}

	res = hid_write(handle, buf, buflen);

	return 0;
}
