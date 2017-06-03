package jswing;

import javax.swing.*;
import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Set;

public class GraphPanel extends JPanel {
    public static final int GRAPHICAL_R = 60;
    public static final int OFFSET_TO_CENTER;
    public static final int SIZE_OF_POINTER = 5;
    public static final int OFFSET_TO_LABEL = 10;
    public static final int SIZE_OF_GRAD = 2;
    public static final int SIZE_OF_GRAPH = 200;
    public static final int SIZE_OF_POINT = 2;

    public static final int BLUE = 0x0000FF;
    public static final Color INNER_POINT_COLOR = Color.green;
    public static final Color OUTER_POINT_COLOR = Color.red;
    public static final Color NOTCHECKED_POINT_COLOR = Color.gray;

    static {
        OFFSET_TO_CENTER = SIZE_OF_GRAPH/2;
    }

    private Color areaColor = new Color(BLUE);

    public void setAreaColor(int r, int g, int b){
        areaColor = new Color(correctValue(r,0,255), correctValue(g,0,255), correctValue(b,0,255));
    }

    public void paint(Graphics g){
        //Background
        g.setColor(new Color(0x48CC5E));
        g.fillRect(0,0,SIZE_OF_GRAPH,SIZE_OF_GRAPH);

        //Rectangle
        g.setColor(areaColor);
        g.drawRect(OFFSET_TO_CENTER,OFFSET_TO_CENTER,-GRAPHICAL_R,GRAPHICAL_R);

        //Triangle
        int[] txs = {OFFSET_TO_CENTER,OFFSET_TO_CENTER+GRAPHICAL_R/2,OFFSET_TO_CENTER};
        int[] tys = {OFFSET_TO_CENTER,OFFSET_TO_CENTER,OFFSET_TO_CENTER+GRAPHICAL_R/2};
        Polygon triangle = new Polygon(txs,tys,3);
        g.fillPolygon(triangle);

        //Circle
        g.fillArc(OFFSET_TO_CENTER-GRAPHICAL_R,OFFSET_TO_CENTER-GRAPHICAL_R,GRAPHICAL_R*2,GRAPHICAL_R*2,0,90);

        //Coordinates
        g.setColor(Color.black);
        g.drawLine(OFFSET_TO_CENTER,GRAPHICAL_R*3,OFFSET_TO_CENTER,SIZE_OF_GRAPH-GRAPHICAL_R*3);
        g.drawLine(OFFSET_TO_CENTER,SIZE_OF_GRAPH-GRAPHICAL_R*3,OFFSET_TO_CENTER+SIZE_OF_POINTER,SIZE_OF_GRAPH-GRAPHICAL_R*3+SIZE_OF_POINTER);
        g.drawLine(OFFSET_TO_CENTER,SIZE_OF_GRAPH-GRAPHICAL_R*3,OFFSET_TO_CENTER-SIZE_OF_POINTER,SIZE_OF_GRAPH-GRAPHICAL_R*3+SIZE_OF_POINTER);
        g.drawString("y",OFFSET_TO_CENTER+OFFSET_TO_LABEL,SIZE_OF_GRAPH-GRAPHICAL_R*3);

        g.drawLine(GRAPHICAL_R*3,OFFSET_TO_CENTER,SIZE_OF_GRAPH-GRAPHICAL_R*3,OFFSET_TO_CENTER);
        g.drawLine(GRAPHICAL_R*3,OFFSET_TO_CENTER,GRAPHICAL_R*3-SIZE_OF_POINTER,OFFSET_TO_CENTER-SIZE_OF_POINTER);
        g.drawLine(GRAPHICAL_R*3,OFFSET_TO_CENTER,GRAPHICAL_R*3-SIZE_OF_POINTER,OFFSET_TO_CENTER+SIZE_OF_POINTER);
        g.drawString("x",GRAPHICAL_R*3-OFFSET_TO_LABEL,OFFSET_TO_CENTER-OFFSET_TO_LABEL);

        //Tags
        g.drawLine(OFFSET_TO_CENTER+GRAPHICAL_R,OFFSET_TO_CENTER-SIZE_OF_GRAD,OFFSET_TO_CENTER+GRAPHICAL_R,OFFSET_TO_CENTER+SIZE_OF_GRAD);
        g.drawString("R",OFFSET_TO_CENTER+GRAPHICAL_R-OFFSET_TO_LABEL/2,OFFSET_TO_CENTER-OFFSET_TO_LABEL/2);

        g.drawLine(OFFSET_TO_CENTER+GRAPHICAL_R/2,OFFSET_TO_CENTER-SIZE_OF_GRAD,OFFSET_TO_CENTER+GRAPHICAL_R/2,OFFSET_TO_CENTER+SIZE_OF_GRAD);
        g.drawString("R/2",OFFSET_TO_CENTER+GRAPHICAL_R-OFFSET_TO_LABEL*4,OFFSET_TO_CENTER-OFFSET_TO_LABEL/2);

        g.drawLine(OFFSET_TO_CENTER-GRAPHICAL_R,OFFSET_TO_CENTER-SIZE_OF_GRAD,OFFSET_TO_CENTER-GRAPHICAL_R,OFFSET_TO_CENTER+SIZE_OF_GRAD);
        g.drawString("-R",OFFSET_TO_CENTER-GRAPHICAL_R-OFFSET_TO_LABEL,OFFSET_TO_CENTER-OFFSET_TO_LABEL/2);

        g.drawLine(OFFSET_TO_CENTER-GRAPHICAL_R/2,OFFSET_TO_CENTER-SIZE_OF_GRAD,OFFSET_TO_CENTER-GRAPHICAL_R/2,OFFSET_TO_CENTER+SIZE_OF_GRAD);
        g.drawString("-R/2",GRAPHICAL_R,OFFSET_TO_CENTER-OFFSET_TO_LABEL/2);

        //

        g.drawLine(OFFSET_TO_CENTER-SIZE_OF_GRAD,OFFSET_TO_CENTER+GRAPHICAL_R,OFFSET_TO_CENTER+SIZE_OF_GRAD,OFFSET_TO_CENTER+GRAPHICAL_R);
        g.drawString("-R",OFFSET_TO_CENTER+OFFSET_TO_LABEL/2,OFFSET_TO_CENTER+GRAPHICAL_R+OFFSET_TO_LABEL/2);

        g.drawLine(OFFSET_TO_CENTER-SIZE_OF_GRAD,OFFSET_TO_CENTER+GRAPHICAL_R/2,OFFSET_TO_CENTER+SIZE_OF_GRAD,OFFSET_TO_CENTER+GRAPHICAL_R/2);
        g.drawString("-R/2",OFFSET_TO_CENTER+OFFSET_TO_LABEL/2,OFFSET_TO_CENTER+GRAPHICAL_R/2+OFFSET_TO_LABEL/2);

        g.drawLine(OFFSET_TO_CENTER-SIZE_OF_GRAD,OFFSET_TO_CENTER-GRAPHICAL_R/2,OFFSET_TO_CENTER+SIZE_OF_GRAD,OFFSET_TO_CENTER-GRAPHICAL_R/2);
        g.drawString("R/2",OFFSET_TO_CENTER+OFFSET_TO_LABEL/2,OFFSET_TO_CENTER-GRAPHICAL_R/2+OFFSET_TO_LABEL/2);

        g.drawLine(OFFSET_TO_CENTER-SIZE_OF_GRAD,OFFSET_TO_CENTER-GRAPHICAL_R,OFFSET_TO_CENTER+SIZE_OF_GRAD,OFFSET_TO_CENTER-GRAPHICAL_R);
        g.drawString("R",OFFSET_TO_CENTER+OFFSET_TO_LABEL/2,OFFSET_TO_CENTER-GRAPHICAL_R+OFFSET_TO_LABEL/2);

        //Border
        g.drawLine(0,0,SIZE_OF_GRAPH,0);
        g.drawLine(0,0,0,SIZE_OF_GRAPH);
        g.drawLine(SIZE_OF_GRAPH,0,SIZE_OF_GRAPH,SIZE_OF_GRAPH);
        g.drawLine(0,SIZE_OF_GRAPH,SIZE_OF_GRAPH,SIZE_OF_GRAPH);

    }

