//kore ni hatariteimas
//ugokenaide
//finale
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "CRCV4.c"
#include "checksumCalc.c"

/* ******************************************************************
 ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: SLIGHTLY MODIFIED
 FROM VERSION 1.1 of J.F.Kurose

   This code should be used for PA2, unidirectional or bidirectional
   data transfer protocols (from A to B. Bidirectional transfer of data
   is for extra credit and is not required).  Network properties:
   - one way network delay averages five time units (longer if there
       are other packets in the channel for GBN), but can be larger
   - frames can be corrupted (either the header or the data portion)
       or lost, according to user-defined probabilities
   - frames will be delivered in the order in which they were sent
       (although some can be lost).
**********************************************************************/

#define BIDIRECTIONAL 1 /* change to 1 if you're doing extra credit */
/* and write a routine called B_output */

/* a "pkt" is the data unit passed from layer 5 (teachers code) to layer  */
/* 5 (students' code).  It contains the data (characters) to be delivered */
/* to layer 5 via the students transport level protocol entities.         */

int A_globalfrmtype;
int A_globalseqnum;
int A_globalacknum;
char A_globalpayload[4];
bool A_ifgotAck;
int A_outstandingACK;

int A_storedacknum;

int B_globalfrmtype;
int B_globalseqnum;
int B_globalacknum;
char B_globalpayload[4];
bool B_ifgotAck;
int B_outstandingACK;

int B_storedacknum;

bool iftimerstarted;

char divisor[100];
int CRC_steps;

struct pkt
{
    char data[4];
};

/* a frame is the data unit passed from layer 5 (students code) to layer */
/* 3 (teachers code).  Note the pre-defined frame structure, which all   */
/* students must follow. */
struct frm
{
    int frmtype;
    int seqnum;
    int acknum;
    //int checksum;
    char checksum[10];
    char payload[4];
};

/********* FUNCTION PROTOTYPES. DEFINED IN THE LATER PART******************/
void starttimer(int AorB, float increment);
void stoptimer(int AorB);
void tolayer1(int AorB, struct frm frame);
void tolayer3(int AorB, char datasent[5]);

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/

/* called from layer 5, passed the data to be sent to other side */

int getChecksum(struct frm send_frm)
{
    int len = strlen(send_frm.payload);
    int datasum = 0;
    for(int i=0; i<len; i++)
    {
        datasum = datasum + send_frm.payload[i];
    }
    int checksum = send_frm.seqnum + send_frm.acknum + datasum;
    return checksum;
}

void A_output(struct pkt packet)
{
    if(A_ifgotAck == true)
    {
        A_ifgotAck = false;

        if(A_outstandingACK == 1)
        {
            //begin_make_frm
            struct frm send_frm;
            send_frm.frmtype = 2;
            send_frm.seqnum = A_globalseqnum;
            send_frm.acknum = 1 - A_globalacknum;
            strcpy(send_frm.payload, packet.data);

            //begin_calc_checksum
            char inputStr[32];
            concatenateChecksum(send_frm.frmtype, send_frm.seqnum, send_frm.acknum, send_frm.payload, inputStr);
            
            if(CRC_steps == 1)
            {
                printf("case3: in A_output(sender side) ; for piggybacked payload %s ; CRC input bit string %s\n", send_frm.payload, inputStr);
                printf("case3: in A_output(sender side) ; divisor %s\n", divisor);
            }

            char *rem = CRC_zeros(inputStr, divisor);

            strcpy(send_frm.checksum, rem);
            if(CRC_steps == 1)
            {
                printf("case3: in A_output(sender side) ; checksum %s\n", send_frm.checksum);
            }
            //end_calc_checksum
            //send_frm.checksum = getChecksum(send_frm);
            //end_make_frm

            //begin_storing_frm_record
            A_globalfrmtype = send_frm.frmtype;
            A_storedacknum = send_frm.acknum;
            strcpy(A_globalpayload, send_frm.payload);
            //end_storing_frm_record

            printf("\nin A_output ; Sending piggybacked ack with payload %s\n", packet.data);

            tolayer1(0, send_frm);
            A_outstandingACK = 0;
            starttimer(0, 100);
        }
        else
        {
            //begin_make_frm
            struct frm send_frm;
            send_frm.frmtype = 0;
            send_frm.seqnum = A_globalseqnum;
            send_frm.acknum = 1 - A_globalacknum;
            strcpy(send_frm.payload, packet.data);
            
            //begin_calc_checksum
            char inputStr[32];
            concatenateChecksum(send_frm.frmtype, send_frm.seqnum, send_frm.acknum, send_frm.payload, inputStr);
            
            if(CRC_steps == 1)
            {
                printf("case3: in A_output(sender side) ; for payload %s ; CRC input bit string %s\n", send_frm.payload, inputStr);
                printf("case3: in A_output(sender side) ; divisor %s\n", divisor);
            }
            
            char *rem = CRC_zeros(inputStr, divisor);
            strcpy(send_frm.checksum, rem);

            if(CRC_steps == 1)
            {
                printf("case3: in A_output(sender side) ; checksum %s\n", send_frm.checksum);
            }
            //end_calc_checksum
            //send_frm.checksum = getChecksum(send_frm);
            //end_make_frm

            //begin_storing_frm_record
            A_globalfrmtype = send_frm.frmtype;
            A_storedacknum = send_frm.acknum;
            strcpy(A_globalpayload, send_frm.payload);
            //end_storing_frm_record

            printf("\nin A_output ; Sending %s\n", packet.data);
            tolayer1(0, send_frm);
            starttimer(0, 100);
        }
    }
    else
    {
        printf("\nin A_output ; packet with payload %s dropped\n", packet.data);
    }
    
}

