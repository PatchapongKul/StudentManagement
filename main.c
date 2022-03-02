#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/** List of Global Variable */
COORD coord = {0,0}; /// top-left corner of window

struct Student{
    char name[50];
    char major[20];
    double gpa;
};
long int rec_size;

/**
    function : gotoxy
    @param input: x and y coordinates
    @param output: moves the cursor in specified position of console
*/
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int main()
{
    mainmenu();
    return 0;
}

void mainmenu(){
    char command;

    system("cls");
    gotoxy(20,1);
    printf("===========================================================================");
    gotoxy(39,3);
    printf("Welcome to Student Management System");
    gotoxy(20,5);
    printf("===========================================================================");
    gotoxy(39,7);
    printf("1. Add Student Profile");
    gotoxy(39,8);
    printf("2. List Student Profiles");
    gotoxy(39,9);
    printf("3. Delete Student Profile");
    gotoxy(39,10);
    printf("4. Modify Student Profile");
    gotoxy(39,11);
    printf("5. Search Student Profile");
    gotoxy(39,12);
    printf("6. Exit Program");
    gotoxy(39,16);
    printf("Enter your command: ");

    command = getche(); // Enter User Command

    switch (command){
    case '1': AddRecord();
        break;
    case '2': ListRecord();
        break;
    case '3': DeleteRecord();
        break;
    case '4': ModifyRecord();
        break;
    case '5': SearchRecord();
        break;
    case '6': exit(0);
        break;
    default:
        printf("\nInvalid Command");
    }
};

void SearchRecord(){
    struct Student student;
    FILE *fp;
    fp = fopen("StudentRecord.DAT","rb"); // original student record
    int i = 5;
    char command,name[50],major[20],std_name[50];
    double gpa;

    system("cls");
    gotoxy(20,1);
    printf("===========================================================================");
    gotoxy(47,3);
    printf("Search Student Records");
    gotoxy(20,5);
    printf("===========================================================================");

    if (fp == NULL){
        gotoxy(33,7);
        printf("The record is empty. Please add a record first.");
        getche();
        mainmenu();
        return;
    };

    gotoxy(50,7);
    printf("1. Name");
    gotoxy(50,8);
    printf("2. Major");
    gotoxy(50,9);
    printf("3. GPA");
    gotoxy(30,11);
    printf("Please Select Category to search: ");
    command = getche();

    switch(command){
        case '1':
            system("cls");
            gotoxy(20,1);
            printf("===========================================================================");
            gotoxy(47,3);
            printf("Search Student Records");
            gotoxy(20,5);
            printf("===========================================================================");
            gotoxy(39,7);
            printf("Enter the student name: ");
            fgets(name,50,stdin);
            name[strlen(name)-1] = '\0';
            printf("\n");
            while (fread(&student,sizeof(student),1,fp)==1){
                if (strcmp(name,student.name)==0){
                    printf("\t\t\t\tRecord no. %d", i/5);
                    printf("\n\t\t\t\t\tName: %s\n\t\t\t\t\tMajor: %s\n\t\t\t\t\tGPA: %.2f",student.name,student.major,student.gpa);
                    printf("\n\t\t\t---------------------------------------------------------------");
                    gotoxy(0,9+i);
                    i += 5;
                }
            };
            break;
        case '2':
            system("cls");
            gotoxy(20,1);
            printf("===========================================================================");
            gotoxy(47,3);
            printf("Search Student Records");
            gotoxy(20,5);
            printf("===========================================================================");
            gotoxy(39,7);
            printf("Enter the student major: ");
            fgets(major,20,stdin);
            major[strlen(major)-1] = '\0';
            printf("\n");
            while (fread(&student,sizeof(student),1,fp)==1){
                if (strcmp(major,student.major)==0){
                    printf("\t\t\t\tRecord no. %d", i/5);
                    printf("\n\t\t\t\t\tName: %s\n\t\t\t\t\tMajor: %s\n\t\t\t\t\tGPA: %.2f",student.name,student.major,student.gpa);
                    printf("\n\t\t\t---------------------------------------------------------------");
                    gotoxy(0,9+i);
                    i += 5;
                }
            };
            break;
        case '3':
            system("cls");
            gotoxy(20,1);
            printf("===========================================================================");
            gotoxy(47,3);
            printf("Search Student Records");
            gotoxy(20,5);
            printf("===========================================================================");
            gotoxy(50,7);
            printf("1. Greater than");
            gotoxy(50,8);
            printf("2. Less than");
            gotoxy(39,10);
            printf("Please Select Category to search: ");
            command = getche();
            gotoxy(39,12);
            printf("Enter Student GPA : ");
            scanf("%lf", &gpa);
            printf("\n");
            if (command == '1'){
                while (fread(&student,sizeof(student),1,fp)==1){
                if (student.gpa >= gpa){
                    printf("\t\t\t\tRecord no. %d", i/5);
                    printf("\n\t\t\t\t\tName: %s\n\t\t\t\t\tMajor: %s\n\t\t\t\t\tGPA: %.2f",student.name,student.major,student.gpa);
                    printf("\n\t\t\t---------------------------------------------------------------");
                    gotoxy(0,14+i);
                    i += 5;
                }};
                break;
            } else if (command == '2'){
                while (fread(&student,sizeof(student),1,fp)==1){
                if (student.gpa <= gpa){
                    printf("\t\t\t\tRecord no. %d", i/5);
                    printf("\n\t\t\t\t\tName: %s\n\t\t\t\t\tMajor: %s\n\t\t\t\t\tGPA: %.2f",student.name,student.major,student.gpa);
                    printf("\n\t\t\t---------------------------------------------------------------");
                    gotoxy(0,14+i);
                    i += 5;
                }};
                break;
            } else {
                fclose(fp);
                printf("\n\n\t\t\t\tInvalid Command");
                printf("\n\n\t\t\t\tPress any key to go to main menu .....");
                getche();
                mainmenu();
                break;
            };

        default:
            fclose(fp);
            printf("\n\n\t\t\t\tInvalid Command");
            printf("\n\n\t\t\t\tPress any key to go to main menu .....");
            getche();
            mainmenu();
            break;
    };

    fclose(fp);

    printf("\n\n\t\t\t\tPress any key to go to main menu .....");
    getche();
    mainmenu();
};

