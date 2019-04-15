#include <stdlib.h>                                                             // All the used libraries
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>

/*                                                                              // Docstring
Project:
Cinema Booker - Assignment 1

Date Last Edited:
4/12/2018

Description:
A program for a Cinema/Theatre
company to store information
about seats.
*/

struct seatStruct                                                               // Structure to store type of seat -
{                                                                               // and owner
    char
    owner[50],
    type;
}; struct seatStruct seats[15][20];

void nullify()
{
    int
    i, t;

    for(i = 0; i < 15; i++)                                                     // Nullifies seats array
    {
        for(t = 0; t < 20; t++)
        {
              strcpy(seats[i][t].owner, "NONE\0");                              // Makes default owner to equal -
              seats[i][t].type = '~';                                           // none
        }
    }
}
bool book(int numOfAdults, int numOfChildren, char name[50])                    // Booking algorithm, called -
{                                                                               // inside of bookTickets()
    int
    i, t, m,
    totalSeats = numOfAdults + numOfChildren,
    consec = 0,
    bookOnRow,
    startingPoint,
    endPoint;

    bool
    found = false;

    for(i = 0; i < 15; i++, consec = 0)                                         // Loops through Y values of -
    {                                                                           // 2D array
        for(t = 0; t < 20; t++)                                                 // Loops X values
        {
            if(seats[i][t].type == '~')                                         // If empty seat is found, recorded
                consec++;
            else
                consec = 0;
            if(consec >= totalSeats)                                            // If there are enough available seats
            {
                bookOnRow = i;
                endPoint = t;
                for(m = 0; m < totalSeats; m++)                                 // Changes all the seats to be taken
                {
                    if(m >= numOfAdults)
                        seats[i][t - m].type = 'C';
                    else
                        seats[i][t - m].type = 'A';
                    strcpy(seats[i][t - m].owner, name);                        // Documents owner under the seat
                    if(m == totalSeats - 1)
                        startingPoint = t - m;
                }
                found = true;                                                   // Now booked, found seats is true
                break;
            }
        }
        if(found)                                                               // Breaks out to stop the loop
            break;
    }
    if(!found)
        printf("\nThese seats can not be placed together! Try booking separately!\n");
    else
    {
        printf("\nYou have seat(s): %c%d -> %c%d", startingPoint + 65, bookOnRow + 1,
        endPoint + 65, bookOnRow + 1);
    }
    return found;
}

int bookTickets(int totalTickets)                                               // Function to book tickets
{
    char
    underName[50];

    int
    numAdultTickets,
    numChildTickets;

    float                                                                       // Sets prices
    adultFullPrice = 15.00,
    childFullPrice = 7.50;

    bool
    validSeats = false,
    bookingSuccess;
    
    while(!validSeats)
    {
        printf("Surname to book under: ");                                          // Gets name to book seats under
        scanf("%s", underName);
    
        printf("Number of adult tickets to book?: ");                               // Gets the amount of adult tickets -
        fflush(stdin);                                                              // to book, then calculates price
        scanf("%d", &numAdultTickets);
        if(numAdultTickets > 0)
            adultFullPrice *= numAdultTickets;
        else
            adultFullPrice = 0;
    
        printf("Number of child/senior tickets to book?: ");                        // Gets amount of child/senior tickets -
        fflush(stdin);                                                              // to book, calculates price
        scanf("%d", &numChildTickets);
        if(numChildTickets > 0)
            childFullPrice *= numChildTickets;
        else
            childFullPrice = 0;
            
        if(numAdultTickets > 20 || numAdultTickets < 0 ||
        numChildTickets > 20 || numChildTickets < 0 ||
        numChildTickets + numAdultTickets < 1)
        {
            system("cls");
            printf("\nPlease enter values that add up to maximum 20 or minimum 1...\n\n");
            continue;
        }
        validSeats = true;
    }

    bookingSuccess = book(numAdultTickets, numChildTickets, underName);         // Booking success will return true -
                                                                                // if it is successfully booked
    if(bookingSuccess)
    {
        printf("\nYou have ticket number(s) %d -> %d!\n", totalTickets + 1,     // Just a large print statement -
        totalTickets + numAdultTickets + numChildTickets);                      // summarises prices

        printf("\nChild/Senior tickes booked: %d for %c%g each(%c%g total)\n\
Adult tickets booked: %d for %c%g each(%c%g total)\n\nGrand Total: %c%.2f\n", numChildTickets, 156, 7.50, 156, childFullPrice,
        numAdultTickets, 156, 15.00, 156, adultFullPrice, 156, adultFullPrice + childFullPrice);

        printf("\nPress any key to continue...");
        getch();
        system("cls");
        return numAdultTickets + numChildTickets;                               // Returns total amount of tickets -
    }                                                                           // for keeping total ticket count
    return 0;
}

void viewTickets()                                                              // Function to view tickets
{
    int
    i, t;

    for(i = 0; i < 20; i++)
        printf("%c ", 65 + i);                                                  // Prints out letters for index
    printf("\n");

    for(i = 0; i < 40; i++)
        printf("_");                                                            // For spacing prints "_"x40
    printf("\n");

    for(i = 0; i < 15; i++, printf("\n"))                                       // Runs through the array and -
    {                                                                           // prints it out
        for(t = 0; t < 20; t++)
        {
            if(t == 19)
                printf("%c", seats[i][t].type);                                 // If end dont print a space at the end
            else                                                                // -
                printf("%c ", seats[i][t].type);                                // Else do do that
        }
        printf("| %d", i + 1);
    }
}

