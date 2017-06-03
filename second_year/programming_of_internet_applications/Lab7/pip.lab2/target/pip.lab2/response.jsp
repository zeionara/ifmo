<%@page language="java" import="java.util.*,silhouette.*" %>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Silhouette checker</title>
  </head>
<body>
  <table border="1" cellspacing="1" cellpadding="1" align = "center">
    <tr>
      <td valign="top" align = "center" height="20">Параметры</td>
    </tr>
    <%
    ArrayList<PontoEx> pontos = (ArrayList<PontoEx>)request.getAttribute("pontos");
    if (pontos != null){
      for (int i = 0; i < pontos.size(); i++) {
        out.println(pontos.get(i).toHTMLTableRaw());
      }
    }
    %>
    <tr>
      <td align = "center">
        x = <%=request.getAttribute("x")%> <br />
        y = <%=request.getAttribute("y")%> <br />
        R = <%=request.getAttribute("r")%><br />
        Result: <%=request.getAttribute("result")%> <br />
      </td>
    </tr>
  </table>
  <div align="center"><a href="pip.lab2/home">Назад</a></div>
</body>
</html>
