import javax.management.Notification;
import javax.management.NotificationBroadcasterSupport;

/**
 * Created by Zerbs on 18.11.2016.
 */
public class HelloWorld extends NotificationBroadcasterSupport implements HelloWorldMBean{
    private String greeting = null;

    public HelloWorld(){
        setGreeting("Hello world! I am Standard MBean!");
    }

    public HelloWorld(String greeting){
        setGreeting(greeting);
    }

    public void setGreeting(String greeting) {
        this.greeting = greeting;
        Notification notification = new Notification("HeloWorld.test",this,-1,System.currentTimeMillis(),greeting);
        sendNotification(notification);
    }

    public String getGreeting() {
        return greeting;
    }

    public void printGreeting() {
        System.out.println(greeting);
    }
}
