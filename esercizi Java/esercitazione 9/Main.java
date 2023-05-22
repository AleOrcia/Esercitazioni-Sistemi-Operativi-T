package ese;

import java.util.Random;

public class Main {

	public static void main(String[] args) {
		
		Random r = new Random(System.currentTimeMillis());
		int prezzoMuseo = r.nextInt(10, 20);
		Museo m = new Museo(r.nextInt(10, 15), prezzoMuseo, r.nextInt(5, 10));
		
		int NT = r.nextInt(15, 30);
		int NS = r.nextInt(1, NT);
		int NG = NT-NS;
		System.out.println("NT="+NT+"\nNS="+NS+"\nNG="+NG);

		System.out.println("Il numero di scolaresche è " + NS + "\nIl numero di gruppi è " + NG);
		System.out.println("Il prezzo del biglietto del museo è " + prezzoMuseo);


		
		Thread [] threads = new Thread[NT];
		
		for (int i = 0; i < NS; i++) {
			threads[i] = new Scolaresca(m, r);
		}
		
		for (int i = 0; i < NG; i++) {
			threads[i+NS] = new Gruppo(m, r);
		}
		
		
		for(Thread x : threads) {
			x.start();
		}
		
		for(Thread x : threads) {
			try {
				x.join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		m.stampa();
	}

}
