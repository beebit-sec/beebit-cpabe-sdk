import sys
import pycpabe

argc = len(sys.argv)

if argc < 5:
	print("Usage: dec [pk] [sk] [ct] [pt]")
	print("pk: path to public key")
	print("sk: path to secret key")
	print("ct: path to encrypted file (cipher text)")
	print("pt: path to original file (plain text)")
	sys.exit()

pk = sys.argv[1]
sk = sys.argv[2]
ct = sys.argv[3]
pt = sys.argv[4]

if pycpabe.cpabe_fdec(pk, sk, ct, pt) == -1:
	print("Decrypt failed!")
	sys.exit()

print("Decrypt success!")
print("File (%s) decrypted to file (%s) " %(ct, pt))
