package ese10;

import java.util.Random;

public class Utente extends Thread{
	
	private Monitor M;
	private Random gen;
	private int counter;
	
	public Utente(Monitor M, Random R, int counter) {
		this.M = M;
		this.gen = R;
		this.counter = counter;
	}
	
	@Override
	public void run() {
		try {
			M.entraSala(counter);
			
		} catch (InterruptedException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		

		int random = gen.nextInt();
		tiposerv S;
		
		if((random%2) == 0) {
			S = tiposerv.ANAGRAFE;
		}else {
			S = tiposerv.PRENOTAZIONE;
		}
		
		int K=0;
		try {
			
			
			K = M.richiedeSportello(S, counter);
			Thread.sleep(gen.nextLong(1,600));
			

		} catch (InterruptedException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		M.esceCUP(K, counter);
	}

}
