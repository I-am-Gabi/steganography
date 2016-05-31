package kgms.pattern;

import org.junit.*;

import static org.junit.Assert.*;

/**
 * Created by Mathieu on 10/01/2016.
 */
public class DirectPatternTest {
	 
	Pattern pattern;
	 
	@Before
    public  void defineContext()
    {
        pattern = new DirectPattern(3, 3);
    }//defineContext()

    @Test
    public void testIsImgBigEnough() throws Exception {
    	assertTrue(pattern.isImgBigEnough(1, 3, 10));
    }

    @Test
    public void testIsImgBigEnough2() throws Exception {
    	assertTrue(!pattern.isImgBigEnough(1, 1, 10));
    }

    @Test
    public void testGetNextPosition() throws Exception {
    	pattern.getInitialPosition();
    	Position nextPos = new Position(1,0);
    	Position pos = pattern.getNextPosition();
        System.out.println(pos.getX() + pos.getY());
        assertEquals("X", nextPos.getX(), pos.getX());
    	assertEquals("Y", nextPos.getY(), pos.getY());
	}


	@Test
    public void testGetNextPosition2() throws Exception {
    	pattern.setPosition(2,2);
    	Position nextPos = new Position(-1,0);
    	Position pos = pattern.getNextPosition();

    	assertEquals(nextPos.getX(), pos.getX());
    	assertEquals(nextPos.getY(), pos.getY());
    }
	
    @Test
    public void testGetInitialPosition() throws Exception {
    	Position initPos = new Position(0,0);
    	assertEquals(initPos.getX(), pattern.getInitialPosition().getX());
    	assertEquals(initPos.getY(), pattern.getInitialPosition().getY());
    }
}