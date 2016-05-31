package kgms.utils;

import kgms.exceptions.WrongArgumentException;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import java.io.IOException;

public class OptionManagerTest {

    @Rule
    public final ExpectedException exception = ExpectedException.none();

    @Test
    public void testConstructor1() throws WrongArgumentException, IOException {
        String[] args = {};
        exception.expect(WrongArgumentException.class);
        OptionManager opt = new OptionManager(args);
    }
    @Test
    public void testConstructor2() throws WrongArgumentException, IOException {
        String[] args = {};
        exception.expect(WrongArgumentException.class);
        OptionManager opt = new OptionManager(args);
    }
    @Test
    public void testConstructor3() throws WrongArgumentException, IOException {
        String[] args = {};
        exception.expect(WrongArgumentException.class);
        OptionManager opt = new OptionManager(args);
    }
}
