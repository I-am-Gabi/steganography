package kgms;

public class Dissimulate {
    
    public static void main(String[] args){
        try {
            Stegano steg = new Stegano();
            steg.initialize(args);
            steg.action();
        }catch (Exception e){
            e.printStackTrace();
        }
        
        //-in args[1] -msg args[3] both args are absolute Path
    }
}