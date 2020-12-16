#include <stdio.h>
#include "hidapi/hidapi.h"

int main (void)
{
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
	const unsigned char buf[2] = {6, 240}; 

	int buflen = 2;

	res = hid_write(handle, buf, buflen);
}
