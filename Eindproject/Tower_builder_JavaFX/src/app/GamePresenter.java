package app;

import buildingblocks.GrassBlock;
import buildingblocks.WallBlock;
import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import javafx.application.Platform;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import model.SerialArduinoConnection;
import model.TypeConverter;

import java.util.Random;


/**
 * Vincent Verboven
 * 16/05/2023
 */
public class GamePresenter implements SerialPortDataListener {

    private final SerialArduinoConnection con;
    private final GameView view;
    private Random random;

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
            string = string.replace("2DArray:","");
            //System.out.println(string);
            tileArray = TypeConverter.convertTo2DArray(string);
        } else {
            System.out.println(string);
        }

        String[][] finalTileArray = tileArray;
        Platform.runLater(() -> {
            if(finalTileArray.length != 0){
                for(int i = 0; i < finalTileArray.length; i++){
                    for(int j = 0; j < finalTileArray[i].length; j++){
                        ImageView block = view.getBlocks()[i][j];
                        int tile = Integer.parseInt(finalTileArray[i][j]);
                        if(tile > 0){
                            //System.out.println(finalTileArray[i][j]);
                            WallBlock wallBlock = new WallBlock(view.getWidth(), view.getHeight());
                            block.setFitWidth(wallBlock.getWidth());
                            block.setFitHeight(wallBlock.getHeight());
                            if(tile == 4){
                                block.setImage(new Image("images/sprites/Door.png"));
                            } else if (tile == 1 && j == 4){
                                block.setImage(new Image("images/sprites/BottomWall.png"));
                            } else {
                                block.setImage(new Image(wallBlock.getImageUrl()));
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
