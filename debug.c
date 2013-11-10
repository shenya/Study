/*
 * function: debug
*/

#include <stdio.h>
#include <stdarg.h>

#define DEBUG 0

#if DEBUG
	#define PRINTF(a, ...) \
	{\
		printf("following is in file: %s, line: %d, function: %s()\n",\
						__FILE__, __LINE__, __FUNCTION__);\
		printf(a, ##__VA_ARGS__);\
	}
#else
	#define PRINTF(a, ...) printf(a, ##__VA_ARGS__)
#endif
		



int main(void)
{
	
	PRINTF("sgy %d: %s\n", 1, "hello world");
	PRINTF("sgy\n");
	return 0;
}
