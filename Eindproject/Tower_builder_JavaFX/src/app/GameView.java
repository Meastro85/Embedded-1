package app;

import buildingblocks.GrassBlock;
import javafx.geometry.HPos;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import javafx.scene.text.Text;

/**
 * Vincent Verboven
 * 16/05/2023
 */
public class GameView extends GridPane {

    private final ImageView[][] blocks = new ImageView[4][5];
    private final ImageView[] grassBlocks = new ImageView[6];
    private ImageView treeOne;
    private ImageView treeTwo;
    private final ImageView[][] skyBlocks = new ImageView[6][7];
    private final int WIDTH;
    private final int HEIGHT;
    private Text startText = new Text();


    public GameView(int width, int height) {
        this.WIDTH = width;
        this.HEIGHT = height;
        initialiseNodes();
        layoutNodes();
    }

    void initialiseNodes() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                blocks[i][j] = new ImageView();
            }
        }

        GrassBlock grassBlock = new GrassBlock(WIDTH, HEIGHT);
        for (int i = 0; i < 6; i++) {
            grassBlocks[i] = new ImageView(new Image(grassBlock.getImageUrl()));
            grassBlocks[i].setFitWidth(grassBlock.getWidth());
            grassBlocks[i].setFitHeight(grassBlock.getHeight());
        }

        treeOne = new ImageView(new Image("images/sprites/Tree1.png"));
        treeOne.setFitWidth(grassBlock.getWidth());
        treeOne.setFitHeight(grassBlock.getHeight());

        treeTwo = new ImageView(new Image("images/sprites/Tree2.png"));
        treeTwo.setFitWidth(grassBlock.getWidth());
        treeTwo.setFitHeight(grassBlock.getHeight());

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                skyBlocks[i][j] = new ImageView(new Image("images/sprites/Sky.png"));
                skyBlocks[i][j].setFitWidth(grassBlock.getWidth());
                skyBlocks[i][j].setFitHeight(grassBlock.getHeight());
            }
        }

        skyBlocks[1][1].setImage(new Image("images/sprites/Clouds2.png"));
        skyBlocks[3][1].setImage(new Image("images/sprites/Clouds3.png"));
        skyBlocks[1][0].setImage(new Image("images/sprites/Clouds1.png"));
        skyBlocks[0][2].setImage(new Image("images/sprites/Clouds1.png"));
        skyBlocks[2][3].setImage(new Image("images/sprites/Clouds3.png"));
        skyBlocks[4][2].setImage(new Image("images/sprites/Clouds2.png"));
        skyBlocks[5][3].setImage(new Image("images/sprites/Clouds1.png"));
        skyBlocks[5][0].setImage(new Image("images/sprites/Sun.png"));

        for (int i = 0; i < 7; ++i) {
            RowConstraints rconstraints = new RowConstraints();
            rconstraints.setPercentHeight(100.0 / 3);
            this.getRowConstraints().add(rconstraints);
        }
        for (int i = 0; i < 6; ++i) {
            ColumnConstraints cconstraints = new ColumnConstraints();
            cconstraints.setPercentWidth(100.0 / 3);
            this.getColumnConstraints().add(cconstraints);
        }

        startText = new Text("Press button 1 to start");
        startText.setStyle("-fx-font-size: 3em");

    }

    void layoutNodes() {

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                this.add(skyBlocks[i][j], i, j);
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                this.add(blocks[i][j], i + 1, j + 1);
            }
        }

        for (int i = 0; i < 6; i++) {
            this.add(grassBlocks[i], i, 6);
        }

        GridPane.setColumnSpan(startText,4);
        GridPane.setHalignment(startText, HPos.CENTER);

        this.add(startText, 1,3);
        this.add(treeOne, 0, 5);
        this.add(treeTwo, 5, 5);

    }

    ImageView[][] getBlocks() {
        return blocks;
    }

    Text getStartText(){
        return startText;
    }


}
