#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "slre.h"
#include <winsock2.h>
#include<string.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

void registerMenu();

void signup();

void login();

void menu();

void logout();

void personalArea();

void tweetProfile();

void search();

void timeline();

void sendTweet();

void refresh();

void comment();

void like();

void changePass();

void setBio();

int server();

int check(char str[1000], char word[1000]);

void printCheck(char *s, int m, int n);

void follow();

void unfollow();

char *sendbuf = "Hi";
char *buffer;
char *message;
int counter = 1;
char string[100];
int not = 0, notRun = 0, line = 0;

int main() {
    registerMenu();
    return 0;
}

int server() {
    WSADATA wsaData;

    SOCKET SendingSocket;

    SOCKADDR_IN ServerAddr, ThisSenderInfo;

    unsigned int Port = 12345;

    int RetCode;

    int BytesSent, nlen;

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (counter == 0) {
        printf("Client: Winsock DLL status is %s.\n", wsaData.szSystemStatus);
    }

    SendingSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (SendingSocket == INVALID_SOCKET) {
        printf("Client: socket() failed! Error code: %ld\n", WSAGetLastError());

        WSACleanup();

        return -1;
    } else if (counter == 0) {
        printf("Client: socket() is OK!\n");
    }

    ServerAddr.sin_family = AF_INET;

    ServerAddr.sin_port = htons(Port);

    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    RetCode = connect(SendingSocket, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr));

    if (RetCode != 0) {
        printf("Client: connect() failed! Error code: %ld\n", WSAGetLastError());

        closesocket(SendingSocket);

        WSACleanup();

        return -1;
    } else {
        if (counter == 0) {
            printf("Client: connect() is OK, got connected...\n");

            printf("Client: Ready for sending and/or receiving data...\n");
        }
    }

    getsockname(SendingSocket, (SOCKADDR *) &ServerAddr, (int *) sizeof(ServerAddr));

    BytesSent = send(SendingSocket, sendbuf, strlen(sendbuf), 0);

    if (BytesSent == SOCKET_ERROR)

        printf("Client: send() error %ld.\n", WSAGetLastError());

    else {
        if (counter == 0) {
            printf("Client: send() is OK - bytes sent: %ld\n", BytesSent);
        }

        memset(&ThisSenderInfo, 0, sizeof(ThisSenderInfo));

        nlen = sizeof(ThisSenderInfo);

        getsockname(SendingSocket, (SOCKADDR *) &ThisSenderInfo, &nlen);
        if (counter == 0) {
            printf("Client: Those bytes represent: \"%s\"\n", sendbuf);
        }
    }

    char *buffer = malloc(1000);
    memset(buffer, 0, 1000);
    recv(SendingSocket, buffer, 999, 0);
    message = buffer;

    if (shutdown(SendingSocket, SD_SEND) != 0)
        if (counter == 0) {
            printf("Client: Well, there is something wrong with the shutdown().The error code: %ld\n",
                   WSAGetLastError());
        } else if (counter == 0) {
            printf("Client: shutdown() looks OK...\n");
        }

    if (closesocket(SendingSocket) != 0)

        printf("Client: Cannot close \"SendingSocket\" socket. Error code: %ld\n", WSAGetLastError());

    else if (counter == 0) {
        printf("Client: Closing \"SendingSocket\" socket...\n");
    }

    if (WSACleanup() != 0)

        printf("Client: WSACleanup() failed!...\n");

    else if (counter == 0) {
        printf("Client: WSACleanup() is OK...\n");
    }
    ++counter;
}

void registerMenu() {
    system("cls");
    printf("Register Menu:\n");
    printf("1. Sign Up\n");
    printf("2. Log In\n");
    int num;
    scanf("%d", &num);
    switch (num) {
        case 1:
            signup();
            break;
        case 2:
            login();
            break;
    }
}

