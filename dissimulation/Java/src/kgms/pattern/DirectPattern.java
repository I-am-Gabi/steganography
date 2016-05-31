package kgms.pattern;

public class DirectPattern extends Pattern {
    public DirectPattern(int height, int width) {
        super(height, width);
        this.pos = new Position(0, 0);
    }

    @Override
    public boolean isImgBigEnough(int nbOfAlterBits, int nbOfAlterChannel, int nbBitsToHide){
        return (nbOfAlterBits*nbOfAlterChannel*this.height*this.width >= nbBitsToHide);
    }

    @Override
    public Position getNextPosition() {
        if (pos.getX() < width - 1)
            pos = new Position(pos.getX() + 1, pos.getY());
        else{
            if (pos.getY() < height - 1){
                pos = new Position(0, pos.getY() + 1);
            }else {
                pos = new Position(-1, 0);
            }
        }
        return pos;
    }

    @Override
    public Position getInitialPosition(){
        this.pos = new Position(0,0);
        return this.pos;
    }
}
