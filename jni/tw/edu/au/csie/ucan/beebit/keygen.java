package tw.edu.au.csie.ucan.beebit;

class keygen {
	public static void main(String[] args) {
		cpabeJNI bee = new cpabeJNI();
		if(bee.keygen("./pubKey","./mstKey","./secKey_ok",3,"bob","make","role = 1") == -1) 
		{
			System.out.print("OK KEYGEN FAILED(JNI)\n");
		}
		System.out.print("OK KEYGEN SUCCESS(JNI)\n");

		if(bee.keygen("./pubKey","./mstKey","./secKey_ng",3,"alice","female","role = 3") == -1)
		{
    			System.out.print("NG KEYGEN FAILED(JNI)\n");
		}
    		System.out.print("NG KEYGEN SUCCESS(JNI)\n");
  }	
}
