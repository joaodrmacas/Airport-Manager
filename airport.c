/* Project made by João Maçãs - 99970 
*
* Contains all functions that interacts directly with the object type Aiport
* from creating it to printing.
*
*/


#include "structs.h"

/**
 * @brief Goes through the airportList trying to find out if airportID is in
 * any airport inside the list.
 * 
 * @param airportID ID from an airport.
 * @param airportList Airport array.
 * @param currentAirports Current airports numbers.
 * @return int: 0 -> if the airport is not find.
 *              1 -> if the airport is find.
 */
int doesAirportExist(char airportID[], Airport airportList[], 
                    int currentAirports){
    int i;

    for (i=0;i<currentAirports;i++){
        if ((!strcmp(airportID,airportList[i].identifier))){
            return EXIT_FAILURE;
        }
    }
    printf("%s: %s",airportID,ERR_NO_SUCH_AP);

    return EXIT_SUCCESS;

}

/*---------------------------------------------------------------------------*/

/**
 * @brief Creates a new airport in case the parameteres pass all the tests.
 * 
 * @param id Airport ID.
 * @param country Airport Country.
 * @param city Airport City.
 * @param list Airport List.
 * @param current Current aiports number.
 * @return int new airport number
 */
int createAirport(char id[],char country[],char city[],Airport list[],
                int current){
    Airport port;
    strcpy(port.identifier,id);
    strcpy(port.country,country);
    strcpy(port.city,city);

    if (!checkAirport(port,list,current)){
        list[current] = port;
        current++;
        printf("%s %s\n",SUC_AIRPORT, port.identifier);
    }

    return current;
}

/* -----------------------------------------------------------------------*/

/**
 * @brief Prints out all airports or a specific airport (depending on the flag),
 *  as well as the number of flights departing from that airport.
 * 
 * @param airportList Airport array.
 * @param currentAirports Current number of airports.
 * @param flightList Flights array.
 * @param currentFlights Current number of flights.
 * @param flag if '0' prints all airports, if '1' prints the airport with the
 *  parameter "ID".
 * @param ID airportID of the airport to be printed.
 */
void printAirports(Airport airportList[],int currentAirports,
                    Flight flightList[],int currentFlights, int flag, char *ID){
    int i;
    int counter;

    /* Prints all airports */
    if (!flag){
        for (i=0;i<currentAirports;i++){
            counter = getFlightTotalNum(flightList,currentFlights,
                                        airportList[i].identifier);
            printf(FORMAT_PRINT_AP,airportList[i].identifier,airportList[i].city
                                    ,airportList[i].country,counter);
        }
    }
    /* Prints an the airport with the parameter ID */
    else if(flag){
        counter = getFlightTotalNum(flightList,currentFlights,ID);
        for (i=0;i<currentAirports;i++){
            if (strcmp(airportList[i].identifier,ID) == 0){
                printf(FORMAT_PRINT_AP,airportList[i].identifier,
                airportList[i].city,airportList[i].country,counter);
            }
        }
    }

    return;
}

/*-----------------------------------------------------------*/


