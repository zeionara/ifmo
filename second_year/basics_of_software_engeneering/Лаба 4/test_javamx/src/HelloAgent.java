import com.sun.jdmk.comm.HtmlAdaptorServer;

import javax.management.*;

/**
 * Created by Zerbs on 18.11.2016.
 */
public class HelloAgent implements NotificationListener{
    private MBeanServer mBeanServer = null;
    public HelloAgent(){
        mBeanServer = MBeanServerFactory.createMBeanServer("HelloAgent");
        HtmlAdaptorServer htmlAdaptorServer = new HtmlAdaptorServer();

        HelloWorld helloWorld = new HelloWorld();

        ObjectName adapterName = null;
        ObjectName helloWorldName = null;

        try{
            adapterName = new ObjectName("HelloAgent:name=helloAdapter1,port=9092");
            htmlAdaptorServer.setPort(9092);
            mBeanServer.registerMBean(htmlAdaptorServer,adapterName);

            htmlAdaptorServer.start();

            helloWorldName = new ObjectName("HelloAgent:name=helloWorld1");
            mBeanServer.registerMBean(helloWorld,helloWorldName);

            helloWorld.addNotificationListener(this,null,null);

        } catch (Exception e){
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        System.out.println("HelloAgent is running");
        HelloAgent helloAgent = new HelloAgent();
    }

    @Override
    public void handleNotification(Notification notification, Object handback) {
        System.out.println("Receiving information");
        System.out.println(notification.getType());
        System.out.println(notification.getMessage());
    }
}