/* need be completed only for extra credit */
void B_output(struct pkt packet)
{
    if(B_ifgotAck == true)
    {
        B_ifgotAck = false;

        if(B_outstandingACK == 1)
        {
            //begin_make_frm
            struct frm send_frm;
            send_frm.frmtype = 2;
            send_frm.seqnum = B_globalseqnum;
            send_frm.acknum = 1 - B_globalacknum;
            strcpy(send_frm.payload, packet.data);

            //begin_calc_checksum
            char inputStr[32];
            concatenateChecksum(send_frm.frmtype, send_frm.seqnum, send_frm.acknum, send_frm.payload, inputStr);
            
            if(CRC_steps == 1)
            {
                printf("case3: in B_output(sender side) ; for piggybacked payload %s ; CRC input bit string %s\n", send_frm.payload, inputStr);
                printf("case3: in B_output(sender side) ; divisor %s\n", divisor);
            }
            
            char *rem = CRC_zeros(inputStr, divisor);
            strcpy(send_frm.checksum, rem);
            
            if(CRC_steps == 1)
            {
                printf("case3: in B_output(sender side) ; checksum %s\n", send_frm.checksum);
            }
            //end_calc_checksum

            //send_frm.checksum = getChecksum(send_frm);
            //end_make_frm

            //begin_storing_frm_record
            B_globalfrmtype = send_frm.frmtype;
            B_storedacknum = send_frm.acknum;
            strcpy(B_globalpayload, send_frm.payload);
            //end_storing_frm_record

            printf("\nin B_output ; Sending piggybacked ack with payload %s\n", packet.data);

            tolayer1(1, send_frm);
            B_outstandingACK = 0;
            starttimer(1, 100);
        }
        else
        {
            //begin_make_frm
            struct frm send_frm;
            send_frm.frmtype = 0;
            send_frm.seqnum = B_globalseqnum;
            send_frm.acknum = 1 - B_globalacknum;
            strcpy(send_frm.payload, packet.data);

            //begin_calc_checksum
            char inputStr[32];
            concatenateChecksum(send_frm.frmtype, send_frm.seqnum, send_frm.acknum, send_frm.payload, inputStr);
            
            if(CRC_steps == 1)
            {
                printf("case3: in B_output(sender side) ; for payload %s ; CRC input bit string %s\n", send_frm.payload, inputStr);
                printf("case3: in B_output(sender side) ; divisor %s\n", divisor);
            }
            
            char *rem = CRC_zeros(inputStr, divisor);
            strcpy(send_frm.checksum, rem);
            
            if(CRC_steps == 1)
            {
                printf("case3: in B_output(sender side) ; checksum %s\n", send_frm.checksum);
            }
            //end_calc_checksum
            //end_make_frm

            //begin_storing_frm_record
            B_globalfrmtype = send_frm.frmtype;
            B_storedacknum = send_frm.acknum;
            strcpy(B_globalpayload, send_frm.payload);
            //end_storing_frm_record

            printf("\nin B_output ; Sending %s\n", packet.data);
            tolayer1(1, send_frm);
            starttimer(1, 100);
        }
    }
    else
    {
        printf("\nin B_output ; packet with payload %s dropped\n", packet.data);
    }
    
}

