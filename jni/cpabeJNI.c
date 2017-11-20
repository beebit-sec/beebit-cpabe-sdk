#include <jni.h>
#include <stdbool.h>
#include "cpabeJNI.h"
#include "../beebitcpabe.h"

JNIEXPORT jint JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_setup
	(JNIEnv * env, jobject obj, jstring pk_path, jstring mk_path) {
	
	int len = (*env)->GetStringLength(env, pk_path);
	//unsigned char* pk = malloc(sizeof(unsigned char) * len);
    	//unsigned char* pk = (*env)->GetByteArrayRegion(env, pk_path, 0);
	unsigned char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);
	len = (*env)->GetArrayLength(env, mk_path);
	//unsigned char* mk = malloc(sizeof(unsigned char) * len);
    	//(*env)->GetByteArrayRegion(env, mk_path, 0, len, mk);
	unsigned char *mk = (*env)->GetStringUTFChars(env, mk_path, 0);

	return cpabe_setup(pk, mk);
}

JNIEXPORT jint JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_keygen
	(JNIEnv * env, jobject obj, jstring pk_path, jstring mk_path, jstring sk_path, jint attr_no, jobjectArray params) {

	unsigned char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);
	unsigned char *mk = (*env)->GetStringUTFChars(env, mk_path, 0);
	unsigned char *sk = (*env)->GetStringUTFChars(env, sk_path, 0);

	int argc = (int) attr_no;

	//unsigned char argv[argc][50];

	char **argv = (char **) malloc(argc * sizeof(char *));
	
	int i;

	for (i = 0; i < argc; i++) {
  		jstring arg = (jstring) ((*env)->GetObjectArrayElement(env, params, i));
  		argv[i] = (char*)((*env)->GetStringUTFChars(env, arg, 0));
		//argv[i] = (char*)(*env)->ReleaseStringUTFChars(env, arg, argc);
  		printf("%s\n",argv[i]);
		//printf("%s\n", argv[i]);
	}
	return cpabe_vkeygen(sk, pk, mk, argc, argv);
}

JNIEXPORT jbyteArray JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_enc
	(JNIEnv * env, jobject obj, jstring pk_path, jbyteArray pt_str, jstring policy_str) {
	unsigned char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);
	jboolean isCopy;
	jbyte* pt = (*env)->GetByteArrayElements(env, pt_str, &isCopy); 
	//unsigned char *pt = (*env)->GetStringUTFChars(env, pt_str, 0);
	unsigned char *policy = (*env)->GetStringUTFChars(env, policy_str, 0);

	unsigned char* ct;

	int len = 0;

	if((len = cpabe_enc(pk, (unsigned char*)pt, policy, &ct)) == -1){
		return NULL;
	}

	jbyteArray bytes = (*env)->NewByteArray(env, len);
	(*env)->SetByteArrayRegion(env, bytes, 0, len, (jbyte*)ct);
	
	return bytes;
}


JNIEXPORT jbyteArray JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_dec
	(JNIEnv * env, jobject obj, jstring pk_path, jstring sk_path, jbyteArray ct_str) {
	unsigned char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);
	unsigned char *sk = (*env)->GetStringUTFChars(env, sk_path, 0);
	jboolean isCopy;
	jbyte* ct = (*env)->GetByteArrayElements(env, ct_str, &isCopy); 

	unsigned char* pt;

	int len = 0;

	if((len = cpabe_dec(pk, sk, (unsigned char*)ct, &pt)) == -1){
		return NULL;
	}

	(*env)->ReleaseByteArrayElements(env, ct_str, ct, 0);

	jbyteArray bytes = (*env)->NewByteArray(env, len);
	(*env)->SetByteArrayRegion(env, bytes, 0, len, (jbyte*)pt);

	return bytes;
}

JNIEXPORT jint JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_fenc
	(JNIEnv * env, jobject obj, jstring pk_path, jstring pt_path, jstring policy_str, jstring ct_path) {
	unsigned char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);
	unsigned char *pt = (*env)->GetStringUTFChars(env, pt_path, 0);
	unsigned char *policy = (*env)->GetStringUTFChars(env, policy_str, 0);
	unsigned char *ct = (*env)->GetStringUTFChars(env, ct_path, 0);

	return cpabe_fenc(pk, pt, policy, ct);
}

JNIEXPORT jint JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_fdec
	(JNIEnv * env, jobject obj, jstring pk_path, jstring sk_path, jstring ct_path) {
	unsigned char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);
	unsigned char *sk = (*env)->GetStringUTFChars(env, sk_path, 0);
	unsigned char *ct = (*env)->GetStringUTFChars(env, ct_path, 0);

	return cpabe_fdec(pk, sk, ct);
}
