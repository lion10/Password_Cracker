#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <time.h>

// openssl library 
int PKCS5_PBKDF2_HMAC(const char *pass, int passlen,
                       const unsigned char *salt, int saltlen, int iter,
                       const EVP_MD *digest,
                       int keylen, unsigned char *out);


void PBKDF2_HMAC_SHA_1(const char* pass, const unsigned char* salt, int32_t iterations, uint32_t outputBytes, char* hexResult)
{
    unsigned int i;
    unsigned char digest[outputBytes];
    PKCS5_PBKDF2_HMAC(pass, strlen(pass), salt, strlen(salt), iterations, EVP_sha512(), outputBytes, digest);
    for (i = 0; i < sizeof(digest); i++)
        sprintf(hexResult + (i * 2), "%02x", 255 & digest[i]);
}



int main(){

    // variables
    int i = 0, j, n = 0, countNumericalValues;
	uint8_t **datalist;
	uint8_t buffer[200], buffer2[16];
	FILE *fp1, *fp2, *fp3, *fp4;

	// time begin
    clock_t begin = clock();

    datalist = (uint8_t**) malloc(500000 * sizeof(uint8_t*));
	for (i = 0; i < 500000; i++)
		datalist[i] = (uint8_t*) malloc(16 * sizeof(uint8_t));
    
    
	fp1 = fopen("passwords_big.txt", "r");
	fp2 = fopen("passwordlist.txt", "w");

    for (i = 0; i < sizeof(buffer); i++)
		buffer[i] = 0;

	while (fgets(buffer, 200, fp1) != NULL ) {
        
        countNumericalValues = 0;
		for (i = 0; i < sizeof(buffer); i++) {
            if (buffer[i] == '\n') {
				buffer[i] = '\0';
			}
            // count the numerical values
			if (buffer[i] >= '0' && buffer[i] <= '9')
				countNumericalValues++;
		}
        
        // most common password the lenght is between 8 to 10 
		if (strlen(buffer) >= 7 && strlen(buffer) <= 10) {
            // check the password have at least one value
			if (countNumericalValues > 0 && n < 500000) {
				fprintf(fp2, "%s\n", buffer);
				n++;
			}


		}

		for (i = 0; i < sizeof(buffer); i++) {
			buffer[i] = 0;
		}
	}

    printf("%d\n", n);

	fclose(fp1);
	fclose(fp2);

	fp3 = fopen("passwordlist.txt", "r");
	fp4 = fopen("hashlist.txt", "w");
    i = 0;

	while (fgets(datalist[i], 16, fp3) != NULL) {
		for (j = 0; j < strlen(datalist[i]); j++) {
			if (datalist[i][j] == '\n') {
				datalist[i][j] = '\0';
			}
		}
		i++;
	}

    for (i = 0; i < n; i++) {
        PBKDF2_HMAC_SHA_1(datalist[i],"SKKU seclab", 10000,16,buffer2);
        fprintf(fp4, "%s\n", buffer2); 
	
	}

	fclose(fp3);
	fclose(fp4);

	// time end
    clock_t end = clock();
    printf("Time taken:%lf\n",(double)(end-begin)/CLOCKS_PER_SEC);
    
	// test the function
    // char *hexResult;
    // hexResult = malloc(4 * sizeof(uint8_t));
    // PBKDF2_HMAC_SHA_1("Ally123","SKKU seclab", 10000,16,hexResult);
    // // printf("%s\n", hexResult);     
 
    return 0;
}


