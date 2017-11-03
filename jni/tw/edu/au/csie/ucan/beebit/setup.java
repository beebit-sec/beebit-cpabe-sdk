package tw.edu.au.csie.ucan.beebit;

class setup {
	public static void main(String[] args) {
		cpabeJNI bee = new cpabeJNI();
		if(bee.setup("./pubKey", "./mstKey") == -1){
    			System.out.print("SETUP FAILED(JNI)\n");
		}
    		System.out.print("SETUP SUCCESS(JNI)\n");
  	}	
}
