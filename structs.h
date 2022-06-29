/* Project made by João Maçãs - 99970 
*
* Header file that includes all used libraries, constants, object structs and 
* function prototypes from all files of this project
*
*/

#ifndef AIRPORT_MANAGER_H
#define AIRPORT_MANAGER_H

/*---Libraries---*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*CONSTANTS*/

/*---Start Values*---*/

#define STARTING_DATE "01-01-2022" /* System starting date */
#define OFFSET 1 /* Used when I needed to increase 1 more byte of memory in
                arrays */

#define MAX_INPUT 65535 /* Max number of chars an input can have. */

/*---Flags---*/
/* Flags for functions to execute according to 'X' case.*/

#define V_FLAG 'v' 
#define P_FLAG 'p'
#define C_FLAG 'c'

/*---Errors---*/

#define ERR_INVALID_DATE "invalid date\n" /* Printed when dates fails test */

#define ERR_INVALID_AP_ID "invalid airport ID\n" /* Printed when ID fails test*/

#define ERR_MAX_AP "too many airports\n"/*Printed when max airports is reached*/

#define ERR_DUPLICATE_AP "duplicate airport\n"/*Printed when trying to create an 
                                                airport with another's ID*/

#define ERR_INVALID_FLIGHTCODE "invalid flight code\n"/*Printed when flight code
                                                    fails test */

#define ERR_DUPLICATE_FLIGHT "flight already exists\n"/* Printed when trying to 
                                        create a flight with another's code*/

#define ERR_MAX_FLIGHTS "too many flights\n"/*Printed when max flights is
                                             reached*/

#define ERR_INVALID_DURATION "invalid duration\n"/*Printed when duration 
                                                fails test*/

#define ERR_INVALID_CAPACITY "invalid capacity\n"/*Printed when capacity fails 
                                                test*/

#define ERR_NO_SUCH_AP "no such airport ID\n"/* Printed when an input airport
                                         ID isnt found on the airport list*/

#define ERR_INVALID_BOOKING "invalid reservation code\n" /*Printed when an input
                                            reservation code isnt valid*/

#define ERR_NO_SUCH_FLIGHT "flight does not exist\n" /*Printed when theres no
                                            flight with the user input ID*/

#define ERR_DUPLICATE_BOOKING "flight reservation already used\n"/*Printed when
                                    there's already a booking with the same ID*/

#define ERR_TOO_MANY_BOOKINGS "too many reservations\n"/* Printed when the
            booking number of people exceed the max capacity of a flight.*/

#define ERR_INVALID_PASSENGER_NUM "invalid passenger number\n"/* Printed when
                                              the number of passengers is < 0*/

#define ERR_CODE_NOT_FOUND "not found\n" /*Printed when the input code isnt 
                                     found on the flights nor the bookings*/

#define ERR_NO_MEMORY "No memory\n" /*Printed when trying to allocate more 
                                memory but there isnt enough.*/

/*---Success---*/

#define SUC_AIRPORT "airport"/* Printed when successfully creating an airport */

/*---Formats---*/

#define FORMAT_PRINT_AP "%s %s %s %d\n" /*Format for printing airports*/
#define FORMAT_INPUT "%*s%s" /*format for sscanf's of the input string*/
#define FORMAT_DATE_TEMPLATE "%d-%d-%d" /* format for dates */
#define FORMAT_HOURS_TEMPLATE "%d:%d" /* format for hours */
#define FORMAT_STRING "%s" /* format for scanf strings */
#define FORMAT_PRINT_FLIGHTS4 "%s %s %s %s\n" /* format for printing flights 
                                                with 5 parameters */

#define FORMAT_PRINT_FLIGHTS5 "%s %s %s %s %s\n" /* format for printing flights
                                                     with 5 parameters */

/*---Limit Values---*/

#define MAX_AIRPORTS 40 /* Max airport number */
#define MAX_FLIGHTS 30000 /* Max flight number */

#define AIRPORTID_LEN 3 /* Max airportID length */
#define COUNTRY_LEN 30 /* Max country name length */
#define CITY_LEN 50 /* Max city name lenght */

#define FLIGHTID_LEN 6 /* Max flightID length */
#define DATE_LEN 10 /* Max date string length */
#define HOURS_LEN 5 /* Max hours string length */

#define MAX_MINS 60 /* Max number of minutes in an hour */
#define MAX_HOURS 24 /* Max number of hours in a day */

#define FEB_DAYS 28 /* Number of days of february */
#define MIN_MONTH_DAYS 30 /*Minimum amount of days for a month except February*/
#define MAX_MONTH_DAYS 31 /*Maximum amount of days for a month */

#define MAX_MONTHS 12 /* Max number of months in a year */

#define MIN_YEAR 2022 /* Earliest year the program accepts in dates */
#define MAX_YEAR 2023 /* Oldest year the program accepts in dates */

