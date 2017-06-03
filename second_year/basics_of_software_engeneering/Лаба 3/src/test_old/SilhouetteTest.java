import junit.framework.TestCase;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Zerbs on 04.11.2016.
 */
public class SilhouetteTest extends TestCase{
    private GeneralSilhouette gsh = new GeneralSilhouette(10);

    public void testsetRFaledLessThanZero() throws Exception {
        int a = 0;
        try {
            gsh.setR(-20);
        } catch (IllegalArgumentException e){
            a = 1;
        }
        assertTrue(a==1);
    }

    public void testsetRFaledEqualsToZero() throws Exception {
        int a = 0;
        try {
            gsh.setR(0);
        } catch (IllegalArgumentException e){
            a = 1;
        }
        assertTrue(a==1);
    }

    public void testsetR() throws Exception {
        gsh.setR(20);
    }

    public void testgetR() throws Exception {
        gsh.setR(20);
        assertTrue(gsh.getR()==20);
    }

}