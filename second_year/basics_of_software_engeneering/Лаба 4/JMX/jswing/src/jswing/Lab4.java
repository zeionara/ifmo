package jswing;

import management.SilhouetteAgent;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.Set;

public class Lab4 extends JFrame{
    private static final int DEFAULT_WINDOW_WIDTH = 1024;
    private static final int DEFAULT_WINDOW_HEIGHT = 480;
    private static final double DEFAULT_R = 10d;
    private static final int DEFAULT_ELEMENT_WIDTH = 100;
    private static final int DEFAULT_ELEMENT_HEIGHT = 20;

    private JComboBox<Double> xComboBox;    //For entering x
    private ArrayList<JCheckBox> yCheckBoxes;   //For entering y
    private JSpinner rSpinner;  //For entering r
    private JTextField pTextField;  //For showing ponto
    private GraphPanel theGraphPanel;   //For showing graph

    private Double R;
    private GeneralSilhouette gsh;
    private Set<Ponto> pontos = new LinkedHashSet<>();

    private SilhouetteAgent silhouetteAgent;

    public static void main(String[] args) {
        new Lab4();
    }

    public Lab4()
    {
        // Initialization
        super();

        try {
            silhouetteAgent = new SilhouetteAgent();
        }catch (Exception e){
            e.printStackTrace();
        }

        setSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setTitle("Fourth Lab");
        setResizable(false);

        JPanel theMainPanel = new JPanel();
        theMainPanel.setLayout(new GridLayout(0,3));

        JPanel thePanelX = newPanelFlowLeft();

        JPanel thePanelY = newPanelFlowLeft();

        JPanel thePanelR = newPanelFlowLeft();

        JPanel thePanelPoint = newPanelFlowLeft();

        //UI components for x
        JLabel xLabel = new JLabel("Please, select x :");
        thePanelX.add(xLabel);

        xComboBox = getComboBoxForX();
        thePanelX.add(xComboBox);
        theMainPanel.add(thePanelX);

        //UI components for y
        JLabel yLabel = new JLabel("Please, select y :");
        thePanelY.add(yLabel);

        yCheckBoxes = getCheckBoxesForY();

        for (JCheckBox checkBox : yCheckBoxes){
            thePanelY.add(checkBox);
        }
        theMainPanel.add(thePanelY);

        //UI components for R
        JLabel rLabel = new JLabel("Please, select R :");
        thePanelR.add(rLabel);

        rSpinner = getSpinnerForR();
        thePanelR.add(rSpinner);

        theMainPanel.add(thePanelR);

        //UI components for point coordinates
        JLabel pLabel = new JLabel("Selected point :");
        thePanelPoint.add(pLabel);

        pTextField = getTextFieldForP();
        thePanelPoint.add(pTextField);

        theMainPanel.add(thePanelPoint);

        //UI components for graph
        theGraphPanel = new GraphPanel();
        theGraphPanel.setPreferredSize(new Dimension(GraphPanel.SIZE_OF_GRAPH,GraphPanel.SIZE_OF_GRAPH));
        theGraphPanel.addMouseListener(new GraphPanelMouseListener());

        theMainPanel.add(theGraphPanel);
        add(theMainPanel);

        setVisible(true);
    }

    private JPanel newPanelFlowLeft(){
        JPanel theNewPanel = new JPanel();
        theNewPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        return theNewPanel;
    }

    private javax.swing.JComboBox<Double> getComboBoxForX() {
        Double[] xs = {-4d, -3d, -2d, 0d, 1d, 2d, 3d, 4d};
        JComboBox<Double> jCB = new javax.swing.JComboBox<>(xs);
        jCB.setFont(new Font("Calibri",Font.PLAIN,12));
        jCB.setPreferredSize(new Dimension(DEFAULT_ELEMENT_WIDTH,DEFAULT_ELEMENT_HEIGHT));
        jCB.addActionListener(new ComboBoxListener());
        return jCB;
    }

    private ArrayList<JCheckBox> getCheckBoxesForY() {
        ArrayList<JCheckBox> jCBs = new ArrayList<>();
        JCheckBox jCB;
        Double[] ys = {-4d, -3d, -2d, 0d, 1d, 2d, 3d, 4d};
        for (Double value : ys){
            jCB = new JCheckBox(value.toString());
            jCBs.add(jCB);
            jCB.addActionListener(new CheckBoxListener());
        }
        return jCBs;
    }

