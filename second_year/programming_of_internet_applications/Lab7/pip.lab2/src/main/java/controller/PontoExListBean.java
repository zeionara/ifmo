package controller;

import java.util.ArrayList;
import silhouette.PontoEx;

  public class PontoExListBean {

    private ArrayList<PontoEx> pontos;

    public PontoExListBean() {
      pontos = new ArrayList<PontoEx>();
    }

    public void add(PontoEx ponto) {
      for (int i = 0; i < pontos.size(); i++){
        if ((pontos.get(i).getX() == ponto.getX()) && (pontos.get(i).getY() == ponto.getY())){
          pontos.get(i).setR(ponto.getR());
          pontos.get(i).setInside(ponto.getInside());
          return;
        }
      }
      pontos.add(ponto);
    }

    public PontoEx get(int i) {
      return pontos.get(i);
    }

    public int size(){
      return pontos.size();
    }
}