/* called from layer 3, when a frame arrives for layer 5 */
void A_input(struct frm frame)
{   
    //begin_check_checksum
    char recStr[32];
    concatenateChecksum(frame.frmtype, frame.seqnum, frame.acknum, frame.payload, recStr);
    
    if(CRC_steps == 1)
    {
        printf("case3: in A_input(receiver side) ; for payload %s ; CRC input bit string %s\n", frame.payload, recStr);
        printf("case3: in A_input(receiver side) ; divisor %s\n", divisor);
    }
    
    char rem[10];
    strcpy(rem, frame.checksum);
    char *checkrem = CRC_rem(recStr, divisor, rem);

    int remlen = strlen(checkrem);
    bool checksumOk = true;

    for(int i=0; i<remlen; i++)
    {
        if(checkrem[i] == '1') checksumOk = false;
    }

    if(checksumOk == false && CRC_steps == 1)
    {
        printf("case3: in A_input(receiver side) ; data transmission error has occured ; found remainder %s\n", checkrem);
    }
    //end_check_checksum

    if(frame.frmtype == 0 || frame.frmtype == 2)
    {
        if((A_globalacknum == frame.seqnum) && (checksumOk))
        {
            A_outstandingACK = 1;
            printf("in A_input ; received correctly and trying to piggyback ack for payload %s\n", frame.payload);
            tolayer3(0, frame.payload);

            A_globalacknum = 1 - frame.seqnum;
        }
        else if((A_globalacknum != frame.seqnum) && (checksumOk))
        {
            //begin_make_ack_frm
            struct frm ack_frm;
            ack_frm.frmtype = 1;
            ack_frm.seqnum = 0;
            ack_frm.acknum = 1 - A_globalacknum;
            //strcpy(ack_frm.payload, 0000);
            //ack_frm.payload[0] = 0;
            for(int i=0; i<4; i++) ack_frm.payload[i] = 0;

            //begin_calc_checksum
            char inputStr[32];
            concatenateChecksum(ack_frm.frmtype, ack_frm.seqnum, ack_frm.acknum, ack_frm.payload, inputStr);
            //printf("in A_input ; input_Str %s\n", inputStr);

            char *tempRem = CRC_zeros(inputStr, divisor);
            strcpy(ack_frm.checksum, tempRem);
            //end_calc_checksum
            //ack_frm.checksum = getChecksum(ack_frm);
            //end_make_ack_frm

            printf("in A_input ; sending again_ACK for duplicate frame; payload %s\n", frame.payload);
            tolayer1(0, ack_frm);

            A_outstandingACK = 0;
        }
        else
        {
            //begin_make_ack_frm
            struct frm ack_frm;
            ack_frm.frmtype = 1;
            ack_frm.seqnum = 0;
            ack_frm.acknum = 1 - A_globalacknum;
            //strcpy(ack_frm.payload, "000");
            //ack_frm.payload[0] = 0;
            for(int i=0; i<4; i++) ack_frm.payload[i] = 0;

            //begin_calc_checksum
            char inputStr[32];
            concatenateChecksum(ack_frm.frmtype, ack_frm.seqnum, ack_frm.acknum, ack_frm.payload, inputStr);
            //printf("in A_input ; input_Str %s\n", inputStr);

            char *tempRem = CRC_zeros(inputStr, divisor);
            strcpy(ack_frm.checksum, tempRem);
            //end_calc_checksum
            //end_make_ack_frm

            printf("in A_input ; sending NACK for corrupted payload %s\n", frame.payload);
            tolayer1(0, ack_frm);

            A_outstandingACK = 0;
        }
    }

    if(frame.frmtype == 1 || frame.frmtype == 2)
    {
        if((frame.acknum == A_globalseqnum) && (checksumOk))
        {
            printf("in A_input ; got ACK\n");
            A_globalseqnum = 1 - A_globalseqnum;
            A_ifgotAck = true;

            stoptimer(0);
        }
        /*else
        {
            A_ifgotAck = false;
        }*/
    }
}

