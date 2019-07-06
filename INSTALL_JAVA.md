# Java Wrapper
Java wrapper uses Java Native Interface (JNI) to call native C APIs of beebit-cpabe-sdk.

## Environment
- **Java Development Kit (JDK)**:
	- default JDK: <code>sudo apt install default-jdk</code>

- **Java Include**: make sure the following environment parameters in Makefile are correct
	- JAVA_PATH
	- JAVA_BIN_PATH
	- JNI_H_PATH
	- JNI_OS_H_PATH

## Installation
You MUST install Java Development Kit (JDK) before install this Java wrapper.
~~~make
make clean
make java
~~~	

## Evaluation
Chagne to java directory
~~~bash
cd java
~~~

### Setup
**Setup** generates the public key and the master key
~~~bash
java -Djava.library.path=.. tw/edu/au/csie/ucan/beebit/setup [pk] [mk]
~~~
- pk: path to generate public key
- mk: path to generate master key

### Keygen
**Keygen** generates the secret key with attributes
~~~bash
java -Djava.library.path=.. tw/edu/au/csie/ucan/beebit/keygen [sk] [pk] [mk] [no] [a1] ... [aN]
~~~
- sk: path to generate secret key
- pk: path to public key
- mk: path to master key
- no: number of attributes in generated secret key
- a1 ... aN: attributes

### Encrypt
**Encrypt** encrypts plaintext to ciphertext
~~~bash
java -Djava.library.path=.. tw/edu/au/csie/ucan/beebit/enc [pk] [pt] [ap] [ct]
~~~	
- pk: path to public key
- pt: path to original file (plaintext)
- ap: access policy
- ct: path to encrypted file (ciphertext)

### Decrypt
**Decrypt** decrypts ciphertext to plaintext
~~~bash
java -Djava.library.path=.. tw/edu/au/csie/ucan/beebit/dec [pk] [sk] [ct] [pt]
~~~
- pk: path to public key
- sk: path to secret key
- ct: path to encrypted file (ciphertext)
- pt: path to original file (plaintext)

### Encrypt / Decrypt
Previous examples encrypt and decrypt files. In this example, you can encrypt / decrypt input data.
~~~bash
java -Djava.library.path=.. tw/edu/au/csie/ucan/beebit/encdec [pk] [sk] [ap]
~~~
- pk: path to public key
- sk: path to secret key
- ap: access policy
