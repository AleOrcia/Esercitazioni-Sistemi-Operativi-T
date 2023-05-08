package ese;

public class Banco {
	
	private int fragole_disp, asparagi_disp;
	private double Pf, Pa, incasso;
	
	public Banco(int frag, int asp, double Pf, double Pa) {
		this.fragole_disp = frag;
		this.asparagi_disp = asp;
		this.Pf = Pf;
		this.Pa = Pa;
		this.incasso = 0;
	}
	
	
	
	public int getFragole_disp() {
		return fragole_disp;
	}



	public int getAsparagi_disp() {
		return asparagi_disp;
	}



	public double getIncasso() {
		return incasso;
	}



	public void setFragole_disp(int fragole_disp) {
		this.fragole_disp = fragole_disp;
	}



	public void setAsparagi_disp(int asparagi_disp) {
		this.asparagi_disp = asparagi_disp;
	}



	public void setIncasso(double incasso) {
		this.incasso = incasso;
	}



	public synchronized int acquista(int f, int a, TipoMerce t){
		int risultato = 0;
		
		if((t.equals(TipoMerce.FRAGOLA)) && f < getFragole_disp()) {
			
			setFragole_disp(getFragole_disp() - f);
			setIncasso(getIncasso() + f*Pf);
			risultato = 1;
			
		}else if((t.equals(TipoMerce.ASPARAGO)) && a < getAsparagi_disp()){
			
			setAsparagi_disp(getAsparagi_disp() - a);
			setIncasso(getIncasso() + a*Pa);
			risultato = 1;
		}
		
		
		return risultato;
		
		}
	
	public synchronized void deposita(int f, int a){
		
		setFragole_disp(getFragole_disp() + f);
		setAsparagi_disp(getAsparagi_disp() + a);

		}

	public synchronized void stampa (){
		
		System.out.println("L'incasso totale è stato di "+ getIncasso());
		System.out.println("Le fragole che sono rimaste invendute sono "+ getFragole_disp());
		System.out.println("Gli asparagi che sono rimasti invenduti sono "+ getAsparagi_disp());

		
		}
}
