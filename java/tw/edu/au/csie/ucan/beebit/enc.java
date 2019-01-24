package tw.edu.au.csie.ucan.beebit;

class enc {
	public static void main(String[] args) {

		if(args.length < 4) {
			System.out.printf("Usage: enc [pk] [pt] [ap] [ct]\n");
			System.out.printf("pk: path to public key\n");
			System.out.printf("pt: path to file (plain text)\n");
			System.out.printf("ap: access policy\n");
			System.out.printf("ct: path to encrypted file (cipher text)\n");
			System.exit(-1);
		}

		String pk = args[0];
		String pt = args[1];
		String ap = args[2];
		String ct = args[3];

		cpabeJNI bee = new cpabeJNI();

		int len = bee.fenc(pk, pt, ap, ct);
		if(len == -1) {
			System.out.printf("Encrypt failed!\n");
			System.exit(-1);
		}

		System.out.printf("Encrypt success!\n");
		System.out.printf("File (%s) encrypted to file (%s) with policy (%s).\n", pt, ct, ap);
	}	
}
