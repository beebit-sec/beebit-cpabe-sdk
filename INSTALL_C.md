# Native C

## Installation
~~~make
make clean
make
sudo make install
~~~	

## Evaluation
There are three users.
- Bob: teacher, cs department
- Alice: student, cs department
- John: teacher, mis department

Chagne to example directory
~~~bash
cd example
~~~

### Step 1. generate public key and master key
~~~bash
./setup pk mk
~~~
A public key, **pk**, and a master key, **mk**, will be generated in example directory.

### Step 2. generate the secret keys for Bob and Alice
~~~base
./keygen sk_bob pk mk 3 "Bob" "CS" "Teacher"
./keygen sk_alice pk mk 3 "Alice" "CS" "Student"
./keygen sk_john pk mk 3 "John" "MIS" "Teacher"
~~~
The secret keys, **sk_bob**, **sk_alice**, and **sk_john** will be generated for Bob, Alice, and John in example directory.

### Step 3. Encrypt data for CS teacher
According to the users' attributes, only Bob can decrypt data.
(There is a file data with content in example directorty.)

~~~bash
./enc pk data "CS and Teacher" data.enc
./dec pk sk_alice data.enc data  # failed since Alice is a student
./dec pk sk_john data.enc data   # failed since John is in MIS department
./dec pk sk_bob data.enc data    # success, data.enc is decrypted to data
~~~

### Step 4. Encrypt data for CS
According to the users' attributes, Bob and Alice can decrypt data.
(There is a file data with content in example directorty.)

~~~bash
./enc pk data "CS" data.enc
./dec pk sk_john data.enc data   # failed since John is in MIS department
./dec pk sk_bob data.enc data    # success, data.enc is decrypred to data
./enc pk data "CS" data.enc
./dec pk sk_alice data.enc data  # success, data.enc is decrypred to data
~~~

### Step 5. Encrypt data for Teacher
According to the users' attributes, Bob and John can decrypt data.
(There is a file data with content in example directorty.)

~~~bash
./enc pk data "Teacher" data.enc
./dec pk sk_alice data.enc data  # failed since Alice is a student
./dec pk sk_bob data.enc data    # success, data.enc is decrypred to data
./enc pk data "Teacher" data.enc
./dec pk sk_john data.enc data   # success, data.enc is decrypred to data
~~~

For command usage, please refer the following section.

## Usage
### Setup
**Setup** generates the public key and the master key
~~~bash
./setup [pk] [mk]
~~~
- pk: path to generate public key
- mk: path to generate master key

### Keygen
**Keygen** generates the secret key with attributes
~~~bash
./keygen [sk] [pk] [mk] [no] [a1] ... [aN]
~~~
- sk: path to generate secret key
- pk: path to public key
- mk: path to master key
- no: number of attributes in generated secret key
- a1 ... aN: attributes

### Encrypt
**Encrypt** encrypts plaintext to ciphertext
~~~bash
./enc [pk] [pt] [ap] [ct]
~~~	
- pk: path to public key
- pt: path to orginal file (plaintext)
- ap: access policy
- ct: path to encrypted file (ciphertext)

### Decrypt
**Decrypt** decrypts ciphertext to plaintext
~~~bash
./dec [pk] [sk] [ct] [pt]
~~~
- pk: path to public key
- sk: path to secret key
- ct: path to encrypted file (ciphertext)
- pt: path to original file (plaintext)

### Encrypt / Decrypt
Previous examples encrypt and decrypt files. In this example, you encrypt / decrypt input data.
~~~bash
./encdec [pk] [sk] [ap]
./encdecb [pk] [sk] [ap]
~~~
- pk: path to public key
- sk: path to secret key
- ap: access policy
