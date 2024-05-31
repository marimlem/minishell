#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

volatile sig_atomic_t sigint_flag = 0;

void sigintHandler(int sig_num) {
    sigint_flag = 1;
}

int main() {
    char *input;

    // Register the SIGINT handler
    signal(SIGINT, sigintHandler);

    // Start the heredoc input
    while (1)
	{

	printf("Enter text (type EOF to finish): ");
    input = readline(NULL);

    // Check if the user pressed Control+C
   		 if (sigint_flag) {
   		     printf("\nInterrupted by user.\n");
   	   		  free(input); // Free the allocated memory for the input
       		 return 0; // Exit normally
   			 }
	}
    // Process the input (example: print it)
    printf("You entered: %s\n", input);

    // Add the input to history
    add_history(input);

    // Free the allocated memory for the input
    free(input);

    return 0;
}

