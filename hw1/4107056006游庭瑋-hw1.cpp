#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THRESHOLD 0.65

char* text = (char*)malloc(sizeof(char)*1024);
char alphabet_upper[][2] = {"A","E","I","O","U"};
char alphabet_lower[][2] = {"a","e","i","o","u"};

int is_cipher(char* text,float threshold);
int is_ascii(char* text);
void strtoupr(char* text);
void decrypt(char* text,int key);
void encrypt(char* text,int key);

int main(){
    
start:
    printf("Input Cipher text or Plain text:\n");
    fgets(text,1024,stdin);
    //strtoupr(text);
    if(!is_ascii(text)){
        printf("Invalid text! Please input ASCII code with space only.\n");
        goto start;
    }
    printf("You typed : %s",text);
    int is_cipher_ = is_cipher(text,THRESHOLD);
    int key = 0;
    if(is_cipher_){
        printf("The system is presumed to be in DECRYPTION mode, please enter the key or enter -1 to switch to ENCRYPTION mode:");
        scanf("%d",&key);
        if(key == -1){
            printf("Has changed to ENCRYPTION mode, please enter the key:");
            scanf("%d",&key);
            encrypt(text,key);
            system("pause");
            return 0;
        }
        decrypt(text,key);
    }else{
        printf("The system is presumed to be in ENCRYPTION mode, please enter the key or enter -1 to switch to DECRYPTION mode:");
        scanf("%d",&key);
        if(key == -1){
            printf("Has changed to DECRYPTION mode, please enter the key:");
            scanf("%d",&key);
            decrypt(text,key);
            system("pause");
            return 0;
        }
        encrypt(text,key);
    }
    system("pause");
}
//檢查是不是密文
int is_cipher(char* text,float threshold){
    int total_voc = 0;
    int valid_voc = 0;
    char* voc = NULL;
    char* text_copy = (char*)malloc(sizeof(char)*1024);
    strcpy(text_copy,text);
    voc = strtok(text_copy," ");
    while(voc != NULL){
        //printf("voc = %s\n",voc);
        total_voc++;
        int i;
        for(i=0;i<5;i++){
            char* ret = strstr(voc,alphabet_upper[i]);
            if(ret != NULL){
                if(*ret == 'A' && *(ret+1) == 'A'){
                    break;
                }
                if(*ret == 'U' && *(ret+1) == 'U'){
                    break;
                }
                valid_voc++;
                break;
            }
        }
        for(i=0;i<5;i++){
            char* ret = strstr(voc,alphabet_lower[i]);
            if(ret != NULL){
                if(*ret == 'a' && *(ret+1) == 'a'){
                    break;
                }
                if(*ret == 'u' && *(ret+1) == 'u'){
                    break;
                }
                valid_voc++;
                break;
            }
        }
        voc = strtok(NULL," ");
    };
    float valid_rate = (float)valid_voc / (float)total_voc;
    printf("Valid rate = %d / %d = %.2f\n",valid_voc,total_voc,valid_rate);
    return valid_rate > threshold ? 0 : 1;
}
void decrypt(char* text,int key){
    int i;
    int tmp;
    for(i=0;i<strlen(text)-1;i++){
        if(text[i] <= 90 && text[i] >= 65){
            for(tmp = text[i] - 65 - key ; tmp<0 ; tmp+=26);
            text[i] = tmp % 26 + 65;
        }
        if(text[i] <= 122 && text[i] >= 97){
            for(tmp = text[i] - 97 - key ; tmp<0 ; tmp+=26);
            text[i] = tmp % 26 + 97;
        }
    }
    printf("%s",text);
    return;
}
void encrypt(char* text,int key){
    int i,tmp;
    for(i=0;i<strlen(text)-1;i++){
        if(text[i] <= 90 && text[i] >= 65){
            for(tmp = text[i] - 65 + key ; tmp<0 ; tmp+=26);
            text[i] = tmp % 26 + 65;
        }
        if(text[i] <= 122 && text[i] >= 97){
            for(tmp = text[i] - 97 + key ; tmp<0 ; tmp+=26);
            text[i] = tmp % 26 + 97;
        }
    }
    printf("%s",text);
    return;
}
void strtoupr(char* text){
    int i;
    for(i=0;i<strlen(text)-1;i++){
        if(text[i] != ' ')
            text[i] = text[i] & 0xDF;
    }
    return;
}
int is_ascii(char* text){
    int i = 0;
    for(i=0;i<strlen(text)-1;i++){
        //printf("%d",text[i]);
        if(text[i] == ' ') continue;
        if((text[i] <= 90 && text[i] >= 65) || (text[i] <= 122 && text[i] >= 97))
            continue;
        else return 0;
    }
    return 1;
}