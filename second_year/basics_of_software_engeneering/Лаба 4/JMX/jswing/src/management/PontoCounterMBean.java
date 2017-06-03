package management;

import jswing.GeneralSilhouette;
import jswing.Ponto;

import java.util.Set;

public interface PontoCounterMBean {
    void pontoAdded(Ponto ponto, GeneralSilhouette gsh);
    void checkAgain(Set<Ponto> pontos, GeneralSilhouette gsh);
    int getTotalCount();
    int getCaughtCount();
}
