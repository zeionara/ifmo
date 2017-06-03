
public class RectangularSilhouette extends Silhouette implements pontoCheckable{

    public RectangularSilhouette(double r){
        super(r);
    }

    public boolean checkPonto(Ponto p){
        float x = p.getX();
        float y = p.getY();
        double r = getR();

        return ((x > -r) && (x < 0)) && ((y > -r) && (y < 0));
    }
}
