<%@page language="java" import="controller.ControllerServlet" %>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
    <link href="styles/style.css" rel="stylesheet"/>
    <script src="https://code.jquery.com/jquery-2.2.4.min.js"></script>
    <script src="scripts/script.js"></script>
    <title>Silhouette checker</title>
  </head>
  <body>
    <h1>Выполнил студент группы P3217 Плюхин Дмитрий Алексеевич вариант 2911</h1>
    <form name="edit" method="POST" action="/pip.lab2/home" id="edit">
    <table id="formtable">
      <tr>
        <td>
          <label>x: </label>
        </td>
        <td>
          <input type="checkbox" name="x1" value="-4" unchecked><label class="after">-4</label>
          <input type="checkbox" name="x2" value="-3" unchecked><label class="after">-3</label>
          <input type="checkbox" name="x3" value="-2" unchecked><label class="after">-2</label>
          <input type="checkbox" name="x4" value="-1" unchecked><label class="after">-1</label>
          <input type="checkbox" name="x5" value="0" unchecked><label class="after">0</label>
          <input type="checkbox" name="x6" value="1" unchecked><label class="after">1</label>
          <input type="checkbox" name="x7" value="2" unchecked><label class="after">2</label>
          <input type="checkbox" name="x8" value="3" unchecked><label class="after">3</label>
          <input type="checkbox" name="x9" value="4" unchecked><label class="after">4</label>
        </td>
      </tr>
      <tr>
        <td>
          <label>y: </label>
        </td>
        <td><input type="text" name="y" id="forminput"><br>
        </td>
      </tr>
      <tr>
        <td>
          <label>r: </label>
        </td>
        <td>
          <select size="1" multiple name="radius">
          	<option value="3">3</option>
            <option value="2.5">2.5</option>
            <option value="2">2</option>
            <option selected value="1.5">1.5</option>
            <option value="1">1</option>
          </select>
        </td>
      </tr>
    </table>
    <div id="area">

    </div>
    <div>
        <input type="submit" value="Submit" name="submit" class="submit" id="formsubmit">
    </div>
    </form>
    <%=ControllerServlet.getCheckedPontosInHTMLTable()%>
  </body>
</html>
