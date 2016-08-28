#ifndef _FILE_H_
#define _FILE_H_

#include <stdint.h>

#define MAX_DATA_POINT_LEN 		4

#define SPN_PROTOCOL_VERSION	1
#define get_spn_version()		(SPN_PROTOCOL_VERSION & 0x0f)
#define SPN_CHECKSUM_LEN		2
#define SPN_MAX_PAYLOAD_LEN		64

/* Protocol Grammer:
 *
 * STARTING_CHARACTER     (PROTOCOL_VERSION  FLAG_BITS_4)     LENGTH_OF_PACKET      PAYLOAD        CHECKSUM     ENDING_CHARACTER
 *        8-Bits                4-Bits         4-Bits		       8-Bits			   -			8-Bits          8-Bits
 * |-----------------------------HEADER FIELDS--------------------------------|    |-PAYLOAD-|  |-Error Check-|
 *
 * Payload is a sequence of Data Points Delimited by a Delimiter!
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
 	SPN_DATA_PKT,
 	SPN_CMD_PKT,
 	
 	SPN_ACK_PKT,
 	SPN_NACK_PKT
 };


struct spn_context_s {
	char starting;
	char delimiter;
	char ending;

	bool err_check;

	int (*payload_decode)(char *, int);
};

extern struct spn_context_s spn_context;
int spn_init(char starting='$', char delimiter=',', char ending='!', bool err_check=false);
int spn_create_pkt(char *pkt, char *payload, int payload_len, bool ack=false, bool err_checksum=false);
int spn_create_ack_pkt(char *pkt, bool ackOrNack=true);


#endif