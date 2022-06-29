/* Project made by João Maçãs - 99970 
*
* Contains all functions that interacts directly with the object type Flight
* from creating it to printing.
*
*/

#include "structs.h"

/**
 * @brief Get the total flights number of the airport with the ID "airportID".
 * 
 * @param list Flights array.
 * @param currentFlights Current flights number.
 * @param airportID ID of the airport which flights will be calculated.
 * @return int Total number of flights
 */
int getFlightTotalNum(Flight list[],int currentFlights,char airportID[]){
    int i, counter=0;

    for (i=0;i<currentFlights;i++){
        if((!strcmp(airportID,list[i].depart))){
            counter++;
        }
    }

    return counter;
}

/*---------------------------------------*/

/**
 * @brief Creates a new Flight in case all the parameters pass throught all the
 * tests.
 * 
 * @param id Flight code.
 * @param departure AirportID of the airport the flight will depart from.
 * @param arrive AirportID of the airport the flight will arrive on.
 * @param date Flight's date.
 * @param hour Flight's hour.
 * @param duration Flight's duration.
 * @param maxPassengers Flight's maximum capacity.
 * @param airportList Airports array.
 * @param flightList Flights array.
 * @param currentAirports Current airports number.
 * @param currentFlights Current flights number.
 * @param todaysDate System's date.
 * @return int new Flights Number
 */
int createFlight(char id[],char departure[],char arrive[],char date[],
                char hour[], char duration[],int maxPassengers,
                Airport airportList[],Flight flightList[],int currentAirports,
                int currentFlights,char todaysDate[]){
    Flight flight;
    strcpy(flight.flightID,id);
    strcpy(flight.depart,departure);
    strcpy(flight.arrive,arrive);
    strcpy(flight.date,date);
    strcpy(flight.hour,hour);
    strcpy(flight.duration,duration);
    flight.maxPassengers = maxPassengers;
    flight = findFlightArrivingHour(flight);
    flight.currPassengers = 0;
    flight.bookingListHead = NULL;
    flight.freeFlag=0;

    if (!checkFlight(flight,flightList,airportList,currentAirports,currentFlights,todaysDate)){
        flightList[currentFlights] = flight;
        currentFlights++;
    }

    return currentFlights;
}

/*-----------------------------------------*/

/**
 * @brief Prints all flights from the flightList as well as it details.
 * 
 * @param flightList FLights array.
 * @param currentFlights Current number of flights.
 * @param flag If 'p', prints according to projects' P case;
 *             If 'c', prints according to project's C case;
 */
void printFlights(Flight flightList[],int currentFlights,char flag){
    int i;

    for (i=0;i<currentFlights;i++){
        /* Prints according to project's P case */
        if (flag == P_FLAG) 
            printf(FORMAT_PRINT_FLIGHTS4, flightList[i].flightID,
                flightList[i].arrive, flightList[i].date, flightList[i].hour);
        /* Prints according to project's C case */
        else if (flag == C_FLAG)
            printf(FORMAT_PRINT_FLIGHTS4, flightList[i].flightID,flightList[i].
            depart, flightList[i].arrivingDate, flightList[i].arrivingHour);
        /* Prints according to project's V case */
        else 
            printf(FORMAT_PRINT_FLIGHTS5, flightList[i].flightID,flightList[i].
            depart, flightList[i].arrive, flightList[i].date, flightList[i].hour);
    }

    return;
}

/**
 * @brief Creates a new Flights List which contains only the flights that depart
 * on the airport with "ID" in case the flag is 'p', or contains flights that
 * arrive on the airport with "ID" in case the flag is 'c'. Sorts the flights
 * and prints them.
 * 
 * @param flightlist Flights array.
 * @param currentFlights Current number of flights.
 * @param ID Used to compare with the arrive airports ID or depart airports ID
 * @param flag if 'p' proceeds like project's P case;
 *             if 'c' proceeds like project's C case;
 */
