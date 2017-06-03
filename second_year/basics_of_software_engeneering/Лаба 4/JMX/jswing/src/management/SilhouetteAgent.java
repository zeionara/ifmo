package management;

import com.sun.jdmk.comm.HtmlAdaptorServer;
import jswing.GeneralSilhouette;
import jswing.Ponto;
import jswing.Silhouette;

import javax.management.*;
import java.lang.management.ManagementFactory;
import java.util.Set;

public class SilhouetteAgent implements NotificationListener{
    private MBeanServer mBeanServer = null;

    public SilhouetteAgent() throws Exception{
        mBeanServer = ManagementFactory.getPlatformMBeanServer();

        HtmlAdaptorServer htmlAdaptorServer = new HtmlAdaptorServer();
        ObjectName adapterName = new ObjectName("SilhouetteAgent:name=htmlAdapter,port=9092");
        htmlAdaptorServer.setPort(9092);
        mBeanServer.registerMBean(htmlAdaptorServer,adapterName);

        htmlAdaptorServer.start();

        ObjectName chiefPontoCounterName = new ObjectName("management:type=PontoCounter,name=ChiefPontoCounter");
        PontoCounter chiefPontoCounter = new PontoCounter();
        mBeanServer.registerMBean(chiefPontoCounter,chiefPontoCounterName);

        ObjectName chiefClickMeasurerName = new ObjectName("management:type=ClickMeasurer,name=ChiefClickMeasurer");
        ClickMeasurer chiefClickMeasurer = new ClickMeasurer();
        mBeanServer.registerMBean(chiefClickMeasurer,chiefClickMeasurerName);

        chiefPontoCounter.addNotificationListener(this,null,null);
    }

    @Override
    public void handleNotification(Notification notification, Object handback) {
        System.out.println("Receiving information...");
        System.out.println(notification.getType());
        System.out.println(notification.getMessage());
    }

    public void GraphPanelClicked() throws Exception{
        ObjectName objectName = new ObjectName("management:type=ClickMeasurer,name=ChiefClickMeasurer");
        mBeanServer.invoke(objectName, "areaClicked", new Object[]{}, new String[]{});
    }

    public void PontoAdded(Ponto ponto, GeneralSilhouette gsh) throws Exception{
        ObjectName objectName = new ObjectName("management:type=PontoCounter,name=ChiefPontoCounter");
        mBeanServer.invoke(objectName, "pontoAdded", new Object[]{ponto, gsh}, new String[]{Ponto.class.getName(), GeneralSilhouette.class.getName()});
    }

    public void RadiusChanged(Set<Ponto> pontos, GeneralSilhouette gsh) throws Exception{
        ObjectName objectName = new ObjectName("management:type=PontoCounter,name=ChiefPontoCounter");
        mBeanServer.invoke(objectName, "checkAgain", new Object[]{pontos, gsh}, new String[]{Set.class.getName(), GeneralSilhouette.class.getName()});
    }
}
