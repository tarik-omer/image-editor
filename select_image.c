// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "definition.h"

// check wether the SELECT parameters are valid integers
int check_if_is_digit(char coord[10])
{
	int is = 1;
	for (int i = 0; i < 10 && coord[i] != '\0'; i++)
		if (isdigit(coord[i]) == 0 && coord[i] != '-')
			// it contains non-digits
			is = 0;
	return is;
}

void swap_coords(int *c1, int *c2)
{
	int aux = *c1;
	*c1 = *c2;
	*c2 = aux;
}

// main select function
void select_comm(img *pic_address)
{
	img pic = *pic_address;
	char *x1_or_not, parameters[100];
	char *ny1 = 0, *nx2 = 0, *ny2 = 0;
	fgets(parameters, 100, stdin);

	int all_good = 0;
	x1_or_not = strtok(parameters, " ");

	if (strstr(x1_or_not, "ALL")) {
		// case SELECT ALL
		pic.x1 = 0;
		pic.x2 = pic.width;
		pic.y1 = 0;
		pic.y2 = pic.height;
		printf("Selected ALL\n");

	} else if (x1_or_not[strlen(x1_or_not) - 1] != '\n') {
		// check to see that there are 4 parameters
		ny1 = strtok(NULL, " ");
		if (ny1[strlen(ny1) - 1] != '\n') {
			nx2 = strtok(NULL, " ");

			if (nx2[strlen(nx2) - 1] != '\n') {
				ny2 = strtok(NULL, " ");
				ny2[strlen(ny2) - 1] = '\0';
				all_good = 1;

			} else {
				printf("Invalid command\n");
				return;
			}
		} else {
			printf("Invalid command\n");
			return;
		}
	} else {
		printf("Invalid command\n");
		return;
	}

	if (all_good == 1) {
		// case SELECT <coords>
		// check if all the parameters are numbers
		int n1 = check_if_is_digit(x1_or_not);
		int n2 = check_if_is_digit(ny1);
		int n3 = check_if_is_digit(nx2);
		int n4 = check_if_is_digit(ny2);

		int x1, x2, y1, y2;
		if (n1 && n2 && n3 && n4) {
			x1 = atoi(x1_or_not);
			y1 = atoi(ny1);
			x2 = atoi(nx2);
			y2 = atoi(ny2);
		} else {
			printf("Invalid command\n");
			return;
		}
		// ordering the coordinates for easier comparison and usage
		if (x1 > x2)
			swap_coords(&x1, &x2);
		if (y1 > y2)
			swap_coords(&y1, &y2);
		// checking whether the coordinates are valid
		if (x1 >= 0 && x2 <= pic.width && y1 >= 0 &&
			y2 <= pic.height && x1 != x2 && y1 != y2) {
			pic.x1 = x1;
			pic.x2 = x2;
			pic.y1 = y1;
			pic.y2 = y2;
			printf("Selected ");
			printf("%d %d %d %d\n", x1, y1, x2, y2);
		} else {
			printf("Invalid set of coordinates\n");
		}
	}
	*pic_address = pic;
}