void printAPFlightList(Flight flightlist[],int currentFlights,char ID[],
                        char flag){
    Flight airportFlights[MAX_FLIGHTS+OFFSET];
    int i;
    int len=0;

    if (flag==P_FLAG){
        /*Creates a flight array with only departure airport flights 
            and sorts it*/
        for(i=0;i<currentFlights;i++){
            if(!strcmp(flightlist[i].depart,ID)){
                airportFlights[len] = flightlist[i];
                len++;
            }
        }
        bubbleSortFlightDepart(airportFlights,len);
    }
    else if(flag==C_FLAG){
        /*Creates a flight array with only arriving airport flights 
            and sorts it*/
        for(i=0;i<currentFlights;i++){
            if(!strcmp(flightlist[i].arrive,ID)){
                airportFlights[len] = flightlist[i];
                len++;
            }
        }
        bubbleSortFlightArrive(airportFlights,len);
    }
    printFlights(airportFlights,len,flag);

    return;
}

/**
 * @brief Calculates the flight arriving date and hours for a certain flight and
 * saves it inside the Flight object.
 * 
 * @param thisFlight Flight we want to calculate arriving date and hours.
 * @return Flight Flight with arriving date and hours.
 */
Flight findFlightArrivingHour(Flight thisFlight){
    int pDay, pMonth, pYear;
    int pHour,pMinute;
    int hour,minute;
    sscanf(thisFlight.date,FORMAT_DATE_TEMPLATE, &pDay,&pMonth,&pYear);
    sscanf(thisFlight.hour, FORMAT_HOURS_TEMPLATE, &pHour,&pMinute);
    sscanf(thisFlight.duration,FORMAT_HOURS_TEMPLATE, &hour,&minute);

    pMinute+=minute;
    pHour+=hour;
    if(pMinute>=MAX_MINS) {
        pMinute-=MAX_MINS;
        pHour++;
    }
    if(pHour>=MAX_HOURS){
        pHour-=MAX_HOURS;
        pDay++;
    }

    switch (pMonth){
        case 2:
            if(pDay>FEB_DAYS){
                pDay-=FEB_DAYS;
                pMonth++;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if(pDay>MIN_MONTH_DAYS){
                pDay-=MIN_MONTH_DAYS;
                pMonth++;
            }
            break;
        default:
            if(pDay>MAX_MONTH_DAYS){
                pDay-=MAX_MONTH_DAYS;
                pMonth++;
            }
            break;
    }

    if(pMonth > MAX_MONTHS){
        pMonth-=MAX_MONTHS;
        pYear++;
    }

    sprintf(thisFlight.arrivingDate,"%02d-%02d-%02d", pDay,pMonth,pYear);
    sprintf(thisFlight.arrivingHour,"%02d:%02d", pHour,pMinute);

    return thisFlight;
}

/**
 * @brief Goes through the whole flights array looking for a flight with 
 * "flightID" as its ID in the specified date.
 * 
 * @param flightList current flights array.
 * @param currentFlight current flights number.
 * @param flightID flightID we're looking for.
 * @param date date of the flight we're looking for.
 * @return int i -> flight index in the "flightList"
 *              -1 -> if the flight is not found.
 */
int findFlight(Flight flightList[],int currentFlight,char* flightID,char* date){
    int i;
    for (i=0;i<currentFlight;i++){
        if(!strcmp(flightID,flightList[i].flightID) && 
            (!datecmp(date,flightList[i].date))){
            return i;
        }
    }
    return -1;
}

/**
 * @brief Goes through the array from the "index" flight, looking for the first
 * flight with "flightID" as its ID.
 * 
 * @param flightList current flight array.
 * @param currentFlight current flights number.
 * @param flightID flight ID we're looking for.
 * @param index index to start looking from.
 * @return int i -> flight index in "flightList";
 *              -1 -> if it doesnt find any flight.
 */
int findFlightNoDate(Flight flightList[],int currentFlight,char* flightID, int index){
    int i;
    if (currentFlight==0)
        return -1;
    else{
        for (i=index;i<currentFlight;i++){
            if(!strcmp(flightID,flightList[i].flightID)){
                return i;
            }
        }
    }
    return -1;
}

/**
 * @brief shifts all elements of the list from "index" on, and decrements the
 * flights number by one.
 * 
 * @param flightList current flights array.
 * @param currentFlights current flights number.
 * @param index index to start shifting from.
 * @return int the decremented flights number.
 */
int deleteFlight(Flight flightList[],int currentFlights,int index){
    for (;index<currentFlights;index++){
        flightList[index] = flightList[index+1];
    }
    currentFlights--;
    return currentFlights;
}