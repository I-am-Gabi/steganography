/* fread example: read an entire file */
#include <stdio.h>
#include <stdlib.h>

#define NL '\n'

int main () {
	FILE *fileptr;
	char *buffer;
	long filelen;

	fileptr = fopen("../resources/file.txt", "rb");  // Open the file in binary mode
	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
	filelen = ftell(fileptr);             // Get the current byte offset in the file
	rewind(fileptr);                      // Jump back to the beginning of the file

	buffer = (char *)malloc((filelen+1)*sizeof(char)); // Enough memory for file + \0
	int n = fread(buffer, filelen, 1, fileptr); // Read in the entire file
	fclose(fileptr); // Close the file
	
	int in_bin[8];
	
	for(int j=0;j<filelen;j++) {
		printf("%c : %d : ", buffer[j], buffer[j]); // Printing the caracter & its integer value
		for(int i=0;i<8;i++){
			in_bin[i] = (buffer[j] >> (7 - i)) & 1;
			printf("%d", in_bin[i]); // Printing the current bit
		}
		putchar(NL);
	}

	return 0;
}