// opyright © 2021 Benno Bielmeier
// SPDX-License-Identifier: EUPL-1.2
/*
 * Advent of Code - Day 3: Toboggan Trajectory
 *
 * With the toboggan login problems resolved, you set off toward the airport.
 * While travel by toboggan might be easy, it's certainly not safe: there's
 * very minimal steering and the area is covered in trees. You'll need to see
 * which angles will take you near the fewest trees.
 *
 * Due to the local geology, trees in this area only grow on exact integer
 * coordinates in a grid. You make a map (your puzzle input) of the open
 * squares (.) and trees (#) you can see. For example:
 *
 * ..##.......
 * #...#...#..
 * .#....#..#.
 * ..#.#...#.#
 * .#...##..#.
 * ..#.##.....
 * .#.#.#....#
 * .#........#
 * #.##...#...
 * #...##....#
 * .#..#...#.#
 *
 * These aren't the only trees, though; due to something you read about once
 * involving arboreal genetics and biome stability, the same pattern repeats to
 * the right many times:
 *
 * ..##.........##.........##.........##.........##.........##.......  --->
 * #...#...#..#...#...#..#...#...#..#...#...#..#...#...#..#...#...#..
 * .#....#..#..#....#..#..#....#..#..#....#..#..#....#..#..#....#..#.
 * ..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#
 * .#...##..#..#...##..#..#...##..#..#...##..#..#...##..#..#...##..#.
 * ..#.##.......#.##.......#.##.......#.##.......#.##.......#.##.....  --->
 * .#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#
 * .#........#.#........#.#........#.#........#.#........#.#........#
 * #.##...#...#.##...#...#.##...#...#.##...#...#.##...#...#.##...#...
 * #...##....##...##....##...##....##...##....##...##....##...##....#
 * .#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#  --->
 *
 * You start on the open square (.) in the top-left corner and need to reach
 * the bottom (below the bottom-most row on your map).
 *
 * The toboggan can only follow a few specific slopes (you opted for a cheaper
 * model that prefers rational numbers); start by counting all the trees you
 * would encounter for the slope right 3, down 1:
 *
 * From your starting position at the top-left, check the position that is
 * right 3 and down 1. Then, check the position that is right 3 and down 1 from
 * there, and so on until you go past the bottom of the map.
 *
 * The locations you'd check in the above example are marked here with O where
 * there was an open square and X where there was a tree:
 *
 * ..##.........##.........##.........##.........##.........##.......  --->
 * #..O#...#..#...#...#..#...#...#..#...#...#..#...#...#..#...#...#..
 * .#....X..#..#....#..#..#....#..#..#....#..#..#....#..#..#....#..#.
 * ..#.#...#O#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#
 * .#...##..#..X...##..#..#...##..#..#...##..#..#...##..#..#...##..#.
 * ..#.##.......#.X#.......#.##.......#.##.......#.##.......#.##.....  --->
 * .#.#.#....#.#.#.#.O..#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#
 * .#........#.#........X.#........#.#........#.#........#.#........#
 * #.##...#...#.##...#...#.X#...#...#.##...#...#.##...#...#.##...#...
 * #...##....##...##....##...#X....##...##....##...##....##...##....#
 * .#..#...#.#.#..#...#.#.#..#...X.#.#..#...#.#.#..#...#.#.#..#...#.#  --->
 *
 * In this example, traversing the map using this slope would cause you to
 * encounter 7 trees.
 *
 * Starting at the top-left corner of your map and following a slope of right 3
 * and down 1, how many trees would you encounter?
 */

/*
 * Author's assumptions about input:
 * 1. The map has a fixed width of at most 31.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_PART_TWO false
#define MAP_ROW_SIZE 32

void usage(const char *program_name)
{
	fprintf(stderr, "Usage:\n\t%s <infile>", program_name ?:
			"toboggan-trajectory");
}

int main(int argc, char *argv[])
{
	char map_row[MAP_ROW_SIZE];
	unsigned int map_column = 0;
	unsigned int tree_count = 0;
	unsigned int skipping = 0;
	const unsigned int slope_down = 1;
	const int slope_right = 3;
	const char tree_character = '#';
	FILE *map_file;

	if (argc < 2) {
		usage(argv[1]);
		exit(EXIT_FAILURE);
	}

	map_file = fopen(argv[1], "r");
	if (!map_file) {
		fprintf(stderr, "File '%s' not found\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while(0 < fscanf(map_file, "%s\n", map_row)) {
		if (skipping > 0) {
			--skipping;
			continue;
		}

		if (map_row[map_column] == tree_character)
			++tree_count;

		skipping = slope_down - 1;
		map_column = (map_column + slope_right) % strlen(map_row);
	}

	fclose(map_file);

	printf("tree count\n%u\n", tree_count);

	return EXIT_SUCCESS;
}
