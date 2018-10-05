/*
*   Monoalphabetic Cipher
*
*    author: dipta
*   created: 05-Oct-2018 00:20:22
*
*/

#include<bits/stdc++.h>
using namespace std;

char cptext[100];
char KEYen[]  =  "abcdefghijklmnopqrstuvwxyz";
char KEYde[]  =  "apfcsvmniehjybogzqrtxwlkud";

void input(char []);
void encrypt(char []);
void decrypt(char []);

int main() {
    char str[100];
    printf("\n\t\tMonoalphabetic Cipher Algorithm");
    printf("\n\t\t-------------------------------\n");

    int choice;
    while(true) {
    	printf("\n\t\t(1) Encrypt");
    	printf("\n\t\t(2) Decrypt");
    	printf("\n\t\t(3) Exit");
    	printf("\n\t\tEnter your choice: ");		scanf("%d", &choice);
    	getchar();

    	switch(choice) {
    		case 1:
    			input(str);
    			encrypt(str);		printf("\n\t\tEncrypt text: %s\n", cptext);
    			break;

    		case 2:
    			input(str);
    			decrypt(str);		printf("\n\t\tDecrypt text: %s\n", cptext);
    			break;

            case 3:
                exit(0);
    			break;

    		default:
                printf("\n\t\t---> Invalid Choice!\n\n");
    			break;
		}
	}

    return 0;
}

void input(char str[]) {
	printf("\n\t\tEnter plain text: "); 	gets(str);
}

void encrypt(char str[]) {
    int len = strlen(str);

    strlwr(str);
    for (int i=0; i<len; i++) {
        if (str[i]>='a' && str[i]<='z') {
            for (int j=0; j<26; j++) {
                if (str[i] == KEYen[j])
                    cptext[i] = KEYde[j];
            }
        }
        else cptext[i] = str[i];
    }
    cptext[len] = '\0';
}

void decrypt(char str[]) {
    int len = strlen(str);

    strlwr(str);
    for (int i=0; i<len; i++) {
        if (str[i]>='a' && str[i]<='z') {
            for (int j=0; j<26; j++) {
                if (str[i] == KEYde[j])
                    cptext[i] = KEYen[j];
            }
        }
        else cptext[i] = str[i];
    }
    cptext[len] = '\0';
}


