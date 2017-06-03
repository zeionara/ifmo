import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Zerbs on 14.11.2016.
 */
public class RectangularSilhouetteTest {
    RectangularSilhouette rectangularSilhouette = null;

    @Before
    public void initialize(){
        rectangularSilhouette = new RectangularSilhouette(10.0);
    }

    @Test
    public void checkPonto_pontoInside_ReturnsTrue() throws Exception {
        //arrange
        Ponto ponto = new Ponto(-2.0f,-2.0f);

        //act
        boolean rezult = rectangularSilhouette.checkPonto(ponto);

        //assert
        assertTrue(rezult);
    }

    @Test
    public void checkPonto_pontoOnTheTopBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(-2.0f,0.0f);

        //act
        boolean rezult = rectangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoOnTheBottomBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(-2.0f,-10.0f);

        //act
        boolean rezult = rectangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoOnTheLeftBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(-10.0f,-2.0f);

        //act
        boolean rezult = rectangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoOnTheRightBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(0.0f,-2.0f);

        //act
        boolean rezult = rectangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }

    @Test
    public void checkPonto_pontoAboveTheTopBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(-2.0f,2.0f);

        //act
        boolean rezult = rectangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoBelowTheBottomBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(-2.0f,-15.0f);

        //act
        boolean rezult = rectangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoOnTheLeftToTheLeftBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(-12.2f,-2.0f);

        //act
        boolean rezult = rectangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoOnTheRightToTheRightBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(2.0f,-2.0f);

        //act
        boolean rezult = rectangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
}