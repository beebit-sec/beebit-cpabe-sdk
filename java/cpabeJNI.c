#include <jni.h>
#include <stdbool.h>
#include "cpabeJNI.h"
#include "../beebitcpabe.h"

JNIEXPORT jint JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_setup
	(JNIEnv * env, jobject obj, jstring pk_path, jstring mk_path) {
	
	int len = (*env)->GetStringLength(env, pk_path);
	char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);

	len = (*env)->GetArrayLength(env, mk_path);
	char *mk = (*env)->GetStringUTFChars(env, mk_path, 0);

	return cpabe_setup(pk, mk);
}

JNIEXPORT jint JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_vkeygen
	(JNIEnv * env, jobject obj, jstring sk_path, jstring pk_path, jstring mk_path, jint attr_no, jobjectArray params) {
	return Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_keygen(env, obj, sk_path, pk_path, mk_path, attr_no, params);
}

JNIEXPORT jint JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_keygen
	(JNIEnv * env, jobject obj, jstring sk_path, jstring pk_path, jstring mk_path, jint attr_no, jobjectArray params) {

	char *sk = (*env)->GetStringUTFChars(env, sk_path, 0);
	char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);
	char *mk = (*env)->GetStringUTFChars(env, mk_path, 0);

	int argc = (int) attr_no;

	char **argv = (char **) malloc(argc * sizeof(char *));
	
	int i;

	for (i = 0; i < argc; i++) {
  		jstring arg = (jstring) ((*env)->GetObjectArrayElement(env, params, i));
  		argv[i] = (char*)((*env)->GetStringUTFChars(env, arg, 0));
  		//printf("%s\n",argv[i]);
	}
	return cpabe_vkeygen(sk, pk, mk, argc, argv);
}

JNIEXPORT jbyteArray JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_enc
	(JNIEnv * env, jobject obj, jstring pk_path, jbyteArray pt_str, jstring policy_str) {
	char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);
	jboolean isCopy;
	jbyte* pt = (*env)->GetByteArrayElements(env, pt_str, &isCopy); 
	int pt_len = (*env)->GetArrayLength(env, pt_str);
	//unsigned char *pt = (*env)->GetStringUTFChars(env, pt_str, 0);
	char *policy = (*env)->GetStringUTFChars(env, policy_str, 0);

	char* ct;

	int len = 0;

	if((len = cpabe_enc_l(pk, (char*)pt, pt_len, policy, &ct)) == -1){
		return NULL;
	}
	jbyteArray bytes = (*env)->NewByteArray(env, len);
	(*env)->SetByteArrayRegion(env, bytes, 0, len, (jbyte*)ct);
	
	return bytes;
}


JNIEXPORT jbyteArray JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_dec
	(JNIEnv * env, jobject obj, jstring pk_path, jstring sk_path, jbyteArray ct_str) {
	char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);
	char *sk = (*env)->GetStringUTFChars(env, sk_path, 0);
	jboolean isCopy;
	jbyte* ct = (*env)->GetByteArrayElements(env, ct_str, &isCopy); 
	int ct_len = (*env)->GetArrayLength(env, ct_str);

	char* pt;

	int len = 0;

	if((len = cpabe_dec(pk, sk, (char*)ct, ct_len, &pt)) == -1){
		return NULL;
	}

	(*env)->ReleaseByteArrayElements(env, ct_str, ct, 0);

	jbyteArray bytes = (*env)->NewByteArray(env, len);
	(*env)->SetByteArrayRegion(env, bytes, 0, len, (jbyte*)pt);

	return bytes;
}

JNIEXPORT jint JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_fenc
	(JNIEnv * env, jobject obj, jstring pk_path, jstring pt_path, jstring policy_str, jstring ct_path) {
	char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);
	char *pt = (*env)->GetStringUTFChars(env, pt_path, 0);
	char *policy = (*env)->GetStringUTFChars(env, policy_str, 0);
	char *ct = (*env)->GetStringUTFChars(env, ct_path, 0);

	return cpabe_fenc(pk, pt, policy, ct);
}

JNIEXPORT jint JNICALL Java_tw_edu_au_csie_ucan_beebit_cpabeJNI_fdec
	(JNIEnv * env, jobject obj, jstring pk_path, jstring sk_path, jstring ct_path, jstring pt_path) {
	char *pk = (*env)->GetStringUTFChars(env, pk_path, 0);
	char *sk = (*env)->GetStringUTFChars(env, sk_path, 0);
	char *ct = (*env)->GetStringUTFChars(env, ct_path, 0);
	char *pt = (*env)->GetStringUTFChars(env, pt_path, 0);

	return cpabe_fdec(pk, sk, ct, pt);
}
