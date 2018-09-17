#include<bits/stdc++.h>
using namespace std;

char cptext[100];

int  Input(char [], int );
void encrypt(char [], int );
void decrypt(char [], int );

int main() {
    int key;
    char str[100];

    int choice;
    while(true) {
    	printf("\n\t\t(1) Encrypt");
    	printf("\n\t\t(2) Decrypt");
    	printf("\n\t\t(3) Exit");
    	printf("\n\t\tEnter your choice: ");		scanf("%d", &choice);
    	getchar();

    	switch(choice) {
    		case 1:
    			key = Input(str, key);
    			encrypt(str, key);		printf("\n\t\tEncrypt text: %s\n", cptext);
    			break;
    		case 2:
    			key = Input(str, key);
    			decrypt(str, key);		printf("\n\t\tDecrypt text: %s\n", cptext);
    			break;
    		default:
    			exit(0);
    			break;
		}
	}

    return 0;
}

int Input(char str[], int key) {
	printf("\n\t\tEnter plain text: "); 	gets(str);
    printf("\t\tEnter key: ");          	scanf("%d", &key);
    return key;
}

void encrypt(char str[], int key) {
    int in = 0;
    for(int i=0; str[i]; i++) {
        if ((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')) {
        	char ch = (str[i]>='a' && str[i]<='z') ? 'a' : 'A';
        	int ind = str[i] - ch;
        	ind = (ind + key) % 26;
        	cptext[in++] = ind + ch;
		}
		else if (str[i] == ' ')	cptext[in++] = str[i];
    }
    cptext[in] = '\0';
}

void decrypt(char str[], int key) {
    int in = 0;
    for(int i=0; str[i]; i++) {
        if ((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')) {
        	char ch = (str[i]>='a' && str[i]<='z') ? 'a' : 'A';
        	int ind = str[i] - ch;
        	for(int k=0; k<key; k++) {
        		if (ind-1 < 0)	ind = 25;
        		else ind = ind - 1;
			}
        	cptext[in++] = ind + ch;
		}
		else if (str[i] == ' ')	cptext[in++] = str[i];
    }
    cptext[in] = '\0';
}


