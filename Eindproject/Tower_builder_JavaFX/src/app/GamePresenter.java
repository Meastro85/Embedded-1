package app;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.scene.control.Label;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.paint.Color;
import model.SerialArduinoConnection;

import java.util.Arrays;

/**
 * Vincent Verboven
 * 16/05/2023
 */
public class GamePresenter implements SerialPortDataListener {

    SerialArduinoConnection con;
    GameView view;

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

        try {
            Thread.sleep(75);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        String string = new String(con.receiveBytes());
        if(string.contains("]")){
            string = string.replace("[", "");
            string = string.substring(0, string.length()-2);
            String[] array = string.split("],");
            tileArray = new String[array.length][array.length];

            for(int i = 0; i < array.length; i++){
                array[i] = array[i].trim();
                String[] number  = array[i].split(", ");

                System.arraycopy(number, 0, tileArray[i], 0, number.length);
            }
        }

        String[][] finalTileArray = tileArray;
        Platform.runLater(() -> {
            if(finalTileArray.length != 0){
                for(int i = 0; i < finalTileArray.length; i++){
                    for(int j = 0; j < finalTileArray[i].length; j++){
                        if(Integer.parseInt(finalTileArray[i][j]) > 0){
                            Label block = view.getBlocks()[i][j];
                            block.setPrefWidth(50);
                            block.setPrefHeight(50);
                            block.setBackground(new Background(new BackgroundFill(Color.RED, CornerRadii.EMPTY, Insets.EMPTY)));
                        }
                    }
                }
            }
        });
    }

}
