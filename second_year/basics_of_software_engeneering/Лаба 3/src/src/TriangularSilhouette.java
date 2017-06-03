
public class TriangularSilhouette extends Silhouette implements pontoCheckable{

    public TriangularSilhouette(double r){
        super(r);
    }

    public boolean checkPonto(Ponto p){
        float x = p.getX();
        float y = p.getY();

        return (y > x - getR()/2) && (x >= 0) && (y <= 0);
    }
}