void signup() {
    not = 0;
    system("cls");
    printf("Sign up:\n");
    printf("Username:\n");
    char username[100];
    char password[100];
    scanf("%s", password);
    printf("Password:\n");
    scanf("%s", username);
    char glue[] = "signup ";
    strcat(glue, password);
    strcat(glue, ", ");
    strcat(glue, username);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    if ('E' == string[0]) {
        ++not;
    }
    z = check(message, "}");
    z = z - 3;
    int t = check(message, "message");
    if (not != 0) {
        printCheck(message, t + 26, z);
    }
    printf("Press any key to continue...\n");
    getch();
    registerMenu();
}

void login() {
    system("cls");
    printf("Log in:\n");
    printf("Username:\n");
    char username[100];
    char password[100];
    scanf("%s", password);
    printf("Password:\n");
    scanf("%s", username);
    char glue[] = "login ";
    strcat(glue, password);
    strcat(glue, ", ");
    strcat(glue, username);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    if ('E' == string[0]) {
        z = check(message, "}");
        z = z - 3;
        int t = check(message, "message");
        printCheck(message, t + 26, z);
        if ('n' == string[9] || 'I' == string[0]) {
            printf("Press any key to continue...\n");
            getch();
            registerMenu();
        } else {
            ++notRun;
            printf("Transferring to logout page...\n");
            printf("Press any key to continue...\n");
            getch();
            logout();
        }

    } else {
        notRun = 0;
        printf("Your Authentication token:\n");
        z = check(message, "}");
        z = z - 3;
        int t = check(message, "message");
        printCheck(message, t + 26, z);
        printf("Press any key to continue...\n");
        getch();
        menu();
    }
}

void menu() {
    system("cls");
    printf("1. Timeline\n");
    printf("2. Search\n");
    printf("3. Tweet Profile\n");
    printf("4. Personal Area\n");
    printf("5. Log Out\n");
    int num;
    scanf("%d", &num);
    switch (num) {
        case 1:
            timeline();
            break;
        case 2:
            search();
            break;
        case 3:
            tweetProfile();
            break;
        case 4:
            personalArea();
            break;
        case 5:
            logout();
            break;
    }
}

void logout() {
    not = 0;
    system("cls");
    printf("Write your authentication token:\n");
    char token[100];
    scanf("%s", token);
    char glue[] = "logout ";
    strcat(glue, token);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    if ('E' == string[0]) {
        ++not;
    }
    z = check(message, "}");
    z = z - 3;
    int t = check(message, "message");
    if (not != 0) {
        printCheck(message, t + 26, z);
        printf("Press any key to continue...\n");
        getch();
        if (notRun == 0) {
            menu();
        } else {
            registerMenu();
        }
    } else {
        notRun = 0;
        printf("Press any key to exit...\n");
        getch();
    }
}

void personalArea() {
    system("cls");
    printf("1. Set Bio\n");
    printf("2. Change Password\n");
    printf("3. Home\n");
    int num;
    scanf("%d", &num);
    switch (num) {
        case 1:
            setBio();
            break;
        case 2:
            changePass();
            break;
        case 3:
            menu();
            break;
    }


}

void tweetProfile() {
    system("cls");
    printf("Write your authentication token:\n");
    char token[100];
    scanf("%s", token);
    char glue[] = "profile ";
    strcat(glue, token);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    printf("\n");
    z = check(message, "}}");
    z = z - 2;
    int t = check(message, "message");
    if ('P' == string[0]) {
        t = t + 3;
        printCheck(message, t + 26, z - 2);
    }
    if ('E' == string[0]) {
        z = check(message, "}");
        printCheck(message, t + 6, z - 4);
    }
    printf("\n");
    printf("Press any key to continue...\n");
    getch();
    menu();
}

