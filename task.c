// Task Manager Project
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 500

char tasks[max],tasksp[max],tasksc[max];

int main(int argc, char* argv[]){
    char * instruction = argv[1];

    // for no argumet
    if(argc == 1){
        printf("./task add 2 hello world  # Add a new item with priority 2 and text hello world to the list\n");
        printf("./task ls                 # Show incomplete priority list items sorted by priority in ascending order\n");
        printf("./task del NUMBER         # Delete the incomplete item with the given priority number\n");
        printf("./task done NUMBER        # Mark the incomplete item with the given priority number as complete\n");
        printf("./task help               # Show usage\n");
        printf("./task report             # Statistics\n");
    }
    // for help argumet
    else if(strcmp(instruction , "help") == 0){
        printf("./task add 2 hello world  # Add a new item with priority 2 and text hello world to the list\n");
        printf("./task ls                 # Show incomplete priority list items sorted by priority in ascending order\n");
        printf("./task del NUMBER         # Delete the incomplete item with the given priority number\n");
        printf("./task done NUMBER        # Mark the incomplete item with the given priority number as complete\n");
        printf("./task help               # Show usage\n");
        printf("./task report             # Statistics\n");        
    }

    // for the add command
    else if(strcmp(instruction , "add") == 0){
        int priority = atoi(argv[2]);
        char * task = argv[3];
        
        FILE *ptr;
        ptr = fopen("task.txt","a+");
        fprintf(ptr,"%d %s.\n",priority,task);
        fclose(ptr);

        printf("Added task: %s with priority %d\n",task,priority);
    }

    // for ls command
    else if(strcmp(instruction , "ls") == 0){
        FILE *ptr;
        char ch;
        int index = 0;

        ptr = fopen("task.txt","r");
        do{
            ch = fgetc(ptr);
            tasks[index] = ch;
            index++;
        }while(ch != EOF);
        fclose(ptr);

        printf("%s\n",tasks);
    }

    // for done command (completed tasks)
    else if(strcmp(instruction , "done") == 0){
        char num = *argv[2];
        FILE *ptr;
        int index = 0,count;
        char ch;

        ptr = fopen("task.txt","r");
        do{
            ch = fgetc(ptr);
            tasks[index] = ch;
            index++;
        }while(ch != EOF);
        fclose(ptr);

        for(int i=0;tasks[i] != EOF;i++){
            if(tasks[i] == num){
                count = i;
            }
        }

        // for genrating completed.txt
        ptr = fopen("completed.txt","a+");
        for(int i=count;tasks[i] != '\n';i++){

            if(tasks[i] == num){
                continue;
            }
            fprintf(ptr,"%c",tasks[i]);
        }
        fprintf(ptr,"\n");
        fclose(ptr);

        for(int i=count;tasks[i] != '\n';i++){
            tasks[i] = ' ';
        }

        ptr = fopen("task.txt","w");
        for(int i=0;tasks[i] != EOF;i++){
            fprintf(ptr,"%c",tasks[i]);
        }
        fclose(ptr);

        printf("Marked item as done.\n");
    }

    // for delete command (del)
    else if(strcmp(instruction , "del") == 0){
        char num = *argv[2];
        FILE *ptr;
        int index = 0,count;
        char ch;

        ptr = fopen("task.txt","r");
        do{
            ch = fgetc(ptr);
            tasks[index] = ch;
            index++;
        }while(ch != EOF);
        fclose(ptr);

        for(int i=0;tasks[i] != EOF;i++){
            if(tasks[i] == num){
                count = i;
            }
        }

        for(int i=count;tasks[i] != '\n';i++){
            tasks[i] = ' ';
        }

        ptr = fopen("task.txt","w");
        for(int i=0;tasks[i] != EOF;i++){
            fprintf(ptr,"%c",tasks[i]);
        }
        fclose(ptr);

        printf("%d item is deleted.\n",(num-48));
    }

    // for report command
    else if(strcmp(instruction , "report") == 0){

        FILE *ptr;
        int index = 0,countp = 0,countc = 0;
        char ch;

        // for counting pending tasks from task.txt
        ptr = fopen("task.txt","r");
        do{
            ch = fgetc(ptr);
            tasksp[index] = ch;
            index++;
        }while(ch != EOF);
        fclose(ptr);

        for(int i=0;tasksp[i] != EOF;i++){
            if(tasksp[i] == '.'){
                countp++;
            }
        }

        // for counting competed tasks from completed.txt
        ptr = fopen("completed.txt","r");
        do{
            ch = fgetc(ptr);
            tasksc[index] = ch;
            index++;
        }while(ch != EOF);
        fclose(ptr);

        for(int i=0;tasksc[i] != EOF;i++){
            if(tasksc[i] == '.'){
                countc++;
            }
        }

        printf("pending : %d\n\n",countp);
        printf("completed : %d\n",countc);
    }

    else{
        printf("\nInvalid command\n\n");
    }

    return 0;
}