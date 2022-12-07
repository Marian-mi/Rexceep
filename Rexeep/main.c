#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "Test/t_parse_table.h"

#define LOGF 0

int main() {
	int sexCount = 0, failCount = 0;

	for (size_t i = 0; i < 1; i++)
	{
		int res = t_parse_table();

		if (res) sexCount++;
		else failCount++;
	}
	if (failCount > 0) printf("failure");
	//printf("sex count: %d \r\nfail count: %d", sexCount, failCount);
}
