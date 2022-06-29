/* Project made by João Maçãs - 99970 
*
* Contains the functions related to all project's possible cases.
*
*/

#include "structs.h"


/**
 * @brief Exit program function, makes sure that all the allocated memmory is 
 * freed.
 * 
 * @param flightList Current flight list.
 * @param currentFlights Currnt flight number.
 * @param todaysDate Systems date.
 */
void caseQ(Flight flightList[],int currentFlights,char* todaysDate){
    int i;
    for(i=0;i<currentFlights;i++){
        if (flightList[i].freeFlag>0)
            freeAllBookings(flightList[i].bookingListHead);
    }
    free(todaysDate);
    exit(EXIT_SUCCESS);
}


/**
 * @brief Parses the input string into it respective value and is in charge of
 * the project A case.
 * 
 * @param input Command input string.
 * @param list Current airport array.
 * @param current Current airports number
 * @return int new airports number
 */
int caseA(char input[],Airport list[], int current){
    char id[AIRPORTID_LEN+OFFSET];
    char country[COUNTRY_LEN+OFFSET], city[CITY_LEN+OFFSET];
    sscanf(input,"%*s%s%s %[^\n]",id,country,city);
    current = createAirport(id,country,city,list,current);
    
    return current;
}


/**
 * @brief Is in charge of project's L case. If the input only has 'l', sorts the 
 * airport list by airport ID. Otherwise, its parses the input string to print 
 * the indicated airports in the input parameter.
 * 
 * @param input Command input string.
 * @param airportList Current airport array.
 * @param currentAirports Curremt airports number.
 * @param flightList Current flight array.
 * @param currentFlights Current flights number.
 */
void caseL(char input[],Airport airportList[],int currentAirports,
            Flight flightList[],int currentFlights){
    char *token;
    int tokenCounter = 1;

    /* Executes project's L command alone (prints AP whole list) */ 
    if ((strlen(input)) == 2){
        bubbleSortAirports(airportList,currentAirports);
        printAirports(airportList,currentAirports,flightList,currentFlights,
                        0,"");
    }
    /* Executes project's L command printing airports with an specific ID */
    else {
        /* token = airportID */
        token = strtok(input," \n");
        while (token != NULL) {
            if (tokenCounter != 1){
                doesAirportExist(token,airportList,currentAirports);
                printAirports(airportList,currentAirports,flightList,
                            currentFlights,1,token);
            }
            token = strtok(NULL, " \n");
            tokenCounter++;
        }
    }
    return;
}

/**
 * @brief Is in charge of project's V case. In case the input is only 'v', it 
 * lists all the current flights by creating order. Else, it parses the input 
 * string with the flight information.
 * 
 * @param input Command input string.
 * @param flightList Current flight array.
 * @param airportList Current airport array.
 * @param currentAirports Current airports number.
 * @param currentFlights Current flights number.
 * @param todaysDate Current system date.
 * @return int new flights number.
 */
int caseV(char input[],Flight flightList[],Airport airportList[],
        int currentAirports, int currentFlights,char todaysDate[]){
    char *token;
    int tokenCounter = 1;
    char flightID[FLIGHTID_LEN+OFFSET];
    char depart[AIRPORTID_LEN+OFFSET], arrive[AIRPORTID_LEN+OFFSET];
    char date[DATE_LEN+OFFSET], hour[HOURS_LEN+OFFSET];
    char duration[HOURS_LEN+OFFSET];
    int maxPassengers=0;

    /* Executes project's V command alone (prints flights whole list) */ 
    if ((strlen(input)) == 2)
        printFlights(flightList,currentFlights,V_FLAG);

    /* Executes project's L command creating new flights */
    else {
        token = strtok(input," \n");
        while (token != NULL) {
            switch (tokenCounter){
            case 2:
                strcpy(flightID,token);
                break;
            case 3:
                strcpy(depart,token);
                break;
            case 4:
                strcpy(arrive,token);
                break;
            case 5:
                strcpy(date,token);
                break;
            case 6:
                strcpy(hour,token);
                break;
            case 7:
                strcpy(duration,token);
                break;
            case 8:
                maxPassengers = atoi(token);
            default:
                break;
            }
            token = strtok(NULL, " \n");
            tokenCounter++;
        }

        currentFlights = createFlight(flightID,depart,arrive,date,hour,
                duration,maxPassengers,airportList,flightList,currentAirports,
                currentFlights,todaysDate);

    }

    return currentFlights;
}

/**
 * @brief Is in charge of project's P and C case. Parses the input string into
 * the selected airportID.
 * 
 * @param input Command input string.
 * @param flightlist Current flight array.
 * @param currentFlights Current flights number.
 * @param airportList Current airport array.
 * @param currentAirports Current airports number.
 * @param flag: 'c' if we its respective to case C or 'p' for P case.
 */
