package ese;


import java.util.Random;

public class Main {

	public static void main(String[] args) {
		
		Random gen = new Random(System.currentTimeMillis()*1000);
		
		Banco B = new Banco(gen.nextInt(5), gen.nextInt(5), gen.nextDouble(6.37), gen.nextDouble(3.76));

		int numOp = gen.nextInt(10);
		int numAc = gen.nextInt(10);
		
		Operaio [] operai = new Operaio[numOp];
		Acquirente [] acquirenti = new Acquirente[numAc];

		
		for(int i = 0; i < numOp; i++) {
			
			Operaio o = new Operaio(B, i);
			operai[i] = o;
		}
		
		for(int j = 0; j < numAc; j++) {
			
			Acquirente a = new Acquirente(B, j);
			acquirenti[j] = a;
		}
		
		for(Thread t : operai) {
			t.start();
		}
		
		
		for(Thread t : acquirenti) {
			t.start();
		}
		
		for(Thread t : operai) {
			try {
				t.join();
			} catch (InterruptedException e) {
				System.err.println(e);
			}
		}
		
		for(Thread t : acquirenti) {
			try {
				t.join();
			} catch (InterruptedException e) {
				System.err.println(e);
			}
		}
		
		B.stampa();

	}

}


