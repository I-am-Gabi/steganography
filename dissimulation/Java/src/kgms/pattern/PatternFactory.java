package kgms.pattern;

public class PatternFactory {
    public static Pattern getPattern(Pattern.PatternName pattern, int x, int y){
        if (pattern == Pattern.PatternName.DIRECT)
            return new DirectPattern(y, x);
        if (pattern == Pattern.PatternName.REVERSE)
            return new ReversePattern(y, x);
        if (pattern == Pattern.PatternName.EXTERNAL_SPIRAL)
            return new ExternalSpiralPattern(y, x);
        if (pattern == Pattern.PatternName.INTERNAL_SPIRAL)
            return new InternalSpiralPattern(y, x);
        return new DirectPattern(y, x);
    }
}