    public void showPonto(Ponto p, double R){
        if (isPontoOnGraph(p,R)){
            addPontoToGraph(p,getGraphics(),R);
        }
    }

    public void showPontoAnimated(Ponto p, Set<Ponto> pontos,double R){
        if (isPontoOnGraph(p,R)){
            //animation
            if (addPontoToGraph(p,getGraphics(),R)){
                new AnimationThread(this,pontos,R).start();
            }
        }
    }

    private boolean addPontoToGraph(Ponto p, Graphics g, double R){
        boolean inArea = false;
        if (p.isChecked()) {
            if (p.isInSilhouette()) {
                g.setColor(INNER_POINT_COLOR);
                inArea = true;
            } else {
                g.setColor(OUTER_POINT_COLOR);
            }
        } else {
            g.setColor(NOTCHECKED_POINT_COLOR);
        }

        g.fillOval((int)p.getGraphX(R)-SIZE_OF_POINT,(int)p.getGraphY(R)-SIZE_OF_POINT,SIZE_OF_POINT*2,SIZE_OF_POINT*2);
        return inArea;
    }



    private boolean isPontoOnGraph(Ponto p, double R){
        return (p.getGraphX(R) >= 0) &&
                (p.getGraphX(R) <= SIZE_OF_GRAPH) &&
                (p.getGraphY(R)>=0) &&
                (p.getGraphY(R)<= SIZE_OF_GRAPH);
    }

    private int correctValue(int value, int lowbound, int highbound){
        if (value < lowbound){
            return lowbound;
        }
        if (value > highbound){
            return highbound;
        }
        return value;
    }
}
