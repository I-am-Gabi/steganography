package kgms;

public class Application {
    private String Fin;
    private String Fout;
    private String in;
    private String out;
    private String msg;
    private int bitsUsed;
    //Un attr pour les channels
    //Un attr pour le pattern (stratégie?)
    private int magicNumber;
    private int metrics;
    
    private Application(){
        bitsUsed = 1;
        //Defaut channels
        //Defaut pattern
        magicNumber = 0x48454C50;
    }
    public int start(){
        
        return 0;
    }
    public static int main(String[] args) {
        Application app = new Application();
        //return app.start();
        app.test();
        return 0;
    }
    public void test(){
        // COMMIT TEST
    }
}
