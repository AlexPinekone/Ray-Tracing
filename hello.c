#include <stdio.h>

int main() {
	int incremental = 0;
	while(incremental < 5000000) {
		printf("Hello this is %d\n", incremental);
		incremental++;
	}
	return 0;
}