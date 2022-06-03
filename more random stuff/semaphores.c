#include<stdio.h>
#include<stdlib.h>

int mutex = 1;
int buffer[5];
int ptr = 0;
int full = 0;
int empty = 5;

int wait(int sem){
	return (--sem);
}

int signal(int sem){
	return (++sem);
}

int producer(){

	if((mutex == 1) && (empty != 0)){
		mutex = wait(mutex);
		full = signal(full);
		empty = wait(empty);
	
		printf("Enter the data to be entered into the buffer: ");
		scanf("%d", &buffer[ptr]);
		printf("The data %d has been produced\n", buffer[ptr]);
		ptr++;
	
		mutex = signal(mutex);
	}else{
		printf("The buffer is full!!\n");
	}
	return 1;
}

int consumer(){

	if((mutex == 1) && (full != 0)){
		mutex = wait(mutex);
		full = wait(full);
		empty = signal(empty);
		int data = buffer[--ptr];
		printf("Consumer has consumed the item %d.\n", data);
	
		mutex = signal(mutex);
	}else{
		printf("The buffer is empty !!\n");
	}
	return 1;
}

int frontend(){

	printf("******* MENU *******\n");
	printf("1. Use Producer\n");
	printf("2. Use Consumer\n");
	printf("3. Exit\n");
	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);
	int retval;
	switch(choice){
		case 1:
			retval = producer();
			break;
		case 2: 
			retval = consumer();
			break;
		case 3:
			retval = 0;
			break;
		default:
			retval = 1;
			printf("Invalid choice !!\n");
			printf("Enter a valid input.\n");
			break;
	}
	return retval;
}

int main(int argc, char *argv[]){

	while(frontend());
	return 1;
}
