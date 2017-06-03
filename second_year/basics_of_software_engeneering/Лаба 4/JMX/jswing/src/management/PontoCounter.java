package management;

import jswing.GeneralSilhouette;
import jswing.GraphPanel;
import jswing.Ponto;

import javax.management.Notification;
import javax.management.NotificationBroadcasterSupport;
import java.util.Set;

public class PontoCounter extends NotificationBroadcasterSupport implements PontoCounterMBean {
    private int totalCount = 0;
    private int caughtCount = 0;

    @Override
    public void pontoAdded(Ponto ponto, GeneralSilhouette gsh) {
        increaseTotalCount();
        if (gsh.checkPonto(ponto)){
            increaseCaughtCount();
        }
        notificateIfNecessary(ponto,gsh.getR());
    }

    @Override
    public void checkAgain(Set<Ponto> pontos, GeneralSilhouette gsh) {
        resetCounts();
        for(Ponto ponto : pontos){
            pontoAdded(ponto,gsh);
        }
    }

    @Override
    public int getTotalCount() {
        return totalCount;
    }

    @Override
    public int getCaughtCount() {
        return caughtCount;
    }

    private void notificateIfNecessary(Ponto ponto, double R){
        double sizeOfArea = R*GraphPanel.SIZE_OF_GRAPH/(2*GraphPanel.GRAPHICAL_R);
        if (((ponto.getX() > sizeOfArea) || (ponto.getX() < -sizeOfArea)) ||
                ((ponto.getY() > sizeOfArea) || (ponto.getY() < -sizeOfArea))){
            sendNotification(new Notification("management.pontoOutsideOfArea",this,-1,System.currentTimeMillis(),
                    "Ponto outside of the visible area"));
        }
    }

    private void increaseTotalCount(){
        totalCount+=1;
    }

    private void increaseCaughtCount(){
        caughtCount+=1;
    }

    private void resetCounts(){
        totalCount = 0;
        caughtCount = 0;
    }
}
