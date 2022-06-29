#include "structs.h"

/**
 * @brief Create a new Booking node in case all the parameteres pass throught
 * all the tests. Checks if there's memory available to allocate a new node, if
 * not, it finishes with an error message.
 * 
 * @param head first element of a booking list.
 * @param bookingID booking ID from the input.
 * @param passengerNum number of passengers from the input.
 * @param flightList current flight array.
 * @param currentFlights current number of flights
 * @param todaysDate current systems date.
 * @return Booking* first element of the booking list with the new node added to
 * the end of it.
 */
Booking* createBookingEl(Booking* head,char* bookingID,int passengerNum,Flight flightList[],int currentFlights,char* todaysDate){
    Booking* aux;
    /* adds the booking element to the head,if there isnt an head element yet */
    if (head==NULL){
        if ((head = (Booking*) calloc(1,sizeof(Booking)))==NULL){
            printf(FORMAT_STRING,ERR_NO_MEMORY);
            caseQ(flightList,currentFlights,todaysDate);
            exit(EXIT_FAILURE);
        }
        if ( (head->bookingID = (char*) calloc ((strlen(bookingID)+OFFSET),sizeof(char)))==NULL){
            printf(FORMAT_STRING,ERR_NO_MEMORY);
            caseQ(flightList,currentFlights,todaysDate);
            exit(EXIT_FAILURE);
        }
        strcpy(head->bookingID,bookingID);
        head->passengerNum=passengerNum;
        head->next=NULL;
    }
    /* adds a new booking node to the end of the list */
    else{
        aux = head;
        while (aux->next != NULL){
            aux = aux->next;
        }
        if( (aux->next = (Booking*) calloc(1,sizeof(Booking)))==NULL){
            caseQ(flightList,currentFlights,todaysDate);
            printf(FORMAT_STRING,ERR_NO_MEMORY);
            exit(EXIT_FAILURE);
        }
        aux = aux->next;
        if ( (aux->bookingID = (char*) calloc ((strlen(bookingID)+OFFSET),sizeof(char)))==NULL){
            caseQ(flightList,currentFlights,todaysDate);
            printf(FORMAT_STRING,ERR_NO_MEMORY);
            exit(EXIT_FAILURE);
        }
        strcpy(aux->bookingID,bookingID);
        aux->passengerNum=passengerNum;
        aux->next=NULL;
    }

    return head;
}

/**
 * @brief prints all the booking node of a booking list to the 
 * stdout.
 * 
 * @param head first element of the booking list.
 */
void printBooking(Booking* head){
    while(head!=NULL){
        printf("%s %d\n",head->bookingID,head->passengerNum);
        head = head->next;
    }
    return;
}

/**
 * @brief frees an allocated booking node and its allocated ID
 * 
 * @param current booking node to be freed.
 */
void freeBooking(Booking* current){
    free(current->bookingID);
    free(current);
    return;
}

/**
 * @brief frees all the allocated booking nodes and its allocated ID 
 * from a booking linked list.
 * 
 * @param head first element from the booking list.
 */
void freeAllBookings(Booking* head){
    Booking* aux;
    while(head!=NULL){
        aux = head;
        head = head->next;
        freeBooking(aux);
    }
    return;
}

/**
 * @brief Goes through a booking list and frees a booking with the "bookingID"
 *  as its ID.
 * 
 * @param head first element of the booking linked list.
 * @param bookingID Unique ID of the booking to delete.
 * @return Booking* first element of the booking linked list without the booking
 * element that was deleted.
 */
Booking* deleteBooking(Booking* head,char* bookingID){
    Booking* previous = head,*after=head->next;
    if (!strcmp(previous->bookingID,bookingID)){
        freeBooking(previous);
        return after;
    }
    while(after!=NULL){
        if(!strcmp(after->bookingID,bookingID)){
            previous->next=after->next;
            freeBooking(after);
            break;
        }
        after = after->next;
        previous = previous->next;
    }
    return head;
}
