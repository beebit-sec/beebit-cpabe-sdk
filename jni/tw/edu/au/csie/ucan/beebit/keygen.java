package tw.edu.au.csie.ucan.beebit;

class keygen {
	public static void main(String[] args) {

		if(args.length < 5) {
			System.out.printf("Usage: keygen [sk] [pk] [mk] [no] [a1] ... [aN]\n");
			System.out.printf("sk: path to generate secret key\n");
			System.out.printf("pk: path to public key\n");
			System.out.printf("mk: path to master key\n");
			System.out.printf("no: number of attributes in generated secret key\n");
			System.out.printf("a1 ... aN: attributes\n");
			System.exit(-1);	
		}

		String sk = args[0];
		String pk = args[1];
		String mk = args[2];
		int no = Integer.parseInt(args[3]);
	
		cpabeJNI bee = new cpabeJNI();
		/*
		if(bee.keygen("./pubKey","./mstKey","./secKey_ok",3,"bob","make","role = 1") == -1) 
		{
			System.out.print("OK KEYGEN FAILED(JNI)\n");
		}
		System.out.print("OK KEYGEN SUCCESS(JNI)\n");
		
		String[] attrs = {"alice","femail","role = 3"};
		*/
		String[] attrs = new String[no];
		int i;
		for(i=0;i<no;i++) {
			attrs[i] = args[4+i];	
			System.out.printf("Attribute %d: %s\n", i, attrs[i]);
		}

		//if(bee.keygen("./pubKey","./mstKey","./secKey_ng",3,"alice","female","role = 3") == -1)
		if(bee.keygen(sk, pk, mk, no, attrs) == -1)
		{
    			System.out.print("Keygen failed!\n");
			System.exit(-1);
		}

    		System.out.printf("Keygen success!\n");
    		System.out.printf("Secret key: %s\n", sk);
  }	
}
