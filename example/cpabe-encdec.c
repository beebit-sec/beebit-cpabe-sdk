#include <stdio.h>
#include "../beebitcpabe.h"

int main(void){

	unsigned char plaintext[256];
	unsigned char* ciphertext = "PLAIN";

	fgets(plaintext, 256, stdin);

	// ENCRYPTION PROCESS
	int enc_length = 0;
	enc_length = cpabe_enc("./pubKey", plaintext, "role <= 2", &ciphertext);
	if(enc_length == -1){
		printf("ENC FAILED\n");
		return -1;
	}
	printf("ENC SUCCESS: (%s->%s[len=%d])\n", plaintext, ciphertext, enc_length);

	// DECRYPTION PROCESS
	unsigned char* result = 0;
	int dec_length = 0;
	
	dec_length = cpabe_dec("./pubKey", "./secKey_ok", ciphertext, &result);
	if(dec_length == -1){
		printf("DEC FAIL\n");
		return -1;
	}
	printf("DEC SUCCESS: (%s->%s[len=%d])\n", ciphertext, result, dec_length);

	return 0;
}

