package jswing;

import javax.swing.*;
import java.util.ArrayList;
import java.util.Set;

public class AnimationThread extends Thread{

    private int step = 17;
    private int delay = 20;

    private GraphPanel animatedGraphPanel;

    private Set<Ponto> pontos;

    private double R;

    private GeneralSilhouette gsh;

    public AnimationThread(GraphPanel graphPanel, Set<Ponto> pontos, double R, GeneralSilhouette gsh){
        animatedGraphPanel = graphPanel;
        this.pontos = pontos;
        this.R = R;
        this.gsh = gsh;
    }

    public void run(){
        int r = 0;
        int g = 0;
        int b = 255;

        animatedGraphPanel.setAreaColor(r,g,b);
        while (r != 255){
            draw(r+=step,g+=step,b-=step);
        }
        while (r != 0){
            draw(r-=step,g-=step,b+=step);
        }
    }

    private void draw(int r, int g, int b){
        animatedGraphPanel.setAreaColor(r,g,b);

        animatedGraphPanel.paint(animatedGraphPanel.getGraphics());

        for (Ponto ponto : pontos){
            animatedGraphPanel.showPonto(ponto,gsh);
        }

        try{
            Thread.sleep(delay);
        } catch (InterruptedException e){
            JOptionPane.showMessageDialog(null, "Error", "Animation thread interrupted", JOptionPane.ERROR_MESSAGE);
        }
    }
}
