package ese;

import java.util.Random;

public class Operaio extends Thread {
	Banco B;
	int fragole = 0;
	int asparagi = 0;
	int indice = 0;

	public Operaio(Banco b, int indice) {
		this.B = b;
		this.indice = indice;
		
	}
	
	@Override
	public void run() {
		
		Random gen = new Random(System.currentTimeMillis()*1000);
		int counter = 0;
		int max = gen.nextInt(3);
		this.fragole = gen.nextInt(15);
		this.asparagi = gen.nextInt(20);
		
		while(counter < max) {
			System.out.println("Sono l'operaio di indice "+ indice);

			this.B.deposita(fragole, asparagi);
			try {
				Thread.sleep(gen.nextInt(100));
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			counter++;
		}
	}
	
}