    private JSpinner getSpinnerForR() {
        R = DEFAULT_R;
        JSpinner rSpinner = new JSpinner();
        rSpinner.setValue(R);
        gsh = new GeneralSilhouette(R);
        rSpinner.setPreferredSize(new Dimension(DEFAULT_ELEMENT_WIDTH,DEFAULT_ELEMENT_HEIGHT));
        rSpinner.addChangeListener(new SpinnerChangeListener());
        return rSpinner;
    }

    private JTextField getTextFieldForP() {
        JTextField pTextField = new JTextField();
        pTextField.setEditable(false);
        pTextField.setText("None");
        pTextField.setPreferredSize(new Dimension(DEFAULT_ELEMENT_WIDTH*3,DEFAULT_ELEMENT_HEIGHT));
        return pTextField;
    }

    public static double getRealX(double x, double R){
        return (x-GraphPanel.OFFSET_TO_CENTER)*R/GraphPanel.GRAPHICAL_R;
    }

    public static double getRealY(double y, double R){
        return (-y+GraphPanel.OFFSET_TO_CENTER)*R/GraphPanel.GRAPHICAL_R;
    }

    private class GraphPanelMouseListener extends MouseAdapter {
        @Override
        public void mouseClicked(MouseEvent e) {

            try {
                silhouetteAgent.GraphPanelClicked();
            } catch (Exception e1) {
                e1.printStackTrace();
            }

            Ponto newPonto = new Ponto(getRealX(e.getX(),R),getRealY(e.getY(),R));
            if (!findPonto(pontos,newPonto)) {

                notifyAgentAboutNewPonto(newPonto);

                pontos.add(newPonto);
                ((GraphPanel) e.getSource()).showPontoAnimated(newPonto, pontos, gsh);
                pTextField.setText(newPonto.toString());
            }
        }
    }

    private class SpinnerChangeListener implements ChangeListener{
        @Override
        public void stateChanged(ChangeEvent e) {
            theGraphPanel.paint(theGraphPanel.getGraphics());
            R = ((Integer)((JSpinner)e.getSource()).getModel().getValue()).doubleValue();

            notifyAgentAboutChangingRadius();

            gsh = new GeneralSilhouette(R);
            for (Ponto ponto : pontos){
                theGraphPanel.showPonto(ponto,gsh);
            }
        }
    }

    private class CheckBoxListener implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
            double x = Double.parseDouble(xComboBox.getModel().getSelectedItem().toString());
            double y = Double.parseDouble(((JCheckBox)e.getSource()).getText());
            Ponto newPonto = new Ponto(x,y);

            if (((JCheckBox)e.getSource()).isSelected() && !findPonto(pontos,newPonto)){

                    notifyAgentAboutNewPonto(newPonto);

                    pontos.add(newPonto);
                    pTextField.setText(newPonto.toString());
                    theGraphPanel.showPontoAnimated(newPonto,pontos,gsh);
            }
        }
    }

    private class ComboBoxListener implements ActionListener{
        @Override
        public void actionPerformed(ActionEvent e) {
            boolean added = false;

            double x = Double.parseDouble(((JComboBox)e.getSource()).getModel().getSelectedItem().toString());
            double y = 0;
            Ponto newPonto = new Ponto(x,y);

            for(JCheckBox ycheckBox : yCheckBoxes) {
                y = Double.parseDouble(ycheckBox.getText());
                newPonto = new Ponto(x,y);
                if (ycheckBox.isSelected() && !findPonto(pontos,newPonto)) {

                    notifyAgentAboutNewPonto(newPonto);

                    pontos.add(newPonto);
                    added = true;
                    pTextField.setText(newPonto.toString());
                }
            }
            if (added){
                theGraphPanel.showPontoAnimated(newPonto,pontos,gsh);
            }
        }
    }

    boolean findPonto(Set<Ponto> pontos, Ponto p){
        for(Ponto ponto : pontos){
            if (ponto.equals(p)){
                return true;
            }
        }
        return false;
    }

    private void notifyAgentAboutNewPonto(Ponto newPonto){
        try {
            silhouetteAgent.PontoAdded(newPonto,new GeneralSilhouette(R));
        } catch (Exception e1) {
            e1.printStackTrace();
        }
    }

    private void notifyAgentAboutChangingRadius(){
        try {
            silhouetteAgent.RadiusChanged(pontos,new GeneralSilhouette(R));
        } catch (Exception e1) {
            e1.printStackTrace();
        }
    }
}