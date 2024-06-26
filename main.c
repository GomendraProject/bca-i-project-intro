#include <stdio.h>
#include <stdlib.h>

struct User
{
    char username[500];
    char password[500];
};

void KeyPressPrompt()
{
    printf("Press any key to continue..");
    getch();
}


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
    KeyPressPrompt();
}

void UpdateUser()
{
    FILE *fp;
    FILE *tmp;
    struct User input, fromFile;

    // Flag to track if we have found the data
    int dataFound = 0;

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
            // Updating to 1, since we have found the data
            dataFound = 1;
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
    // If we have found the data
    if(dataFound == 1)
    {
        // Remove the original file
        remove("user.dat");
        // Rename the temp file to original file
        rename("tmp.dat", "user.dat");
        printf("Data updated. \n");
    }
    // If we did not find the data
    else
    {
        // Remove the temp file
        remove("tmp.dat");
        printf("Username not found.");
    }
    KeyPressPrompt();
}

void DeleteUser()
{
    FILE *fp;
    FILE *tmp;
    struct User input, fromFile;

    // Flag to track if we have found the data
    int dataFound = 0;

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
            // Updating to 1, since we have found the data
            dataFound = 1;
            // Deleting the data. So, no copying to temp file
        }
        // We save the data from original file to temp file
        else
        {
            fwrite(&fromFile, sizeof(fromFile), 1, tmp);
        }
    }
    fclose(fp);
    fclose(tmp);
    // If we have found the data
    if(dataFound == 1)
    {
        // Remove the original file
        remove("user.dat");
        // Rename the temp file to original file
        rename("tmp.dat", "user.dat");
        printf("Data deleted. \n");
    }
    // If we did not find the data
    else
    {
        // Remove the temp file
        remove("tmp.dat");
        printf("Username not found.");
    }
    KeyPressPrompt();
}

void Menu()
{
    int choice;
    while(1)
    {
        system("cls");
        printf("1. View Users \n");
        printf("2. Update User \n");
        printf("3. Delete User \n");
        printf("4. Exit \n");
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
            DeleteUser();
            break;
        case 4:
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
        printf("3. Exit \n");
        printf("Please input your choice: \t");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                if(Login())
                {
                    printf("Authentication successful.");
                    KeyPressPrompt();
                    Menu();
                }
                else{
                    printf("Invalid username / password");
                    KeyPressPrompt();
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

int UserNameDuplicated(char username[500])
{
    FILE *fp;
    int found = 0;
    struct User u;
    fp = fopen("user.dat", "rb");

    while(
          fread(&u, sizeof(u), 1, fp) == 1
          )
    {
        if(strcmp(u.username, username) == 0)
        {
            found = 1;
            break;
        }
    }
    fclose(fp);
    return found;
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

    if(UserNameDuplicated(u.username))
    {
        printf("Username duplicated");
        KeyPressPrompt();
        return;
    }

    fp = fopen("user.dat", "ab");

    fwrite(&u, sizeof(u), 1, fp);

    fclose(fp);

    printf("User registered!");
    KeyPressPrompt();
}

int main()
{
    StartApp();
    return 0;
}

