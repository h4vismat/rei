#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>
#include <curl/curl.h>

#define TRUE 1
#define FALSE 0

void run_polygon(void) {

int main(int argc, char *argv[]) {
	int i;

	printf("Rei - a investment terminal with connection to various services.\n");

	printf("[1] Polygon\n");

	i = getchar();
	
	if(i ==  '1') {
		run_polygon();
	}
}

