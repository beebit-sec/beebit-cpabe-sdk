package tw.edu.au.csie.ucan.beebit;

class dec {
	public static void main(String[] args) {

		if(args.length < 4) {
			System.out.printf("Usage: dec [pk] [sk] [ct] [pt]\n");
			System.out.printf("pk: path to public key\n");
			System.out.printf("sk: path to secret key\n");
			System.out.printf("ct: path to encrypted file (cipher text)\n");
			System.out.printf("pt: path to original file (plain text)\n");
			System.exit(-1);
		}

		String pk = args[0];
		String sk = args[1];
		String ct = args[2];
		String pt = args[3];

		cpabeJNI bee = new cpabeJNI();

		int len = bee.fdec(pk, sk, ct, pt);
		if(len == -1) {
			System.out.printf("Decrypt failed!\n");
			System.exit(-1);
		}
		System.out.printf("Decrypt success!\n");
		System.out.printf("File (%s) decrypted to file (%s).\n", ct, pt);
	}	
}
