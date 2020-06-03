#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void update_attandance(int);
int day_enter();
int month_enter();
int year_enter();
int is_valid_date(int ,int ,int);
int is_already_exist(int);
int main()
{
    int number_of_students=5;
    update_attandance(number_of_students);
    return 0;
}
void update_attandance(int number_of_students)
{
    int i, j, k;
    int check;
    int dd = 0, mm = 0, yyyy = 0,yyyymmdd=0;//input date
    char ch;//tmp char
    FILE *f_attendance_sheet,*f_rollno_sheet ;

    date_enter://for re-entering date

    printf("Enter the data:\n");

    dd = day_enter();
    mm = month_enter();
    yyyy = year_enter();
    // date inputed
    check=is_valid_date(dd, mm, yyyy);
    switch(check)
    {
    case -1:
        printf("\nInvalid day...\nPlease re-enter the date... ");
        getch();
        system("cls");
        goto date_enter;
    case -2:
        printf("\nInvalid month...\nPlease re-enter the date... ");
        getch();
        system("cls");
        goto date_enter;
    default:
        system("cls");
    }
    // Date part complete
    /*
    check date
    */
    printf("Attendance Update:-");
    printf("\nDate : %d / %d / %d \n\n",dd, mm, yyyy);
    yyyymmdd+=yyyy*10000;
    yyyymmdd+=mm*100;
    yyyymmdd+=dd;
    check=is_already_exist(yyyymmdd);
    if(check == 1)
    {
        printf("\nInputed date already exits\nPress 'Y' if you want to continue or Press any other key to go back");
        againgetch:
        ch=getch();
        if(ch== 13)
            goto againgetch;
        if(ch == 'y' || ch == 'Y'  && ch != 13)
        {
            system("cls");
            printf("Attendance Update:-");
            printf("\nDate : %d / %d / %d \n\n",dd, mm, yyyy);
            f_attendance_sheet=fopen("Attendance Sheet.txt","a+");
        }
        else if(ch != 13)
            exit(0);

    }
    else if(check == 0)
        f_attendance_sheet=fopen("Attendance Sheet.txt","a+");
    else if(check == 2)
        f_attendance_sheet=fopen("Attendance Sheet.txt","w");


    f_rollno_sheet=fopen("Rollno Sheet.txt","r");

    int cnt=0,tmp_roll,scaned_rollno;
    char *attendance_string=malloc(sizeof(char)*(number_of_students+1));
    char first_name[20],middle_name[20],last_name[20];
    for(cnt=0;cnt<number_of_students;cnt++)
        attendance_string[cnt]='1';
    attendance_string[cnt]='\0';
    cnt=0;
    i=0;
    printf("Enter roll number one by one.To complete enter 0 as roll number");
    while(1)
    {
        printf("\nEnter Absent Roll No.:");
        i=0;
        tmp_roll=0;
        while(1)
        {
            ch=getch();
            if(ch == 13 && i > 0)
            {
                break;
            }
            else if(ch == 8 && i>0)
            {
                while(i != 0)
                {
                    printf("\b \b");
                    i--;
                }
                tmp_roll=0;
            }
            else if( ch >= '0' && ch <= '9')
            {
                i++;
                tmp_roll*=10;
                tmp_roll+= (ch-'0');
                printf("%c",ch);
            }
        }
        if(tmp_roll == 0)
        {
            fprintf(f_attendance_sheet,"%d %s\n",yyyymmdd,attendance_string);
            printf("\nAttendance successfully updated");
            fclose(f_rollno_sheet);
            fclose(f_attendance_sheet);
            break;
        }
        cnt=1;
        while(fscanf(f_rollno_sheet,"%d %s %s %s",&scaned_rollno,middle_name,first_name,last_name) != EOF)
        {

            if(tmp_roll == scaned_rollno)
            {
                attendance_string[cnt-1]='0';
                printf("\nAttendance updated");
                break;
            }
            cnt++;

        }
        rewind(f_rollno_sheet);
        if(cnt>number_of_students)
        {
            printf("\nInvalide roll number");
        }
    }
    getch();
    free(attendance_string);
    return ;
}
/*
function to enter day...
*/
int day_enter()
{
    int i=0,dd=0;
    char ch;
    printf("Date(DD):");
    while(i <= 2)
    {
        ch=getch();
        if(i > 0 && ch == 13)
            break;
        else if(ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
            if(i == 0)
                dd = 0;
            else if(i == 1)
            {
                dd = dd / 10;
            }
        }
        else if(ch >= '0' && ch <= '9' && i < 2)
        {

            printf("%c",ch);
            if(i == 0)
                dd += (ch-48);
            else if(i == 1)
            {
                dd = dd * 10;
                dd += (ch-48);
            }
            i++;
        }
    }
    return dd;
}
/*
function to enter month...
*/
int month_enter()
{
    int i=0,mm=0;
    char ch;
    printf("\nMonth(MM):");
    while(i <= 2)
    {
        ch = getch();
        if(i > 0 && ch == 13)
            break;
        else if(ch == 8 && i > 0)
        {
            i--;
            printf("\b \b");
            if(i == 0)
                mm = 0;
            else if(i == 1)
            {
                mm = mm / 10;
            }
        }
        else if(ch >= '0' && ch <= '9' && i < 2)
        {
            if(i == 0)
                mm += (ch-48);
            else if(i == 1)
            {
                mm = mm * 10;
                mm += (ch-48);
            }
            printf("%c",ch);
            i++;
        }
    }
    return mm;
}
/*
function to enter year...
*/
int year_enter()
{
    int i=0,yyyy=0,j=1;
    char ch;
    printf("\nYear(YYYY):");
    while(i <= 4)
    {
        ch=getch();
        if(i == 4 && ch == 13)
            break;
        else if(ch==8 && i>0)
        {
            i--;
            printf("\b \b");
            if(i == 0)
                yyyy = 0;
            else
            {
                yyyy=yyyy/10;
            }
        }
        else if(ch >= '0' && ch<= '9' && i < 4)
        {
            if(i != 0)
                yyyy *= 10;
            yyyy += (ch-48);
            printf("%c",ch);
            i++;
        }
    }
    return yyyy;
}
/*
function to check date...
*/
int is_valid_date(int dd, int mm, int yyyy)
{
    int is_leap_year=0;
    if(yyyy % 4 == 0 && (yyyy % 100 != 0) || (yyyy % 400 == 0))
        is_leap_year=1;//leap year confirm
    if( mm > 0 && mm <= 12)
    {
        switch(mm)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(dd > 0 && dd <= 31)
                return 0;// Valid date...
            break;
        case 2:
            if((dd > 0 && dd <=28) || (is_leap_year && dd == 29 ))
                return 0;//Valid date...
            break;
        default:
            if(dd>0 && dd <= 30)
                return 0;//Valid date...
        }
        return -1;//Invalid day...
    }
    else
        return -2;//Invalid month...
}
int is_already_exist(int yyyymmdd)
{
    char ch,attendace[1000];
    int date;
    FILE *f_attendance_sheet;
    f_attendance_sheet=fopen("Attendance Sheet.txt","r");
    if(f_attendance_sheet == NULL)
    {
        fclose(f_attendance_sheet);
        f_attendance_sheet=fopen("Attendance Sheet.txt","w");
        fclose(f_attendance_sheet);
        return 2;
    }
    while( fscanf( f_attendance_sheet,"%d %s",&date,attendace) != EOF )
    {
        if(date == yyyymmdd)
        {
            fclose(f_attendance_sheet);
            return 1;
        }
    }
    fclose(f_attendance_sheet);
    return 0;
}
