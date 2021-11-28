// opyright © 2021 Benno Bielmeier
// SPDX-License-Identifier: EUPL-1.2
/*
 * Advent of Code - Day 4: Passport Processing
 *
 * You arrive at the airport only to realize that you grabbed your North Pole
 * Credentials instead of your passport. While these documents are extremely
 * similar, North Pole Credentials aren't issued by a country and therefore
 * aren't actually valid documentation for travel in most of the world.
 *
 * It seems like you're not the only one having problems, though; a very long
 * line has formed for the automatic passport scanners, and the delay could
 * upset your travel itinerary.
 *
 * Due to some questionable network security, you realize you might be able to
 * solve both of these problems at the same time.
 *
 * The automatic passport scanners are slow because they're having trouble
 * detecting which passports have all required fields. The expected fields are
 * as follows:
 *
 * - byr (Birth Year)
 * - iyr (Issue Year)
 * - eyr (Expiration Year)
 * - hgt (Height)
 * - hcl (Hair Color)
 * - ecl (Eye Color)
 * - pid (Passport ID)
 * - cid (Country ID)
 *
 * Passport data is validated in batch files (your puzzle input). Each passport
 * is represented as a sequence of key:value pairs separated by spaces or
 * newlines. Passports are separated by blank lines.
 *
 * Here is an example batch file containing four passports:
 *
 * ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
 * byr:1937 iyr:2017 cid:147 hgt:183cm
 *
 * iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
 * hcl:#cfa07d byr:1929
 *
 * hcl:#ae17e1 iyr:2013
 * eyr:2024
 * ecl:brn pid:760753108 byr:1931
 * hgt:179cm
 *
 * hcl:#cfa07d eyr:2025 pid:166559648
 * iyr:2011 ecl:brn hgt:59in
 *
 * The first passport is valid - all eight fields are present. The second
 * passport is invalid - it is missing hgt (the Height field).
 *
 * The third passport is interesting; the only missing field is cid, so it
 * looks like data from North Pole Credentials, not a passport at all! Surely,
 * nobody would mind if you made the system temporarily ignore missing cid
 * fields. Treat this "passport" as valid.
 *
 * The fourth passport is missing two fields, cid and byr. Missing cid is fine,
 * but missing any other field is not, so this passport is invalid.
 *
 * According to the above rules, your improved system would report 2 valid
 * passports.
 *
 * Count the number of valid passports - those that have all required fields.
 * Treat cid as optional. In your batch file, how many passports are valid?
 */

/*
 * Author's assumptions about input:
 * 1. No line exceeds 149 character (inclusive newline).
 * 2. No (inconsistent) duplicate key entries per passport.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSPORT_FIELD_COUNT 8
#define BUFFER_SIZE 150
#define CONFIG_PART_TWO false

void usage(const char *program_name)
{
	fprintf(stderr, "Usage:\n\t%s <infile>", program_name ?:
			"passport-processing");
}

int main(int argc, char *argv[])
{
	char line[BUFFER_SIZE];
	unsigned char fields_present = 0x00;
	const unsigned char fields_required = 0x7F; /* Ignore missing cid */
	unsigned int valid_count = 0;
	FILE *batch_file;
	const char *search_keys[PASSPORT_FIELD_COUNT] = { "byr", "iyr", "eyr",
		"hgt", "hcl", "ecl", "pid", "cid" };

	if (argc < 2) {
		usage(argv[1]);
		exit(EXIT_FAILURE);
	}

	batch_file = fopen(argv[1], "r");
	if (!batch_file) {
		fprintf(stderr, "File '%s' not found\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, BUFFER_SIZE, batch_file)) {
		/* "\n" is also being read and stored in `line` */
		if (strlen(line) == 1) {
			if ((fields_present & fields_required) ==
					fields_required)
				++valid_count;
			/* Reset fields and continue with next passport */
			fields_present = 0x00;
			continue;
		}

		for (int i = 0; i < PASSPORT_FIELD_COUNT; ++i) {
			/* Check presents of each search key in current line */
			if(strstr(line, search_keys[i]))
				fields_present |= (1 << i);
		}
	}

	fclose(batch_file);

	printf("valid count:\n%u\n", valid_count);

	return EXIT_SUCCESS;
}
