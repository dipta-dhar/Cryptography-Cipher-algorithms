#include<bits/stdc++.h>
using namespace std;

char cptext[100];

void Input(char [], char [] );
void encrypt(char [], char [] );
void decrypt(char [], char [] );
void prePosses (char [], char [] );
void vernamCipher (char [], char [] );

int main ()
{
    char str[100], key[100];

    printf("\tVernam Cipher Algorithm\n");
    printf("\t-----------------------\n");

    vernamCipher(str, key);   /* algorithm */

    return 0;
}

void vernamCipher (char str[], char key[]) {

    int choice;
    while(1) {
        printf("\n\t\t(1) Encrypt");
    	printf("\n\t\t(2) Decrypt");
    	printf("\n\t\t(3) Exit");
    	printf("\n\t\tEnter your choice: ");		scanf("%d", &choice);
    	getchar();

    	switch(choice) {
    		case 1:
    			Input(str, key);
    			prePosses(str, key);
    			encrypt(str, key);		printf("\n\t\tEncrypt text: %s\n", cptext);
    			break;
    		case 2:
    			Input(str, key);
    			prePosses(str, key);
    			decrypt(str, key);		printf("\n\t\tDecrypt text: %s\n", cptext);
    			break;
    		default:
    			exit(0);
    			break;
		}
    }
}

void Input(char str[], char key[]) {
	printf("\n\t\tEnter plain text: "); 	gets(str);
    printf("\t\tEnter key: ");          	scanf("%s", key);
}

void encrypt(char str[], char key[]) {
    int in = 0;
    for(int i=0; str[i]; i++) {
        if (str[i]>='a' && str[i]<='z') {
            char ch = (key[i]>='a' && key[i]<='z') ? 'a' : 'A';
            int ind = ((str[i]-'a' + key[i] - ch) % 26) + 'a';
            cptext[in++] = ind;
        } else if (str[i]>='A' && str[i]<='Z') {
            char ch = (key[i]>='a' && key[i]<='z') ? 'a' : 'A';
            int ind = ((str[i]-'A' + key[i] - ch) % 26) + 'A';
            cptext[in++] = ind;
        } else  cptext[in++] = str[i];
    }
    cptext[in] = '\0';
}

void decrypt(char str[], char key[]) {
    int in = 0;
    for(int i=0; str[i]; i++) {
        if (str[i]>='a' && str[i]<='z') {
            char ch = (key[i]>='a' && key[i]<='z') ? 'a' : 'A';
            int ind = ((str[i]-'a') - (key[i]-ch));
            ind = (ind < 0) ? (ind + 26)+'a' : (ind + 'a');
            cptext[in++] = ind;
        } else if (str[i]>='A' && str[i]<='Z') {
            char ch = (key[i]>='a' && key[i]<='z') ? 'a' : 'A';
            int ind = ((str[i]-'A') - (key[i]-ch));
            ind = (ind < 0) ? (ind + 26)+'A' : (ind + 'A');
            cptext[in++] = ind;
        } else  cptext[in++] = str[i];
    }
    cptext[in] = '\0';
}

void prePosses (char str[], char key[]) {
    int lenMsg = strlen(str);
    int lenKey = strlen(key);

    if (lenMsg != lenKey) {
        for(int i=lenKey; i<lenMsg; i++) {
            key[i] = key[lenKey-1];
        }
        key[lenMsg] = '\0';
    }
}
