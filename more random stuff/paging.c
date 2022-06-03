#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int **page_table;
int *process_n_pages;
int frame[100];
int n_proc;

int enter_process(){

	//setting up the ram
	for(int i = 0; i < 100; i++){
		frame[i] = -1;
	}

	printf("Enter the number of processes: ");
	scanf("%d", &n_proc);

	page_table = malloc(sizeof(int*)*n_proc);
	process_n_pages = malloc(sizeof(int)*n_proc);
	int free_frames = 100;
	for(int i = 0; i < n_proc; i++){
		
		//dealing with each process one by one
		printf("Enter the number of pages for process #%d: ", i);
		int n_pages;
		scanf("%d", &n_pages);
		page_table[i] = malloc(sizeof(int)*n_pages);
		process_n_pages[i] = n_pages;
		//assigning frames to the pages of the current process
		srand(time(0));
		for(int j = 0; j < n_pages; j++){
			while(1){
				//this happens if the main memory is fully filled up
				if(free_frames <= 0){
					page_table[i][j] = -1;
					break;
				}
				int alloted_frame = rand()%100;
				//assigning a frame to the page (as long as memory is still available)
				if(frame[alloted_frame] == -1){
					frame[alloted_frame] = i;
					free_frames--;
					page_table[i][j] = alloted_frame;
					break;
				}
			}
		}
		printf("Finished assigning frames to process %d\n", i);
	}
	printf("Page tables for all the processes created.\n");
	return 1;
}

int paging(){
	
	printf("Enter the process no: ");
	int process_no;
	scanf("%d", &process_no);
	if(process_no+1 > n_proc || process_no < 0){
		printf("Invalid process number\n");
		return 1;
	}
	printf("Enter the page to be retrieved: ");
	int page_no;
	scanf("%d", &page_no);
	if(process_n_pages[process_no] < page_no){
		printf("Invalid page number\n");
		return 1;
	}
	printf("Enter the offset value: ");
	int offset;
	scanf("%d", &offset);

	printf("Virtual Address = %d: %d\n", page_no, offset);
	int frame_no = page_table[process_no][page_no-1];
	if(frame_no == -1){
		printf("The page is still in secondary memory.\n");
	}else{
		printf("Physical Address = %d: %d\n", page_table[process_no][page_no-1]+1, offset);
	}
	printf("Displaying Physical Memory:-\n");
	printf("\t [1]\t [2]\t [3]\t [4]\t [5]\t [6]\t [7]\t [8]\t [9]\t [10]\n");
	for(int i = 0; i < 10; i++){
		printf("[%d]\t", i);
		for(int j = 0; j < 10; j++){
			printf(" %d\t", frame[10*i+j]);
		}
		printf("\n");
	}

	return 1;
}

int mainMenu(){

	printf("*******MENU*******\n");
	printf("1. Enter process \n");
	printf("2. Simulate Paging\n");
	printf("3. Exit\n");
	
	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);

	int retval;
	switch(choice){
		case 1:
			retval = enter_process();
			break;
		case 2:
			retval = paging();
			break;
		case 3:
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
