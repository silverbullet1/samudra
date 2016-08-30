#include "file.h"
#include "utils.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


struct spn_context_s spn_context;

int spn_init(char starting, char delimiter, char ending, bool err_check)
{
	spn_context.starting = starting;
	spn_context.delimiter = delimiter;
	spn_context.ending = ending;

	spn_context.err_check = err_check;
	spn_context.payload_decode = NULL;
	return 0;
}


int spn_checksum(char *pkt, size_t len);
int spn_parse(void *message)
{
	char *pkt = reinterpret_cast<char *>(message);

	struct spn_pkt_header_s *h = reinterpret_cast<struct spn_pkt_header_s *>(pkt);
	if (h->start != spn_context.starting)
		goto ERROR;
	if (h->version != get_spn_version())
		goto ERROR;
	if (h->length >= SPN_MAX_PAYLOAD_LEN)
		goto ERROR;

	if (!h->checksum_protected)
		goto DECODE;
	if (spn_context.err_check) {
		if (spn_checksum(pkt, h->length + sizeof(struct spn_pkt_header_s)))
			goto ERROR;
	}
DECODE:
	pkt += sizeof(struct spn_pkt_header_s);
	if (spn_context.payload_decode(pkt, h->length))
		goto ERROR;

	pkt += SPN_CHECKSUM_LEN;
END:
	if (*pkt != spn_context.ending)
		goto ERROR;
	return 0;


ERROR:
	std :: cerr << "Error" << std :: endl;
	return -1;
}

int spn_checksum(char *pkt, size_t len)
{
	uint16_t crc16 = util :: crc16(pkt, len);
	if (*pkt++ != crc16 & 0x00ff)
		return -1;

	if (*pkt++ != ( crc16 >> 8 ) & 0x00ff)
		return -1;
	return 0;
}

void spn_bind_frame_func(int (*payload_decode)(char *, int))
{
	spn_context.payload_decode = payload_decode;
}


int func(char *dp, int len)
{
	if (!dp)
		return -1;
	printf("%s and length - %d\n", dp, len);
	return 0;
}

#define __MAIN__

#ifdef __MAIN__
int main()
{
	spn_init();
	char pkt[1000];
	spn_bind_frame_func(func);

	char payload[] = "abhishek";
	spn_create_pkt(pkt, payload, strlen(payload));
	//std :: cout << "Message Received: " << pkt << std :: endl;
	spn_parse(pkt);
	return 0;
}
#endif