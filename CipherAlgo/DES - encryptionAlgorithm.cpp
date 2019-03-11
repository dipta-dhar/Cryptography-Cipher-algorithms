
/**
 *      DES - [Data Encryption Standard] Algorithm
 *
 *       author: dipta
 *      created: 15-Sep-2018 02:52:20
**/


#include<bits/stdc++.h>
using namespace std;

char inPT[100], inKey[100], sCT[100];
int PT[100], key[50][100],  bCT[100];

void Display();
void DESinput();
void DESencryption();

void DESfunction(int [], int [], int );
void PTpreposses(char [], int []);
void Round(int [], int [], int );
void sTable(int [], int []);
void KEYpreposses(char []);

void DecToBi(int , int [] );
void Copy(int [], int [], int );
void BinToHex(int [], char [] );
void TexToBin(char [], int [] );

/*
input:
     PT: ABCDEFGH
    Key: 1234ABCD

output:
     Cipher Text:
        Binary Form: 0011 0011 1010 0100 1111 0111 1101 1100 1110 1111 1100 1010 1100 1100 1010 1111
        Hexadecimal: 33A4F7DCEFCACCAF
*/

int main()
{
    cout << "\n\t\tDES - [Data Encryption Standard] Algorithm";
    cout << "\n\t\t------------------------------------------\n\n";

    int choice;
    while(true) {
    	printf("\n\t\t(1) Encrypt");
    	printf("\n\t\t(2) Exit");
    	printf("\n\t\tEnter your choice: ");		scanf("%d", &choice);

    	switch(choice) {
    		case 1:
    		    DESencryption();
    			break;

            case 2:
                exit(0);
    			break;

    		default:
                printf("\n\t\t----> Invalid choice!\n");
    			break;
		}
	}

    return 0;
}

void DESencryption() {
    DESinput();
    PTpreposses(inPT, PT);
    KEYpreposses(inKey);

    int L0[50], R0[50];
    /// L0: Left haves (32-bit), R0: Right haves (32-bit)
    for (int i=0; i<32; i++) {
        L0[i] = PT[i];
        R0[i] = PT[i+32];
    }

    for (int i=1; i<=16; i++) {
        Round(L0, R0, i);
    }

    /// Swap RiLi & store into output array
    int output[100];
    for(int i=0; i<32; i++) {
        output[i] = R0[i];
        output[i+32] = L0[i];
    }

    int inIP[] =   { 40,   8,  48,  16,  56,  24,  64,  32,
                     39,   7,  47,  15,  55,  23,  63,  31,
                     38,   6,  46,  14,  54,  22,  62,  30,
                     37,   5,  45,  13,  53,  21,  61,  29,
                     36,   4,  44,  12,  52,  20,  60,  28,
                     35,   3,  43,  11,  51,  19,  59,  27,
                     34,   2,  42,  10,  50,  18,  58,  26,
                     33,   1,  41,   9,  49,  17,  57,  25};

    int Temp[100];
    Copy(output, Temp, 64);
    for (int i=0; i<64; i++)  output[i] = Temp[inIP[i] - 1];

    Copy(output, bCT, 64);
    BinToHex(output, sCT);

    Display();
}

void Round(int L0[], int R0[], int roundNum) {
    int output[100];
    DESfunction(R0, output, roundNum);

    int Ri[100];
    for (int i=0; i<32; i++) {
        Ri[i] = L0[i] ^ output[i];
    }

    /// Swap or Update L0 & R0
    Copy(R0, L0, 32);
    Copy(Ri, R0, 32);
}

void DESfunction(int R0[], int output[], int roundNum) {
    /// Table-3 (input: 32-bit, output: 48-bit)
    int Expand[] = { 32,   1,   2,   3,   4,   5,   4,   5,
                      6,   7,   8,   9,   8,   9,  10,  11,
                     12,  13,  12,  13,  14,  15,  16,  17,
                     16,  17,  18,  19,  20,  21,  20,  21,
                     22,  23,  24,  25,  24,  25,  26,  27,
                     28,  29,  28,  29,  30,  31,  32,   1};

    int ER0[100];
    for (int i=0; i<48; i++) ER0[i] = R0[Expand[i] - 1];

    int Temp[100];
    /// Find K1+E(R0)
    for (int i=0; i<48; i++) {
        Temp[i] = key[roundNum][i] ^ ER0[i];
    }

    /// input: 48-bit, output: 32-bit
    sTable(Temp, output);

    int P[] =  { 16,   7,  20,  21,
                 29,  12,  28,  17,
                  1,  15,  23,  26,
                  5,  18,  31,  10,
                  2,   8,  24,  14,
                 32,  27,   3,   9,
                 19,  13,  30,   6,
                 22,  11,   4,  25 };

    /// copy output to Temp
    Copy(output, Temp, 32);
    for (int i=0; i<32; i++) output[i]  = Temp[P[i] - 1];
}

