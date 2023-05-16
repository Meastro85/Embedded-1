import app.GamePresenter;
import app.GameView;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
import model.SerialArduinoConnection;

/**
 * Vincent Verboven
 * 16/05/2023
 */
public class Main extends Application {

    public static void main(String[] args) {
        Application.launch(args);
    }


    @Override
    public void start(Stage stage) throws Exception {
        SerialArduinoConnection con = new SerialArduinoConnection();
        GameView view = new GameView();

        new GamePresenter(con, view);
        Scene scene = new Scene(view);
        stage.setScene(scene);
        stage.setWidth(200);
        stage.setHeight(300);
        stage.show();
    }
}
