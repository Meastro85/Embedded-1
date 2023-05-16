package app;

import javafx.scene.control.TextArea;
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
    private final ImageView[][] blocks = new ImageView[4][5];

    public GameView() {
        initialiseNodes();
        layoutNodes();
    }

    void initialiseNodes() {
        tileArray = new TextArea();

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 5; j++){
                blocks[i][j] = new ImageView();
            }
        }

        for(int i = 0; i < 7; ++i){
            RowConstraints rconstraints = new RowConstraints();
            rconstraints.setPercentHeight(100.0/3);
            this.getRowConstraints().add(rconstraints);
        }
        for(int i = 0; i < 6; ++i){
            ColumnConstraints cconstraints = new ColumnConstraints();
            cconstraints.setPercentWidth(100.0/3);
            this.getColumnConstraints().add(cconstraints);
        }

    }

    void layoutNodes() {
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 5; j++){
                this.add(blocks[i][j], i+1, j+1);
            }
        }
        this.setGridLinesVisible(true);
    }

    TextArea getTileArray(){return tileArray;}

    ImageView[][] getBlocks(){return blocks;}

    void resetBlock(int i, int j){
        blocks[i][j] = new ImageView();
    }

}
