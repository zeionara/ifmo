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

    public String getPontosTable(){
      String table = "<table id='pontos'><tbody><tr><td>x</td><td>y<td>r</td><td>Location</td></tr>";
      //out.println("<!DOCTYPE html><html><head><meta http-equiv='Content-Type' content='text/html; charset=windows-1251'><title>Silhouette checker</title></head><body><table border='1' cellspacing='1' cellpadding='1' align='center'><tr><td valign='top' align='center' height='20px'>Params</td></tr>");
      for (int i = 0; i < pontos.size(); i++) {
        table = table + pontos.get(i).toHTMLTableRaw();
      }
      table = table + "</tbody></table>";
      return table;
    }
}
