package kgms.pattern;

import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Mathieu on 10/01/2016.
 */
public class ReversePatternTest {
	
	Pattern pattern;
	 
	@Before
    public  void defineContext()
    {
    	pattern = new ReversePattern(3, 3);
    }//defineContext()

    @Test
    public void testIsImgBigEnough() throws Exception {
    	assertTrue(!pattern.isImgBigEnough(1, 3, 31));
    }

    @Test
    public void testIsImgBigEnough2() throws Exception {
    	assertTrue(pattern.isImgBigEnough(3, 1, 15));
    }

    @Ignore
    public void testGetNextPosition() throws Exception {
    	pattern.getInitialPosition();
    	Position nextPos = new Position(2,1);
    	Position pos = pattern.getNextPosition();

    	assertEquals(nextPos.getX(), pos.getX());
    	assertEquals(nextPos.getY(), pos.getY()); 
	}

    @Ignore
    public void testGetNextPosition2() throws Exception {
    	pattern.setPosition(2,0);
    	Position nextPos = new Position(1,2);
    	Position pos = pattern.getNextPosition();

    	assertEquals(nextPos.getX(), pos.getX());
    	assertEquals(nextPos.getY(), pos.getY());	
    }

	@Test
    public void testGetNextPosition3() throws Exception {
    	pattern.setPosition(0,0);
    	Position nextPos = new Position(-1,0);
    	Position pos = pattern.getNextPosition();

    	assertEquals(nextPos.getX(), pos.getX());
    	assertEquals(nextPos.getY(), pos.getY());
    }
	
    @Test
    public void testGetInitialPosition() throws Exception {
    	Position initPos = new Position(2,2);
    	assertEquals(initPos.getX(), pattern.getInitialPosition().getX());
    	assertEquals(initPos.getY(), pattern.getInitialPosition().getY());
    }
}