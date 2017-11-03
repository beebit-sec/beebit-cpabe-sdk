#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <pbc.h>
#include <pbc_random.h>
#include <stdio.h>
#include <stdlib.h>
#define MILLION 1000000
#include <time.h>
#include "bswabe.h"
#include "common.h"
#include "../beebitcpabe.h"

//char* pub_file   = 0;
//char* prv_file   = 0;
//char* in_file    = 0;
//char* out_file   = 0;
/* int   no_opt_sat = 0; */
/* int   report_ops = 0; */
int   keep       = 0;

int cpabe_fdec(unsigned char* pk_path, unsigned char* sk_path, unsigned char* ct_path){

	bswabe_pub_t* pub;
	bswabe_prv_t* prv;
	int file_len;
	GByteArray* aes_buf;
	GByteArray* plt;
	GByteArray* cph_buf;
	GByteArray* sf_pf;
	GByteArray* sf_prvf;
	bswabe_cph_t* cph;
	element_t m;

	unsigned char* pub_file = pk_path;
	unsigned char* prv_file = sk_path;
	unsigned char* in_file  = ct_path;
	unsigned char* out_file;

	if(keep && !strcmp(in_file, out_file) ){
		printf("cannot keep input file when decrypting file in place \n");
	}	

	if((sf_pf = suck_file(pub_file)) == NULL) {
		return -1;
	}
	if((sf_prvf = suck_file(prv_file)) == NULL){
		return -1;
	}
	if((read_cpabe_file(in_file, &cph_buf, &file_len, &aes_buf))==-1){
		return -1;
	}

	pub = bswabe_pub_unserialize(sf_pf, 1);
	 
	prv = bswabe_prv_unserialize(pub,sf_prvf, 1);
	cph = bswabe_cph_unserialize(pub, cph_buf, 1);
 
	if(!bswabe_dec(pub, prv, cph, m)){
		return die("%s", bswabe_error());
	}
	
	bswabe_cph_free(cph);
	
	plt = aes_128_cbc_decrypt(aes_buf, m);
	g_byte_array_set_size(plt, file_len);
	g_byte_array_free(aes_buf, 1);

	if(strlen(in_file) > 6 && !strcmp(in_file + strlen(in_file) - 6, ".cpabe") ){
		out_file = g_strndup(in_file, strlen(in_file) - 6);
	}else{
		out_file = strdup(in_file);
		keep=1;
	}

	if(spit_file(out_file, plt, 1)==-1){
		return -1;
	}

	if( !keep )
		unlink(in_file);

	return 0;
}

int cpabe_dec(unsigned char* pk_path, unsigned char* sk_path, unsigned char* ct, unsigned char** pt){

	bswabe_pub_t* pub;
	bswabe_prv_t* prv;
	int file_len;
	GByteArray* aes_buf;
	GByteArray* plt;
	GByteArray* cph_buf;
	GByteArray* sf_pf;
	GByteArray* sf_prvf;
	bswabe_cph_t* cph;
	element_t m;
	int dec_len;

	unsigned char* pub_file = pk_path;
	unsigned char* prv_file = sk_path;
	unsigned char* in_file  = ct;

	if((sf_pf = suck_file(pub_file)) == NULL) {
		return -1;
	}
	if((sf_prvf = suck_file(prv_file)) == NULL){
		return -1;
	}

	file_len = *((int*)in_file);
	guint aes_len = *((guint*)(in_file+4));
	guint cph_len = *((guint*)(in_file+8));
	
	aes_buf = g_byte_array_new();
	g_byte_array_set_size(aes_buf, aes_len);
	//g_byte_array_append(aes_buf, in_file+8, aes_len);
	memcpy(aes_buf->data, in_file+12, aes_len);
	//aes_buf = g_byte_array_new_take(in_file+8, aes_len);
	cph_buf = g_byte_array_new();
	g_byte_array_set_size(cph_buf, cph_len);
	//g_byte_array_append(cph_buf, in_file+8+aes_len, cph_len);
	memcpy(cph_buf->data, in_file+12+aes_len, cph_len);
	//cph_buf = g_byte_array_new_take(in_file+8+aes_len, cph_len);
	//file_len = cipher->len;

	pub = bswabe_pub_unserialize(sf_pf, 1);
	 
	prv = bswabe_prv_unserialize(pub,sf_prvf, 1);

	cph = bswabe_cph_unserialize(pub, cph_buf, 1);

	if(!bswabe_dec(pub, prv, cph, m)){
		return die("%s", bswabe_error());
	}
	
	bswabe_cph_free(cph);
	
	plt = aes_128_cbc_decrypt(aes_buf, m);
	g_byte_array_set_size(plt, file_len);
	g_byte_array_free(aes_buf, 1);

	*pt = plt->data;
	dec_len = plt->len;
	//if(strlen(in_file) > 6 && !strcmp(in_file + strlen(in_file) - 6, ".cpabe") ){
	//	out_file = g_strndup(in_file, strlen(in_file) - 6);
	//}else{
	//	out_file = strdup(in_file);
	//	keep=1;
	//}

	//if(spit_file(out_file, plt, 1)==-1){
	//	return -1;
	//}

	//if( !keep )
	//	unlink(in_file);

	return dec_len;
}
