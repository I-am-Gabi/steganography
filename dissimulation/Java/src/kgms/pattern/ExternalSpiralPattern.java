package kgms.pattern;

public class ExternalSpiralPattern extends Pattern {
    int incr;

    public ExternalSpiralPattern(int height, int width) {
        super(height, width);
        incr = 0;
        this.pos = new Position(0, 0);
    }

    @Override
    public boolean isImgBigEnough(int nbOfAlterBits, int nbOfAlterChannel, int nbBitsToHide){
        return nbOfAlterBits*nbOfAlterChannel*height*width >= nbBitsToHide;
    }

    @Override
    public Position getNextPosition() {
    	if(pos.getX() == incr && pos.getY() == incr + 1 && !(height - incr < height/2 && width - incr < width/2))
    		incr++;
        if (pos.getY() == incr &&	pos.getX() < width - incr - 1)
            pos = new Position(pos.getX() + 1, pos.getY());
        else if(pos.getX() == width - incr - 1 && pos.getY() < height - incr - 1)
        	pos = new Position(pos.getX(), pos.getY() + 1);
        else if(pos.getY() == height - incr - 1 && pos.getX() > incr)
        	pos = new Position(pos.getX() - 1, pos.getY());
        else if(pos.getX() == incr && pos.getY() > incr + 1)
        	pos = new Position(pos.getX(), pos.getY() - 1);
        else
            pos = new Position(-1, 0);
        
        return pos;
    }

    @Override
    public Position getInitialPosition(){
        this.pos = new Position(0,0);
        incr = 0;
        return this.pos;
    }
}
