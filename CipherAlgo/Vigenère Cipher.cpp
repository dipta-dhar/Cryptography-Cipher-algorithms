#include<bits/stdc++.h>
using namespace std;

char cptext[100];
char table[50][50];

void fillTable();
void Input(char [], char [] );
void encrypt(char [], char [] );
void decrypt(char [], char [] );
void prePosses (char [], char [] );
void vigenereCipher (char [], char [] );

int main ()
{
    char str[100], key[100];

    vigenereCipher(str, key);   /* algorithm */

    return 0;
}

void vigenereCipher (char str[], char key[]) {

    fillTable();

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

void fillTable() {
    for(int col=0; col<26; col++) {
        for(int row=0; row<26; row++) {
            table[col][row] = ((col + row)%26) + 'A';
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
        int col = key[i] - 'A';
        int row = str[i] - 'A';

        if (str[i]>='A' && str[i]<='Z') {
            cptext[in++] = table[col][row];
        }
        else cptext[in++] = str[i];
    }
    cptext[in] = '\0';
}

void decrypt(char str[], char key[]) {
    int in = 0;
    for(int i=0; str[i]; i++) {
        if (str[i]>='A' && str[i]<='Z') {
            int col = key[i] - 'A';
            char ch = str[i];
            int row = 0;
            for(int i=0; i<26; i++) {
                if (table[col][i] == ch) {
                    row = i;
                    break;
                }
            }
            cptext[in++] = table[0][row];
        }
        else cptext[in++] = str[i];
    }
    cptext[in] = '\0';
}

void prePosses (char str[], char key[]) {
    strupr(str);    strupr(key);

    int len     = strlen(str);
    int lenKey  = strlen(key);
    int index   = lenKey;

    if (len > lenKey) {
        for(int i=lenKey; i<len; i++) {
            if (str[i]>='A' && str[i]<='Z') {
                key[index++] = key[i % lenKey];
            }
            else
            key[index++] = ' ';
        }
        key[index] = '\0';
    }
    else key[len] = '\0';
}
