package jswing;

public class CircularSilhouette extends Silhouette implements pontoCheckable{

    public CircularSilhouette(double r){
        super(r);
    }

    public boolean checkPonto(Ponto p){
        double x = p.getX();
        double y = p.getY();
        double r = getR();

        return (x*x + y*y < r*r) && (x > 0) && (y > 0);
    }
}
