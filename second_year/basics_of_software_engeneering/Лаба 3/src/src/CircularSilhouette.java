
public class CircularSilhouette extends Silhouette implements pontoCheckable{

    public CircularSilhouette(double r){
        super(r);
    }

    public boolean checkPonto(Ponto p){
        float x = p.getX();
        float y = p.getY();
        double r = getR();

        return (x*x + y*y < r*r) && (x > 0) && (y > 0);
    }
}
