import junit.framework.TestCase;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Zerbs on 05.11.2016.
 */
public class GeneralSilhouetteTest extends TestCase{

    public void testcheckPonto() throws Exception{
        GeneralSilhouette gsh = new GeneralSilhouette(5);
        assertFalse(gsh.checkPonto(new Ponto(0,0)));
        assertFalse(gsh.checkPonto(new Ponto(0,3)));
        assertFalse(gsh.checkPonto(new Ponto(0,7)));
        assertTrue(gsh.checkPonto(new Ponto(2,0)));
        assertFalse(gsh.checkPonto(new Ponto(2.5f,0)));
        assertFalse(gsh.checkPonto(new Ponto(0,-3)));
        assertFalse(gsh.checkPonto(new Ponto(0,-7)));

        assertFalse(gsh.checkPonto(new Ponto(0,-2.5f)));
        assertTrue(gsh.checkPonto(new Ponto(0,-2)));
        assertFalse(gsh.checkPonto(new Ponto(3,0)));
        assertFalse(gsh.checkPonto(new Ponto(7,0)));
        assertFalse(gsh.checkPonto(new Ponto(-3,0)));
        assertFalse(gsh.checkPonto(new Ponto(-7,0)));

        assertFalse(gsh.checkPonto(new Ponto(0,5)));
        assertFalse(gsh.checkPonto(new Ponto(5,0)));
        assertFalse(gsh.checkPonto(new Ponto((float)Math.sqrt(10),(float)Math.sqrt(15))));
        assertFalse(gsh.checkPonto(new Ponto(10,10)));
        assertTrue(gsh.checkPonto(new Ponto(2,2)));

        assertFalse(gsh.checkPonto(new Ponto(-5,-5)));
        assertFalse(gsh.checkPonto(new Ponto(-2,-5)));
        assertFalse(gsh.checkPonto(new Ponto(-5,-2)));
        assertTrue(gsh.checkPonto(new Ponto(-2,-2)));

        assertFalse(gsh.checkPonto(new Ponto(-2,2)));
        assertFalse(gsh.checkPonto(new Ponto(2,-2)));
        assertTrue(gsh.checkPonto(new Ponto(1,-1)));
    }

}