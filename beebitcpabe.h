#ifndef BEEBITCPABE_H
#define BEEBITCPABE_H

#include "cpabebuf.h"

cpabebuf* cpabe_enc_b(char* pk, char* pt, int pt_len, char* ap, cpabebuf* buf);
cpabebuf* cpabe_dec_b(char* pk, char* sk, char* ct, int ct_len, cpabebuf* buf);

int cpabe_setup(char* pk, char* mk);
/*  Purpose:
 *  Generate system parameters, a public key, and a master key
 *  used in keygen, encrytion, decrption
 *
 *  Parameters:
 *  1. pk: path to generate public key
 *  2. mk: path to generate master key
 *
 *  Return:
 *   0: success
 *  -1: failed
 */

int cpabe_vkeygen(char* sk, char* pk, char* mk, int no, char** attr);
/*  Purpose:
 *  Generate a secret key with the given attributes with public key and master key
 *  About the key attributes, please refer the following link 
 *  http://acsc.cs.utexas.edu/cpabe/cpabe-keygen.html
 *
 *  Parameters:
 *  1. pk: path to generate secret key
 *  2. pk: path of public key
 *  3. mk: path of master key 
 *  4. no: number of attributes
 *  5. attr: a serial of attributes in two forms, non-numerical and numerical, specified by string.
 *  (Ex. "boy", "student" for non-numerical attributes and "salary = 1000", "age >= 18" for numerical attributes)
 *
 *  Return:
 *   0: success
 *  -1: failed
 */

int cpabe_keygen(char* sk, char* pk, char* mk, int no, ...);
/*  Purpose:
 *  Generate a secret key with the given attributes with public key and master key
 *  About the key attributes, please refer the following link 
 *  http://acsc.cs.utexas.edu/cpabe/cpabe-keygen.html
 *
 *  Parameters:
 *  1. sk: path to generate secret key
 *  1. pk: path of public key
 *  2. mk: path of master key 
 *  4. no: number of attributes
 *  5. ...: a serial of attributes in two forms, non-numerical and numerical, specified by string.
 *  (Ex. "boy", "student" for non-numerical attributes and "salary = 1000", "age >= 18" for numerical attributes)
 *
 *  Return:
 *   0: success
 *  -1: failed
 */

int cpabe_enc(char* pk, void* pt, int pt_len, char* ap, void** ct);
int cpabe_enc_l(char* pk_, void* pt, int pt_len, char* ap, void** ct);
/*  Purpose:
 *  Encrypt non-file plaintext into non-file ciphertext with public key and policy using CPABE.  
 *
 *  Parameters:
 *  1. pk: path of public key
 *  2. pt: plain text (byte)
 *  3. pt_len: length of plain text
 *  3. ap: access policy (Please refer http://acsc.cs.utexas.edu/cpabe/cpabe-enc.html)
 *  (Ex. "boy and salary > 1000")
 *  4. ct: cipher text (byte)
 *
 *  Return:
 *   n: length of cipher text
 *  -1: failed
 */

int cpabe_fenc(char* pk, char* pt, char* ap, char* ct);
/*  Purpose:
 *  Encrypt file-based plaintext into file-based ciphertext with public key and policy using CPABE.  
 *
 *  Parameters:
 *  1. pk: path of public key
 *  2. pt: path of plain text (file)
 *  3. ap: access policy (Please refer http://acsc.cs.utexas.edu/cpabe/cpabe-enc.html)
 *  (Ex. "boy and salary > 1000")
 *  4. ct: path of cipher text (file)
 *
 *  Return:
 *   0: success
 *  -1: failed
 */

int cpabe_dec(char* pk, char* sk, void* ct, int ct_len, void** pt);
/*  Purpose:
 *  Decrypt non-file ciphertext into non-file plaintext with public key and secret key using CPABE.  
 *
 *  Parameters:
 *  1. pk: path of public key
 *  2. sk: path of secret key
 *  3. ct: cipher text (byte)
 *  4. pt: plain text (byte)
 *
 *  Return:
 *   n: length of plain text
 *  -1: failed
 */

int cpabe_fdec(char* pk, char* sk, char* ct, char* pt);
/*  Purpose:
 *  Decrypt file-based ciphertext into file-based plaintext with public key and secret key using CPABE.  
 *
 *  Parameters:
 *  1. pk: path of public key
 *  2. sk: path of secret key
 *  3. ct: path of cipher text (file)
 *  4. pt: path of plain text (file)
 *
 *  Return:
 *   0: success
 *  -1: failed
 */
#endif
