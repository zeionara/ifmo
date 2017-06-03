import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Zerbs on 14.11.2016.
 */
public class Lab3Test {
    Lab3 lab3 = null;
    @Before
    public void initialize(){
        lab3 = new Lab3();
    }

    @Test
    public void main_correctStringArray_NoException() throws Exception {
        //arrange
        String args[] = {"1.2","4.33","5.6"};

        //act
        lab3.main(args);

        //assert
        //No one exception throwed
    }
    @Test
    public void main_emptyStringArray_NoException() throws Exception {
        //arrange
        String args[] = {};

        //act
        lab3.main(args);

        //assert
        //No one exception throwed
    }
    @Test
    public void main_incorrectStringArray_NoException() throws Exception {
        //arrange
        String args[] = {"aaa","12.2","bbb"};

        //act
        lab3.main(args);

        //assert
        //No one exception throwed
    }
    @Test
    public void main_radiusLessThanZeroInStringArray_NoException() throws Exception {
        //arrange
        String args[] = {"-13"};

        //act
        lab3.main(args);

        //assert
        //No one exception throwed
    }
    @Test
    public void main_radiusEqualsToZeroInStringArray_NoException() throws Exception {
        //arrange
        String args[] = {"0.0"};

        //act
        lab3.main(args);

        //assert
        //No one exception throwed
    }

}