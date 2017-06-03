import junit.framework.TestCase;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Zerbs on 05.11.2016.
 */
public class Lab3Test extends TestCase{
    @Test
    public void testMain() {
        Lab3 lab3 = new Lab3();
        String[] args;
        args = new String[]{};

        lab3.main(args);
        args = new String[]{""};
        lab3.main(args);
        args = new String[]{"hello"};
        lab3.main(args);
        args = new String[]{"h","e","l","l","o"};
        lab3.main(args);

        args = new String[]{"-12"};
        lab3.main(args);
        args = new String[]{"-12.9"};
        lab3.main(args);
        args = new String[]{"-12","-13","-14"};
        lab3.main(args);
        args = new String[]{"0"};
        lab3.main(args);
        args = new String[]{"12"};
        lab3.main(args);
        args = new String[]{"12","13","14"};
        lab3.main(args);
    }

}