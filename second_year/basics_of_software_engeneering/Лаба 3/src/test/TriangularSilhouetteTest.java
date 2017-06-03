import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class TriangularSilhouetteTest {
    TriangularSilhouette triangularSilhouette = null;

    @Before
    public void initialize(){
        triangularSilhouette = new TriangularSilhouette(10.0);
    }

    @Test
    public void checkPonto_pontoInside_returnsTrue() throws Exception {
        //arrange
        Ponto ponto = new Ponto(2.0f,-2.0f);

        //act
        boolean rezult = triangularSilhouette.checkPonto(ponto);

        //assert
        assertTrue(rezult);
    }

    @Test
    public void checkPonto_pontoOnTheTopBound_returnsTrue() throws Exception {
        //arrange
        Ponto ponto = new Ponto(2.0f,0.0f);

        //act
        boolean rezult = triangularSilhouette.checkPonto(ponto);

        //assert
        assertTrue(rezult);
    }
    @Test
    public void checkPonto_pontoOnTheLeftBound_returnsTrue() throws Exception {
        //arrange
        Ponto ponto = new Ponto(0.0f,-2.0f);

        //act
        boolean rezult = triangularSilhouette.checkPonto(ponto);

        //assert
        assertTrue(rezult);
    }
    @Test
    public void checkPonto_pontoOnTheBottomBound_returnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(5.0f,-5.0f);

        //act
        boolean rezult = triangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }

    @Test
    public void checkPonto_pontoAboveTheTopBound_returnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(2.0f,2.0f);

        //act
        boolean rezult = triangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoToTheLeftOfTheLeftBound_returnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(-2.0f,-2.0f);

        //act
        boolean rezult = triangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
    @Test
    public void checkPonto_pontoBelowTheBottomBound_returnsFalse() throws Exception {
        //arrange
        Ponto ponto = new Ponto(5.0f,-10.0f);

        //act
        boolean rezult = triangularSilhouette.checkPonto(ponto);

        //assert
        assertFalse(rezult);
    }
}