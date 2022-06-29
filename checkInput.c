/* Project made by João Maçãs - 99970 
*
* Contains all the functions that will test all the input data raising an error
* onto the stdout if any of those tests fail.
*
*/

#include "structs.h"

/**
 * @brief Checks if the parameteres data is accepted by the program (passing 
 * certain tests), generating an error and printing it to the stdout in case 
 * it doesn't.
 * 
 * @param date Date that will be tested.
 * @param todaysDate Systems date.
 * @return int: 0 -> if passes all tests;
 *              1 -> if fails any test;
 */
int checkDate(char date[], char todaysDate[]){
    int day,month,year;
    int pday,pmonth,pyear;
    int dateLen = strlen(date);

    if (dateLen<0 || dateLen>(DATE_LEN))
        return EXIT_FAILURE;

    sscanf(date,FORMAT_DATE_TEMPLATE,&day,&month,&year); 
    sscanf(todaysDate,FORMAT_DATE_TEMPLATE,&pday,&pmonth,&pyear);

    if(year>MAX_YEAR || year<MIN_YEAR)
        return EXIT_FAILURE;

    /* Checks if the date is in the past */
    else if (year == pyear){
        if (month < pmonth) 
            return EXIT_FAILURE;
        else if (month == pmonth)
            if (day < pday) 
                return EXIT_FAILURE;
    }
    
    /* Checks if the date is more than a year in the future */
    else if (year > pyear) {
        if (month > pmonth) 
            return EXIT_FAILURE;
        else if (month == pmonth)
            if (day > pday) 
                return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/**
 * @brief Checks if the parameter "hours" is accepted by the program (passing
 * certain tests) generating an error and printing it to the stdout in case it
 * doesn't.
 * 
 * @param hours Hours that will be tested.
 * @return int: 0 -> If passes all tests;
 *              1 -> If fails any test.
 */
int checkHour(char hours[]){
    int hour,minute;

    if (strlen(hours)>(HOURS_LEN)) 
        return EXIT_FAILURE;
    else if (sscanf(hours,FORMAT_HOURS_TEMPLATE, &hour, &minute) != 2) 
        return EXIT_FAILURE;
    else if (hour<0 || hour>MAX_HOURS-OFFSET || minute<0 || 
        minute>MAX_MINS-OFFSET) 
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/**
 * @brief Checks if the parameter "hours" is accepted by the program (passing
 * certain tests) generating an error and printing it to the stdout in case it
 * doesn't.
 * 
 * @param hours Duration that will be tested.
 * @return int: 0 -> If passes all tests;
 *              1 -> If fails any test.
 */
int checkDuration(char hours[]){
    int hour,minutes;

    sscanf(hours,FORMAT_HOURS_TEMPLATE, &hour, &minutes);
    if((hour>MAX_DURATION)||(hour==MAX_DURATION && minutes>0)) 
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/**
 * @brief Checks if the parameter "port" is accepted by the program (passing
 * certain tests) generating an error and printing it to the stdout in case it
 * doesn't.
 * 
 * @param port Airport that will be tested.
 * @param list Aiports array.
 * @param currentNum Current airports number.
 * 
 * @return int: 0 -> If passes all tests;
 *              1 -> If fails any test.
 */
int checkAirport(Airport port, Airport list[],int currentNum){
    int i;

    if((strlen(port.identifier))!=AIRPORTID_LEN){
        printf(FORMAT_STRING,ERR_INVALID_AP_ID);
        return EXIT_FAILURE;
    }

    /* Checks if ID is all capital letters */
    for (i=0;i<AIRPORTID_LEN;i++){
        if(!(port.identifier[i]>='A' && port.identifier[i]<='Z')){
            printf(FORMAT_STRING,ERR_INVALID_AP_ID);
            return EXIT_FAILURE;
        }
    }

    if (currentNum>=MAX_AIRPORTS){
        printf(FORMAT_STRING,ERR_MAX_AP);
        return EXIT_FAILURE;
    }
    
    /* Checks if there's already an airport with the ID */
    for (i=0; i<currentNum; i++){
        if (!strcmp(list[i].identifier,port.identifier)){
            printf(FORMAT_STRING,ERR_DUPLICATE_AP);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Checks if the parameter "flight" is accepted by the program (passing
 * certain tests) generating an error and printing it to the stdout in case it
 * doesn't.
 * 
 * @param flight Flight that will be tested.
 * @param flightList Flight array.
 * @param airportList Airport array.
 * @param currentAirports Current airports number.
 * @param currentFlights Current flights number.
 * @param todaysDate System's date.
 * @return int: 0 -> If passes all tests;
 *              1 -> If fails any test;
 */
int checkFlight(Flight flight,Flight flightList[],Airport airportList[],
                int currentAirports, int currentFlights,char todaysDate[]){
    int i;

    if (checkFlightID(flight.flightID)){
        printf(FORMAT_STRING,ERR_INVALID_FLIGHTCODE);
        return EXIT_FAILURE;
    }

    /* Checks if there's already a flight with the given code on the same day */
    for (i=0;i<currentFlights;i++){
        if( (!strcmp(flightList[i].flightID,flight.flightID)) && 
            (!strcmp(flightList[i].date,flight.date)) ){
            printf(FORMAT_STRING,ERR_DUPLICATE_FLIGHT);
            return EXIT_FAILURE;
        }
    }

    if((!doesAirportExist(flight.arrive,airportList,currentAirports)) ||
     (!doesAirportExist(flight.depart,airportList,currentAirports))) 
        return EXIT_FAILURE;

    else if(currentFlights>=MAX_FLIGHTS){
        printf(FORMAT_STRING,ERR_MAX_FLIGHTS);
        return EXIT_FAILURE;
    }

    else if(checkDate(flight.date,todaysDate)){
        printf(FORMAT_STRING,ERR_INVALID_DATE);
        return EXIT_FAILURE;
    }

    else if(checkHour(flight.duration) || checkDuration(flight.duration)){
        printf(FORMAT_STRING,ERR_INVALID_DURATION);
        return EXIT_FAILURE;
    }

    else if(flight.maxPassengers<MIN_CAPACITY){
        printf(FORMAT_STRING, ERR_INVALID_CAPACITY);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Checks if the parameter "flightID" is accepted by the program (passing
 * certain tests) generating an error and printing it to the stdout in case it
 * doesn't.
 * 
 * @param flightID ID from a flight that will be tested.
 * @return int 0 -> If passes all tests;
 *              1 -> If fails any test;
 */
int checkFlightID(char flightID[]){
    int i;
    int len;
    len = strlen(flightID);
    if(len>FLIGHTID_LEN || len<=0)
        return EXIT_FAILURE;

    /*Checks if the first 2 are capital letter and the rest is a number between
        1 and 4 characters */
    for (i=0;i<len;i++){
        switch (i){
        case 0:
        case 1:
            if(!(flightID[i]>='A' && flightID[i]<='Z'))
                return EXIT_FAILURE;
            break;
        default:
            if(!(flightID[i]>='0' && flightID[i]<='9'))
                return EXIT_FAILURE;
            break;
        }
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Checks if "bookingCode" passes all necessary tests to be considered an
 * actual booking code according to the project.
 * 
 * @param bookingCode Code gotten from input.
 * @return int 0 -> If passes all tests;
 *          int 1 -> if fails any test;
 */
int checkBookingCode(char* bookingCode){
    int len,i;
    len = strlen(bookingCode);

    if (len<MIN_RESERVATIONID_LEN)
        return EXIT_FAILURE;

    for (i=0; i<len;i++){
        if (!(bookingCode[i]>='0' && bookingCode[i]<='9') &&
            !(bookingCode[i]>='A' && bookingCode[i]<='Z'))
            return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

/**
 * @brief Goes through a booking list to see if there's any code with the same
 * name as the parameter "bookingCode".
 * 
 * @param head first element of a booking linked list.
 * @param bookingCode string we're looking for in the list.
 * @return int 0 -> if there is no duplicate.
 *          int 1 -> if it finds a duplicate.
 */
int checkDuplicateBookingCodes(Booking* head,char* bookingCode){
    
    while (head!=NULL)
    {
        if (!strcmp(head->bookingID,bookingCode))
            return EXIT_FAILURE;
        head=head->next;
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Checks if the booking that user has input, passes all necessary tests
 * to be valid. Prints an error message if its not possible to create the 
 * booking.
 * 
 * @param bookingCode booking code from the input.
 * @param flightCode flight code from the input.
 * @param date date from the input.
 * @param num number of people in the booking from the input.
 * @param flightList current flight array.
 * @param currFlights current flights number.
 * @param todaysDate current systems date.
 * @return int 0 -> if the booking is valid and can be created.
 *              1 -> if it fails any of the tests.
 */
int checkBooking(char* bookingCode,char* flightCode,char* date, int num,Flight flightList[],int currFlights,char* todaysDate){
    int i,j;
    if (checkBookingCode(bookingCode)){
        printf(FORMAT_STRING,ERR_INVALID_BOOKING);
        return EXIT_FAILURE;
    }

    else if((i = findFlight(flightList,currFlights,flightCode,date))==-1){
        printf("%s: %s",flightCode,ERR_NO_SUCH_FLIGHT);
        return EXIT_FAILURE;
    }
    
    /*Checks all the flights for a duplicate of "bookingCode"*/
    for (j=0; j<currFlights; j++){
        if (checkDuplicateBookingCodes(flightList[j].bookingListHead,bookingCode)){
            printf("%s: %s",bookingCode,ERR_DUPLICATE_BOOKING);
            return EXIT_FAILURE;
        }
    }
    
    if(flightList[i].currPassengers+num>flightList[i].maxPassengers){
        printf(FORMAT_STRING,ERR_TOO_MANY_BOOKINGS);
        return EXIT_FAILURE;
    }

    else if(checkDate(date,todaysDate)){
        printf(FORMAT_STRING,ERR_INVALID_DATE);
        return EXIT_FAILURE;
    }

    else if(num<MIN_RESERVATION_NUM){
        printf(FORMAT_STRING,ERR_INVALID_PASSENGER_NUM);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
