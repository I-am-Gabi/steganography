package kgms.pattern;

public class InternalSpiralPattern extends Pattern {
    int incr;
    int middleWidth;
    int middleHeight;

    public InternalSpiralPattern(int height, int width) {
        super(height, width);
        incr = 0;
        middleWidth = width/2;
        middleHeight = height/2;
        this.pos = new Position(middleWidth, middleHeight);
    }

    @Override
    public boolean isImgBigEnough(int nbOfAlterBits, int nbOfAlterChannel, int nbBitsToHide) {
        int nbOfBitsToAlter = (nbBitsToHide % (nbOfAlterBits*nbOfAlterChannel) == 0)? nbBitsToHide/(nbOfAlterBits*nbOfAlterChannel) : nbBitsToHide/(nbOfAlterBits*nbOfAlterChannel) + 1;
        
        if(width == height)
            return (width * (width - 1 + width%2)) >= nbOfBitsToAlter;
        if(width < height)
            return (width % 2 == 0)? width * (width - 1) >= nbOfBitsToAlter : width * (width + 1) >= nbOfBitsToAlter;  
        return height*height >= nbOfBitsToAlter;
    }

    @Override
    public Position getNextPosition() {
        if(pos.getX() == middleWidth - incr && pos.getY() == middleHeight - incr - 1 && middleWidth + incr < width && middleHeight + incr < height)
            incr++;
        if (pos.getX() == middleWidth && pos.getY() == middleHeight)
            pos = new Position(pos.getX(), pos.getY() - 1);
        else if(pos.getY() == middleHeight - incr && pos.getX() < middleWidth + incr)
            pos = new Position(pos.getX() + 1, pos.getY());
        else if(pos.getX() == middleWidth + incr && pos.getY() < middleHeight + incr)
            pos = new Position(pos.getX(), pos.getY() + 1);
        else if(pos.getY() == middleHeight + incr && pos.getX() > middleWidth - incr)
            pos = new Position(pos.getX() - 1, pos.getY());
        else if(pos.getX() == middleWidth - incr && pos.getY() > middleHeight - incr - 1)
            pos = new Position(pos.getX(), pos.getY() - 1);
        else
            pos = new Position(-1, 0);
        
        return pos;
    }

    @Override
    public Position getInitialPosition() {
        this.pos = new Position(width/2, height/2);
        incr = 1;
        return this.pos;
    }
}
