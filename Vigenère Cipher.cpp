#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
      int count, j;
      char message[50];
      char key[20];
      printf("\nEnter Message To Encode:\t");
      fflush(stdin);
      scanf("%[^\n]s", message);
      printf("\nEnter Key:\t");
      fflush(stdin);
      scanf("%[^\n]s", key);
      int message_length = strlen(message), key_length = strlen(key);
      char temp_key[message_length], encrypted_message[message_length], decrypted_message[message_length];
      for(count = 0, j = 0; count < message_length; ++count, ++j)
      {
            if(j == key_length)
            {
                  j = 0;
            }
            temp_key[count] = key[j];
      }
      temp_key[count] = '\0';
      count = 0;
      while(count < message_length)
      {
            encrypted_message[count] = ((message[count] + temp_key[count]) % 26) + 'A';
            count = count + 1;
      }
      encrypted_message[count] = '\0';
      count = 0;
      while(count < message_length)
      {
            decrypted_message[count] = (((encrypted_message[count] - temp_key[count]) + 26) % 26) + 'A';
            count = count + 1;
      }
      decrypted_message[count] = '\0';
      printf("\n-------------------------------\n");
      printf("\nIntial String:\t%s", message);
      printf("\nKey:\t%s", key);
      printf("\nGenerated Key:\t%s", temp_key);
      printf("\nEncrypted Message:\t%s", encrypted_message);
      printf("\nDecrypted Message:\t%s", decrypted_message);
      return 0;
}
