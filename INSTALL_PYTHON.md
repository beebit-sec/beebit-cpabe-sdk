# Python Wrapper
Python wrapper uses Simplified Wrapper and Interface Generator (SWIG) to call native C APIs of beebit-cpabe-sdk.

## Environment
- swig: <code>sudo apt install swig</code>
- python: <code>sudo apt install python</code>
- python-dev: <code>sudo apt install python-dev</code>

## Installation
~~~make
make clean
make python
~~~	

## Evaluation
Chagne to example directory
~~~bash
cd python
~~~

### Setup
**Setup** generates the public key and the master key
~~~bash
python setup.py [pk] [mk]
~~~
- pk: path to generate public key
- mk: path to generate master key

### Keygen
**Keygen** generates the secret key with attributes
~~~bash
python keygen.py [sk] [pk] [mk] [no] [a1] ... [aN]
~~~
- sk: path to generate secret key
- pk: path to public key
- mk: path to master key
- no: number of attributes in generated secret key
- a1 ... aN: attributes

### Encrypt
**Encrypt** encrypts plaintext to ciphertext
~~~bash
python enc.py [pk] [pt] [ap] [ct]
~~~	
- pk: path to public key
- pt: path to original file (plaintext)
- ap: access policy
- ct: path to encrypted file (ciphertext)

### Decrypt
**Decrypt** decrypts ciphertext to plaintext
~~~bash
python dec.py [pk] [sk] [ct] [pt]
~~~
- pk: path to public key
- sk: path to secret key
- ct: path to encrypted file (ciphertext)
- pt: path to original file (plaintext)

### Encrypt / Decrypt
Previous examples encrypt and decrypt files. In this example, you can encrypt / decrypt input data.
~~~bash
python encdec.py [pk] [sk] [ap]
~~~
- pk: path to public key
- sk: path to secret key
- ap: access policy
