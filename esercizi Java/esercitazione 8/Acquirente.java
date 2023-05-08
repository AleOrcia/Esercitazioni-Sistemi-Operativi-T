package ese;

import java.util.Random;

public class Acquirente extends Thread {
	Banco B;
	int indice = 0;
	
	public Acquirente(Banco b, int indice) {
		this.B = b;
		this.indice = indice;
	}
	
	@Override
	public void run() {
		int OK = 0;
		
		Random gen = new Random(System.currentTimeMillis()*1000);
		int fragole = gen.nextInt(20);
		int asparagi = gen.nextInt(20);
		int r = gen.nextInt(2);
		
		if(r == 0) {
			OK = B.acquista(fragole, asparagi, TipoMerce.FRAGOLA);
		}else {
			OK = B.acquista(fragole, asparagi, TipoMerce.ASPARAGO);
		}
		
		if(OK==1) {
			System.out.println("Acquisto riuscito! Indice: "+ indice);

		}else {
			System.out.println("Acquisto fallito! Indice: " + indice);
		}
		
	}
	
	

}
