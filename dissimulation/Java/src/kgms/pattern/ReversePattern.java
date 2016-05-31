package kgms.pattern;

public class ReversePattern extends Pattern {
    public ReversePattern(int height, int width) {
        super(height, width);
    	this.pos = new Position(width-1, height-1);
    }
    
    @Override
    public boolean isImgBigEnough(int nbOfAlterBits, int nbOfAlterChannel, int nbBitsToHide){
        return nbOfAlterBits*nbOfAlterChannel*height*width >= nbBitsToHide;
    }

    @Override
    public Position getNextPosition() {
        if (pos.getX() > 0)
            pos = new Position(pos.getX() - 1, pos.getY());
        else{
            if (pos.getY() > 0){
                pos = new Position(width-1, pos.getY() - 1);
            }else {
                pos = new Position(-1, 0);
            }
        }
        return pos;
    }

    @Override
    public Position getInitialPosition(){
        this.pos = new Position(width-1, height-1);
        return this.pos;
    }
}
