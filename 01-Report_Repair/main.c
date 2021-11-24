// Copyright © 2021 Benno Bielmeier
// SPDX-License-Identifier: EUPL-1.2
/*
 * Advent of Code - Day 1: Report Repair
 *
 * After saving Christmas five years in a row, you've decided to take a
 * vacation at a nice resort on a tropical island. Surely, Christmas will go on
 * without you.
 *
 * The tropical island has its own currency and is entirely cash-only. The gold
 * coins used there have a little picture of a starfish; the locals just call
 * them stars. None of the currency exchanges seem to have heard of them, but
 * somehow, you'll need to find fifty of these coins by the time you arrive so
 * you can pay the deposit on your room.
 *
 * To save your vacation, you need to get all fifty stars by December 25th.
 *
 * Collect stars by solving puzzles. Two puzzles will be made available on each
 * day in the Advent calendar; the second puzzle is unlocked when you complete
 * the first. Each puzzle grants one star. Good luck!
 *
 * Before you leave, the Elves in accounting just need you to fix your expense
 * report (your puzzle input); apparently, something isn't quite adding up.
 *
 * Specifically, they need you to find the two entries that sum to 2020 and
 * then multiply those two numbers together.
 *
 * For example, suppose your expense report contained the following:
 *
 * 1721
 * 979
 * 366
 * 299
 * 675
 * 1456
 *
 * In this list, the two entries that sum to 2020 are 1721 and 299. Multiplying
 * them together produces 1721 * 299 = 514579, so the correct answer is 514579.
 *
 * Of course, your expense report is much larger. Find the two entries that sum
 * to 2020; what do you get if you multiply them together?
 */

/*
 * Author's assumptions about input:
 * 1. Only integer values
 * 2. Only unsigned values
 * 3. All values are unique, no duplicates
 */

#include <stdio.h>
#include <stdlib.h>

#define TARGET_VALUE 2020

/**
 * struct node - Element of naive linked list.
 * @value: payload value.
 * @next: reference to next linked list element.
 */
struct node
{
	int value;
	struct node *next;
};

/**
 * compare_int() - Compare two integers.
 * @a: reference to first integer.
 * @b: reference to second integer.
 *
 * Return: -1, 0 or 1
 */
int compare_int(const void *a, const void *b)
{
	int x = *(int *)a;
	int y = *(int *)b;

	return (x > y) - (x < y);
}

/**
 * print_usage() - Print the usage message to stderr.
 * @program_name: name of the program.
 */
void print_usage(const char *program_name)
{
	fprintf(stderr, "Usage:\n\t%s <infile>\n",
			program_name ?: "repair-report");
}

/**
 * int_bsearch() - Customized binary search in sorted integer array.
 * @ptr: pointer to the array to examine.
 * @left: left most index in array.
 * @right: right most index in array.
 * @key: element to search for.
 *
 * Return: index of the biggest element less than or equal the key element.
 */
int int_bsearch(const int *ptr, int left, int right, int key)
{
	if (right >= left) {
		int mid = left + (right - left) / 2;
		if (ptr[mid] == key)
			return mid;
		if (ptr[mid] > key)
			return int_bsearch(ptr, left, mid - 1, key);
		return int_bsearch(ptr, mid + 1, right, key);
	}
	return left - 1;
}

int main(int argc, char *argv[])
{
	FILE *expense;
	int nr;
	size_t count = 0;
	struct node *head = NULL;
	int clip_value, clip_index;

	if (argc < 2) {
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	/* READ FROM FILE */
	expense = fopen(argv[1], "r");
	while (0 < fscanf(expense, "%u\n", &nr)) {
		struct node *current = malloc(sizeof(struct node));
		*current = (struct node){.value = nr, .next = head};
		head = current;
		count++;
	}
	fclose(expense);

	/* CONVERT LIST TO ARRAY */
	int *input = malloc(sizeof(int) * count);
	for (int i = 0; i < count; ++i) {
		input[i] = head->value;
		struct node *next = head->next;
		free(head);
		head = next;
	}

	/* SORT IN ASCENDING ORDER */
	qsort(input, count, sizeof(*input), compare_int);

	/* PREPARE CLIPPING */
	clip_value = (TARGET_VALUE / 2) - 1;
	clip_index = int_bsearch(input, 0, count, clip_value);

	/* FIND MATCHING PAIR */
	for (int i = count - 1; i > clip_index; --i) {
		for (int j = i - 1; j >= 0; --j) {
			int delta = input[i] + input[j] - TARGET_VALUE;
			if (delta == 0) {
				printf("%u * %u = %u\n", input[i], input[j],
						input[i] * input[j]);
				goto success;
			} else if (delta < 0) {
				// input[j] will only get smaller in following
				// iteration
				break;
			}
		}
	}

	fprintf(stderr, "No matching values found\n");

success:
	free(input);
	return EXIT_SUCCESS;
}