/* called when A's timer goes off */
void A_timerinterrupt(void)
{
    //begin_make_frm
    struct frm send_frm;
    send_frm.frmtype = A_globalfrmtype;
    send_frm.seqnum = A_globalseqnum;
    send_frm.acknum = A_storedacknum; //age 0 chilo
    strcpy(send_frm.payload, A_globalpayload);

    //begin_calc_checksum
    char inputStr[32];
    concatenateChecksum(send_frm.frmtype, send_frm.seqnum, send_frm.acknum, send_frm.payload, inputStr);
    //printf("in A_timerinterrupt ; input_Str %s\n", inputStr);

    char *rem = CRC_zeros(inputStr, divisor);
    strcpy(send_frm.checksum, rem);
    //end_calc_checksum
    //send_frm.checksum = getChecksum(send_frm);
    //end_make_frm

    printf("in A_timerinterrupt ; Re-sending global-> %s\n", A_globalpayload);

    tolayer1(0, send_frm);
    starttimer(0, 100);
}

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init(void)
{
    A_globalfrmtype = -1;
    A_globalseqnum = 0;
    A_globalacknum = 0;
    A_ifgotAck = true;
    A_outstandingACK = 0;
    iftimerstarted = false;
}

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a frame arrives for layer 5 at B*/
void B_input(struct frm frame)
{
    //begin_calculate_frame_checksum
    //begin_check_checksum
    char recStr[32];
    concatenateChecksum(frame.frmtype, frame.seqnum, frame.acknum, frame.payload, recStr);
    
    if(CRC_steps == 1)
    {
        printf("case3: in B_input(receiver side) ; for payload %s ; CRC input bit string %s\n", frame.payload, recStr);
        printf("case3: in B_input(receiver side) ; divisor %s\n", divisor);
    }
    
    char rem[10];
    strcpy(rem, frame.checksum);
    char *checkrem = CRC_rem(recStr, divisor, rem);

    int remlen = strlen(checkrem);
    bool checksumOk = true;

    for(int i=0; i<remlen; i++)
    {
        if(checkrem[i] == '1') checksumOk = false;
    }

    if(checksumOk == false && CRC_steps == 1)
    {
        printf("case3: in B_input(receiver side) ; data transmission error has occured ; found remainder %s\n", checkrem);
    }
    //end_check_checksum
    //end_calculate_frame_checksum

    if(frame.frmtype == 0 || frame.frmtype == 2)
    {
        if((B_globalacknum == frame.seqnum) && (checksumOk))
        {
            B_outstandingACK = 1;
            printf("in B_input ; received correctly and trying to piggyback ack for payload %s\n", frame.payload);
            tolayer3(1, frame.payload);

            B_globalacknum = 1 - frame.seqnum;
            //printf("here\n");
        }
        else if((B_globalacknum != frame.seqnum) && (checksumOk))
        {
            //begin_make_ack_frm
            struct frm ack_frm;
            ack_frm.frmtype = 1;
            ack_frm.seqnum = 0;
            ack_frm.acknum = 1 - B_globalacknum;
            //strcpy(ack_frm.payload, "000");
            //ack_frm.payload[0] = 0;
            for(int i=0; i<4; i++) ack_frm.payload[i] = 0;

            //begin_calc_checksum
            char inputStr[32];
            concatenateChecksum(ack_frm.frmtype, ack_frm.seqnum, ack_frm.acknum, ack_frm.payload, inputStr);

            char *tempRem = CRC_zeros(inputStr, divisor);
            strcpy(ack_frm.checksum, tempRem);
            //end_calc_checksum
            //ack_frm.checksum = getChecksum(ack_frm);
            //end_make_ack_frm

            printf("in B_input ; sending again_ACK for duplicate frame; payload %s\n", frame.payload);
            tolayer1(1, ack_frm);

            B_outstandingACK = 0;
        }
        else
        {
            //begin_make_ack_frm
            struct frm ack_frm;
            ack_frm.frmtype = 1;
            ack_frm.seqnum = 0;
            ack_frm.acknum = 1 - B_globalacknum;
            //strcpy(ack_frm.payload, "000");
            //ack_frm.payload[0] = 0;
            for(int i=0; i<4; i++) ack_frm.payload[i] = 0;

            //begin_calc_checksum
            char inputStr[32];
            concatenateChecksum(ack_frm.frmtype, ack_frm.seqnum, ack_frm.acknum, ack_frm.payload, inputStr);
            //printf("in B_input ; input_Str %s\n", inputStr);

            char *tempRem = CRC_zeros(inputStr, divisor);
            strcpy(ack_frm.checksum, tempRem);
            //end_calc_checksum
            //ack_frm.checksum = getChecksum(ack_frm);
            //end_make_ack_frm

            printf("in B_input ; sending NACK for corrupted payload %s\n", frame.payload);
            tolayer1(1, ack_frm);

            B_outstandingACK = 0;
        }
    }
    
    if(frame.frmtype == 1 || frame.frmtype == 2)
    {
        if((frame.acknum == B_globalseqnum) && (checksumOk))
        {
            printf("in B_input ; got ACK\n");
            B_globalseqnum = 1 - B_globalseqnum;
            B_ifgotAck = true;

            stoptimer(1);
        }
        /*else
        {
            B_ifgotAck = false;
        }*/
    }
}

