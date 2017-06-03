package jswing;

public class RectangularSilhouette extends Silhouette implements pontoCheckable{

    public RectangularSilhouette(double r){
        super(r);
    }

    public boolean checkPonto(Ponto p){
        double x = p.getX();
        double y = p.getY();
        double r = getR();

        return ((x > -r) && (x < 0)) && ((y > -r) && (y < 0));
    }
}
