#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct {
    char name[MAX_NAME];
    char address[100];
    char aadhaar_number[15];
    int age;
}person;

person p[TABLE_SIZE];

person * hash_table[TABLE_SIZE];

//hashing function
int hash(char * name){
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value= 0;
    for(int i=0; i<length; i++){
        hash_value+=name[i];
        hash_value=(hash_value*name[i])%TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table(){
    for(int i=0; i<TABLE_SIZE; i++){
        hash_table[i]=NULL;
    }
}

void print_table(){
    for(int i=0; i<TABLE_SIZE; i++){
        if(hash_table[i]==NULL){
            printf("%d\t---\n", i);
        }
        else{
            
            printf("%d\t%s\t\t\t", i, hash_table[i]->name);
             printf("\t%s\t\t\t", hash_table[i]->address);
              //printf("\t%s\t\t\t",  hash_table[i]->dob);
               printf("\t%s\t\t",  hash_table[i]->aadhaar_number);
                printf("\t%d\t\t\t\n",  hash_table[i]->age);
        }
    }
}

//insert into hash table
bool insert(person * p){
    if(p==NULL) 
    return false;
    int index = hash(p->name);
    {
    for(int i=0; i<TABLE_SIZE; i++){
        int try = (i+index)%TABLE_SIZE;
        if(hash_table[try]==NULL){
            hash_table[try]=p;
            return true;
        }
    }
    }
    return false;
}

//to find a person in the table by their name
person *lookup(char*name){
    int index = hash(name);
    for(int i=0; i<TABLE_SIZE; i++){
        int try = (index +i)%TABLE_SIZE;
        if(hash_table[try]!=NULL && strncmp(hash_table[try]->name, name, TABLE_SIZE)==0){
            return hash_table[try];
            
        }
    }
    return NULL;
}

person* delete_name(char*name){
    int index= hash(name);
     for(int i=0; i<TABLE_SIZE; i++){
         int try = (index +i)%TABLE_SIZE;
         if(hash_table[try]!=NULL && strncmp(hash_table[try]->name, name, TABLE_SIZE)==0){
             person * tmp = hash_table[try];
             hash_table[try]=NULL;
             return tmp;
         }
     }
  return NULL;
}

int main() {
    int i=0;
    person * pointer; 
    person* deleted_name;
    char name[TABLE_SIZE];
    int choice, ch=0;
    char c;
    init_hash_table();
    
    printf("\t\t\t---------Aadhaar card details database!--------- \n\n");
     while(ch==0){
    
    printf("1. Insert an entry \n");
    printf("2. Delete an entry \n");
    printf("3. Look for a particular entry \n");
    printf("4. Display Database\n");
    printf("5. Exit\n");
    printf("Enter your choice \n");
    
    scanf("%d", &choice);
   
    switch(choice){
        case 1:
        for(int i=0; i<10; i++){
        printf("Enter name: ");
        scanf(" %[^\n]" , p[i].name);
         printf("Enter address: ");
        scanf(" %[^\n]", p[i].address);
      
         printf("Enter Aadhaar card number: ");
        scanf(" %[^\n]", p[i].aadhaar_number);
         printf("Enter age: ");
        scanf("%d", &p[i].age);
        insert(&p[i]);
        printf("Enter another person's details? Enter Y/N \t");
        scanf(" %c", &c);
        if(c=='y'|| c=='Y'){
            continue;
        }
        else{
            break;
        }
        }
       break;
    
        case 2: {
            printf("Enter the person name to be deleted\n");
            scanf("%s",&name);
            deleted_name=delete_name(name);
            if(deleted_name==NULL)
            printf("Person not found in database! \n");
            else
            printf("The info of %s has been deleted\n",deleted_name->name);
            
            
            break;
        }
       case 3:
       {
        printf("enter the name of the person to be searched\n");
        scanf("%s",&name);
        pointer=lookup(name);
        if(pointer==NULL)
        printf("Person not found in database! \n");
        else{
        printf("The name of the person is %s\n",pointer->name);
          printf("The address of the person is %s\n",pointer->address);
         // printf("The date of birth of the person is %s\n",pointer->dob);
      printf("The aadhar number of the person is %s\n",pointer->aadhaar_number);
      printf("The age of the person is %d\n",pointer->age);
        }
        break;
        } 
       case 4 :
       {
        print_table();
        break;
       }  
       case 5:
       {
        exit(0);
        break;
       } 
    }
    
    }
    return 0;
}