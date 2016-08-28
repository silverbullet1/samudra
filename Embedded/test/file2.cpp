#include "file.h"
#include "utils.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int spn_create_pkt(char *pkt, char *payload, int payload_len, bool ack/*=false*/, bool err_checksum/*=false*/)
{
	struct spn_pkt_header_s *h = reinterpret_cast<struct spn_pkt_header_s *>(pkt);
	h->start = spn_context.starting;
	h->version = get_spn_version();
	
	h->pkt_type = SPN_DATA_PKT;
	h->checksum_protected = err_checksum;
	h->length = payload_len;
	h->ack_required = ack;

	char *ptr = pkt + sizeof(struct spn_pkt_header_s);
	uint16_t crc16;
	memcpy(ptr, payload, payload_len);

	ptr = ptr + payload_len;
	if (!err_checksum)
		goto END;
	crc16 = util :: crc16(pkt, payload_len + sizeof(spn_pkt_header_s));
	*ptr++ = crc16 & 0x00ff;
	*ptr++ = ( crc16 >> 8 ) & 0x00ff;

END:
	*ptr++ = spn_context.ending;
	*ptr = '\0';
	return 0;
}

int spn_create_ack_pkt(char *pkt, bool ackOrNack/*=true*/)
{
	struct spn_pkt_header_s *h = reinterpret_cast<struct spn_pkt_header_s *>(pkt);
	h->start = spn_context.starting;
	h->version = get_spn_version();
	h->pkt_type = SPN_ACK_PKT;
	
	if (!ackOrNack)
		h->pkt_type = SPN_NACK_PKT;

	h->checksum_protected = false;
	h->length = 0;
	h->ack_required = false;

	char *end = pkt + sizeof(struct spn_pkt_header_s);
	*end++ = spn_context.ending;
	*end = '\0';
	return 0;
}


int spn_create_payload(const char *format, int repeat, ...)
{

}


#ifdef __MAIN__
int main()
{
	spn_init();
	char data[100];
	char payload[100];
	int len =100;

	spn_create_pkt(data, payload, len);
	return 0;
}
#endif
