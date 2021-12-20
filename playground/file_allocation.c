#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int contiguous(){

	int memory[100];
	int flag[100];
	int directory_table[100][2];
	int n_files = -1;
	int mem_size = 100;
	int check = 0;

	//initialising arrays
	for(int i = 0; i < mem_size; i++){
		memory[i] = -1;
		flag[i] = 0;
		directory_table[i][0] = -1;
		directory_table[i][1] = -1;
	}

	int choice = 0;
	while(choice != 4){
		printf("--- Contiguous Memory Allocation ---\n");
		printf("1. Enter a new file.\n");
		printf("2. Display memory.\n");
		printf("3. Display directory table.\n");
		printf("4. Exit.\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch(choice){
			case 1:
				n_files++;
				printf("Enter the size of the file: ");
				int file_size;
				scanf("%d", &file_size);

				//now allocating memory to this file
				for(int i = 0; i < mem_size; i++){
					check = 0;
					if(flag[i] == 0){
						//checking the next (file_size-1) slots if there is sufficient contiguous free space
						for(int j = 0; j < file_size; j++){
							if(flag[i+j] == 1 || (i+j) >= mem_size){
								check = 1;
								i = i+j;
								break;
							}
						}
						//if there is contiguous free slots available
						if(check == 0){
							for(int j = 0; j < file_size; j++){
								flag[i+j] = 1;
								memory[i+j] = n_files;
							}
							directory_table[n_files][0] = i;
							directory_table[n_files][1] = file_size;
							check = 2;
						}
						/*
						 * Alternatively, check could also have been 1, meaning that from
						 * the current ith location, atleast one of the (i+file_size) blocks
						 * are filled.
						 *
						 * In that case, we just search for the next free slot.
						 */
					}
					/*
					 * When control reaches here, check is either one of the following values:-
					 * 
					 * check = 1: This happens if the currently checked free slots doesnt have enough
					 * contiguous free space to hold the current file.
					 *
					 * check = 2: This happens if the currently checked blocks is unoccupied. In that case, 
					 * check first remains as 0 (as set at the beginning of the loop), and after the
					 * memory blocks have been allocated, check is set to 2.
					 */

					//printing allocation details
					if(check == 2){
						printf("The file has been allocated into memory. Details:-\n");
						printf("File Number: %d\n", n_files);
						printf("File Starting Block: %d\n", directory_table[n_files][0]);
						printf("File Size: %d\n", directory_table[n_files][1]);
						break;
					}
				}
				if(check != 2){
					printf("The file could not be allocated into memory.\n");
				}
				break;
			case 2:
				printf("Displaying memory:-\n");
				for(int i = 0; i < 10; i++){
					for(int j = 0; j < 10; j++){
						printf("%d\t", memory[10*i+j]);
					}
					printf("\n");
				}
				break;
			case 3:
				printf("Displaying directory table:-\n");
				printf("File Name\t Start Block\t File Size\n");
				for(int i = 0; i <= n_files; i++){
					printf("%d\t\t %d\t\t %d\n", i, directory_table[i][0], directory_table[i][1]);
				}
				break;
			case 4:
				printf("Exiting contiguous memory allocation.\n");
				break;
			default:
				printf("Invalid Input. Try again !\n");
				break;
		}
	}
	return 1;
}

