#include <stdio.h>
#include <stdlib.h>

// Prototype for function that calculates the file length in bytes
void my_get_file_length(char *name);

int main(int argc, char *argv[])
{
    // Look up file stats with helper function (File Size : 3744768 bytes | Total Blocks: 7314)
    my_get_file_length(argv[1]);
}

// Helper function to get file length
void my_get_file_length(char *name)
{
	FILE *file;
	char *buffer;
	unsigned long file_len_helper_function;

	//Open file
	file = fopen(name, "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", name);
		// return;
	}
	
	//Get file length
	fseek(file, 0, SEEK_END);
	file_len_helper_function = ftell(file);
	fseek(file, 0, SEEK_SET);

	//Allocate memory
	buffer = (char *)malloc(file_len_helper_function+1);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
        fclose(file);
		return;
	}

	//Read file contents into buffer
	fread(buffer, file_len_helper_function, 1, file);
	fclose(file);

	//Do whatever with buffer
    int block_size = 512;
    unsigned long total_blocks = file_len_helper_function / block_size;

    printf("File Size   : %lu bytes\n", file_len_helper_function);
    printf("Total Blocks: %lu\n", total_blocks);

    // Free memory at end
	free(buffer);

}