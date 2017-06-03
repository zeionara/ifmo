/**
 * Created by Zerbs on 18.11.2016.
 */
public class HelloWorld implements HelloWorldMBean{
    private String greeting = null;

    public HelloWorld(){
        setGreeting("Hello world! I am Standard MBean!");
    }

    public HelloWorld(String greeting){
        setGreeting(greeting);
    }

    public void setGreeting(String greeting) {
        this.greeting = greeting;
    }

    public String getGreeting() {
        return greeting;
    }

    public void printGreeting() {
        System.out.println(greeting);
    }
}