/* called when B's timer goes off */
void B_timerinterrupt(void)
{
    //begin_make_frm
    struct frm send_frm;
    send_frm.frmtype = B_globalfrmtype;
    send_frm.seqnum = B_globalseqnum;
    send_frm.acknum = B_storedacknum; //age 0 chilo
    strcpy(send_frm.payload, B_globalpayload);

    //begin_calc_checksum
    char inputStr[32];
    concatenateChecksum(send_frm.frmtype, send_frm.seqnum, send_frm.acknum, send_frm.payload, inputStr);
    //printf("in B_timerinterrupt ; input_Str %s\n", inputStr);

    char *rem = CRC_zeros(inputStr, divisor);
    strcpy(send_frm.checksum, rem);
    //end_calc_checksum
    //send_frm.checksum = getChecksum(send_frm);
    //end_make_frm

    printf("in B_timerinterrupt ; Re-sending global-> %s\n", B_globalpayload);
    //if(send_frm.checksum == 304) printf("here\n");

    tolayer1(1, send_frm);
    starttimer(1, 100);
}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init(void)
{
    B_globalfrmtype = -1;
    B_globalseqnum = 0;
    B_globalacknum = 0;
    B_ifgotAck = true;
    B_outstandingACK = 0;
}

/*****************************************************************
***************** NETWORK EMULATION CODE STARTS BELOW ***********
The code below emulates the layer 3 and below network environment:
    - emulates the tranmission and delivery (possibly with bit-level corruption
        and frame loss) of frames across the layer 3/5 interface
    - handles the starting/stopping of a timer, and generates timer
        interrupts (resulting in calling students timer handler).
    - generates packet to be sent (passed from later 5 to 5)

THERE IS NOT REASON THAT ANY STUDENT SHOULD HAVE TO READ OR UNDERSTAND
THE CODE BELOW.  YOU SHOLD NOT TOUCH, OR REFERENCE (in your code) ANY
OF THE DATA STRUCTURES BELOW.  If you're interested in how I designed
the emulator, you're welcome to look at the code - but again, you should have
to, and you defeinitely should not have to modify
******************************************************************/

struct event
{
    float evtime;       /* event time */
    int evtype;         /* event type code */
    int eventity;       /* entity where event occurs */
    struct frm *frmptr; /* ptr to frame (if any) assoc w/ this event */
    struct event *prev;
    struct event *next;
};
struct event *evlist = NULL; /* the event list */

/* possible events: */
#define TIMER_INTERRUPT 0
#define FROM_layer3 1
#define FROM_layer1 2

