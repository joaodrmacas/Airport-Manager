/* Project made by João Maçãs - 99970 
*
* Contains all functions that sort an object type array as well as a function
* to comparate dates to be able to sort flights.
*
*/

#include "structs.h"

/**
 * @brief Compares 2 dates, returning different values according to their value.
 * 
 * @param date1 First Date.
 * @param date2 Second Date.
 * @return int: 0 if the dates are the same;
 *              1 if date1 is bigger than date2;
 *              -1 if date1 is smaller than date2.
 */
int datecmp(char date1[], char date2[]){
    int day1,month1,year1;
    int day2,month2,year2;

    sscanf(date1,"%d-%d-%d",&day1,&month1,&year1); 
    sscanf(date2,"%d-%d-%d",&day2,&month2,&year2);

    if (year1==year2 && month1==month2 && day1==day2) return EQUAL_DATE;

    if (year1<year2) return SMALLER_DATE;
    else if (year1==year2){
        if (month1<month2) return SMALLER_DATE;
        else if(month1==month2)
            if (day1<day2) return SMALLER_DATE;
    }

    return BIGGER_DATE;
}

/**
 * @brief Bubble sorts a flight list according to their flight depart date and 
 * hour from earliest to oldest.
 * 
 * @param flightsList Flights array.
 * @param currFlights Current flights number.
 */
void bubbleSortFlightDepart (Flight flightsList[],int currFlights){
    int i=0,j;
    int swapped=0;
    Flight Temp;

    do{
        swapped = 0;
        for (j=0; j<(currFlights-1-i);j++){
            if(datecmp(flightsList[j].date,flightsList[j+OFFSET].date)>0){
                Temp = flightsList[j];
                flightsList[j] = flightsList[j+OFFSET];
                flightsList[j+OFFSET] = Temp;
                swapped=1;
            }
            else if( (!datecmp(flightsList[j].date,flightsList[j+OFFSET].date))
                    && 
                    (strcmp(flightsList[j].hour,flightsList[j+OFFSET].hour)>0)){
                Temp = flightsList[j];
                flightsList[j] = flightsList[j+OFFSET];
                flightsList[j+OFFSET] = Temp;
                swapped=1;
            }
        }
        i++;
    } while(swapped==1);

    return;
}

/**
 * @brief Bubble sorts a flight list according to their flight arriving date and 
 * hour from earliest to oldest.
 * 
 * @param flightsList Flights array.
 * @param currFlights Current flights number.
 */
void bubbleSortFlightArrive (Flight flightsList[],int currFlights){
    int i=0,j;
    int swapped=0;
    Flight Temp;

    do{
        swapped = 0;
        for (j=0; j<(currFlights-1-i);j++){
            if(datecmp(flightsList[j].arrivingDate,
                flightsList[j+OFFSET].arrivingDate)>0){
                Temp = flightsList[j];
                flightsList[j] = flightsList[j+OFFSET];
                flightsList[j+OFFSET] = Temp;
                swapped=1;
            }
            else if( (!datecmp(flightsList[j].arrivingDate,
                    flightsList[j+OFFSET].arrivingDate)) && 
                    (strcmp(flightsList[j].arrivingHour,
                    flightsList[j+OFFSET].arrivingHour)>0) ){
                Temp = flightsList[j];
                flightsList[j] = flightsList[j+OFFSET];
                flightsList[j+OFFSET] = Temp;
                swapped=1;
            }
        }
        i++;
    } while(swapped==1);

    return;
}

/**
 * @brief Bubble sorts an airport array by the airport ID, alphabetically.
 * 
 * @param airportsList Airports array.
 * @param currAirports Current number of airports.
 */
void bubbleSortAirports (Airport airportsList[],int currAirports){
    int i=0,j;
    int swapped=0;
    Airport Temp;
    do{
        swapped = 0;
        for (j=0; j<(currAirports-1-i);j++){
            if(strcmp(airportsList[j].identifier,airportsList[j+OFFSET].
                identifier)>0){
                Temp = airportsList[j];
                airportsList[j] = airportsList[j+OFFSET];
                airportsList[j+OFFSET] = Temp;
                swapped=1;
            }
        }
        i++;
    } while(swapped==1);

    return;
}

/**
 * @brief Bubble sorts the booking linked list alphabetically by bookingID.
 * 
 * @param listHead first node of the booking linked list.
 * @return Booking* the new head of the sorted linked list.
 */
Booking* bubbleSortBooking(Booking* listHead){
    int swapped=1;
    Booking* left,*right,*head, aux_struct;
    head = &aux_struct;
    head->next = listHead;
    if (listHead!=NULL && listHead->next!=NULL){
        while(swapped){
            swapped=0;
            left=head;
            right = head->next;
            while(right->next!=NULL){
                if(strcmp(right->bookingID,right->next->bookingID)>0){
                    left->next=swapBooking(right,right->next);
                    swapped=1;
                }
                left = right;
                if(right->next!=NULL)
                    right=right->next;
            }
        }
    }
    right = head->next;
    return right;
}

/**
 * @brief swaps 2 elements of the booking linked list 
 * 
 * @param left left node.
 * @param right right node.
 * @return Booking* the new left node.
 */
Booking* swapBooking(Booking* left, Booking* right){
    left->next = right->next;
    right->next = left;
    return right;
}
