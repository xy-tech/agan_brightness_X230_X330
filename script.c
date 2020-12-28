#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hidapi/hidapi.h"

int main (int argc, char *argv[])
{
	if (argc > 1)
	{
		printf("too many arguments");
	}

	int res;
	hid_device *handle;
	
	res = hid_init();
	
	handle = hid_open(0x10C4, 0x83CE, NULL);

	if (handle == NULL)
	{
		printf("unable to open device");
	}
	else
	{
		printf("device open!");
	}
	
		
	//write to 0x06, followed by the value of brightness
	//read from 0x04, followed by the actual value of brightness
	//value to write is in multiples of 16
	//value to read is just 0 to 15
	
	int buflen = 2;
	unsigned char buf[2];
	buf[0] = 6;

	if (argc == 0)
	{	
		buf[1] = 240;
		printf("max brightness");
	}
	else
	{
		buf[1] = atoi(argv[1]) * 16;
		printf("adjust brightness");
	}

	res = hid_write(handle, buf, buflen);

	return 0;
}
