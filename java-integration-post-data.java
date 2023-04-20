import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import org.json.JSONObject;

public class Example {
    public static void main(String[] args) throws IOException {
        String query_c = "INSERT INTO `test`(`name`,`lname`) VALUES ("Gopal","Dubey")";
        String query = query_c.replaceAll("\s", "+");
        String url = "https://apiin.touchsql.com/?database=mydb&api=Your_API&key=Your_Key&query=" + query;

        URL urlObj = new URL(url);
        HttpURLConnection conn = (HttpURLConnection) urlObj.openConnection();
        conn.setRequestMethod("GET");

        BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        String inputLine;
        StringBuffer response = new StringBuffer();
        while ((inputLine = in.readLine()) != null) {
            response.append(inputLine);
        }
        in.close();

        JSONObject data = new JSONObject(response.toString());
        System.out.println(data);

        if (data.getBoolean("TRUE")) {
            System.out.println("Data inserted");
        } else if (data.getBoolean("FALSE")) {
            System.out.println("Try again");
        }
    }
}
