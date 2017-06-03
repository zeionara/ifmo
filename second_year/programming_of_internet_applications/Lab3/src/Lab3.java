import java.text.ParseException;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;

//Файл Lab3.java
public class Lab3 {
    public static void main (String[] args){
        HashSet pontos = new HashSet();
        Silhouette slh;
        try {
            slh = new Silhouette(Double.parseDouble(args[0]));
        } catch (IndexOutOfBoundsException e){
            System.out.println("There are no arguments");
            return;
        } catch (NumberFormatException e){
            System.out.println("There is not number in argument");
            return;
        }

        pontos.add(new Ponto(-3,4));
        pontos.add(new Ponto(0,3));
        pontos.add(new Ponto(0,0));
        pontos.add(new Ponto(3,2));
        pontos.add(new Ponto(0,3));
        pontos.add(new Ponto(4,-4));
        pontos.add(new Ponto(-4,-5));
        pontos.add(new Ponto(2,-3));
        pontos.add(new Ponto(3,3));

        Ponto curPonto;

        for (Iterator i = pontos.iterator(); i.hasNext();){
            curPonto = (Ponto)i.next();
            if (!slh.checkPonto(curPonto)){
                System.out.println(curPonto);
            }
        }
    }
}