int linked(){
	
	struct block{
		int data;
		int ptr;
	};
	struct block memory[100];
	int flag[100];
	int directory_table[100][2];
	int mem_size = 100;
	int check = 0;
	int n_files = -1;
	int free_space = mem_size;

	for(int i = 0; i < mem_size; i++){
		memory[i].data = -1;
		memory[i].ptr = -1;
		flag[i] = 0;
		directory_table[i][0] = -1;
		directory_table[i][1] = -1;
	}

	int choice = 0;
	while(choice != 4){
		printf("--- Linked File Allocation ---\n");
		printf("1. Enter file\n");
		printf("2. Display memory\n");
		printf("3. Display Directory Table\n");
		printf("4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
	
		switch(choice){
			case 1:
				printf("Enter the file size: ");
				int file_size;
				scanf("%d", &file_size);
	
				if(free_space < file_size){
					printf("The file size is larger than the remaining free space.\n");
					break;
				}else if(file_size <= 0){
					printf("Invalid file size !\n");
				}

				//if control reaches here, then it is posiible to allocate memory to the file
				n_files++;
				//now allocating memory to the file
				srand(time(0));
				int allocated = 0;
				int prev_index = -1;
				while(allocated < file_size){
					//a random block is selected and if free, is allocated to the current file
					int curr_index = rand()%mem_size;
					if(flag[curr_index] == 0){
						flag[curr_index] = 1;
						memory[curr_index].data = n_files;
						allocated++;
						free_space--;
						//if this is the first allocated block, make an entry into the directory table
						if(allocated == 1){
							directory_table[n_files][0] = curr_index;
						}
						//if this is the last allocated block, record it in the directory table
						if(allocated == file_size){
							directory_table[n_files][1] = curr_index;
						}
						//linking the current block to its predecessor
						if(prev_index != -1){
							memory[prev_index].ptr = curr_index;
							prev_index = curr_index;
						}else{
							//for the very first block of the file
							prev_index = curr_index;
						}
					}
				}
				printf("File has been entered successfully.\n");
				break;
			case 2:
				printf("Displaying memory:-\n");
				for(int i = 0; i < 10; i++){
					for(int j = 0; j < 10; j++){
						printf("%d\t", memory[10*i+j].data);
					}
					printf("\n");
				}
				break;
			case 3:
				printf("Displaying directory table:-\n");
				printf("File Name\t Start Block\t End Block\n");
				for(int i = 0; i <= n_files; i++){
					printf("%d\t\t %d\t\t %d\n", i, directory_table[i][0], directory_table[i][1]);
				}
				//printing individual files in the linked list fashion
				printf("Displaying the linked list representation of files:-\n");
				for(int i = 0; i <= n_files; i++){
					int curr_index = directory_table[i][0];
					printf("File #%d: %d", i, curr_index);
					while(curr_index != directory_table[i][1]){
						curr_index = memory[curr_index].ptr;
						printf(" -> %d", curr_index);
					}
					printf("\n");
				}
				break;
			case 4:
				printf("Exiting linked memory allocation\n");
				break;
			default:
				printf("Invalid Input. Try again !\n");
				break;
		}
	}

	return 1;
}

int indexed(){
	
	struct block{
		int data;
		int ptr[99];
	};
	struct block memory[100];
	int flag[100];
	int directory_table[100];
	int mem_size = 100;
	int n_files = -1;
	int free_space = mem_size;

	for(int i = 0; i < mem_size; i++){
		memory[i].data = -1;
		for(int j = 0; j < mem_size-1; j++){
			memory[i].ptr[j] = -1;
		}
		flag[i] = 0;
		directory_table[i]= -1;
	}

	int choice = 0;
	while(choice != 4){
		printf("--- Indexed File Allocation ---\n");
		printf("1. Enter file\n");
		printf("2. Display memory\n");
		printf("3. Display Directory Table\n");
		printf("4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
	
		switch(choice){
			case 1:
				printf("Enter the file size: ");
				int file_size;
				scanf("%d", &file_size);
	
				if(free_space < file_size+1){
					printf("The file size is larger than the remaining free space.\n");
					break;
				}else if(file_size <= 0){
					printf("Invalid file size !\n");
				}

				//if control reaches here, then it is possible to allocate memory to the file
				n_files++;

				srand(time(0));
				int allocated = 0;
				int fat_index;
				//finding a block to act as the index block for the file
				while(1){
					fat_index = rand()%100;
					if(flag[fat_index] == 0){
						directory_table[n_files] = fat_index;
						memory[fat_index].data = -2;
						flag[fat_index] = 1;
						free_space--;
						break;
					}
				}
				//allocating memory to the file
				while(allocated < file_size){
					int curr_index = rand()%mem_size;
					//checking if selected slot is free. If yes, allocate it to the file
					if(flag[curr_index] == 0){
						flag[curr_index] = 1;
						memory[curr_index].data = n_files;
						memory[fat_index].ptr[allocated] = curr_index;
						allocated++;
						free_space--;
					}
				}
				printf("File has been entered successfully.\n");
				break;
			case 2:
				printf("Displaying memory:-\n");
				for(int i = 0; i < 10; i++){
					for(int j = 0; j < 10; j++){
						printf("%d\t", memory[10*i+j].data);
					}
					printf("\n");
				}
				break;
			case 3:
				printf("Displaying directory table:-\n");
				printf("File Name\t Index Block\n");
				for(int i = 0; i <= n_files; i++){
					printf("%d\t\t %d\n", i, directory_table[i]);
				}
				printf("Displaying each file seperately:-\n");
				for(int i = 0; i <= n_files; i++){
					int fat_index = directory_table[i];
					printf("File #%d: ", i);
					if(memory[fat_index].data != -2){
						printf("ERROR\n");
					}
					printf("%d", memory[fat_index].ptr[0]);
					for(int j = 1; j < mem_size-1; j++){
						if(memory[fat_index].ptr[j] != -1){
							printf(" -> %d", memory[fat_index].ptr[j]);
						}else{
							break;
						}
					}
					printf("\n");
				}
				break;
			case 4:
				printf("Exiting indexed memory allocation\n");
				break;
			default:
				printf("Invalid Input. Try again !\n");
				break;
		}
	}

	return 1;
}

int mainMenu(){

	printf("******* MENU *******\n");
	printf("1. Contiguous File Allocation\n");
	printf("2. Linked File Allocation\n");
	printf("3. Indexed File Allocation\n");
	printf("4. Exit\n");
	
	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);

	int retval;
	switch(choice){
		case 1:
			retval = contiguous();
			break;
		case 2:
			retval = linked();
			break;
		case 3:
			retval = indexed();
			break;
		case 4:
			retval = 0;
			break;
		default:
			printf("Invalid Input !\n");
			retval = 1;
	}
	return retval;
}

int main(int argc, char *argv[]){
	
	while(mainMenu());
	return 1;
}
