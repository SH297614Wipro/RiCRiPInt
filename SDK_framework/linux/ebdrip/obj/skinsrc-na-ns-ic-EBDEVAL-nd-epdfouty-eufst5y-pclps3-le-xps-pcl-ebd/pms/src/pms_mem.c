#include "pms_mem.h"
#include <stdio.h>

long memVal = 0;
long ShowMemVal()
{
	printf("Current Memory Usage: %lu bytes\n", memVal);
	return 0;
}
