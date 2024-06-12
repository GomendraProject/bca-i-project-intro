#include <stdio.h>
#include <stdlib.h>

void PerformAdd()
{
    printf("Input first: ");
    printf("Input first: ");
    printf("Input first: ");
    printf("Input first: ");
    printf("Input first: ");
}

void Menu()
{
    int choice;
    while(1)
    {
        system("cls");
        printf("1. Add \n");
        printf("2. Divide \n");
        printf("1. Exit \n");
        printf("Please make your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            PerformAdd();
            break;
        case 2:
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice");
        }
    }
}

void StartApp()
{
    while(1)
    {
        int choice;
        system("cls");
        printf("Login to proceed \n");
        printf("1. Login \n");
        printf("2. Register \n");
        printf("1. Exit \n");
        printf("Please input your choice: \t");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                if(Login())
                {
                    printf("Authentication successful. Press any key to continue..");
                    getch();
                    Menu();
                }
                else{
                    printf("Invalid username / password. Press any key to continue..");
                    getch();
                }
                break;
            case 2:
                Register();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice");
        }
    }
}

struct User
{
    char username[500];
    char password[500];
};

int Login()
{
    char username[500], password[500];
    struct User u;
    FILE * fp;
    system("cls");
    printf("Login: Please enter your username and password \n");
    printf("Username: \t");
    scanf("%s", &username);
    printf("Password: \t");
    scanf("%s", &password);

    fp = fopen("user.dat", "rb");

    while(
          fread(&u, sizeof(u), 1, fp) == 1
          )
    {
        if(
           strcmp(username, u.username) == 0
           && strcmp(password, u.password) == 0
           )
        {
           fclose(fp);
           return 1;
        }
    }
    fclose(fp);
    return 0;
}

void Register()
{
    FILE *fp;
    struct User u;
    system("cls");
    printf("Please enter your username and password \n");
    printf("Username: \t");
    scanf("%s", &u.username);
    printf("Password: \t");
    scanf("%s", &u.password);

    fp = fopen("user.dat", "ab");

    fwrite(&u, sizeof(u), 1, fp);

    fclose(fp);

    printf("User registered! Press any key to continue..");
    getch();
}

int main()
{
    StartApp();
    return 0;
}