#define MAX_DURATION 12 /* Maximum flight duration */

#define MIN_CAPACITY 10 /* Minumum fligth capacity */
#define MIN_RESERVATION_NUM 1 /*Minimum number of passengers in a booking*/

#define MIN_RESERVATIONID_LEN 10 /* Minimum length of a booking ID */

/*---Dates---*/
/* Used in return values for the function to compare dates */

#define EQUAL_DATE 0 
#define SMALLER_DATE -1
#define BIGGER_DATE 1


/*STRUCTS*/

/* Booking Object Struct */
typedef struct booking{
    char* bookingID;
    int passengerNum;
    struct booking* next;
}Booking;

/* Flight Object Struct */
typedef struct{
    char flightID[FLIGHTID_LEN+OFFSET];
    char depart[AIRPORTID_LEN+OFFSET],arrive[AIRPORTID_LEN+OFFSET];
    char date[DATE_LEN+OFFSET], hour[HOURS_LEN+OFFSET];
    char arrivingDate[DATE_LEN+OFFSET], arrivingHour[HOURS_LEN+OFFSET];
    char duration[HOURS_LEN+OFFSET];
    int maxPassengers,currPassengers;
    Booking* bookingListHead;
    int freeFlag;
}Flight;

/* Airport Object Struct */
typedef struct{
    char identifier[AIRPORTID_LEN+OFFSET];
    char country[COUNTRY_LEN+OFFSET];
    char city[CITY_LEN+OFFSET];
}Airport;



/*FUNCOES*/

/*Cases.c*/

void caseQ(Flight flightList[],int currentFlights,char* todaysDate);

int caseA(char input[],Airport list[], int current);

void caseL(char input[],Airport airportList[],int currentAirports,
            Flight flightList[],int currentFlights);

int caseV(char input[],Flight flightList[],Airport airportList[],
            int currentAirports, int currentFlights,char todaysDate[]);

void casePandC(char input[],Flight flightlist[],int currentFlights,
                Airport airportList[], int currentAirports,char flag);

char* caseT(char input[], char todaysDate[]);

void caseR(char input[],Flight flightList[],int currentFlights,char* todaysDat);

int caseE(char *input,Flight flightList[],int currentFlights);

/*checkInput.c*/

int checkDate(char date[], char todaysDate[]);

int checkHour(char hours[]);

int checkDuration(char hours[]);

int checkAirport(Airport port,Airport list[],int currentNum);

int checkFlight(Flight flight,Flight flightList[],Airport airportList[],
                int currentAirports, int currentFlights,char todaysDate[]);

int checkFlightID(char flightID[]);

int checkBookingCode(char* bookingCode);

int checkDuplicateBookingCodes(Booking* head,char* bookingCode);

int checkBooking(char* bookingCode,char* flightCode,char* date, 
                int num,Flight flightList[],int currFlights,char* todaysDate);

/*aiport.c*/

int doesAirportExist(char airportID[], Airport airportList[],
                    int currentAirports);

int createAirport(char id[],char country[],char city[],Airport list[],
                    int current);

void printAirports(Airport airportList[],int currentAirports,Flight flightList[]
                    ,int currentFlights, int flag, char *ID);

/*flights.c*/

int getFlightTotalNum(Flight list[],int currentFlights,char airportID[]);

int createFlight(char id[],char departure[],char arrive[],char date[],
        char hour[], char duration[],int maxPassengers,Airport airportList[],

Flight flightList[],int currentAirports,int currentFlights,char todaysDate[]);

void printFlights(Flight flightList[],int currentFlights,char flag);

void printAPFlightList(Flight flightlist[],int currentFlights,char ID[],
                        char flag);

Flight findFlightArrivingHour(Flight thisFlight);

int findFlight(Flight flightList[],int currentFlight,char* flightID, char* dat);



int deleteFlight(Flight flightList[],int currentFlights,int index);
int findFlightNoDate(Flight flightList[],int currentFlight,char* flightID, int index);

int deleteAllFlights(Flight flightList[],int currentFlights,char* flightID);

/*sortAlgo.c*/

int datecmp(char date1[], char date2[]);

void bubbleSortFlightDepart (Flight flightsList[],int currFlights);

void bubbleSortFlightArrive (Flight flightsList[],int currFlights);

void bubbleSortAirports (Airport airportsList[],int currAirports);

Booking* bubbleSortBooking(Booking* listHead);

Booking* swapBooking(Booking* left, Booking* right);


/*booking.c*/

Booking* createBookingEl(Booking* head,char* bookingID,int passengerNum,Flight flightList[],int currentFlights,char* todaysDate);
void printBooking(Booking* head);
Booking* deleteBooking(Booking* head,char* bookingID);
void freeAllBookings(Booking* head);
void freeBooking(Booking* current);

#endif