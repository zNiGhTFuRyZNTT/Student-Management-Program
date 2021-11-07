#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <sys/stat.h>
#define MAX_OP 7

typedef struct student {
    char name[50];
    char last_name[70];
    int student_number;
    float avg;
} std;

// <- --Protos-- ->
int menu(char **ops, int size, int *std_count);
void arrowH(int realPos, int arrowPos);
void addStudent(std *students, int *pos);
void bsortDesc(struct student list[80], int s);



// <=--- Consts ---=> //
const char* filename = "students_stats.txt";

// <- --main-- ->
int main(void) {
    FILE *file;
    // char* token;
    //<=------=>
    std students[300];
    char name[512], last_name[512];
    int student_number, avg;
    int std_counter = 0;
    char *opss[] = {
    "Add Student",
    "Del Student",
    "Find Student",
    "List by Average",
    "Save to file",
    "Load from file",
    "Exit",
    };
    start:
    // printf("%s\n", opss[1]);
    while (true) {
        // temporary variables to work in different places.
        int temp3 = 0;
        int temp;
        int counter = 0;
        char tmp1[1024];
        // char* std_load_line_content[310];
        char lines2[300];

        // <---------------->

        float AVGs[300];
        int choice = menu(opss, MAX_OP, &std_counter);
        int student_counter = 0;
        char nullStr[20] = {"\0"};  // empty string to remove student
        char x = 'Y';

        switch (choice){
            case 1: // Add Student
                system("cls");
                // get deatails
                addStudent(students, &std_counter);
                // printf("%s\n", students[std_counter].name);
                std_counter++;
                goto start;
            case 2: // Del Student
                del:
                if (std_counter < 1)
                    puts("[!] You have to add at least 1 student to be able to remove.");
                printf("Enter the number of the student you want to remove:\n>> ");
                if (fgets(tmp1, sizeof(tmp1), stdin) != NULL) {
                    int test_std_number;
                    if(sscanf(tmp1, "%d", &test_std_number) == 1){
                        temp = test_std_number;
                    } else{
                        puts("Expected a number not characters! please try again.");
                        goto del;
                    }
                }
                puts("[?] Searching ...");
                for(int i = 0; i <= std_counter; i++){
                    if(students[i].student_number == temp){
                        student_counter++;
                        // <----- --- -Printing the Results- --- ----->
                        printf("Found %d result/s:\n name= %s , last name= %s, student_number= %d, average= %0.2f\n",
                        student_counter, students[i].name, students[i].last_name, students[i].student_number, students[i].avg);
                         // --------------- -------- ------ --- --- - - .
                        printf("If you want to DELETE PRESS Y/y: ");
                        temp3 = getch();
                        if (temp3 == 121 || temp3 == 89){
                            strcpy(students[i].name, nullStr); //Put null into Name
                            strcpy(students[i].last_name, nullStr); //Null into Surname
                            students[i].student_number = 0; //Null into StudentNumber
                            students[i].avg = 0; //Null into Average
                            std_counter--;
                            printf("\n[>] Student Removed.\n");
                            printf("\n[>] Press Enter to go back to Main Menu.\n");
                            getch();
                            goto start;
                        } else 
                            goto start;

                    } else {
                        printf("[!] No Students found with students number -> %d\n", temp);
                        printf("\n[>] Press Enter to go back to Main Menu.\n");
                        getch();
                        goto start;
                    }
                };
            case 3:
                find:
                if (std_counter < 1)
                puts("[!] You have to add at least 1 student to be able to remove.");
                puts("Enter the number of the student you want to find:\n>> ");
                if (fgets(tmp1, sizeof(tmp1), stdin) != NULL) {
                    int test_std_number;
                    if(sscanf(tmp1, "%d", &test_std_number) == 1){
                        temp = test_std_number;
                    } else{
                        puts("Expected a number not characters! please try again.");
                        goto find;
                    }
                }
                puts("[?] Searching ...\n");
                for(int i = 0; i < std_counter; i++){
                    if(students[i].student_number == temp){
                        student_counter++;
                        // <----- --- -Printing the Results- --- ----->
                        puts("===============================================");
                        printf("[>] Found %d Result/s:\n name= %s , last name= %s, student_number= %d, average= %0.2f\n",
                        student_counter, students[i].name, students[i].last_name, students[i].student_number, students[i].avg);
                        puts("===============================================");

                        puts("\n[>] Press Enter to keep searching or ESC go back to Main Menu.\n");
                        int key = getch();
                        if (key == 27)
                            goto start;
                        else
                            goto find;

                    } else {
                        puts("\n[!] Nothing Found, press Enter to try again or ESC to return to main menu \n");
                        int key = getch();
                        if (key == 27)
                            goto start;
                        else
                            goto find;
                    }
                    
                };
            case 4:
                bsortDesc(students, std_counter);
                for(int i = 0; i < std_counter; i++) {
                    printf("\n[>] name= %s  last name= %s student_number= %d average= %0.2f\n",students[i].name, students[i].last_name, students[i].student_number, students[i].avg);
                }
            case 5:
                file = fopen(filename, "w");
                puts("[>] Writing to file...");
                for(int i = 0; i < std_counter; i++) {
                    fprintf(file ,"%s_%s_%d_%0.2f\n", students[i].name, students[i].last_name, students[i].student_number, students[i].avg);
                }
                fclose(file);
                puts("Done.");
            case 6:
                // int count = 0;
                file = fopen(filename, "r");
                while (fgets(lines2, sizeof(lines2), file)) {
                    // counter = 0;
                    char* eptr;
                    char* token = strtok(lines2, "_");
                    strcpy(students[counter].name, token);
                    token = strtok(NULL, "_");
                    strcpy(students[counter].last_name, token);
                    token = strtok(NULL, "_");
                    students[counter].student_number = strtol(token, &eptr, 10);
                    token = strtok(NULL, "_");
                    students[counter].avg = strtof(token, &eptr);
                    counter++;
                    student_counter++;
                    std_counter++;
                    // printf("%s\n", lines2);
                }
                for(int i = 0; i < student_counter; i++) {
                    printf("[>] Added -> name: %s, last_name: %s, student_number: %d, average= %0.2f\n", students[i].name, students[i].last_name, students[i].student_number, students[i].avg);
                }
                fclose(file);
                printf("\n[>] Press Enter to go back to Main Menu.\n");
                getch();
                goto start;
            case 7:
                exit(0);

        }

    }
    return 0;
};





