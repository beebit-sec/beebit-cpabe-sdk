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
extern int cpabe_setup(char* pk_path, char* mk_path);
extern int cpabe_vkeygen(char* sk_path, char* pk_path, char* mk_path, int attr_no, char** argv);
extern int cpabe_keygen(char* sk_path, char* pk_path, char* mk_path, int attr_no, ...);
extern int cpabe_enc(char* pk_path, char* pt, char* policy_str, char** ct);
extern int cpabe_enc_l(char* pk_path, char* pt, int pt_len, char* policy_str, char** ct);
extern cpabebuf* cpabe_enc_b(char* pk_path, char* pt, int pt_len, char* policy_str, cpabebuf* buf);
extern int cpabe_fenc(char* pk_path, char* pt_path, char* policy_str, char* ct_path);
extern int cpabe_dec(char* pk_path, char* sk_path, char* ct, char** pt);
extern cpabebuf* cpabe_dec_b(char* pk_path, char* sk_path, char* ct, cpabebuf* buf);
extern int cpabe_fdec(char* pk_path, char* sk_path, char* ct_path, char* pt_path);
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
