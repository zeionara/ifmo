import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.PropertyResourceBundle;
import java.util.ResourceBundle;

/**
 * Created by Zerbs on 20.11.2016.
 */
public class Main {
    public static void main(String[] args) {
        ResourceBundle resourceBundle = ResourceBundle.getBundle("MyResources");
        System.out.print(resourceBundle.getString("hello"));
        PropertyResourceBundle propertyResourceBundle = null;
        try {
            propertyResourceBundle = new PropertyResourceBundle(new FileReader("src\\MyResources_ru.properties"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(new File(".").getAbsolutePath());
        System.out.print(propertyResourceBundle.getString("hello"));
    }
}
