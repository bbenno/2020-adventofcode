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
 *
 * --- Part Two ---
 *
 * While it appears you validated the passwords correctly, they don't seem to
 * be what the Official Toboggan Corporate Authentication System is expecting.
 *
 * The shopkeeper suddenly realizes that he just accidentally explained the
 * password policy rules from his old job at the sled rental place down the
 * street! The Official Toboggan Corporate Policy actually works a little
 * differently.
 *
 * Each policy actually describes two positions in the password, where 1 means
 * the first character, 2 means the second character, and so on. (Be careful;
 * Toboggan Corporate Policies have no concept of "index zero"!) Exactly one of
 * these positions must contain the given letter. Other occurrences of the
 * letter are irrelevant for the purposes of policy enforcement.
 *
 * Given the same example list from above:
 *
 * - 1-3 a: abcde is valid: position 1 contains a and position 3 does not.
 * - 1-3 b: cdefg is invalid: neither position 1 nor position 3 contains b.
 * - 2-9 c: ccccccccc is invalid: both position 2 and position 9 contain c.
 *
 * How many passwords are valid according to the new interpretation of the
 * policies?
 */

/*
 * Author's assumptions about input:
 * 1. Each password is at most 59 character long.
 * 2. Each password does only contain ASCII symbols.
 * 3. Each password is at least as long as the second number.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 60
#define CONFIG_PART_TWO true

void usage(const char *program_name)
{
	fprintf(stderr, "Usage:\n\t%s <infile>", program_name ?:
			"password-philosophy");
}

bool is_valid_one(const int min_times, const int max_times, const char
		policy_letter, const char *ptr)
{
	unsigned int occourences = 0;
	while (*ptr) {
		if (*ptr == policy_letter)
			++occourences;
		++ptr;
	}

	return min_times <= occourences && occourences <= max_times;
}

bool is_valid_two(const int position1, const int position2, const char
		policy_letter, const char *ptr)
{
	// Position is one-based
	const int i1 = position1 - 1;
	const int i2 = position2 - 1;

	return (ptr[i1] == policy_letter || ptr[i2] == policy_letter) &&
		ptr[i1] != ptr[i2];
}

int main(int argc, char *argv[])
{
	unsigned int counter_valid = 0;
	unsigned int nr1, nr2;
	char letter;
	char password_buffer[BUFFER_SIZE];
	FILE *password_list;
	bool (*is_valid)(const int, const int, const char, char const *);

	if (argc < 2) {
		usage(argv[1]);
		exit(EXIT_FAILURE);
	}

	if (CONFIG_PART_TWO)
		is_valid = is_valid_two;
	else
		is_valid = is_valid_one;

	password_list = fopen(argv[1], "r");
	if (!password_list) {
		fprintf(stderr, "File '%s' not found\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// fscanf return value will always be at least 1 due to string match
	// for password_buffer
	while(1 < fscanf(password_list, "%u-%u %c: %59s", &nr1, &nr2, &letter,
				password_buffer)) {
		if (is_valid(nr1, nr2, letter, password_buffer))
			++counter_valid;
	}

	fclose(password_list);

	printf("number of valid passwords:\n%u\n", counter_valid);

	return EXIT_SUCCESS;
}
