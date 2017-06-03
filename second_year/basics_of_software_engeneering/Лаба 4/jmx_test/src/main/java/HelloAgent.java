import com.sun.jdmk.comm.HtmlAdaptorServer;

import javax.management.*;

/**
 * Created by Zerbs on 18.11.2016.
 */
public class HelloAgent {
    private MBeanServer mBeanServer = null;
    public HelloAgent(){
        mBeanServer = MBeanServerFactory.createMBeanServer("HelloAgent");
        HtmlAdaptorServer htmlAdaptorServer = new HtmlAdaptorServer();

        HelloWorld helloWorld = new HelloWorld();

        ObjectName adapterName = null;
        ObjectName helloWorldName = null;

        try{
            helloWorldName = new ObjectName("HelloAgent:name=helloWorld1");
            mBeanServer.registerMBean(helloWorld,helloWorldName);

            adapterName = new ObjectName("HelloAgent:name=helloAdapter1,port=9092");
            htmlAdaptorServer.setPort(9092);
            mBeanServer.registerMBean(htmlAdaptorServer,adapterName);

            htmlAdaptorServer.start();
        } catch (Exception e){
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        System.out.println("HelloAgent is running");
        HelloAgent helloAgent = new HelloAgent();
    }
}
