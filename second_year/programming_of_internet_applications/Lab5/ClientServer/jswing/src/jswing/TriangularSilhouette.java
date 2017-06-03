package jswing;

public class TriangularSilhouette extends Silhouette implements pontoCheckable{

    public TriangularSilhouette(double r){
        super(r);
    }

    public boolean checkPonto(Ponto p){
        double x = p.getX();
        double y = p.getY();

        return (y > x - getR()/2) && (x >= 0) && (y <= 0);
    }
}
