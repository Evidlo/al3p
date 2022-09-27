#include "al3p.h"

// compute size of thin packet, in bytes
uint32_t len_thin(thin_t packet) {
	return 6 + packet.lf;
}

// pack thin packet into buffer
al3p_error_t pack_thin(uint8_t* buff, uint32_t size, thin_t p) {
	JabplcMeta_t meta = {
		buff,
		size,
		0
	};
	JabplcError_t error;

	error = jabplc_pack_uint8(&meta, p.sm << 7 | (p.pchar & mask(7)));
	/* if (error != JABPLC_SUCCESS) { */
	/* 	fprintf(stderr, "%s : Failed : Unable to pack due to error code %u\n", __func__, error); */
	/* 	exit(1); */
	/* } */
	errcheck(__func__, error);
	error = jabplc_pack_uint8(&meta, p.lfp << 7 | (p.cchar & mask(7)));
}

int main() {
	uint8_t payload[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	thin_t packet = {
		0, // sm
		0, // pchar
		1, // lfp
		0, // cchar
		0, // seq
		/* 0, // ssq */
		/* 0, // tot */
		8, // lf
		// payload
		&payload,
	};
	uint32_t packet_size = len_thin(packet);

	uint32_t buff[100];
	pack_thin(&buff, packet_size, packet);

	for (uint8_t i=0; i<packet_size; i++) {
		printf("%d\n", buff[i]);
	}
}
