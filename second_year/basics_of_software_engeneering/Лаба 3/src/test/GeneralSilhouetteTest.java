import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Zerbs on 14.11.2016.
 */
public class GeneralSilhouetteTest {
    GeneralSilhouette generalSilhouette = null;
    @Before
    public void initialize(){
        generalSilhouette = new GeneralSilhouette(10.0);
    }

    @Test
    public void checkPonto_pontoInTheBeginningOfCoordinates_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(0.0f,0.0f);

        //act
        boolean rezult = generalSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }

    @Test
    public void checkPonto_pontoInTheTriangularSilhouette_ReturnsTrue() throws Exception {
        //arrange
        Ponto ponto = new Ponto(0.2f,-4.2f);

        //act
        boolean rezult = generalSilhouette.checkPonto(ponto);

        //assert
        assertTrue(rezult);
    }
    @Test
    public void checkPonto_pontoInTheRectangularSilhouette_ReturnsTrue() throws Exception {
        //arrange
        Ponto ponto = new Ponto(-0.2f,-4.2f);

        //act
        boolean rezult = generalSilhouette.checkPonto(ponto);

        //assert
        assertTrue(rezult);
    }
    @Test
    public void checkPonto_pontoInTheCircularSilhouette_ReturnsTrue() throws Exception {
        //arrange
        Ponto ponto = new Ponto(0.2f,4.2f);

        //act
        boolean rezult = generalSilhouette.checkPonto(ponto);

        //assert
        assertTrue(rezult);
    }

}