import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.highgui.Highgui;
import org.opencv.highgui.VideoCapture;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.image.BufferedImage;
import java.io.File;

/**
 * Created by T540p on 2015-08-06.
 */
public class OpenCVCameraCapture extends JFrame {

    static {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
    }

    public static void main(String[] args) {
        JFrame window = new JFrame("CAMERA TEST");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(true);
        window.setLocationRelativeTo(null);
        JLabel label = new JLabel("", JLabel.CENTER);
        window.getContentPane().add(label);
        window.validate();
        window.setVisible(true);
        Mat frame = new Mat();
        VideoCapture cap = new VideoCapture(0);
        while (true) {
            cap.retrieve(frame);
            Highgui.imwrite("camera.jpg", frame);
            try {
                BufferedImage bufImg = ImageIO.read(new File("camera.jpg"));
                label.setIcon(new ImageIcon(bufImg));
                //jlabel.repaint();
                //works even without repaint
            } catch (Exception e) {
            }

            ImageIcon ico = new ImageIcon("camera.jpg");
            window.setSize(ico.getIconWidth() + 10, ico.getIconHeight() + 35);
            window.repaint();
        }


    }
}