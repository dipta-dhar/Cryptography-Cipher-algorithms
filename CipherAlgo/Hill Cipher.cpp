/*
*   Hill Cipher
*
*   author: dipta
*   created: 05-Oct-2018 01:07:20
*
*/

#include<bits/stdc++.h>
using namespace std;

char cptext[100];

void input(char []);
void encrypt(char []);
void decrypt(char []);

void removeSpaces(char []);

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
    int key[][3] = {{  3, 10, 20},
                    { 20,  9, 17},
                    {  9,  4, 17}};
    strlwr(str);
    removeSpaces(str);

    int row, col = 3;
    int len = strlen(str);
    (len%3 == 0) ? row=len/3 : row=(len/3)+1;

    int messageVector[row][col], indx = 0;
    for (int i=0; i<row;  i++) {
        for (int j=0; j<col; ) {
            if (indx < len) {
                if (str[indx]>='a' && str[indx]<='z') {
                    messageVector[i][j] = str[indx] - 'a';
                    j++;
                }
            }
            else {
                messageVector[i][j] = 'z' - 'a';
                j++;
            }
            indx++;
        }
    }

    indx = 0;
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            int c0 = messageVector[i][0]*key[0][j] + messageVector[i][1]*key[1][j] + messageVector[i][2]*key[2][j];
            cptext[indx++] = (c0%26) + 'a';
        }
    }
    cptext[indx] = '\0';
}

void decrypt(char str[]) {
    int keyIN[][3] = {{  3, 10, 20},
                      { 20,  9, 17},
                      {  9,  4, 17}};

    int Mirror[][3] = {{  85,   90,  -10},
                       {-187, -129, -349},
                       {  -1,  -78, -173}};

    /// ((09*Mirror[][]) % 26)
    int CoFactor[][3] =  {{ 11, 22, 14},
                          {  7,  9, 21},
                          { 17,  0,  3}};

    strlwr(str);
    removeSpaces(str);

    int row, col = 3;
    int len = strlen(str);
    (len%3 == 0) ? row=len/3 : row=(len/3)+1;

    int key[3][3];
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            key[i][j] = ((CoFactor[i][j] % 26 + 26) % 26);
        }
    }

    int messageVector[row][col], indx = 0;
    for (int i=0; i<row;  i++) {
        for (int j=0; j<col; ) {
            if (indx < len) {
                if (str[indx]>='a' && str[indx]<='z') {
                    messageVector[i][j] = str[indx] - 'a';
                    j++;
                }
            }
            else {
                messageVector[i][j] = 'z' - 'a';
                j++;
            }
            indx++;
        }
    }

    indx = 0;
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            int c0 = messageVector[i][0]*key[0][j] + messageVector[i][1]*key[1][j] + messageVector[i][2]*key[2][j];
            cptext[indx++] = (c0%26) + 'a';
        }
    }
    cptext[indx] = '\0';
}

void removeSpaces(char str[]) {
    int count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];
    str[count] = '\0';
}