void search() {
    system("cls");
    printf("Search a username:\n");
    char searchUsername[100];
    char token[100];
    scanf("%s", searchUsername);
    printf("Write your authentication token:\n");
    scanf("%s", token);
    system("cls");
    char glue[] = "search ";
    strcat(glue, token);
    strcat(glue, ", ");
    strcat(glue, searchUsername);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    printf("\n");
    z = check(message, "]}}");
    z = z - 1;
    int t = check(message, "message");
    if ('P' == string[0]) {
        t = t + 3;
        printCheck(message, t + 26, z - 2);
    } else {
        printCheck(message, t + 9, z - 4);
    }
    printf("\n");
    printf("Press any key to continue...\n");
    getch();
    menu();
}

void timeline() {
    system("cls");
    printf("1. Send Tweet\n");
    printf("2. Refresh\n");
    printf("3. Home\n");
    int num;
    scanf("%d", &num);
    switch (num) {
        case 1:
            sendTweet();
            break;
        case 2:
            refresh();
            break;
        case 3:
            menu();
            break;
    }

}

void sendTweet() {
    system("cls");
    char token[100];
    char tweet[1000];
    printf("Write your tweet:\n");
    scanf("%*c%[^\n]s", token);
    printf("Write your authentication token:\n");
    scanf("%s", tweet);
    char glue[] = "send tweet ";
    strcat(glue, tweet);
    strcat(glue, ", ");
    strcat(glue, token);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    z = check(message, "}");
    z = z - 3;
    int t = check(message, "message");
    if ('S' == string[0]) {
        t = t + 5;
    }
    printCheck(message, t + 26, z);
    printf("Press any key to continue...\n");
    getch();
    timeline();
}

void refresh() {
    system("cls");
    char token[100];
    printf("Write your authentication token:\n");
    scanf("%s", token);
    char glue[] = "refresh ";
    strcat(glue, token);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    line = 1;
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    z = check(message, "]}");
    z = z - 1;
    int t = check(message, "message");
    if ('L' == string[0]) {
        printCheck(message, t + 26, z - 2);
        line = 0;
        printf("\n");
        printf("1. Follow\n");
        printf("2. Unfollow\n");
        printf("3. Like!\n");
        printf("4. Comment\n");
        printf("5. Back\n");
        int num;
        scanf("%d", &num);
        switch (num) {
            case 1:
                follow();
                break;
            case 2:
                unfollow();
                break;
            case 3:
                like();
                break;
            case 4:
                comment();
                break;
            case 5:
                timeline();
                break;
        }
    } else {
        printCheck(message, t + 26, z - 2);
        line = 0;
        printf("Press any key to continue...\n");
        getch();
        timeline();
    }
}

void like() {
    printf("Tweet Number:\n");
    char tweetNum[100];
    char token[100];
    scanf("%s", tweetNum);
    printf("Write your authentication token:\n");
    scanf("%s", token);
    char glue[] = "like ";
    strcat(glue, token);
    strcat(glue, ", ");
    strcat(glue, tweetNum);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    z = check(message, "}");
    z = z - 3;
    int t = check(message, "message");
    if ('S' == string[0]) {
        t = t + 5;
    }
    printCheck(message, t + 26, z);
    printf("Press any key to continue...\n");
    getch();
    timeline();
}

void comment() {
    printf("Tweet Number:\n");
    char tweetNum[100];
    char token[100];
    scanf("%s", tweetNum);
    printf("Write your comment:\n");
    char comment[100000];
    scanf("%*c%[^\n]s", token);
    printf("Write your authentication token:\n");
    scanf("%s", comment);
    char glue[] = "comment ";
    strcat(glue, comment);
    strcat(glue, ", ");
    strcat(glue, tweetNum);
    strcat(glue, ", ");
    strcat(glue, token);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    z = check(message, "}");
    z = z - 3;
    int t = check(message, "message");
    if ('S' == string[0]) {
        t = t + 5;
    }
    printCheck(message, t + 26, z);
    printf("Press any key to continue...\n");
    getch();
    timeline();
}

