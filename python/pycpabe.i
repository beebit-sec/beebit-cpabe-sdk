%typemap(in) char ** {
    /* Check if is a list */
    if (PyList_Check($input)) {
    int size = PyList_Size($input);
    int i = 0;
    $1 = (char **) malloc((size+1)*sizeof(char *));
    for (i = 0; i < size; i++) {
      PyObject *o = PyList_GetItem($input,i);
      if (PyString_Check(o))
        $1[i] = PyString_AsString(PyList_GetItem($input,i));
      else {
        PyErr_SetString(PyExc_TypeError,"list must contain strings");
        free($1);
        return NULL;
      }
    }
    $1[i] = 0;
  } else {
    PyErr_SetString(PyExc_TypeError,"not a list");
    return NULL;
  }
}

%typemap(freearg) char ** {
  free((char *) $1);
}

%module pycpabe
//%include "typemaps.i"
//%apply char **OUTPUT {char** ct};
//%apply char *OUTPUT {char** pt};
//%inline %{
//extern int cpabe_setup(char* pk_path, char* mk_path);
//extern int cpabe_vkeygen(char* sk_path, char* pk_path, char* mk_path, int attr_no, char** argv);
//extern int cpabe_keygen(char* sk_path, char* pk_path, char* mk_path, int attr_no, ...);
//extern int cpabe_enc(char* pk_path, char* pt, char* policy_str, char** ct);
//extern int cpabe_enc_l(char* pk_path, char* pt, int pt_len, char* policy_str, char** ct);
//extern int cpabe_fenc(char* pk_path, char* pt_path, char* policy_str, char* ct_path);
//extern int cpabe_dec(char* pk_path, char* sk_path, char* ct, char** pt);
//extern int cpabe_fdec(char* pk_path, char* sk_path, char* ct_path, char* pt_path);
//%}

extern int cpabe_setup(char* pk_path, char* mk_path);
extern int cpabe_vkeygen(char* sk_path, char* pk_path, char* mk_path, int attr_no, char** argv);
extern int cpabe_keygen(char* sk_path, char* pk_path, char* mk_path, int attr_no, ...);
extern int cpabe_enc(char* pk_path, char* pt, char* policy_str, char** ct);
extern int cpabe_enc_l(char* pk_path, char* pt, int pt_len, char* policy_str, char** ct);
extern int cpabe_fenc(char* pk_path, char* pt_path, char* policy_str, char* ct_path);
extern int cpabe_dec(char* pk_path, char* sk_path, char* ct, char** pt);
extern int cpabe_fdec(char* pk_path, char* sk_path, char* ct_path, char* pt_path);
