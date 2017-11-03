#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <glib.h>
#include <pbc.h>
#include <pbc_random.h>
#include <stdarg.h>
#include "bswabe.h"
#include "common.h"
#include "policy_lang.h"

/*
	TODO ensure we don't give out the same attribute more than once (esp
	as different numerical values)
*/

//char*  pub_file = 0;
//char*  msk_file = 0;
//char** attrs    = 0;

//char*  out_file = "priv_key";

gint comp_string( gconstpointer a, gconstpointer b){
	return strcmp(a, b);
}

int cpabe_keygen(char* priv_name, char* pub_key, char* msk_key, int attribute, ...){

	bswabe_pub_t* pub;
	bswabe_msk_t* msk;
	bswabe_prv_t* prv;
	GSList* alist;
	GSList* ap;
	alist = 0;
	int i;
	int n;

	unsigned char* pub_file = pub_key;
	unsigned char* msk_file = msk_key;
	unsigned char* out_file = "priv_key";

	//if( !pub_file || !msk_file || !alist ) 是否判斷有無檔案
	if(!strcmp(priv_name,"default")){
		out_file = "priv_key";
	}else{
		out_file = priv_name;
	}

	va_list valist;
	int num;

	va_start(valist,attribute);

	for(num=0;num<attribute;num++){
		char *att;
		att = va_arg(valist,char*);
		if(parse_attribute(&alist,att) == -1){
			return -1;
		}
	}

	va_end(valist);
	alist = g_slist_sort(alist, comp_string);//排序照英文字母頭
	n = g_slist_length(alist);

	unsigned char** attrs = malloc((n + 1) * sizeof(char*));
	i = 0;

	for(ap = alist; ap ; ap = ap->next )
		attrs[i++] = ap->data;
  	
	attrs[i] = 0;
  
	GByteArray* temp;

	if((temp  = suck_file(pub_file)) == NULL) {
		return -1;
	}
  	pub = bswabe_pub_unserialize(temp, 1);

	
	if((temp  = suck_file(msk_file)) == NULL) {
		return -1;
	}
  	msk = bswabe_msk_unserialize(pub, temp, 1);
  
  	prv = bswabe_keygen(pub, msk, attrs);
	if(spit_file(out_file, bswabe_prv_serialize(prv), 1)==-1){
		return -1;
	}
  
  	return 0;
}

int cpabe_vkeygen(char* priv_name, char* pub_key, char* msk_key, int attribute, char** argv){

	bswabe_pub_t* pub;
	bswabe_msk_t* msk;
	bswabe_prv_t* prv;
	GSList* alist;
	GSList* ap;
	alist = 0;
	int i;
	int n;

	unsigned char* pub_file = pub_key;
	unsigned char* msk_file = msk_key;
	unsigned char* out_file = "priv_key";

	//if( !pub_file || !msk_file || !alist ) 是否判斷有無檔案
	if(!strcmp(priv_name,"default")){
		out_file = "priv_key";
	}else{
		out_file = priv_name;
	}

	//va_list valist;
	int num;

	//va_start(valist,attribute);

	for(num=0;num<attribute;num++){
		//char *att;
		//att = va_arg(valist,char*);
		if(parse_attribute(&alist,argv[num]/*att*/) == -1){
			return -1;
		}
	}

	//va_end(valist);
	alist = g_slist_sort(alist, comp_string);//排序照英文字母頭
	n = g_slist_length(alist);

	unsigned char** attrs = malloc((n + 1) * sizeof(char*));
	i = 0;

	for(ap = alist; ap ; ap = ap->next )
		attrs[i++] = ap->data;
  	
	attrs[i] = 0;
  
	GByteArray* temp;

	if((temp  = suck_file(pub_file)) == NULL) {
		return -1;
	}
  	pub = bswabe_pub_unserialize(temp, 1);

	
	if((temp  = suck_file(msk_file)) == NULL) {
		return -1;
	}
  	msk = bswabe_msk_unserialize(pub, temp, 1);
  
  	prv = bswabe_keygen(pub, msk, attrs);
	if(spit_file(out_file, bswabe_prv_serialize(prv), 1)==-1){
		return -1;
	}
  
  	return 0;
}