void seeOwnerSeat()                                                             // See the owner of a specific -
{                                                                               // seat
    char
    xIndexChar;

    int
    xIndexInt,
    yIndexInt;

    printf("Enter the seat ID(A1, B6, F7 format): ");                                   // Reads the index that the user -
    fflush(stdin);                                                              // wishes to know the owner of
    scanf("%c%d", &xIndexChar, &yIndexInt);
    xIndexChar = toupper(xIndexChar);
    xIndexInt = (int)xIndexChar - 65;                                           // Converts from human values into -
    yIndexInt--;                                                                // array indexes
    
    if (yIndexInt >= 15 || xIndexInt >= 20)
    {
        printf("Invalid reference!\n");
        return;
    }

    printf("%s owns this seat!\n", seats[yIndexInt][xIndexInt].owner);
}

void writeArrFile()
{
     int
     i, t;

     FILE                                                                       // File pointer vars
     *ownerList,
     *seatAval;

     ownerList = fopen("ownerList.txt", "w");
     seatAval = fopen("seatAval.txt", "w");                                     // Re-writes file fully

     for(i = 0; i < 15; i++, fprintf(ownerList, "\n"))
     {
        for(t = 0; t < 20; t++)
            fprintf(ownerList, "%s ", seats[i][t].owner);                       // Write owners
     }

     for(i = 0; i < 15; i++, fprintf(seatAval, "\n"))
     {
        for(t = 0; t < 20; t++)
            fprintf(seatAval, "%c", seats[i][t].type);                          // Writes seat types
     }
}

void readArrFile()
{
    int
    i, t;

    FILE                                                                        // File pointer vars
    *ownerList,
    *seatAval;

    ownerList = fopen("ownerList.txt", "r");
    seatAval = fopen("seatAval.txt", "r");                                      // Opens the 2 files

    for(i = 0; i < 15; i++)
    {
        for(t = 0; t < 20; t++)
            fscanf(ownerList, "%s ", seats[i][t].owner);                        // Loads the owners
    }

    for(i = 0; i < 15; i++, fscanf(seatAval, "\n"))                             // Goes to next line
    {
        for(t = 0; t < 20; t++)
            fscanf(seatAval, "%c", &seats[i][t].type);                          // Gets all seats types
    }
}

int loadTicketsBooked()
{
    int
    ticketNum = 0,
    i, t;

    for(i = 0; i < 15; i++)
    {
        for(t = 0; t < 20; t++)
        {
            if(seats[i][t].type != '~')                                         // Counts the amount of -
                ticketNum++;                                                    // tickets booked
        }
    }
    return ticketNum;
}

int main()                                                                      // Main functions, called on -
{                                                                               // initialisation
    int
    ticketsBooked = 0,
    choice = 0;

    char
    answer;

    FILE
    *fileExist1,
    *fileExist2;                                                                // Declares file pointers

    bool
    exit = false;

    nullify();                                                                  // Nullifys seats[][]

    printf("What You Need To Know:\n\n\
    Type the number of the thing you would like to do\n\n\
    Follow the simple instructions to fully complete\n\n\
    Make sure to ALWAYS exit using the main menu\n\n");
    printf("\nPress any key to continue...");
    getch();
    system("cls");

    if((fileExist1 = fopen("ownerList.txt", "r")))
    {                                                                           // If the files exist -
        if((fileExist2 = fopen("seatAval.txt", "r")))                           // load them
        {
            readArrFile();
            printf("Files loaded successfully...\n");
            ticketsBooked = loadTicketsBooked();                                // Tickets booked is found
        }
    }

    while(!exit)
    {
        printf("\nWelcome!\nTickets booked: %d\n\n", ticketsBooked);
                                                                                // Asks user what to do
        printf("1: Book Tickets\n2: View Tickets\n3: See Seat Owner\n4: Delete Seat Data\n5: Exit\n> ");
        fflush(stdin);
        scanf("%d", &choice);
        system("cls");

        switch(choice)                                                          // Switch statement to call the correct -
        {                                                                       // function for the users choice
            case 1:
                ticketsBooked += bookTickets(ticketsBooked);
                break;
            case 2:
                viewTickets();
                break;
            case 3:
                seeOwnerSeat();
                break;
            case 4:
                printf("Are you sure you want to delete ALL seat data?(Y/N): ");
                fflush(stdin);
                scanf("%c", &answer);                                           // Verifys that user wants to delete data
                answer = toupper(answer);
                system("cls");
                if(answer == 'Y')
                {
                    nullify();
                    ticketsBooked = 0;                                          // If yes, data wiped
                    printf("Seat data deleted!\n");
                }
                break;
            case 5:
                exit = true;
                writeArrFile();
                break;
            default:                                                            // If invalid option is selected
                printf("That is not a valid option! Please enter a number between 1-5\n");
                break;
        }
    }
    return 0;
} 