#define OFF 0
#define ON 1
#define A 0
#define B 1

int TRACE = 1;     /* for my debugging */
int nsim = 0;      /* number of packets from 5 to 5 so far */
int nsimmax = 0;   /* number of pkts to generate, then stop */
float time = 0.000;
float lossprob;    /* probability that a frame is dropped  */
float corruptprob; /* probability that one bit is frame is flipped */
float lambda;      /* arrival rate of packets from layer 5 */
int ntolayer1;     /* number sent into layer 3 */
int nlost;         /* number lost in media */
int ncorrupt;      /* number corrupted by media*/

void init();
void generate_next_arrival(void);
void insertevent(struct event *p);

int main()
{
    //freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    struct event *eventptr;
    struct pkt pkt2give;
    struct frm frm2give;

    int i, j;
    char c;

    init();
    A_init();
    B_init();

    while (1)
    {
        eventptr = evlist; /* get next event to simulate */
        if (eventptr == NULL)
            goto terminate;
        evlist = evlist->next; /* remove this event from event list */
        if (evlist != NULL)
            evlist->prev = NULL;
        if (TRACE >= 2)
        {
            printf("\nEVENT time: %f,", eventptr->evtime);
            printf("  type: %d", eventptr->evtype);
            if (eventptr->evtype == 0)
                printf(", timerinterrupt  ");
            else if (eventptr->evtype == 1)
                printf(", fromlayer3 ");
            else
                printf(", fromlayer1 ");
            printf(" entity: %d\n", eventptr->eventity);
        }
        time = eventptr->evtime; /* update time to next event time */
        if (eventptr->evtype == FROM_layer3)
        {
            if (nsim < nsimmax)
            {
                if (nsim + 1 < nsimmax)
                    generate_next_arrival(); /* set up future arrival */
                /* fill in pkt to give with string of same letter */
                j = nsim % 26;
                for (i = 0; i < 4; i++)
                    pkt2give.data[i] = 97 + j;
                pkt2give.data[3] = 0;
                if (TRACE > 2)
                {
                    printf("          MAINLOOP: data given to student: ");
                    for (i = 0; i < 4; i++)
                        printf("%c", pkt2give.data[i]);
                    printf("\n");
                }
                nsim++;
                if (eventptr->eventity == A)
                    A_output(pkt2give);
                else
                    B_output(pkt2give);
            }
        }
        else if (eventptr->evtype == FROM_layer1)
        {
            frm2give.frmtype = eventptr->frmptr->frmtype;
            frm2give.seqnum = eventptr->frmptr->seqnum;
            frm2give.acknum = eventptr->frmptr->acknum;
            //frm2give.checksum = eventptr->frmptr->checksum;
            strcpy(frm2give.checksum, eventptr->frmptr->checksum);
            for (i = 0; i < 4; i++)
                frm2give.payload[i] = eventptr->frmptr->payload[i];
            if (eventptr->eventity == A) /* deliver frame by calling */
                A_input(frm2give); /* appropriate entity */
            else
                B_input(frm2give);
            free(eventptr->frmptr); /* free the memory for frame */
        }
        else if (eventptr->evtype == TIMER_INTERRUPT)
        {
            if (eventptr->eventity == A)
                A_timerinterrupt();
            else
                B_timerinterrupt();
        }
        else
        {
            printf("INTERNAL PANIC: unknown event type \n");
        }
        free(eventptr);
    }

terminate:
    printf(
        " Simulator terminated at time %f\n after sending %d pkts from layer3\n",
        time, nsim);
}

