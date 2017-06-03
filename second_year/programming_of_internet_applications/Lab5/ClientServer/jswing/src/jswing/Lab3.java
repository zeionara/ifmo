package jswing;
import java.util.*;


//Файл Lab3.java
public class Lab3 {
    public static void main (String[] args){
        Set pontos = new HashSet();
        GeneralSilhouette slh;
        try {
            slh = new GeneralSilhouette(Double.parseDouble(args[0]));
        } catch (IndexOutOfBoundsException e){
            System.out.println("There are no arguments");
            return;
        } catch (NumberFormatException e){
            System.out.println("There is not number in argument");
            return;
        } catch (IllegalArgumentException e){
            System.out.println("Radius can't be less than or equals to 0");
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
