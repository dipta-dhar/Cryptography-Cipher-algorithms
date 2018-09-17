#include<bits/stdc++.h>
using namespace std;

char cptext[1000];
char railMatrix[100][1000];

int Input(char [], int );
void encrypt(char [], int );
void decrypt(char [], int );
void prePosses (char [], int );
void railFenceCipher (char [], int );

int main ()
{
    char str[1000];
    int  key;

    printf("\tRail Fence Cipher Algorithm\n");
    printf("\t---------------------------\n");

    railFenceCipher(str, key);   /* algorithm */

    return 0;
}

void railFenceCipher (char str[], int key) {

    int choice;
    while(1) {
        printf("\n\t\t(1) Encrypt");
    	printf("\n\t\t(2) Decrypt");
    	printf("\n\t\t(3) Exit");
    	printf("\n\t\tEnter your choice: ");		scanf("%d", &choice);
    	getchar();

    	switch(choice) {
    		case 1:
    			key = Input(str, key);
    			prePosses(str, key);
    			encrypt(str, key);		printf("\n\t\tEncrypt text: %s\n", cptext);
    			break;
    		case 2:
    			key = Input(str, key);
    			prePosses(str, key);
    			decrypt(str, key);		printf("\n\t\tDecrypt text: %s\n", cptext);
    			break;
    		default:
    			exit(0);
    			break;
		}
    }
}

int Input(char str[], int key) {
	printf("\n\t\tEnter plain text: "); 	gets(str);
    printf("\t\tEnter key: ");          	scanf("%d", &key);
    return key;
}

void encrypt(char str[], int key) {
    int msgLen = strlen(str);
    int in = 0;
    for(int i = 0; i < key; ++i)
        for(int j = 0; j < msgLen; ++j)
            if(railMatrix[i][j] != '\n')
                cptext[in++] = railMatrix[i][j];
    cptext[in] = '\0';
}

void decrypt(char str[], int key) {
    int msgLen = strlen(str);
    int in = 0;
    for(int i = 0; i < key; ++i)
        for(int j = 0; j < msgLen; ++j)
            if(railMatrix[i][j] != '\n')
                railMatrix[i][j] = str[in++];

    int row=0, col=0, k=-1;
    for(int i=0, in=0; i < msgLen; ++i){
        cptext[in++] = railMatrix[row][col++];
        if(row == 0 || row == key-1)
            k= k * (-1);
        row = row + k;
    }
    cptext[in] = '\0';
}

void prePosses (char str[], int key) {
    int msgLen = strlen(str);
    int k = -1, row = 0, col = 0;

    for(int i = 0; i < key; ++i)
        for(int j = 0; j < msgLen; ++j)
            railMatrix[i][j] = '\n';

    for(int i = 0; i < msgLen; ++i){
        railMatrix[row][col++] = str[i];
        if(row == 0 || row == key-1)
            k= k * (-1);
        row = row + k;
    }
}

