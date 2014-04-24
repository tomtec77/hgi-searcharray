/*
 * searcharray.c
 *
 * MIT Hacking a Google Interview Handout 1
 * Question: Searching through an array
 * Given a sorted array of n integers, how can you find the location of a
 * particular integer i?
 *
 * Array of data: generated with sorting.c (10000 random unsigned
 * integers, sorted in increasing order)
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10000
#define MAX_ARRAY_VALUE 2*ARRAY_SIZE


int main()
{
	FILE *fp;
	int i, buf, check;
	int first, last, middle;
	unsigned int value=0;
	time_t t0, t1;
	clock_t c0, c1;
	unsigned int array[ARRAY_SIZE];


	/* I/O section. Here we ask the user to input a value which will be
	   searched in the array. The data are positive integers between 1
	   and 20000 */
	while (value <= 0 || value > MAX_ARRAY_VALUE) {
		printf("Array search. Please input a value: ");
		scanf("%d", &value);
		if (value <= 0 || value > MAX_ARRAY_VALUE) {
			printf("Invalid number entered, please try again\n");
		}
	}
	printf("\n"); fflush(stdout);

	/* Open data file and read in the array */
	fp = fopen("array.dat", "r");
	if (fp==NULL) {
		printf("Error: cannot open file 'array.dat' - Stop.\n");
		fflush(stdout);
	    exit(EXIT_FAILURE);
	}

	i = 0;
	while (!feof(fp)) {
		if (fscanf(fp, "%d %u\n", &buf, &array[i]) != 2)
			break;
		i++;
	}

	fclose(fp);

	/* Control printout */
	/*for (i=0; i<ARRAY_SIZE; i++)
		printf("i, n[i]: %u %u\n", i, array[i]);
	fflush(stdout);*/

	/* To time the first part of the program */
	t0 = time(NULL);
	c0 = clock();

	/* This is the bad answer: go over every element of the array,
	   comparing the given element to each of them until a match is
	   found (linear search) */
	printf("Searching in the array (method 1)...\n");
	check = 0;
	for (i=0; i<ARRAY_SIZE; i++) {
		if (array[i]==value) {
			printf("Value found in array at position %d\n", i);
			check++;
		}
		/* We do not insert a break here, to search for repeated values */
	}
	if (check == 0)
		printf("Value not found in the array.\n");
	fflush(stdout);

	t1 = time(NULL);
	c1 = clock();
	printf("Elapsed wall clock time: %ld\n", (long)(t1-t0));
	printf("Elapsed CPU time:        %le\n\n",
			(double)(c1-c0)/ (double)CLOCKS_PER_SEC);
	fflush(stdout);

	/* This is the good answer: use binary search */
	printf("Searching in the array (method 2)...\n");

	/* To time the second part of the program */
	t0 = time(NULL);
	c0 = clock();

	first = 0;
	last  = ARRAY_SIZE-1;
	middle = (first+last)/2;

	while (first <= last) {
		if (array[middle] < value)
	         first = middle + 1;
		else if (array[middle] == value) {
			printf("Value found in array at position %d\n", middle);
			break;
		}
		else
			last = middle - 1;

		middle = (first + last)/2;
	}
	if (first > last)
		printf("Value not found in the array.\n");
	fflush(stdout);

	/* Now, a binary search stops when a matching value is found - not
	   good for handling duplicates. But if we know that the list is
	   sorted, then the duplicates must be next to the value we just
	   found. First check the elements to the left */
	i = middle - 1;
	while (array[i] == array[middle]) {
		printf("Value found in array at position %d\n", i);
		i--;
	}

	/* Now check elements to the right */
	i = middle + 1;
	while (array[i] == array[middle]) {
		printf("Value found in array at position %d\n", i);
		i++;
	}

	t1 = time(NULL);
	c1 = clock();
	printf("Elapsed wall clock time: %ld\n", (long)(t1-t0));
	printf("Elapsed CPU time:        %le\n",
			(double)(c1-c0)/ (double)CLOCKS_PER_SEC);
	fflush(stdout);

	return EXIT_SUCCESS;
}
