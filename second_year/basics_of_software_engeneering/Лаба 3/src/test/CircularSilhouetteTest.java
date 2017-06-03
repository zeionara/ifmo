import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Zerbs on 14.11.2016.
 */
public class CircularSilhouetteTest {
    CircularSilhouette circularSilhouette = null;
    @Before
    public void initialize(){
        circularSilhouette = new CircularSilhouette(5.0);
    }

    @Test
    public void checkPonto_pontoInside_ReturnsTrue() throws Exception {
        //arrange
        Ponto ponto = new Ponto(0.1f,0.1f);

        //act
        boolean rezult = circularSilhouette.checkPonto(ponto);

        //assert
        assertTrue(rezult);
    }

    @Test
    public void checkPonto_pontoOnTheLeftBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(0.0f,0.1f);

        //act
        boolean rezult = circularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoOnTheBottomBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(0.1f,0.0f);

        //act
        boolean rezult = circularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoOnTheTopBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(3.0f,4.0f);

        //act
        boolean rezult = circularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }

    @Test
    public void checkPonto_pontoOnTheLeftToTheLeftBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(-2.2f,0.1f);

        //act
        boolean rezult = circularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoBelowTheBottomBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(0.1f,-2.1f);

        //act
        boolean rezult = circularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoAboveTheTopBound_ReturnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(3.0f,5.0f);

        //act
        boolean rezult = circularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }

}