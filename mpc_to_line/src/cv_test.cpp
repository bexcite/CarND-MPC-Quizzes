#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

double deg2rad(double deg) { return deg * M_PI / 180; };
double rad2deg(double rad) { return rad * 180 / M_PI; };

class RoadCanvas {
public:
  RoadCanvas(int canvasWidth, int canvasHeight, double worldStartX, double worldStartY, double worldLength, double worldWidth):
          canvasWidth(canvasWidth),
          canvasHeight(canvasHeight),
          worldStartX(worldStartX),
          worldStartY(worldStartY),
          worldWidth(worldWidth),
          worldLength(worldLength),
          vWidth(10),
          vLength(20),
          span(5) {
    canvas = cv::Mat::zeros(canvasHeight, canvasWidth, CV_8UC3);
  };

  void drawVehicle(double x, double y, double psi) {
    cv::Scalar white = cv::Scalar(255.0, 255.0, 255.0, 0);
    cv::Scalar green = cv::Scalar(0, 255.0, 0, 0);

    // create mask
    cv::Mat mask = cv::Mat::zeros(canvas.size(), CV_8UC3);

    cv::Point screenCoords = worldToScreen(x, y);

    int centerX = screenCoords.x;
    int centerY = screenCoords.y;

    // draw on mask
    cv::rectangle(mask,
                  cv::Point(centerX - vWidth/2, centerY + vLength/2),
                  cv::Point(centerX + vWidth/2, centerY - vLength/2),
                  white);
    cv::arrowedLine(mask, cv::Point(centerX, centerY + vLength/2 - 2), cv::Point(centerX, centerY - vLength/2 + 2), cv::Scalar(0, 255.0, 0, 0),
                    1, 8, 0, 0.6);


    // rotate mask
    cv::Mat rotation = cv::getRotationMatrix2D(cv::Point(centerX, centerY), rad2deg(psi), 1);
    std::cout << "rotation = " << rotation << std::endl;

    cv::warpAffine(mask, mask, rotation, mask.size());


    cv::addWeighted(canvas, 1, mask, 1, 0, canvas);
  }

  cv::Mat getCanvas() { return canvas; }

  cv::Point worldToScreen(double x, double y) {
    double screenY = canvasHeight - span - (x - worldStartX) * canvasHeight / worldLength;
    double screenX = (y - worldStartY) * canvasWidth / worldWidth;
    return cv::Point(screenX, screenY);
  }

private:
  cv::Mat canvas;
  int canvasWidth;
  int canvasHeight;
  double worldStartX, worldStartY;
  double worldWidth, worldLength;

  int vWidth, vLength, span;
};

/*
void drawVehicle(cv::Mat& image, double x, double y, double psi) {
  int w = 10;
  int l = 20;
  int bottom = 20;

  cv::Scalar white = cv::Scalar(255.0, 255.0, 255.0, 0);

  // create mask
  cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC3);

  int centerX = image.size().width/2 + y;
  int centerY = image.size().height - bottom - x;

  // draw on mask
  cv::rectangle(mask,
                cv::Point(centerX - w/2, centerY + l/2),
                cv::Point(centerX + w/2, centerY - l/2),
                white);
  cv::arrowedLine(mask, cv::Point(centerX, centerY + l/2 - 2), cv::Point(centerX, centerY - l/2 + 2), cv::Scalar(0, 255.0, 0, 0),
                  1, 8, 0, 0.6);


  // rotate mask
  cv::Mat rotation = cv::getRotationMatrix2D(cv::Point(centerX, centerY), rad2deg(psi), 1);
  std::cout << "rotation = " << rotation << std::endl;

  cv::warpAffine(mask, mask, rotation, mask.size());


  cv::addWeighted(image, 1, mask, 1, 0, image);
}
 */

int main(int argc, char** argv )
{

  int window_height = 800;
  int window_width = 800;

//  cv::Mat image;
  //image = imread( argv[1], 1 );
//  image = cv::Mat::zeros(window_height, window_width, CV_8UC3);

  namedWindow("Display Image", cv::WINDOW_NORMAL);


  RoadCanvas canvas(window_height, window_width, -10, -10, 110, 20);
  //canvas.drawVehicle(0, 0, 0.3);

//  cv::imshow("Display Image", canvas.getCanvas());
//  cv::waitKey(0);




  double x = 10;
  double y = 0;
  double psi = 0;
  for (int i = 0; i < 50; ++i) {
    psi = i * 2 * M_PI / 30;
//    x = 10 + 25 * i;
//    y = 30 * sin(psi);
    x = i;
    y = 5 * sin(psi);


//    drawVehicle(image, x, y, psi);
//    cv::imshow("Display Image", image);

    canvas.drawVehicle(x, y, psi);

    cv::imshow("Display Image", canvas.getCanvas());
    cv::waitKey(0);
  }

  cv::waitKey(0);

  //std::cout << image << std::endl;




  std::cout << "hello";


  return 0;
}
