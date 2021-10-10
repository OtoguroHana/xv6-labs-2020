#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
	int parent_to_child[2];
	int child_to_parent[2];
	char ch;
	pipe(parent_to_child);
	pipe(child_to_parent);

	if (fork() == 0) {
		close(child_to_parent[0]);
		close(parent_to_child[1]);
		if (read(parent_to_child[0], &ch, 1) != 1) {
			fprintf(2, "child read error\n");
			exit(1);
		}
		printf("%d: received ping\n", get_pid());
		write(child_to_parent[1], &ch, 1);

		close(child_to_parent[1]);
		close(parent_to_child[0]);
		exit(0);
	} else {
		close(child_to_parent[1]);
		close(parent_to_child[0]);
		write(parent_to_child[1], &ch, 1);
		if (read(child_to_parent[0], &ch, 1) != 1) {
			fprintf(2, "parent write error\n");
			exit(1);
		}
		printf("%d: received pong\n", getpid());
		close(parent_to_child[1]);
		close(child_to_parent[0]);
		exit(0);
	}
}