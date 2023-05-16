package app;

import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;

/**
 * Vincent Verboven
 * 16/05/2023
 */
public class GameView extends GridPane {
    private TextArea tileArray;
    private ImageView block;
    private Label[][] blocks = new Label[4][4];

    public GameView() {
        initialiseNodes();
        layoutNodes();
    }

    void initialiseNodes() {
        tileArray = new TextArea();
        block = new ImageView();

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                blocks[i][j] = new Label();
            }
        }

        for(int i = 0; i < 6; ++i){
            RowConstraints rconstraints = new RowConstraints();
            rconstraints.setPercentHeight(100.0/3);
            this.getRowConstraints().add(rconstraints);
        }
        for(int i = 0; i < 4; ++i){
            ColumnConstraints cconstraints = new ColumnConstraints();
            cconstraints.setPercentWidth(100.0/3);
            this.getColumnConstraints().add(cconstraints);
        }

    }

    void layoutNodes() {
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                this.add(blocks[i][j], i, j+2);
            }
        }
        this.setGridLinesVisible(true);
    }

    TextArea getTileArray(){return tileArray;}

    ImageView getBlock(){return block;}

    Label[][] getBlocks(){return blocks;}

}
