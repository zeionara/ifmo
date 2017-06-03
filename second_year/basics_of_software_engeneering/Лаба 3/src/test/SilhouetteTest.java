import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Zerbs on 14.11.2016.
 */
public class SilhouetteTest {
    TriangularSilhouette triangularSilhouette = null;

    @Before
    public void initialize(){
        triangularSilhouette = new TriangularSilhouette(10.0);
    }

    @Test
    public void setR_RmoreThanZero_RsuccesfullySet() throws Exception {
        //arrange
        double newR = 15.0f;

        //act
        triangularSilhouette.setR(newR);

        //assert
        assertTrue(triangularSilhouette.getR()==newR);
    }
    @Test(expected = IllegalArgumentException.class)
    public void setR_RequalsToZero_ThrowedIllegalArgumentException() throws Exception {
        //arrange
        double newR = 0.0f;

        //act
        triangularSilhouette.setR(newR);

        //assert
        //Exception throwed
    }
    @Test(expected = IllegalArgumentException.class)
    public void setR_LessThanZero_ThrowedIllegalArgumentException() throws Exception {
        //arrange
        double newR = -10.0f;

        //act
        triangularSilhouette.setR(newR);

        //assert
        //Exception throwed
    }

}