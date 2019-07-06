#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <pbc.h>
#include <pbc_random.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bswabe.h"
#include "common.h"
#include "policy_lang.h"
#include "../beebitcpabe.h"

//char* pub_file = 0;
//char* in_file  = 0;
//char* out_file = 0;
//int   keep     = 0;

char* policy = 0;

int cpabe_fenc(char* pk_path, char* pt_path, char* policy_str, char* ct_path){
	bswabe_pub_t* pub;
	bswabe_cph_t* cph;
	int file_len;
	GByteArray* plt;
	GByteArray* cph_buf;
	GByteArray* aes_buf;
	element_t m;

	char* out_file = 0;
	int keep = 0;

	if(!strcmp(pt_path, ct_path)) {return die("%s","Plaintext can not the same as ciphertext.");}

    	if((policy = parse_policy_lang(policy_str)) == NULL){return -1;}

	if(!strcmp(ct_path, "default")){
		out_file = g_strdup_printf("%s.cpabe", pt_path);
	}else{
		out_file = ct_path;
	}

	GByteArray* temp;

	if((temp = suck_file(pk_path)) == NULL){return -1;}

    	pub = bswabe_pub_unserialize(temp, 1);
	
    	if(!(cph = bswabe_enc(pub, m, policy))){
		return die("%s", bswabe_error());
	}

        free(policy);
	cph_buf = bswabe_cph_serialize(cph);
	bswabe_cph_free(cph);

	plt = suck_file(pt_path);
	file_len = plt->len;
	aes_buf = aes_128_cbc_encrypt(plt, m);
	g_byte_array_free(plt, 1);
	element_clear(m);
 
 	if(write_cpabe_file(out_file, cph_buf, file_len, aes_buf)==-1){
		return -1;
	}

	g_byte_array_free(cph_buf, 1);
	g_byte_array_free(aes_buf, 1);
 
	if(!keep)
 		unlink(pt_path);
	return 0;
}

cpabebuf* cpabe_enc_b(char* pk_path, char* pt, int pt_len, char* policy_str, cpabebuf* buf){
	int len = -1;
	len = cpabe_enc(pk_path, pt, pt_len, policy_str, &(buf->data));
	if(len == -1) {
		return NULL;
	}
	buf->len = len;
	return buf;
}

int cpabe_enc(char* pk_path, void* pt, int pt_len, char* policy_str, void** ct){
	bswabe_pub_t* pub;
	bswabe_cph_t* cph;
	int file_len;
	GByteArray* plt;
	GByteArray* cph_buf;
	GByteArray* aes_buf;
	element_t m;

	// Access policty checking
    	if((policy = parse_policy_lang(policy_str)) == NULL){ return -1;}

	GByteArray* temp;
	if((temp = suck_file(pk_path)) == NULL){return -1;}
    	pub = bswabe_pub_unserialize(temp, 1);
	
    	if(!(cph = bswabe_enc(pub, m, policy))){
		return die("%s", bswabe_error());
	}
        free(policy);

	cph_buf = bswabe_cph_serialize(cph);
	bswabe_cph_free(cph);

	file_len = pt_len;//strlen(pt);
	//plt = g_byte_array_new_take(plaintext, file_len);
	plt = g_byte_array_new();
	g_byte_array_set_size(plt, file_len);
	//g_byte_array_append(plt, plaintext, file_len);
	memcpy(plt->data, pt, file_len);	

	aes_buf = aes_128_cbc_encrypt(plt, m);

	g_byte_array_free(plt, 1);
	element_clear(m);
 
	int len = aes_buf->len+cph_buf->len+12;
	char* cipher = malloc(sizeof(char)*len);

	memcpy(cipher, (char*)&file_len, 4);
	memcpy(cipher+4, (char*)&aes_buf->len, 4);
	memcpy(cipher+8, (char*)&cph_buf->len, 4);
	memcpy(cipher+12, (char*)aes_buf->data, aes_buf->len);
	memcpy(cipher+12+aes_buf->len, (char*)cph_buf->data, cph_buf->len);

	//cipher->len = file_len;
	//cipher->aes_buf = (char*)aes_buf->data;
	//cipher->aes_len = aes_buf->len;
	//cipher->cph_buf = (char*)cph_buf->data;
	//cipher->cph_len = cph_buf->len;

	*ct = cipher;
	
	g_byte_array_free(aes_buf, 1);
 
	return len;
}
