#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

int main() {

	// variables
    FILE *fp1, *fp2, *fp3, *fp4;
	uint8_t **username, **userhash, **hashlist, **passwordlist;
	uint8_t buffer[200];
	int *match;
	int i, j, count = 0, nuser=0, nlist=0;
    
	// time begin
    clock_t begin = clock();

    // declaration
    username = (uint8_t**)malloc(500000 * sizeof(uint8_t*));
    userhash = (uint8_t**)malloc(500000 * sizeof(uint8_t*));
    hashlist = (uint8_t**)malloc(500000 * sizeof(uint8_t*));
    passwordlist = (uint8_t**)malloc(500000 * sizeof(uint8_t*));
    match = (int*)malloc(500000 * sizeof(int));

    
	for (i = 0; i < 500000; i++)
		username[i] = (uint8_t*)malloc(100 * sizeof(uint8_t));

	for (i = 0; i < 500000; i++)
		userhash[i] = (uint8_t*)malloc(100 * sizeof(uint8_t));
	
	for (i = 0; i < 500000; i++)
		hashlist[i] = (uint8_t*)malloc(100 * sizeof(uint8_t));

	for (i = 0; i < 500000; i++)
		passwordlist[i] = (uint8_t*)malloc(10 * sizeof(uint8_t)); 
    

    // intialization
    for (i = 0; i < 500000; i++) {
		for (j = 0; j < 100; j++)
			username[i][j] = 0;
	}

	for (i = 0; i < 500000; i++) {
		for (j = 0; j < 100; j++)
			userhash[i][j] = 0;
	}

	for (i = 0; i < 500000; i++) {
		for (j = 0; j < 100; j++)
			hashlist[i][j] = 0;
	}

	for (i = 0; i < 500000; i++) {
		for (j = 0; j < 10; j++)
			passwordlist[i][j] = 0;
	}

    for (i = 0; i < 500000; i++){
        match[i] = 0;
    }

	printf("meow1\n");
    fp1 = fopen("hashedPasswords.txt", "r");
	fp2 = fopen("hashlist.txt", "r");
	fp3 = fopen("passwordlist.txt", "r");
	fp4 = fopen("Passwords.txt", "w");

	printf("meow2\n");
	while (fgets(buffer, 200, fp1) != NULL) {

		i = 0; j = 0;
		while (buffer[i] != ':') i++;

		i++;
		printf("	pst1\n");
		while (buffer[i] != ':') {
			if (buffer[i] != ' ') {
				username[nuser][j] = buffer[i];
				j++;
				i++;
			}
		}
		username[nuser][j] = '\0';

		i++; j = 0;
		printf("	pst2\n");
		while (i < strlen(buffer)) {
			userhash[nuser][j] = buffer[i];
			j++;
			i++;
		}
		printf("	pst3\n");
		if (userhash[nuser][j - 1] == '\n')
			userhash[nuser][j - 1] = '\0';

		else if (feof(fp1))
			userhash[nuser][j] = '\0';
		printf("	pst4\n");
		nuser++;
	}
	
	printf("meow3\n");
	while (fgets(buffer, 50, fp2) != NULL) {
		// printf("%s", buffer);
		buffer[32] = '\0';

		for (i = 0; i < 50; i++)
			hashlist[nlist][i] = buffer[i];
		
		nlist++;
	}
	
	printf("meow4\n");	
	nlist = 0;
	while (fgets(buffer, 50, fp3) != NULL) {

		for (i = 0; i < strlen(buffer); i++) {
			passwordlist[nlist][i] = buffer[i];
			if (passwordlist[nlist][i] == '\n')
				passwordlist[nlist][i] = '\0';
		}

		if (feof(fp3))
			passwordlist[nlist][i] = '\0';
		
		nlist++;
	}
	printf("meow5\n");
	for (i = 0; i < nuser; i++) {
		count = 0;

		for (j=0; j < nlist; j++) {
			if (strcmp(hashlist[j], userhash[i]) == 0) {
				match[i] = j;
				count = 1;
			}
			if (count == 1)
				break;
		}

		if (count == 0)
			match[i] = 99999;
	}

	printf("meow6\n");
	for (i = 0; i < nuser; i++) {
		// the hash of password not in my list
		if (match[i] == 99999)
			fprintf(fp4, "%d:%s:%s\n", i + 1, username[i], "Password Not FOUND");
		else
			fprintf(fp4, "%d:%s:%s\n", i + 1, username[i], passwordlist[match[i]]);
	}

    printf("meow7\n");

    // time end
    clock_t end = clock();

	printf("Purrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr ^^^^^\n");
    printf("Time taken:%lf\n",(double)(end-begin)/CLOCKS_PER_SEC);

}