//-------------------------------------------------------------------------------------------------------
// <- --Functions-- ->
void addStudent(std *students, int *pos) {
    char temp[1024];
    char name[1024];
    char last_name[1024];
    unsigned long int student_number;
    float avg;
    puts("Enter student details:");
    // ============= name ===========
    printf("Name >>");
    fgets(name, 60, stdin);
    name[strlen(name) - 1] = '\0';
    printf("Last Name >>");
    fgets(last_name, 60, stdin);
    last_name[strlen(last_name) - 1] = '\0';
    tryA:
    // ------------------- Student Number Validation------------------------
    printf("Student Number >>");
    if (fgets(temp, sizeof(temp), stdin) != NULL) {
        int test_std_number;
        temp[strlen(temp) - 1] = '\0';
        if(sscanf(temp, "%d", &test_std_number) == 1){
            student_number = test_std_number;
            test_std_number = 0;
        } else{
            puts("Expected a number not characters! please try again.");
            goto tryA;
        }
    }
    for (int i = 0; i < *pos; i++) {
        if (student_number == students[i].student_number){
            puts("[!] That student number already exists, please try again!");
            goto tryA;
        }

    }
    // ----------------------------------------------------------------------
    // ------------------- Student Average Validation------------------------
    tryA2:
    printf("Average >>");
    if (fgets(temp, sizeof(temp), stdin) != NULL) {
        float test_std_number;
        if(sscanf(temp, "%f", &test_std_number) == 1){
            avg = test_std_number;
        } else{
            puts("Expected a number not characters! please try again.");
            goto tryA2;
        }
    }
    // ----------------------------------------------------------------------
    //<- -- --- add the student --- -- ->
    strcpy(students[*pos].name, name);
    strcpy(students[*pos].last_name, last_name);
    students[*pos].student_number = student_number;
    students[*pos].avg = avg;
    //<- -- --- Confirmation --- -- ->
    puts("===============================================");
    printf("[>] Student Added, name= %s, last_name=%s, student_number=%d with average of %0.2f\n",
     students[*pos].name, students[*pos].last_name, students[*pos].student_number,students[*pos].avg);
    puts("===============================================");
    //<- -- --- - --- -- ->
    printf("[>] current students = %d\n", *pos+1);
    puts("[<] Press Enter to go back to main menu");
    getch();
    // printf("%s\n", students[*pos].name);
};

int menu(char **ops, int size, int *std_count) {
    system("cls");
    int position = 1;
    int keyPressed = 0;
    // size_t size = sizeof(ops)/sizeof(ops[0]);
    while (keyPressed != 13){
    system("cls");
    puts("[!] Haji pashmat narize");
    printf("[>] Current Studends : %d\n", *std_count);
    puts("|========Select========|");
    for(int i = 0; i < size; i++){
        arrowH(i+1, position); printf(" |%s\n", ops[i]);
        
    }

    puts("|======================|");
    puts("[!] Press ESC to Exit");

    keyPressed = getch();
    if (keyPressed == 80 && position != MAX_OP){
        position ++;
    } else if (keyPressed == 72 && position != 1){
        position --;
    } else if (keyPressed == 27)
        exit(1);
    else{
        position = position;
    }
    }
    return position;
};

void arrowH(int realPos, int arrowPos) {
    if (realPos == arrowPos) {
        printf(">>");
    } else {
        printf("  ");
    }
}
void bsortDesc(struct student list[80], int s) {
    int i, j;
    struct student temp;
    
    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1-i); j++)
        {
            if (list[j].avg < list[j + 1].avg)
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            } 
        }
    }
}