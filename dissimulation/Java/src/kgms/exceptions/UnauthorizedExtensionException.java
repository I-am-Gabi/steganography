package kgms.exceptions;

public class UnauthorizedExtensionException extends Exception{
    /**
     *
     */
    private static final long serialVersionUID = 1L;
    
    public String toString(){
        return "Error : file extension unauthorized or not matching  the specified one(Fin)";
    }
}
