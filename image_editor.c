// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "definition.h"
#include "load_image.h"
#include "exit_image.h"
#include "save_image.h"
#include "select_image.h"
#include "rotate_image.h"
#include "crop_image.h"
#include "apply_image.h"

int main(void)
{
	char command[100];
	// the main struct instance that we will work on
	// modifying it along the way
	img pic;
	pic.is_loaded = 0;

	while (1) {
		scanf("%s", command);
		if (!strcmp(command, "LOAD")) {
			// LOAD
			char path[1000];
			scanf("%s", path);
			lock_and_load(path, &pic);

		} else if (!strcmp(command, "EXIT")) {
			// EXIT
			exit_all(&pic);
			break;

		} else if (!strcmp(command, "SELECT") && pic.is_loaded == 1) {
			// SELECT
			select_comm(&pic);

		} else if (!strcmp(command, "ROTATE") && pic.is_loaded == 1) {
			// ROTATE
			do_a_barrel_roll(&pic);

		} else if (!strcmp(command, "CROP") && pic.is_loaded == 1) {
			// CROP
			crop_crop_crop(&pic);

		} else if (!strcmp(command, "APPLY") && pic.is_loaded == 1) {
			// APPLY
			char param[100];
			fgets(param, 100, stdin);
			apply_it(&pic, param);

		} else if (!strcmp(command, "SAVE") && pic.is_loaded == 1) {
			// SAVE
			save_the_world(&pic);

		} else if (pic.is_loaded == 1) {
			// if the command is invalid, scrap the rest of the input line
			char trash[100];
			fgets(trash, 100, stdin);
			printf("Invalid command\n");

		} else {
			char trash[100];
			fgets(trash, 100, stdin);
			printf("No image loaded\n");
		}
	}
	return 0;
}
