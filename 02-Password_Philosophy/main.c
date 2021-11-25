// opyright © 2021 Benno Bielmeier
// SPDX-License-Identifier: EUPL-1.2
/*
 * Advent of Code - Day 2: Password Philosophy
 *
 * Your flight departs in a few days from the coastal airport; the easiest way
 * down to the coast from here is via toboggan.
 *
 * The shopkeeper at the North Pole Toboggan Rental Shop is having a bad day.
 * "Something's wrong with our computers; we can't log in!" You ask if you can
 * take a look.
 *
 * Their password database seems to be a little corrupted: some of the
 * passwords wouldn't have been allowed by the Official Toboggan Corporate
 * Policy that was in effect when they were chosen.
 *
 * To try to debug the problem, they have created a list (your puzzle input) of
 * passwords (according to the corrupted database) and the corporate policy
 * when that password was set.
 *
 * For example, suppose you have the following list:
 *
 * 1-3 a: abcde
 * 1-3 b: cdefg
 * 2-9 c: ccccccccc
 *
 * Each line gives the password policy and then the password. The password
 * policy indicates the lowest and highest number of times a given letter must
 * appear for the password to be valid. For example, 1-3 a means that the
 * password must contain a at least 1 time and at most 3 times.
 *
 * In the above example, 2 passwords are valid. The middle password, cdefg, is
 * not; it contains no instances of b, but needs at least 1. The first and
 * third passwords are valid: they contain one a or nine c, both within the
 * limits of their respective policies.
 *
 * How many passwords are valid according to their policies?
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 60
#define CONFIG_PART_TWO false

void usage(const char *program_name)
{
	fprintf(stderr, "Usage:\n\t%s <infile>", program_name ?: "password-philosophy");
}

int main(int argc, char *argv[])
{
	unsigned int counter_valid = 0;
	unsigned int min_times, max_times;
	char policy_letter;
	char password_buffer[BUFFER_SIZE];
	FILE *password_list;

	if (argc < 2)
	{
		usage(argv[1]);
		exit(EXIT_FAILURE);
	}

	password_list = fopen(argv[1], "r");
	while(1 < fscanf(password_list, "%u-%u %c: %59s", &min_times, &max_times,
				&policy_letter, password_buffer)) {
		unsigned int occourences = 0;
		const char *ptr = password_buffer;

		while (*ptr)
		{
			if (*ptr == policy_letter)
				++occourences;
			++ptr;
		}

		if (min_times <= occourences && occourences <= max_times)
			++counter_valid;
	}

	printf("number of valid passwords:\n%u\n", counter_valid);

	return EXIT_SUCCESS;
}
