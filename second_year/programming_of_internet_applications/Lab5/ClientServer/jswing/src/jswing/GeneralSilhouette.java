package jswing;

public class GeneralSilhouette extends Silhouette implements pontoCheckable{

    public GeneralSilhouette(double r){
        super(r);
    }

    public boolean checkPonto(Ponto p){
        double r = getR();

        return  (new CircularSilhouette(r).checkPonto(p) ||
                new RectangularSilhouette(r).checkPonto(p) ||
                new TriangularSilhouette(r).checkPonto(p)) &&
                !((p.getX()==0) && (p.getY()==0));
    }
}
