package ese;

import java.util.Random;

public class Gruppo extends Thread{
	private int cardinalita;
	private Museo m;
	private Random r;
	
	public Gruppo(Museo m, Random r) {
		this.cardinalita = r.nextInt(10, 40);
		this.m = m;
		this.r = r;
	}
	
	@Override
	public void run() {
		
		try {
			m.EntraG(cardinalita);
			Thread.sleep(r.nextLong(1,3)*100);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		try {
			m.EsceG();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
