#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DATA_POINT_LEN 		4

int safe_while_ndx=0;
#define MAX_SAFE_NDX			100
#define SAFE_WHILE(x)			for (safe_while_ndx=0; (safe_while_ndx < MAX_SAFE_NDX) && (x); safe_while_ndx++)
#define IS_WHILE_EXP()			(safe_while_ndx >= MAX_SAFE_NDX)
#define DEFAULT_TIMEOUT			1000

#define SPN_PROTOCOL_VERSION	1.0

/* Protocol Grammer:
 *
 * STARTING_CHARACTER     (PROTOCOL_VERSION  FLAG_BITS_4)     LENGTH_OF_PACKET      PAYLOAD        CHECKSUM     ENDING_CHARACTER
 *        8-Bits                4-Bits         4-Bits		       8-Bits			   -			8-Bits          8-Bits
 * |-----------------------------HEADER FIELDS--------------------------------|    |-PAYLOAD-|  |-Error Check-|
 */



//Beware!! Functions are not Thread Safe and are not Reentrant Functions
//Need a Fix for Thread Safety!


 struct spn_pkt_header_s {
 	char start;
 	union {
 		uint8_t flags;
 		struct {
 			uint8_t version:4;

 			uint8_t pkt_type:2;
 			uint8_t checksum_protected:1;
 			uint8_t ack_required:1;
 		};
 	};
 	uint8_t length;
 };

 enum spn_pkt_type_e {
 	SPN_DATA,
 	SPN_CMD,
 	
 	SPN_ACK,
 	SPN_NACK
 };


struct spn_context_s {
	char starting;
	char delimiter;
	char ending;

	int timeout;
	bool err_check;

	int (*payload_decode)(char *);
};

struct spn_context_s spn_context;


int spn_init(char starting='$', char delimiter=',', char ending='!', int timeout=DEFAULT_TIMEOUT, bool err_check=false)
{
	spn_context.starting = starting;
	spn_context.delimiter = delimiter;
	spn_context.ending = ending;

	spn_context.timeout = timeout;
	spn_context.err_check = err_check;
	return 0;
}


int spn_parse(void *message)
{
	char *mess = reinterpret_cast<char *>(message);

	SAFE_WHILE (isspace(*mess)) mess++;
	if (IS_WHILE_EXP())
		goto ERROR;

	if ((*mess++) != spn_context.starting)
		goto ERROR;

	char data_point[MAX_DATA_POINT_LEN+1];
	SAFE_WHILE ((*mess) && (*mess != spn_context.ending)) {
		int i;
		for (i=0; (i < MAX_DATA_POINT_LEN) && (*mess != spn_context.delimiter) && (*mess != spn_context.ending); i++)
			data_point[i] = *mess++;

		if (i >= MAX_DATA_POINT_LEN)
			goto ERROR;

		data_point[i] = '\0';
		if (spn_context.payload_decode(data_point))
			goto ERROR;


		for (i=0; (i < 15) && isspace(*mess); i++, mess++);
		if (i >= 15)
			goto ERROR;
		if (*mess == spn_context.ending)
			break;
		if (*mess != spn_context.delimiter)
			goto ERROR;
		mess++;
	}

	if (IS_WHILE_EXP())
		goto ERROR;

	return 0;
ERROR:
	std :: cerr << "Error" << std :: endl;
	return -1;
}

void spn_bind_frame_func(int (*payload_decode)(char *))
{
	spn_context.payload_decode = payload_decode;
}

void spn_bind_err_checking(int (*err_check_func)(int ))
{
	spn_context.err_check_func = err_check_func;
}

int func(char *dp)
{
	if (!dp)
		return -1;
	printf("%s\n", dp);
	return 0;
}

#define __MAIN__

#ifdef __MAIN__
int main()
{
	spn_init();
	spn_bind_frame_func(func);

	char mess[] = "       $12L,4R!";
	std :: cout << "Message Received: " << mess << std :: endl;
	spn_parse(mess);
	return 0;
}
#endif