package kgms.ui;

public class CommandLineParser {
    private String command;
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

    public CommandLineParser(){}
    public CommandLineParser(String command){
        this.command = command;
    }
    public void parse(){

    }
}
