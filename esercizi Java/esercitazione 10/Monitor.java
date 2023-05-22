package ese10;
import java.util.Random;
import java.util.concurrent.locks.*;

public class Monitor {
	
	private int N;
	private int Sportelli[];
	private int SportelliLiberi;
	private int PostiLiberi;
	private int sospSportelli = 0;
	private int sospSala = 0;
	private Lock lock = new ReentrantLock();
	private Condition sala = lock.newCondition();
	private Condition sportello = lock.newCondition();
	private Random gen;
	private int tot_anagrafe = 0;
	private int tot_prenotazioni = 0;
	
	public Monitor(int MAX, int N, Random R) {
		this.N = N;
		this.gen = R;
		Sportelli = new int[N];
		
		this.PostiLiberi = MAX;
		this.SportelliLiberi = N;
		
		for(int i = 0; i < N; i++) {
			Sportelli[i] = 0;
		}
		
	}
	
	public void entraSala(int counter) throws InterruptedException {
		
		lock.lock();
		try {
			while(PostiLiberi == 0) {
				sospSala++;
				sala.await();
				sospSala--;
				
			}
			
			Thread.sleep(gen.nextLong(1,1000));

			PostiLiberi--;
			System.out.println("Sono l'utente numero " + (counter+1)+ " e sono entrato in sala");

		}finally {
			lock.unlock();
		}
		
}
	
	public int richiedeSportello(tiposerv S, int counter) throws InterruptedException {
		
		int i = 0;
		lock.lock();
		
		try {
			
			while(SportelliLiberi == 0) {
				sospSportelli++;
				sportello.await();
				sospSportelli--;
			}
			

			if(sospSala > 0) {
				sala.signal();
			}
			
			PostiLiberi++;

			SportelliLiberi--;

			for(i = 0; i < N; i++) {
				if(Sportelli[i] == 0) {
					Sportelli[i] = 1;
					break;
				}
			}
			
			
			if(S.equals(tiposerv.ANAGRAFE)) {
				tot_anagrafe++;
			}else{
				tot_prenotazioni++;
			}
			
			Thread.sleep(gen.nextLong(1,200));
			System.out.println("Sono l'utente numero " + (counter+1)+ " e ho occupato uno sportello");

				
		}finally {
			lock.unlock();
		}
		return i;
		
	}
	
	public void esceCUP(int K, int counter) {
		
		lock.lock();
		
		try {

			System.out.println("INDICE SPORTELLO: "+ K);
			Sportelli[K] = 0;
			SportelliLiberi++;

			if(sospSportelli > 0) {
				sportello.signal();
			}
			
			System.out.println("Sono l'utente numero " + (counter+1)+ " e sono uscito dal CUP");

		}finally {
			lock.unlock();
		}
	}
	
	public void stampa() {
		System.out.println("Il numero totale di prenotazioni è stato: " + tot_prenotazioni);
		System.out.println("Il numero totale di servizi anagrafe è stato: " + tot_anagrafe);

	}

}