void init() /* initialize the simulator */
{
    int i;
    float sum, avg;
    float jimsrand();

    printf("-----  Stop and Wait Network Simulator Version 1.1 -------- \n\n");
    printf("Enter the number of packets to simulate: ");
    scanf("%d",&nsimmax);
    printf("Enter  frame loss probability [enter 0.0 for no loss]:");
    scanf("%f",&lossprob);
    printf("Enter frame corruption probability [0.0 for no corruption]:");
    scanf("%f",&corruptprob);
    printf("Enter average time between packets from sender's layer3 [ > 0.0]:");
    scanf("%f",&lambda);
    printf("Enter generator polynomial: ");
    scanf("%s", divisor);
    printf("CRC steps: ");
    scanf("%d", &CRC_steps);
    printf("Enter TRACE:");
    scanf("%d",&TRACE);

    srand(9999); /* init random number generator */
    sum = 0.0;   /* test random number generator for students */
    for (i = 0; i < 1000; i++)
        sum = sum + jimsrand(); /* jimsrand() should be uniform in [0,1] */
    avg = sum / 1000.0;
    if (avg < 0.25 || avg > 0.75)
    {
        printf("It is likely that random number generation on your machine\n");
        printf("is different from what this emulator expects.  Please take\n");
        printf("a look at the routine jimsrand() in the emulator code. Sorry. \n");
        exit(1);
    }

    ntolayer1 = 0;
    nlost = 0;
    ncorrupt = 0;

    time = 0.0;              /* initialize time to 0.0 */
    generate_next_arrival(); /* initialize event list */
}

/****************************************************************************/
/* jimsrand(): return a float in range [0,1].  The routine below is used to */
/* isolate all random number generation in one location.  We assume that the*/
/* system-supplied rand() function return an int in therange [0,mmm]        */
/****************************************************************************/
float jimsrand(void)
{
    double mmm = RAND_MAX;
    float x;                 /* individual students may need to change mmm */
    x = rand() / mmm;        /* x should be uniform in [0,1] */
    return (x);
}

/********************* EVENT HANDLINE ROUTINES *******/
/*  The next set of routines handle the event list   */
/*****************************************************/

void generate_next_arrival(void)
{
    double x, log(), ceil();
    struct event *evptr;
    float ttime;
    int tempint;

    if (TRACE > 2)
        printf("          GENERATE NEXT ARRIVAL: creating new arrival\n");

    x = lambda * jimsrand() * 2; /* x is uniform on [0,2*lambda] */
    /* having mean of lambda        */
    evptr = (struct event *)malloc(sizeof(struct event));
    evptr->evtime = time + x;
    evptr->evtype = FROM_layer3;
    if (BIDIRECTIONAL && (jimsrand() > 0.5))
        evptr->eventity = B;
    else
        evptr->eventity = A;
    insertevent(evptr);
}

void insertevent(struct event *p)
{
    struct event *q, *qold;

    if (TRACE > 2)
    {
        printf("            INSERTEVENT: time is %lf\n", time);
        printf("            INSERTEVENT: future time will be %lf\n", p->evtime);
    }
    q = evlist;      /* q points to header of list in which p struct inserted */
    if (q == NULL)   /* list is empty */
    {
        evlist = p;
        p->next = NULL;
        p->prev = NULL;
    }
    else
    {
        for (qold = q; q != NULL && p->evtime > q->evtime; q = q->next)
            qold = q;
        if (q == NULL)   /* end of list */
        {
            qold->next = p;
            p->prev = qold;
            p->next = NULL;
        }
        else if (q == evlist)     /* front of list */
        {
            p->next = evlist;
            p->prev = NULL;
            p->next->prev = p;
            evlist = p;
        }
        else     /* middle of list */
        {
            p->next = q;
            p->prev = q->prev;
            q->prev->next = p;
            q->prev = p;
        }
    }
}

void printevlist(void)
{
    struct event *q;
    int i;
    printf("--------------\nEvent List Follows:\n");
    for (q = evlist; q != NULL; q = q->next)
    {
        printf("Event time: %f, type: %d entity: %d\n", q->evtime, q->evtype,
               q->eventity);
    }
    printf("--------------\n");
}

/********************** Student-callable ROUTINES ***********************/

/* called by students routine to cancel a previously-started timer */
void stoptimer(int AorB /* A or B is trying to stop timer */)
{
    struct event *q, *qold;

    if (TRACE > 2)
        printf("          STOP TIMER: stopping timer at %f\n", time);
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
    for (q = evlist; q != NULL; q = q->next)
        if ((q->evtype == TIMER_INTERRUPT && q->eventity == AorB))
        {
            /* remove this event */
            if (q->next == NULL && q->prev == NULL)
                evlist = NULL;          /* remove first and only event on list */
            else if (q->next == NULL) /* end of list - there is one in front */
                q->prev->next = NULL;
            else if (q == evlist)   /* front of list - there must be event after */
            {
                q->next->prev = NULL;
                evlist = q->next;
            }
            else     /* middle of list */
            {
                q->next->prev = q->prev;
                q->prev->next = q->next;
            }
            free(q);
            return;
        }
    printf("Warning: unable to cancel your timer. It wasn't running.\n");
}