void PTpreposses(char pt[], int output[]) {
    /// input: Text, output: 64-bit Binary (Text --> ASCII-decimal-value --> Binary)
    TexToBin(pt, output);

    /// Initial permutation (input: 64-bit, output: 64-bit)
    int IP[] = { 58,  50,  42,  34,  26,  18,  10,   2,
                 60,  52,  44,  36,  28,  20,  12,   4,
                 62,  54,  46,  38,  30,  22,  14,   6,
                 64,  56,  48,  40,  32,  24,  16,   8,
                 57,  49,  41,  33,  25,  17,   9,   1,
                 59,  51,  43,  35,  27,  19,  11,   3,
                 61,  53,  45,  37,  29,  21,  13,   5,
                 63,  55,  47,  39,  31,  23,  15,   7};

    int Temp[100];
    Copy(output, Temp, 64);
    /// Apply IP
    for (int i=0; i<64; i++) output[i] = Temp[IP[i] -1];
}

void KEYpreposses(char inputKEY[]) {
    int output[100];
    TexToBin(inputKEY, output);

    int Temp[100];
    int kTemp[100], kLeft[50], kRight[50];
    /// Table-1 (input: 64-bit, output: 56-bit)
    int pc1[] = {57,  49,  41,  33,  25,  17,   9,   1,
                 58,  50,  42,  34,  26,  18,  10,   2,
                 59,  51,  43,  35,  27,  19,  11,   3,
                 60,  52,  44,  36,  63,  55,  47,  39,
                 31,  23,  15,   7,  62,  54,  46,  38,
                 30,  22,  14,   6,  61,  53,  45,  37,
                 29,  21,  13,   5,  28,  20,  12,   4};

    Copy(output, Temp, 64);
    /// store 56-bit in output array
    for (int i=0; i<56; i++) {
        output[i] = Temp[pc1[i] - 1];
    }

    /// Divide key into two halves. C0: Left haves, D0: Right haves
    int C0[28], D0[28];
    for (int i=0; i<28; i++) {
        C0[i] = output[i];
        D0[i] = output[i+28];
    }

    /// Table-2 (input: 56-bit, output: 48-bit)
    int pc2[] = {14,  17,  11,  24,   1,   5,   3,  28,
                 15,   6,  21,  10,  23,  19,  12,   4,
                 26,   8,  16,   7,  27,  20,  13,   2,
                 41,  52,  31,  37,  47,  55,  30,  40,
                 51,  45,  33,  48,  44,  49,  39,  56,
                 34,  53,  46,  42,  50,  36,  29,  32};

    int Ci[28], Di[28], CiDi[48];
    for (int roundNum=1; roundNum<=16; roundNum++) {
        /// Swap Left Shifts (1 bit) into both haves
        if (roundNum==1 || roundNum==2 || roundNum==9 || roundNum==16) {
            for (int i=1; i<28; i++) { Ci[i-1]=C0[i]; Di[i-1]=D0[i]; }
            Ci[27] = C0[0];
            Di[27] = D0[0];
        }
        /// Swap Left Shifts (2 bit) into both haves
        else {
            for (int i=2; i<28; i++) { Ci[i-2]=C0[i]; Di[i-2]=D0[i]; }
            Ci[26]=C0[0], Ci[27]=C0[1];
            Di[26]=D0[0], Di[27]=D0[1];
        }

        /// Find CiDi
        for (int i=0; i<28; i++) {
            CiDi[i] = Ci[i];
            CiDi[i+28] = Di[i];
        }

        Copy(CiDi, Temp, 56);
        for (int i=0; i<48; i++) CiDi[i] = Temp[pc2[i] - 1];

        /// Update C0 & D0
        Copy(Ci, C0, 28);
        Copy(Di, D0, 28);

        /// Store Key into key array
        Copy(CiDi, key[roundNum], 48);
    }
}

