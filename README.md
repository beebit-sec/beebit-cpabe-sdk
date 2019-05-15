# beebit-cpabe-sdk (v0.2)
The **Beebit** project provides a set of modules for developers who attempt to secure data communication in Internet of Thing (IoT) environment.

The **beebit-cpabe-sdk** module implements a novel cryptosystem called Ciphertext-Policy Attribute-Based Encryption (**CP-ABE**)[1]. CP-ABE is an one-to-many asymmetric cryptosystem with supporting fine-grained access control. Data owner can encrypt plaintext to ciphertext with embedded access policy. Each data user has one secret key with personal attributes. Only the secret keys with attributes, that satisfy the access policy, can decrypt ciphertext to plaintext. We believe that CP-ABE is suitable in cloud and IoT environment.

The implementation of **beebit-cpabe-sdk** is based on the following open source projects.
1. PBC Library: the pairing-based cryptography library from Standord University. [Link](https://crypto.stanford.edu/pbc/)
2. libbswabe: a library implementing the core crypto operations of CP-ABE. [Link](http://acsc.cs.utexas.edu/cpabe/)
3. cpabe: a higher level functions and user interface of CP-ABE. [Link](http://acsc.cs.utexas.edu/cpabe/)

## Environment
- **OS**: Linux (Ubuntu is the test system)
- **Tools**:
	- flex: <code>sudo apt install flex</code>
	- bison: <code>sudo apt install bison</code>
- **Library**:
	- glib (>2.0.0): <code>sudo apt install libglib2.0-dev</code>
	- gmp (>4.0.0): <code>sudo apt install libgmp-dev</code>
	- ssl: <code>sudo apt install libssl-dev</code>
- **Library pbc**:
	- Download source from [https://crypto.stanford.edu/pbc/](https://crypto.stanford.edu/pbc/)
	- Unpack source tarball (eg., <code>tar zxvf pbc-0.5.14.tar.gz</code>)
	- Build source
		- <code>./configure --prefix=/usr/local --with-pic</code> 
		- <code>make</code> 
		- <code>sudo make install</code> 
- **Library bswabe**:
	- Download source from [http://acsc.cs.utexas.edu/cpabe/](http://acsc.cs.utexas.edu/cpabe/)
	- Unpack source tarball (eg., <code>tar zxvf libbswabe-0.9.tar.gz</code>)
	- Build source
		- <code>./configure --prefix=/usr/local</code> 
		- <code>make CC="gcc -fPIC"</code> 
		- <code>sudo make install</code> 

## Installation
The **beebit-cpabe-sdk** current supports three languages, native C, Java, and Python.

1. [Native C](INSTALL_C.md)
2. [Java Wrapper](INSTALL_JAVA.md) / JNI [2]
3. [Python Wrapper](INSTALL_PYTHON.md) / SWIG [3]

## Reference
1. John Bethencourt ; Amit Sahai ; Brent Waters, "Ciphertext-Policy Attribute-Based Encryption,"  2007 IEEE Symposium on Security and Privacy (SP '07).
2. https://docs.oracle.com/javase/8/docs/technotes/guides/jni/
3. http://www.swig.org/