void ModifyRecord(){
    struct Student student;
    FILE *fp;
    fp = fopen("StudentRecord.DAT","rb+"); // original student record
    char name[50],major[20];
    int found = 0;
    double gpa;

    system("cls");
    gotoxy(20,1);
    printf("===========================================================================");
    gotoxy(47,3);
    printf("Modify Student Records");
    gotoxy(20,5);
    printf("===========================================================================");
    gotoxy(30,7);

    if (fp == NULL){
        gotoxy(33,7);
        printf("The record is empty. Please add a record first.");
        getche();
        mainmenu();
        return;
    };
    printf("Enter the student name to modify: ");
    fgets(name,50,stdin);
    name[strlen(name)-1] = '\0';

    while (fread(&student,sizeof(student),1,fp) == 1){
        if (strcmp(name,student.name)==0){
            found = 1;
            break;
        }
    }

    if (found == 1){
        printf("\n\n\t\t\t\tEnter new major: ");
        fgets(major,20,stdin);
        major[strlen(major)-1] = '\0';
        printf("\t\t\t\tEnter new GPA: ");
        scanf("%lf",&gpa);
        fflush(stdin);

        strcpy(student.major,major);
        student.gpa = gpa;

        fseek(fp,-sizeof(student),SEEK_CUR);
        fwrite(&student,sizeof(student),1,fp);
    } else {
        printf("No record found");
    };

    fclose(fp);

    printf("\n\n\t\t\t\tPress any key to go to main menu .....");
    getche();
    mainmenu();
};

void DeleteRecord(){
    struct Student student;
    char name[50];
    int found = 0;
    FILE *fp,*ft;

    fp = fopen("StudentRecord.DAT","rb+"); // original student record
    ft = fopen("Temp.DAT","wb"); //Temp file for deleting record

    system("cls");
    gotoxy(20,1);
    printf("===========================================================================");
    gotoxy(47,3);
    printf("Delete Student Records");
    gotoxy(20,5);
    printf("===========================================================================");
    gotoxy(30,7);

    if (fp == NULL){
        gotoxy(33,7);
        printf("The record is empty. Please add a record first.");
        getche();
        mainmenu();
        return;
    }
    printf("Enter the student name to delete: ");
    fgets(name,50,stdin);
    name[strlen(name)-1] = '\0';



    while(fread(&student,sizeof(student),1,fp)==1){
        if (strcmp(student.name,name) != 0){
            fwrite(&student,sizeof(student),1,ft);
            //fseek(ft,0,SEEK_END);
        } else {
            found = 1;
        };
    };

    fclose(fp);
    fclose(ft);
    gotoxy(30,10);
    if (remove("StudentRecord.dat")==0 && found == 1){
        printf("File is deleted.");
    } else {
        printf("Error Deleting.");
    };
    rename("Temp.DAT","StudentRecord.DAT");

    printf("\n\n\t\t\t\tPress any key to go to main menu .....");
    getche();
    mainmenu();
};

void ListRecord(){
    struct Student student;
    int i = 5;
    system("cls");
    gotoxy(20,1);
    printf("===========================================================================");
    gotoxy(47,3);
    printf("List Student Records");
    gotoxy(20,5);
    printf("===========================================================================");
    gotoxy(0,7);

    FILE *fp;
    fp = fopen("StudentRecord.dat", "rb");
    if (fp == NULL){
        gotoxy(33,7);
        printf("The record is empty. Please add a record first.");
        getche();
        mainmenu();
        return;
    };
    while(fread(&student,sizeof(student),1,fp)==1){
        printf("\t\t\t\tRecord no. %d", i/5);
        printf("\n\t\t\t\t\tName: %s\n\t\t\t\t\tMajor: %s\n\t\t\t\t\tGPA: %.2f",student.name,student.major,student.gpa);
        printf("\n\t\t\t---------------------------------------------------------------");
        gotoxy(0,7+i);
        i += 5;
    };
    fclose(fp);
    printf("\n\n\t\t\t\tPress any key to go to main menu .....");
    getche();
    mainmenu();
};

void AddRecord(){
    FILE *fp;
    fp = fopen("StudentRecord.DAT","ab");
    char confirm;
    struct Student student;

    system("cls");
    gotoxy(20,1);
    printf("===========================================================================");
    gotoxy(49,3);
    printf("Add Student Record");
    gotoxy(20,5);
    printf("===========================================================================");

    // User manually types input of each student
    gotoxy(39,7);
    printf("Enter the student name: ");
    fgets(&student.name,50,stdin);
    student.name[strlen(student.name)-1] = '\0';
    gotoxy(39,8);
    printf("Enter the student major: ");
    fgets(&student.major,20,stdin);
    student.major[strlen(student.major)-1] = '\0';
    gotoxy(39,9);
    printf("Enter the student GPA: ");
    scanf("%lf", &student.gpa);
    fflush(stdin);

    gotoxy(39,12);
    printf("Do you want to confirm? (y/n): ");
    confirm = getche();

    if (confirm == 'y'){
        fwrite(&student,sizeof(student),1,fp);
        fclose(fp);
        mainmenu();
    } else {
        fclose(fp);
        mainmenu();
    };
};
