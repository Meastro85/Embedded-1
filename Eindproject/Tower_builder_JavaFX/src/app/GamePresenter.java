package app;

import buildingblocks.WallBlock;
import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import javafx.application.Platform;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import model.SerialArduinoConnection;
import model.TypeConverter;


/**
 * Vincent Verboven
 * 16/05/2023
 */
public class GamePresenter implements SerialPortDataListener {

    private final SerialArduinoConnection con;
    private final GameView view;

    public GamePresenter(SerialArduinoConnection con, GameView view) {
        this.con = con;
        this.view = view;
        con.addDatalistener(this);
    }

    @Override
    public int getListeningEvents() {
        return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
    }

    @Override
    public void serialEvent(SerialPortEvent event) {
        if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) {
            return;
        }
        String[][] tileArray = {};
        StringBuilder stringB = new StringBuilder();

        do{
            stringB.append(new String(con.receiveBytes()));
        }while(!stringB.toString().endsWith("$"));

        String string = stringB.toString().replace("$","");
        if(string.startsWith("2DArray:")){
            if(!view.getStartText().getStyle().contains("visibility: hidden")){
                view.getStartText().setStyle("visibility: hidden");
                view.getScoreText().setStyle("visibility: hidden");
            }
            string = string.replace("2DArray:","");
            tileArray = TypeConverter.convertTo2DArray(string);
        } else if(string.startsWith("stop")){
            view.getStartText().setStyle("visibility: visible; -fx-font-size: 3em; ");
            string = string.replace("stop","");
            int score = TypeConverter.convertToInt(string);
            view.getScoreText().setText("Score: " + score);
            view.getScoreText().setStyle("visibility: visible; -fx-font-size: 3em; ");
        }

        String[][] finalTileArray = tileArray;
        Platform.runLater(() -> {
            if(finalTileArray.length != 0){
                for(int i = 0; i < finalTileArray.length; i++){
                    for(int j = 0; j < finalTileArray[i].length; j++){
                        ImageView block = view.getBlocks()[i][j];
                        int tile = Integer.parseInt(finalTileArray[i][j]);
                        if(tile > 0){
                            WallBlock wallBlock = new WallBlock(view.getWidth(), view.getHeight());
                            block.setFitWidth(wallBlock.getWidth());
                            block.setFitHeight(wallBlock.getHeight());
                            if(tile == 4){
                                block.setImage(new Image("images/sprites/Door.png"));
                            } else if (tile == 5){
                                block.setImage(new Image("images/sprites/BottomWall.png"));
                            } else if (tile == 1){
                                block.setImage(new Image(wallBlock.getImageUrl()));
                            } else if (tile == 2){
                                block.setImage(new Image("images/sprites/Window.png"));
                            } else if(tile == 3){
                                block.setImage(new Image("images/sprites/Roof.png"));
                            }
                        } else{
                            block.imageProperty().set(null);
                        }
                    }
                }
            }
        });
    }

}
