package ese10;

import java.util.Random;

public class Main {

	public static void main(String[] args) throws InterruptedException {
		Random gen = new Random(System.currentTimeMillis());

		int MAX = 50;
		int N = 10;
		int numUtenti = gen.nextInt(1,MAX);
		Utente[] utenti = new Utente[numUtenti];
		Monitor M = new Monitor(MAX, N, gen);
		
		for(int i = 0; i < numUtenti; i++) {
			utenti[i] = new Utente(M, gen, i);
		}
		
		for(Utente x : utenti) {
			x.start();
		}
		
		for(Utente x : utenti) {
			x.join();
		}
		
		M.stampa();

	}

}
