package controller;
import java.util.ArrayList;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.ServletConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import silhouette.*;

@WebServlet(name = "AreaCheckServlet", loadOnStartup = 1, urlPatterns = {"/check"})
public class AreaCheckServlet extends HttpServlet {

  private static PontoExListBean pontosBean;

  private static boolean isNumber(String s) throws NumberFormatException {
    try {
        Double.parseDouble(s);
        return true;
    } catch (NumberFormatException e) {
        return false;
    }
  }

  @Override
  public void init(ServletConfig config) throws ServletException {
    super.init(config);
    if (pontosBean == null){
      pontosBean = new PontoExListBean();
    }
  }

  @Override
  protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    GeneralSilhouette slh = new GeneralSilhouette(Double.parseDouble(request.getParameter("radius")));
    double y = Double.parseDouble(request.getParameter("y"));
    double radius = Double.parseDouble(request.getParameter("radius"));
    double x = 0.0;
    ArrayList<PontoEx> pontos = new ArrayList<PontoEx>();
    PrintWriter out = response.getWriter();

    if (((request.getParameter("x") != null) && (isNumber(request.getParameter("x"))))){
        x = Double.parseDouble(request.getParameter("x"));
        pontos.add(new PontoEx(x,y,radius,slh.checkPonto(new Ponto(x,y))));
        AreaCheckServlet.pontosBean.add(pontos.get(pontos.size()-1));
    }

    for (int i = 1; i <= 9; i++){
      if ((request.getParameter("x"+i) != null) && (isNumber(request.getParameter("x"+i)))){
        x = Double.parseDouble(request.getParameter("x"+i));
        pontos.add(new PontoEx(x,y,radius,slh.checkPonto(new Ponto(x,y))));
        AreaCheckServlet.pontosBean.add(pontos.get(pontos.size()-1));
      }
    }

    request.setAttribute("pontos",pontos);
    if (pontos.size() != 0) {
      out.println("<!DOCTYPE html><html><head><meta http-equiv='Content-Type' content='text/html; charset=windows-1251'><title>Silhouette checker</title></head><body><table border='1' cellspacing='1' cellpadding='1' align='center'><tr><td>x</td><td>y</td><td>r</td><td>Location</td></tr>");
      for (int i = 0; i < pontos.size(); i++) {
        out.println(pontos.get(i).toHTMLTableRaw());
      }
      out.println("</table><div align='center'><a href='/pip.lab2/home'>Back</a></div></body></html>");
    } else {
      out.println("<!DOCTYPE html><html><head><meta http-equiv='Content-Type' content='text/html; charset=UTF-8'><title>Silhouette checker</title></head><body><p>There are no points</p><div align='center'><a href='pip.lab2/home'>Back</a></div></body></html>");
    }
  }

  public static String getCheckedPontosInHTMLTable(){
    String table = "<table id='pontos'><tbody><tr><td>x</td><td>y<td>r</td><td>Location</td></tr>";
    //out.println("<!DOCTYPE html><html><head><meta http-equiv='Content-Type' content='text/html; charset=windows-1251'><title>Silhouette checker</title></head><body><table border='1' cellspacing='1' cellpadding='1' align='center'><tr><td valign='top' align='center' height='20px'>Params</td></tr>");
    for (int i = 0; i < AreaCheckServlet.pontosBean.size(); i++) {
      table = table + AreaCheckServlet.pontosBean.get(i).toHTMLTableRaw();
    }
    table = table + "</tbody></table>";
    return table;
  }
}