void sTable(int input[], int output[]) {
    int s1[4][16] =  {{ 14,   4,  13,   1,   2,  15,  11,   8,   3,  10,   6,  12,   5,   9,   0,   7 },
                      {  0,  15,   7,   4,  14,   2,  13,   1,  10,   6,  12,  11,   9,   5,   3,   8 },
                      {  4,   1,  14,   8,  13,   6,   2,  11,  15,  12,   9,   7,   3,  10,   5,   0 },
                      { 15,  12,   8,   2,   4,   9,   1,   7,   5,  11,   3,  14,  10,   0,   6,  13 }};

    int s2[4][16] =  {{ 15,   1,   8,  14,   6,  11,   3,   4,   9,   7,   2,  13,  12,   0,   5,  10 },
                      {  3,  13,   4,   7,  15,   2,   8,  14,  12,   0,   1,  10,   6,   9,  11,   5 },
                      {  0,  14,   7,  11,  10,   4,  13,   1,   5,   8,  12,   6,   9,   3,   2,  15 },
                      { 13,   8,  10,   1,   3,  15,   4,   2,  11,   6,   7,  12,   0,   5,  14,   9 }};

    int s3[4][16] =  {{ 10,   0,   9,  14,   6,   3,  15,   5,   1,  13,  12,   7,  11,   4,   2,   8 },
                      { 13,   7,   0,   9,   3,   4,   6,  10,   2,   8,   5,  14,  12,  11,  15,   1 },
                      { 13,   6,   4,   9,   8,  15,   3,   0,  11,   1,   2,  12,   5,  10,  14,   7 },
                      {  1,  10,  13,   0,   6,   9,   8,   7,   4,  15,  14,   3,  11,   5,   2,  12 }};

    int s4[4][16] =  {{  7,  13,  14,   3,   0,   6,   9,  10,   1,   2,   8,   5,  11,  12,   4,  15 },
                      { 13,   8,  11,   5,   6,  15,   0,   3,   4,   7,   2,  12,   1,  10,  14,   9 },
                      { 10,   6,   9,   0,  12,  11,   7,  13,  15,   1,   3,  14,   5,   2,   8,   4 },
                      {  3,  15,   0,   6,  10,   1,  13,   8,   9,   4,   5,  11,  12,   7,   2,  14 }};

    int s5[4][16] =  {{  2,  12,   4,   1,   7,  10,  11,   6,   8,   5,   3,  15,  13,   0,  14,   9 },
                      { 14,  11,   2,  12,   4,   7,  13,   1,   5,   0,  15,  10,   3,   9,   8,   6 },
                      {  4,   2,   1,  11,  10,  13,   7,   8,  15,   9,  12,   5,   6,   3,   0,  14 },
                      { 11,   8,  12,   7,   1,  14,   2,  13,   6,  15,   0,   9,  10,   4,   5,   3 }};

    int s6[4][16] =  {{ 12,   1,  10,  15,   9,   2,   6,   8,   0,  13,   3,   4,  14,   7,   5,  11 },
                      { 10,  15,   4,   2,   7,  12,   9,   5,   6,   1,  13,  14,   0,  11,   3,   8 },
                      {  9,  14,  15,   5,   2,   8,  12,   3,   7,   0,   4,  10,   1,  13,  11,   6 },
                      {  4,   3,   2,  12,   9,   5,  15,  10,  11,  14,   1,   7,   6,   0,   8,  13 }};

    int s7[4][16] =  {{  4,  11,   2,  14,  15,   0,   8,  13,   3,  12,   9,   7,   5,  10,   6,   1 },
                      { 13,   0,  11,   7,   4,   9,   1,  10,  14,   3,   5,  12,   2,  15,   8,   6 },
                      {  1,   4,  11,  13,  12,   3,   7,  14,  10,  15,   6,   8,   0,   5,   9,   2 },
                      {  6,  11,  13,   8,   1,   4,  10,   7,   9,   5,   0,  15,  14,   2,   3,  12 }};

    int s8[4][16] =  {{ 13,   2,   8,   4,   6,  15,  11,   1,  10,   9,   3,  14,   5,   0,  12,   7 },
                      {  1,  15,  13,   8,  10,   3,   7,   4,  12,   5,   6,  11,   0,  14,   9,   2 },
                      {  7,  11,   4,   1,   9,  12,  14,   2,   0,   6,  10,  13,  15,   3,   5,   8 },
                      {  2,   1,  14,   7,   4,  10,   8,  13,  15,  12,   9,   0,   3,   5,   6,  11 }};

    int tem[10], in=0, index=0, oo[10];
    for (int i=1; i<=8; i++) {
        tem[0] = input[in++];
        tem[1] = input[in++];
        tem[2] = input[in++];
        tem[3] = input[in++];
        tem[4] = input[in++];
        tem[5] = input[in++];

        int row = tem[0]*2 + tem[5]*1;
        int col = tem[1]*8 + tem[2]*4 + tem[3]*2 + tem[4]*1;

        if (i == 1) {
            int value = s1[row][col];
            DecToBi(value, oo);
        }
        else if (i == 2) {
            int value = s2[row][col];
            DecToBi(value, oo);
        }
        else if (i == 3) {
            int value = s3[row][col];
            DecToBi(value, oo);
        }
        else if (i == 4) {
            int value = s4[row][col];
            DecToBi(value, oo);
        }
        else if (i == 5) {
            int value = s5[row][col];
            DecToBi(value, oo);
        }
        else if (i == 6) {
            int value = s6[row][col];
            DecToBi(value, oo);
        }
        else if (i == 7) {
            int value = s7[row][col];
            DecToBi(value, oo);
        }
        else if (i == 8) {
            int value = s8[row][col];
            DecToBi(value, oo);
        }

        output[index++] = oo[0];
        output[index++] = oo[1];
        output[index++] = oo[2];
        output[index++] = oo[3];
    }
}

