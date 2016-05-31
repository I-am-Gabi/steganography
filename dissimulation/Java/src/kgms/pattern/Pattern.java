package kgms.pattern;

public abstract class Pattern {
    public enum PatternName{
        DIRECT,
        REVERSE,
        EXTERNAL_SPIRAL,
        INTERNAL_SPIRAL
    }
    protected Position pos;
    protected int height;
    protected int width;

    public Pattern(int height, int width){
        this.height = height;
        this.width = width;
    }

    public void setPosition(int w, int h){
        this.pos = new Position(w, h);
    }

    abstract public boolean isImgBigEnough(int nbOfAlterBits, int nbOfAlterChannel, int nbBitsToHide);
    abstract public Position getInitialPosition(); 
    abstract public Position getNextPosition();
}
