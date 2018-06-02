package tw.edu.au.csie.ucan.beebit;

class setup {
	public static void main(String[] args) {
		cpabeJNI beebit = new cpabeJNI();
		if(beebit.setup("./pubKey", "./mstKey") == cpabeJNI.EXIT_FAILURE){
    			System.out.print("SETUP FAILED(JNI)\n");
		}
    		System.out.print("SETUP SUCCESS(JNI)\n");
  	}	
}
