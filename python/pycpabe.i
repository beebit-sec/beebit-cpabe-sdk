%module pycpabe
%include type.i
%{
#include "../beebitcpabe.h"
%}
/*
%typemap(in) cpabebuf* {
  if (!PyString_Check($input)) {
    PyErr_SetString(PyExc_ValueError,"Expected a string");
    return NULL;
  }
  $1 = PyString_AsString($input);
  $2 = PyString_Size($input);
}
*/
extern cpabebuf* new_cpabebuf();
extern void free_cpabebuf(cpabebuf* buf);
extern int cpabebuf_len(cpabebuf* buf);
extern int cpabe_setup(char* pk, char* mk);
extern int cpabe_vkeygen(char* sk, char* pk, char* mk, int no, char** attr);
extern int cpabe_keygen(char* sk, char* pk, char* mk, int no, ...);
extern int cpabe_enc(char* pk, void* pt, int pt_len, char* ap, void** ct);
extern cpabebuf* cpabe_enc_b(char* pk, char* pt, int pt_len, char* ap, cpabebuf* buf);
extern int cpabe_fenc(char* pk, char* pt, char* ap, char* ct);
extern int cpabe_dec(char* pk, char* sk, void* ct, int ct_len, void** pt);
extern cpabebuf* cpabe_dec_b(char* pk, char* sk, char* ct, int ct_len, cpabebuf* buf);
extern int cpabe_fdec(char* pk, char* sk, char* ct, char* pt);
/*
%typemap(in) cpabebuf* {
  $1 = PyString_AsString($input->data);
  $2 = PyString_Size($input->len);
}

%typemap(out) char* {
    $result = PyString_FromStringAndSize($1->data,$1->len);
}
*/
%include "cdata.i"
extern void* cpabebuf_data(cpabebuf* buf);
