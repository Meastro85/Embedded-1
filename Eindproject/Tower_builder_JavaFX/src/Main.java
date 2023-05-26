import app.GamePresenter;
import app.GameView;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.image.Image;
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

        final int WIDTH = 600;
        final int HEIGHT = 700;

        SerialArduinoConnection con = new SerialArduinoConnection();
        GameView view = new GameView(WIDTH, HEIGHT);

        new GamePresenter(con, view);
        Scene scene = new Scene(view);
        stage.setScene(scene);
        stage.setWidth(WIDTH);
        stage.setHeight(HEIGHT);
        stage.setResizable(false);
        stage.getIcons().add(new Image("images/sprites/Door.png"));
        stage.setTitle("Tower Builder");
        stage.setOnCloseRequest(windowEvent -> con.closePort());
        stage.show();
    }
}
