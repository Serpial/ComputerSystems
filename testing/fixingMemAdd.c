

int main() {
	
	return 0;
}


void displayMemBin () {
	int counter=0;
	printf("Memory Location\t->\tInstruction\n"); // Heading
	char memLoc[BITS_NUM_WORDS+1], instruc[INST_SIZE+1];

	while(memory[counter]!=0) {
		strcpy(memLoc, decToBinStr(counter,BITS_NUM_WORDS));
		strcpy(instruc, decToBinStr(memory[counter], INST_SIZE));
		printf("%s\t->\t%s\n", memLoc, instruc);
		counter++;
	}
}