void follow() {
    printf("Which user do you want to follow?:\n");
    char username[100];
    char token[100];
    scanf("%s", username);
    printf("Write your authentication token:\n");
    scanf("%s", token);
    char glue[] = "follow ";
    strcat(glue, token);
    strcat(glue, ", ");
    strcat(glue, username);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    z = check(message, "}");
    z = z - 3;
    int t = check(message, "message");
    if ('S' == string[0]) {
        t = t + 5;
    }
    printCheck(message, t + 26, z);
    int num;
    scanf("%d", &num);
    switch (num) {
        case 1:
            follow();
            break;
        case 2:
            unfollow();
            break;
        case 3:
            like();
            break;
        case 4:
            comment();
            break;
        case 5:
            timeline();
            break;
    }
}

void unfollow() {
    printf("Which user do you want to unfollow?:\n");
    char username[100];
    char token[100];
    scanf("%s", username);
    printf("Write your authentication token:\n");
    scanf("%s", token);
    char glue[] = "unfollow ";
    strcat(glue, token);
    strcat(glue, ", ");
    strcat(glue, username);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    z = check(message, "}");
    z = z - 3;
    int t = check(message, "message");
    if ('S' == string[0]) {
        t = t + 5;
    }
    printCheck(message, t + 26, z);
    int num;
    scanf("%d", &num);
    switch (num) {
        case 1:
            follow();
            break;
        case 2:
            unfollow();
            break;
        case 3:
            like();
            break;
        case 4:
            comment();
            break;
        case 5:
            timeline();
            break;
    }
}

void changePass() {
    system("cls");
    char token[100];
    printf("Previous password:\n");
    char previousPassword[100];
    scanf("%s", previousPassword);
    printf("New password:\n");
    char password[100];
    scanf("%s", token);
    printf("Write your authentication token:\n");
    scanf("%s", password);
    char glue[] = "change password ";
    strcat(glue, password);
    strcat(glue, ", ");
    strcat(glue, previousPassword);
    strcat(glue, ", ");
    strcat(glue, token);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    z = check(message, "}");
    z = z - 3;
    int t = check(message, "message");
    if ('S' == string[0]) {
        t = t + 5;
    }
    printCheck(message, t + 26, z);
    printf("Press any key to continue...\n");
    getch();
    personalArea();

}

void setBio() {
    system("cls");
    printf("Set your bio:\n");
    char bio[100000];
    char token[100];
    scanf("%*c%[^\n]s", bio);
    printf("Write your authentication token:\n");
    scanf("%s", token);
    char glue[] = "set bio ";
    strcat(glue, token);
    strcat(glue, ", ");
    strcat(glue, bio);
    strcat(glue, "\n");
    sendbuf = glue;
    server();
    int z = check(message, ",");
    z = z - 3;
    printCheck(message, 9, z);
    z = check(message, "}");
    z = z - 3;
    int t = check(message, "message");
    if ('S' == string[0]) {
        t = t + 5;
    }
    printCheck(message, t + 26, z);
    printf("Press any key to continue...\n");
    getch();
    personalArea();
}

int check(char str[], char word[]) {
    int i, j, Flag;
    i = 0;

    while (str[i] != '\0') {
        if (str[i] == word[0]) {
            Flag = 1;
            j = 0;
            while (word[j] != '\0') {
                if (str[i + j] != word[j]) {
                    Flag = 0;
                    break;
                }
                j++;
            }
        }
        if (Flag == 1) {
            break;
        }
        i++;
    }
    if (Flag == 0) {}
    else {
        return i + 1;
    }
}

void printCheck(char *s, int m, int n) {
    int i = 0;
    for (int c = m; c <= n; c++) {
        if (s[c] == ',') {
            printf("\n\n");
        }
        if (line == 1 && s[c] == 'i' && s[c + 1] == 'd' && s[c + 2] == '\"') {
            printf("\n-------------\n");
        }
        if (s[c] != ',' && s[c] != '\"') {
            printf("%c", s[c]);
        }
        string[i] = s[c];
        ++i;
        if (c == n) {
            printf("\n");
        }
    }
}