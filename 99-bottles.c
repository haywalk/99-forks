/**
 * Hayden Walker
 * 2023-10-05
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void print_beers(int beers);

/**
 * Display the lyrics to '99 bottles of beer' by creating
 * a child process to display each verse.
 * 
 * Inspired by: http://www.99-bottles-of-beer.net/
 */
int main()
{
	int beers = 99, status;
	pid_t pid;

	while(beers >= 0) {
		pid = fork();

		switch(pid) {
		case -1: 
			// failed to create a child process
			exit(EXIT_FAILURE);
		case 0:
			// this process is a child process
			print_beers(beers);
			exit(EXIT_SUCCESS);
		default:
			// this process is the parent process
			printf("This beer's PID: %d\n", pid);
			waitpid(pid, &status, 0);
			beers--; 
		}
	}

	exit(EXIT_SUCCESS);
}

/**
 * Print the verse for `beers` number of beers.
 */
void print_beers(int beers)
{
	switch(beers) {
	case 0:
		printf("No more bottles of beer on the wall, ");
		printf("no more bottles of beer.\n");
		printf("Go to the store and buy some more, ");
		printf("99 bottles of beer on the wall.\n");
		break;
	case 1:
		printf("1 bottle of beer on the wall, ");
		printf("1 bottle of beer.\n");
		printf("Take one down and pass it around, ");
		printf("no more bottles of beer on the wall.\n\n");
		break;
	default:
		printf("%d bottles of beer on the wall, ", beers);
		printf("%d bottles of beer.\n", beers);
		printf("Take one down and pass it around, ");
		printf("%d %s of beer on the wall.\n\n", 
			beers - 1, beers - 1 > 1 ? "bottles" : "bottle");
		break;
	}
}