void casePandC(char input[],Flight flightlist[],int currentFlights,
                Airport airportList[], int currentAirports,char flag){
    char airportID[AIRPORTID_LEN+OFFSET];

    sscanf(input,FORMAT_INPUT, airportID);
    if(doesAirportExist(airportID,airportList,currentAirports))
        printAPFlightList(flightlist,currentFlights,airportID,flag);

    return;
}

/**
 * @brief Is in charge of project's T case. Fast forwards the system date,
 * maximum 1 year from current system date.
 * 
 * @param input Command input string.
 * @param todaysDate Current system date.
 * @return char* new system date.
 */
char* caseT(char input[],char *todaysDate){
    char date[DATE_LEN+OFFSET];

    sscanf(input,FORMAT_INPUT,date);
    if (checkDate(date,todaysDate)){
        printf(FORMAT_STRING, ERR_INVALID_DATE);
        return todaysDate;
    }
    strcpy(todaysDate,date);
    printf("%s\n",todaysDate);
    
    return todaysDate;
}

/**
 * @brief Is in charge of projects R case. Parses the input and also prints
 * some input errors.
 * 
 * @param input Command input string.
 * @param flightList Current flight array.
 * @param currentFlights Current flights number.
 * @param todaysDate Current systems date.
 */
void caseR(char input[],Flight flightList[],int currentFlights,char* todaysDate){
    char *token,*flightCode=NULL, *flightDate=NULL, *bookingID=NULL;
    int i=0,passengerNum=0;
    int addBookingFlag=0,tokenCounter=1;
    token = strtok(input," \n");
    while (token != NULL) {
        switch (tokenCounter){
        case 2:
            flightCode=token;
            break;
        case 3:
            flightDate=token;
            break;
        case 4:
            addBookingFlag=1;
            bookingID=token;
            break;
        case 5:
            passengerNum=atoi(token);
            break;
        }
        token = strtok(NULL, " \n");
        tokenCounter++;
    }
    i = findFlight(flightList,currentFlights,flightCode,flightDate);
    if(!addBookingFlag){
        if (i==-1){
            printf("%s: %s", flightCode, ERR_NO_SUCH_FLIGHT);
            return;
            }
        else if(checkDate(flightDate,todaysDate)){
            printf(FORMAT_STRING,ERR_INVALID_DATE);
            return;
        }
        else{
            flightList[i].bookingListHead = bubbleSortBooking(flightList[i].bookingListHead);
            printBooking(flightList[i].bookingListHead);
        }
    }
    else{
        if (!checkBooking(bookingID,flightCode,flightDate,passengerNum,flightList,currentFlights,todaysDate)){
            flightList[i].currPassengers+=passengerNum;
            flightList[i].bookingListHead = createBookingEl(flightList[i].bookingListHead,bookingID,passengerNum,flightList,currentFlights,todaysDate);
            flightList[i].freeFlag++;
        }
    }

    return;

}

/**
 * @brief Is in charge of project's E case. Checks if the input code is
 * a flight or booking code.
 * 
 * @param input Command input string.
 * @param flightList Current flights array.
 * @param currentFlights Current flights number.
 * @return the new flights number in case it removed any.
 */
int caseE(char *input,Flight flightList[],int currentFlights){
    int i=0,j=0,flag=0;
    char* code;
    Booking *aux=NULL;
    code = (char*) malloc((strlen(input)+OFFSET)*sizeof(char));
    sscanf(input,"%*c%s",code);

    /* Checks if "code" is a booking code */
    if (!checkBookingCode(code)){
        for (j=0;j<currentFlights;j++){
            aux = flightList[j].bookingListHead;
            while(aux!=NULL){
                if (!strcmp(aux->bookingID,code)){
                    flightList[j].currPassengers-=aux->passengerNum;
                    flightList[j].bookingListHead = deleteBooking(flightList[j].bookingListHead,code);
                    flightList[j].freeFlag--;
                    free(code);
                    return currentFlights;
                }
                aux = aux->next;
            }
        }
    }
    /* Checks if "code" is a flight code */
    else if(!checkFlightID(code)){
        /* while it finds flights with an ID == code, it keeps deleting them */
        while((i=findFlightNoDate(flightList,currentFlights,code,i))!=-1){
            if (flightList[i].freeFlag>0) freeAllBookings(flightList[i].bookingListHead);
            currentFlights = deleteFlight(flightList,currentFlights,i);
            if(!flag) flag++;
        }
    }
    
    /* if doesnt find any flight or code with that ID */
    if(!flag) printf(FORMAT_STRING,ERR_CODE_NOT_FOUND);
    free(code);

    return currentFlights;

}