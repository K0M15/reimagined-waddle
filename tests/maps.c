#include <stdio.h>
#include <stdlib.h>

void output_header(FILE *fptr, size_t height, size_t width)
{
	fputs("P3\n");
	fputs("P3\n3 3\n255\n");
}

//TODO: Implement testing for images
int main(void)
{
	FILE *fptr;

	fptr = fopen("image.ppm", "w");
	if (!fptr)
	{
		printf("File could not be opened!");
		exit(1);
	}
	fputs("P3\n3 3\n255\n\
0 0 0 0 0 127 0 0 255\n\
0 0 0 0 127 0 0 255 0\n\
0 0 0 127 0 0 255 0 0\n", fptr);
	fclose(fptr);
	fptr = 0;
}
