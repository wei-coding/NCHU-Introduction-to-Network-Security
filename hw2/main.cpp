#include <stdio.h>
#include <stdlib.h>
#include <string.h>
class Virginia_Cipher{
    private:
        char *key;
    public:
        Virginia_Cipher(char *key);
        int encrypt(const char *);
        int decrypt(const char *);
        char* converter(char *);
};
Virginia_Cipher::Virginia_Cipher(char *key){
    int i;
    this->key = key;
    this->key[strlen(this->key)-1] = '\0';
    for(i=0;i<strlen(key) - 1;i++){
        if((key[i] <= 'z' && key[i] >= 'a') || (key[i] <= 'Z' && key[i] >= 'A')){
            continue;
        }else if(((key[i] <= '9' && key[i] >= '0') || key[i] == ' ') && i == 0){
            this->key = this->converter(key);
            break;
        }else{
            fprintf(stderr,"Invalid key.\n");
            system("pause");
            exit(-1);
        }
    }
    
}
int Virginia_Cipher::encrypt(const char *plaintext){
    char *ciphertext = (char *)malloc(sizeof(char) * strlen(plaintext));
    int i;
    char base;
    for(i=0;i<strlen(plaintext) - 1;i++){
        if(plaintext[i] <= 'Z' && plaintext[i] >= 'A') base = 'A';
        else if(plaintext[i] <= 'z' && plaintext[i] >= 'a') base = 'a';
        else {
            ciphertext[i] = plaintext[i];
            continue;
        }
        ciphertext[i] = (plaintext[i] - base + this->key[i % strlen(this->key)] - base) % 26 + base;
    }
    ciphertext[i] = '\0';
    printf("Cipher text is : %s\n",ciphertext);
    return 0;
}
int Virginia_Cipher::decrypt(const char *ciphertext){
    char *plaintext = (char *)malloc(sizeof(char) * strlen(ciphertext));
    int i,temp = 0;
    char base;
    for(i=0;i<strlen(ciphertext) - 1;i++){
        if(ciphertext[i] <= 'Z' && ciphertext[i] >= 'A') base = 'A';
        else if(ciphertext[i] <= 'z' && ciphertext[i] >= 'a') base = 'a';
        else {
            plaintext[i] = ciphertext[i];
            continue;
        }
        plaintext[i] = (ciphertext[i] - this->key[i% strlen(this->key)]) % 26 + base;
    }
    plaintext[i] = '\0';
    printf("Plain text is : %s\n",plaintext);
    return 0;
}
char* Virginia_Cipher::converter(char *key){
    char *alphabet_key = (char *)malloc(sizeof(char) * 1024);
    char *alphabet = NULL;
    int key_num = 0;
    int i;
    alphabet = strtok(key," ");
    for(i = 0;alphabet != NULL;alphabet = strtok(NULL," ") , i++){
        sscanf(alphabet,"%d",&key_num);
        alphabet_key[i] = (key_num % 26) + 'a';
    }
    alphabet_key[i] = '\0';
    return alphabet_key;
}
int main(int argc, char *argv[]){
    
start:
    printf("Input some text...\n");
    char *text = (char *) malloc(sizeof(char) * 1024);
    fflush(stdin);
    fgets(text,1024, stdin);
    printf("Input the key WITHOUT ANY PUNCTUATION...Or input POSITIVE INTEGER KEY LIST with SPACE separated...\n");
    char *key = (char *) malloc(sizeof(char) * 1024);
    fgets(key,1024, stdin);
    Virginia_Cipher *vc = new Virginia_Cipher(key);
    int mode = 0;
    printf("Type 0 to enter ENCRYPT MODE, 1 to enter DECRYPT MODE: ");
    scanf("%d",&mode);
    if(mode == 0){
        vc->encrypt(text);
    }else if(mode == 1){
        vc->decrypt(text);
    }else{
        printf("mode error\n");
        goto start;
    }
    system("pause");
}