void starttimer(int AorB /* A or B is trying to start timer */, float increment)
{
    struct event *q;
    struct event *evptr;

    if (TRACE > 2)
        printf("          START TIMER: starting timer at %f\n", time);
    /* be nice: check to see if timer is already started, if so, then  warn */
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
    for (q = evlist; q != NULL; q = q->next)
        if ((q->evtype == TIMER_INTERRUPT && q->eventity == AorB))
        {
            printf("Warning: attempt to start a timer that is already started\n");
            return;
        }

    /* create future event for when timer goes off */
    evptr = (struct event *)malloc(sizeof(struct event));
    evptr->evtime = time + increment;
    evptr->evtype = TIMER_INTERRUPT;
    evptr->eventity = AorB;
    insertevent(evptr);

    iftimerstarted = true;
}

/************************** TOlayer1 ***************/
void tolayer1(int AorB, struct frm frame)
{
    struct frm *myfrmptr;
    struct event *evptr, *q;
    float lastime, x;
    int i;

    ntolayer1++;

    /* simulate losses: */
    if (jimsrand() < lossprob)
    {
        nlost++;
        if (TRACE > 0)
            printf("          TOlayer1: frame being lost\n");
        return;
    }

    /* make a copy of the frame student just gave me since he/she may decide */
    /* to do something with the frame after we return back to him/her */
    myfrmptr = (struct frm *)malloc(sizeof(struct frm));
    myfrmptr->frmtype = frame.frmtype;
    myfrmptr->seqnum = frame.seqnum;
    myfrmptr->acknum = frame.acknum;
    //myfrmptr->checksum = frame.checksum;
    strcpy(myfrmptr->checksum, frame.checksum);
    for (i = 0; i < 4; i++)
        myfrmptr->payload[i] = frame.payload[i];
    if (TRACE > 2)
    {
        printf("          TOlayer1: seq: %d, ack %d, check: %s ", myfrmptr->seqnum,
               myfrmptr->acknum, myfrmptr->checksum);
        for (i = 0; i < 4; i++)
            printf("%c", myfrmptr->payload[i]);
        printf("\n");
    }

    /* create future event for arrival of frame at the other side */
    evptr = (struct event *)malloc(sizeof(struct event));
    evptr->evtype = FROM_layer1;      /* frame will pop out from layer1 */
    evptr->eventity = (AorB + 1) % 2; /* event occurs at other entity */
    evptr->frmptr = myfrmptr;         /* save ptr to my copy of frame */
    /* finally, compute the arrival time of frame at the other end.
       medium can not reorder, so make sure frame arrives between 1 and 10
       time units after the latest arrival time of frames
       currently in the medium on their way to the destination */
    lastime = time;
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next) */
    for (q = evlist; q != NULL; q = q->next)
        if ((q->evtype == FROM_layer1 && q->eventity == evptr->eventity))
            lastime = q->evtime;
    evptr->evtime = lastime + 1 + 9 * jimsrand();

    /* simulate corruption: */
    if (jimsrand() < corruptprob)
    {
        ncorrupt++;
        if ((x = jimsrand()) < .75)
            myfrmptr->payload[0] = 'Z'; /* corrupt payload */
        else if (x < .875)
            myfrmptr->seqnum = 999999;
        else
            myfrmptr->acknum = 999999;
        if (TRACE > 0)
            printf("          TOlayer1: frame being corrupted\n");
    }

    if (TRACE > 2)
        printf("          TOlayer1: scheduling arrival on other side\n");
    insertevent(evptr);
}

void tolayer3(int AorB, char datasent[4])
{
    int i;
    if (TRACE > 2)
    {
        printf("          TOlayer3: data received: ");
        for (i = 0; i < 4; i++)
            printf("%c", datasent[i]);
        printf("\n");
    }
}
