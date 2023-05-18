package buildingblocks;

public abstract class BaseBlock {

    final int widthBlocks = 6;
    final int heightBlocks = 7;
    final double width;
    final double height;
    String imageUrl;

    public BaseBlock(double screenWidth, double screenHeight, String imageUrl){
        width = screenWidth / (double) widthBlocks;
        height = screenHeight / (double) heightBlocks;
        this.imageUrl = imageUrl;
    }

    public double getWidth(){
        return width;
    }

    public double getHeight(){
        return height;
    }

    public String getImageUrl(){
        return imageUrl;
    }

}
