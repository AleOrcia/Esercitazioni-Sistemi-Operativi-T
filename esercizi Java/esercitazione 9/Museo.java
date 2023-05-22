package ese;

import java.util.concurrent.Semaphore;

public class Museo {
	private int PT;
	private Semaphore SM;
	private Semaphore SemG; //privato
	private Semaphore SemS; //privato
	private int MAX;
	private int NA;
	private int totale;
	private int personeTotali;
	
	public Museo(int PT, int MAX, int NA) {
		this.PT = PT;
		this.SM = new Semaphore(1);
		this.MAX = MAX;
		this.NA = NA;
		this.SemG = new Semaphore(0);
		this.SemS = new Semaphore(0);
		this.totale = 0;
		this.personeTotali = 0;
	}
	
	
	public void EntraS(int cardinalita) throws InterruptedException {
		SM.acquire();
		
		while(MAX <= 0) {
			
			SM.release();
			SemS.acquire();
			SM.acquire();
			
		}		
		MAX--;
		
		accumulaPersone(cardinalita);

		
		SM.release();
		
	}
	
	public void EntraG(int cardinalita) throws InterruptedException {
		
		SM.acquire();
		
		while(MAX <= 0 || NA <= 0) {
			
			SM.release();
			SemG.acquire();
			SM.acquire();
			
		}		
		MAX--;
		NA--;
		
		accumulaSoldi(cardinalita);
		accumulaPersone(cardinalita);
		
		SM.release();
		
	}
	
	public void EsceS() throws InterruptedException {
		SM.acquire();
		MAX++;
		SemS.release();
		SM.release();
		
	}
	
	public void EsceG() throws InterruptedException {
		SM.acquire();
		MAX++;
		NA++;
		SemG.release();
		SM.release();
		
	}
	
	public void stampa() {
		System.out.println("La somma degli importi di tutti i\n"
				+ "biglietti venduti è di "+ totale + " e il numero totale di persone\n"
				+ "che hanno visitato il museo è "+ personeTotali);
	}
	
	public void accumulaSoldi(int cardi) {
		
		totale = totale + (cardi*PT);		
	}
	
	public void accumulaPersone(int cardi) {
		personeTotali += cardi;
	}
	

}




