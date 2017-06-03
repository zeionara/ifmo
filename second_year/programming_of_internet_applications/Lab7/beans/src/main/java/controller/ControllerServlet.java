package controller;
import java.io.*;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "ControllerServlet", loadOnStartup = 1, urlPatterns = {"/home"})

public class ControllerServlet extends HttpServlet {

  @Override
  protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
    handleRequest(req, res, 1);
  }

  @Override
  protected void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
    handleRequest(req, res, 0);
  }

  private static boolean isNumber(String s) throws NumberFormatException {
    try {
        Double.parseDouble(s);
        return true;
    } catch (NumberFormatException e) {
        return false;
    }
  }

  protected boolean isThereData(HttpServletRequest req){
    if ((req.getParameter("y") == null) || (req.getParameter("radius") == null) ||
        (!isNumber(req.getParameter("radius"))) || (!isNumber(req.getParameter("y")))) return false;

    if ((req.getParameter("x") != null) && (isNumber(req.getParameter("x")))) return true;

    for (int i = 1; i <= 9; i++){
      if ((req.getParameter("x"+i) != null) && (isNumber(req.getParameter("x"+i)))) return true;
    }

    return false;
  }

  protected void handleRequest(HttpServletRequest req, HttpServletResponse res, int method) throws ServletException, IOException{
    PrintWriter out = res.getWriter();
    String xValue = req.getParameter("x");
    String yValue = req.getParameter("y");
    String nextJSP = "/pip.lab2/request.jsp";

    if ((method == 0) && (isThereData(req))){
      RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/check");
      dispatcher.forward(req,res);
    }

    res.sendRedirect(nextJSP);
  }

  public static String getCheckedPontosInHTMLTable(){
    return AreaCheckServlet.getCheckedPontosInHTMLTable();
  }
}
