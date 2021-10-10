#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(2, "Usage: sleep NUMBER...\n");
		exit(1);
	} else {
		sleep(atoi(argv[1]));
		exit(0);
	}
}