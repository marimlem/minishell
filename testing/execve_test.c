#include <unistd.h>

int main(void) {
    char *file = "/usr/bin/ls";
    char *const args[] = {"/usr/bin/ls", "-a", "-l", NULL};
    char *const env[] = {"ENV=World", NULL};
	
    execve(file, args, NULL);

    return 0;
}