package tw.edu.au.csie.ucan.beebit;

class setup {
  public static void main(String[] args) {
    
    if(args.length < 2) {
      System.out.printf("Usage: setup [pk] [mk]\n");
      System.out.printf("pk: path to generate public key\n");
      System.out.printf("mk: path to generate master key\n");
      System.exit(-1);
		}

		String pk = args[0];
		String mk = args[1];

		cpabeJNI bee = new cpabeJNI();
		if(bee.setup(pk, mk) == -1){
    	System.out.printf("Setup failed!\n");
			System.exit(-1);
		}
    System.out.printf("Setup success!\n");
    System.out.printf("Public key: %s\n", pk);
    System.out.printf("Master key: %s\n", mk);
  }
}	
