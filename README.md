# beebit-cpabe-sdk (v0.1)
Project BeeBit provides a series of SDK for developers who attempt to secure data communication. 

Module **beebit-cpabe-sdk** implements a novel encryption method called Ciphertext-Policy Attribute Based Encryption (**CP-ABE**). CP-ABE is a one-to-many asymmetric cryptosystem with supporting fine-grained access control. Data publisher can encrypt data and embed access policy using the publc key. Each data subscriber has a secret key with personal attributes. Only the data subscribers whose attributes meets the access policy can decrpy data using their secret keys. We believe that the features of CP-ABE is suitable for most Internet of Things (IoT) applications.

The development of **beebit-cpabe-sdk** is based on the following open source contributions.
1. PBC Library: the pairing-based cryptography library from Standord University. [Link](https://crypto.stanford.edu/pbc/)
2. libbswabe: a library implementing the core crypto operations of CP-ABE. [Link](http://acsc.cs.utexas.edu/cpabe/)
3. cpabe: a higher level functions and user interface of CP-ABE. [Link](http://acsc.cs.utexas.edu/cpabe/)

## A. INSTALLATION
For C developers, refer INSTALL_C

For JAVA developers, refer INSTALL_JAVA

For API reference, refer beebitcpabe.h

## REFERENCE
[1] http://blog.csdn.net/huifeideyema/article/details/51695231 
