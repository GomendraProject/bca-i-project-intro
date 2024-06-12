#include <stdio.h>
#include <stdlib.h>

struct User
{
    char username[500];
    char password[500];
};


void ViewUserList()
{
    FILE *fp;
    struct User u;
    fp = fopen("user.dat", "rb");

    system("cls");

    printf("User List \n");
    printf("Username \t Password \n");
    printf("___________________________ \n");
    while(
          fread(&u, sizeof(u), 1, fp) == 1
          )
    {
        printf("%s \t %s \n", u.username, u.password);
    }
    fclose(fp);

    printf("Press any key to continue..");
    getch();
}

void UpdateUser()
{
    FILE *fp;
    FILE *tmp;
    struct User input, fromFile, toTempFile;
    system("cls");
    printf("Please enter the username and password \n");

    printf("Username: \t");
    scanf("%s", &input.username);

    fp = fopen("user.dat", "rb");
    tmp = fopen("tmp.dat", "wb");

    // Read all data from original file
    while(
          fread(&fromFile, sizeof(fromFile), 1, fp) == 1
          )
    {
        // If the username of data from file matches
        // We update the data and save it to temp file
        if(strcmp(fromFile.username, input.username) == 0)
        {
            printf("Input New Password: \t");
            scanf("%s", input.password);

            fwrite(&input, sizeof(input), 1, tmp);
        }
        // We save the data from original file to temp file
        else
        {
            fwrite(&fromFile, sizeof(fromFile), 1, tmp);
        }
    }
    fclose(fp);
    fclose(tmp);
    remove("user.dat");
    rename("tmp.dat", "user.dat");

    printf("Data updated. Press any key to continue..");
    getch();
}

void Menu()
{
    int choice;
    while(1)
    {
        system("cls");
        printf("1. View Users \n");
        printf("2. Update User \n");
        printf("3. Exit \n");
        printf("Please make your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            ViewUserList();
            break;
        case 2:
            UpdateUser();
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
