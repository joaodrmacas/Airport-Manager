/* Project made by João Maçãs - 99970 
*
* Only contains the main function with the input handling
*
*/

#include "structs.h"

/*
To do:
-> ponteiros em sscanfs
*/

/**
 * @brief Handles the command input from user.
 * 
 * @return int 0
 */
int main(){
    char *todaysDate;
    char input[MAX_INPUT];
    int currentAirports=0,currentFlights=0;
    Airport airportList[MAX_AIRPORTS+OFFSET];
    Flight flightList[MAX_FLIGHTS+OFFSET];

    if ((todaysDate = malloc(sizeof (char) * (DATE_LEN+OFFSET)))==NULL){
        printf(FORMAT_STRING,ERR_NO_MEMORY);
        exit(EXIT_FAILURE);
    }

    strcpy(todaysDate,STARTING_DATE);
    while(1){
        fgets(input,MAX_INPUT*sizeof(char), stdin);
        /* Handles the input according to the first letter of the string */
        switch (input[0]){
            case 'q':
            case EOF:
                caseQ(flightList,currentFlights,todaysDate);
                break;
            case 'a':
                currentAirports = caseA(input,airportList,currentAirports);
                break;
            case 'l':
                caseL(input,airportList,currentAirports,flightList,
                    currentFlights);
                break;
            case 'v':
                currentFlights = caseV(input,flightList,airportList,
                                    currentAirports,currentFlights,todaysDate);
                break;
            case 'p':
                casePandC(input,flightList,currentFlights,airportList,
                        currentAirports,P_FLAG);
                break;
            case 'c':
                casePandC(input,flightList,currentFlights,airportList,
                        currentAirports,C_FLAG);
                break;
            case 't':
                todaysDate = caseT(input,todaysDate);
                break;
            case 'r':
                caseR(input,flightList,currentFlights,todaysDate);
                break;
            case 'e':
                currentFlights = caseE(input,flightList,currentFlights);
                break;
        }
    }
    
    return EXIT_SUCCESS;
}