void Display() {
    cout << "\n\t\tOutput:";
    cout << "\n\t\t------\n";
    cout << "\t\tCipher Text:\n";
    cout << "\t\t Binary Form: ";
    for (int i=0; i<64; i++) {
        if (i!=0 && i%4==0) cout << " ";
        cout << bCT[i];
    }
    cout << "\n\t\t Hexadecimal: " << sCT << endl;
}

void DESinput() {
    printf("\n\t\tEnter Plain Text: ");     scanf("%s", inPT);
    printf("\t\tEnter  Key value: ");       scanf("%s", inKey);
}

void Copy(int input[], int output[], int SIZE) {
    for (int i=0; i<SIZE; i++) {
        output[i] = input[i];
    }
}

void DecToBi(int input, int output[]) {
    /// Assign output array as zero(0)
    for (int i=0; i<4; i++) output[i] = 0;

    int tem[4], in = 0;
    while (input != 0) {
        tem[in++] = input%2;
        input = input/2;
    }

    for (int i=0; i<in; i++) {
        output[3-i] = tem[i];
    }
}

void BinToHex(int in[], char out[]) {
    int index = 0, tem[4];
    for (int i=0; i<16; i++) {
        tem[0] = in[index++];
        tem[1] = in[index++];
        tem[2] = in[index++];
        tem[3] = in[index++];

        int value = tem[0]*8 + tem[1]*4 + tem[2]*2 + tem[3]*1;

        if (value == 0)         { out[i] = '0'; }
        else if (value == 1)    { out[i] = '1'; }
        else if (value == 2)    { out[i] = '2'; }
        else if (value == 3)    { out[i] = '3'; }
        else if (value == 4)    { out[i] = '4'; }
        else if (value == 5)    { out[i] = '5'; }
        else if (value == 6)    { out[i] = '6'; }
        else if (value == 7)    { out[i] = '7'; }
        else if (value == 8)    { out[i] = '8'; }
        else if (value == 9)    { out[i] = '9'; }
        else if (value == 10)   { out[i] = 'A'; }
        else if (value == 11)   { out[i] = 'B'; }
        else if (value == 12)   { out[i] = 'C'; }
        else if (value == 13)   { out[i] = 'D'; }
        else if (value == 14)   { out[i] = 'E'; }
        else                    { out[i] = 'F'; }
    }
    out[17] = '\0';
}

void TexToBin(char input[], int output[]) {
    /// Text into ASCII value
    int Temp[10];
    for (int i=0; i<8; i++) {
        Temp[i] = input[i];
    }

    /// ASCII value --> Binary
    int indx = 0;
    for (int i=0; i<8; i++) {
        int num = Temp[i];

        int out[8], in = 0;
        while (num != 0) {
            out[in++] = num % 2;
            num /= 2;
        }

        int Bin[8];
        for (int j=0; j<8; j++) Bin[j]=0;
        for (int j=0; j<in; j++) {
            Bin[7-j] = out[j];
        }

        for (int j=0; j<8; j++) output[indx++] = Bin[j];
    }
}


