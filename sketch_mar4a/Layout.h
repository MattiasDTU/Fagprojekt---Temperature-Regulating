//////////////////////////////////////////////////////////////////////////////////////////                              _                            _   
//                            | |    __ _ _   _  ___  _   _| |_                         //
//                            | |   / _` | | | |/ _ \| | | | __|                        //
//                            | |__| (_| | |_| | (_) | |_| | |_                         //
//                            |_____\__,_|\__, |\___/ \__,_|\__|                        //
//                                        |___/                                         //
//////////////////////////////////////////////////////////////////////////////////////////
//  In this file you can find the layout functions for each window used on the arduino  //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
#include "Colors.h"
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
int freeze_color = BLUE;
int hot_color = RED;
int normal_color = GREEN;
int graph_color = CYAN;
float freezing = 15.2;
float hot = 36.0;
int sensor_ID;
void background(){
  tft.fillScreen(BLACK);tft.setTextSize(1);tft.setCursor(0, 230);
  tft.print("Made by Mattias & Emil");
}
void text(const char* text, int x, int y,int size, int color1, int color2 ) {
  tft.setTextSize(size);tft.setTextColor(color1);tft.setCursor(x+1, y+1);tft.print(text);
  tft.setTextColor(color2);tft.setCursor(x, y);tft.print(text);
}
void number(float number, int x, int y,int size, int color1, int color2 ) {
  tft.setTextSize(size);tft.setTextColor(color1);tft.setCursor(x+1, y+1);tft.print(number,1);
  tft.setTextColor(color2);tft.setCursor(x, y);tft.print(number,1);
}
void exit_button() {
  tft.fillRoundRect(260+2, 210+2, 55, 25,5, WHITE);tft.fillRoundRect(260, 210, 55, 25,5, RED);
  tft.drawRoundRect(260, 210, 55, 25, 5, WHITE);tft.setTextColor(WHITE);tft.setTextSize(2);
  tft.setCursor(260+5, 210+5);tft.print("Exit");
}
void Menu_Layout() {
    background();
    ///////////////// ALL SENSORS
    tft.fillRoundRect(45+5, 40+5, 230, 50, 5, WHITE);
    tft.fillRoundRect(45, 40, 230, 50, 5, RED);  // x, y, width, height, color
    tft.drawRoundRect(45, 40, 230, 50, 5, WHITE);  // x, y, width, height, color
    text("All Sensors", 60, 55,3, BLACK, WHITE );
    ///////////////// Noget
    tft.fillRoundRect(45+5, 100+5, 230, 50, 5, WHITE);
    tft.fillRoundRect(45, 100, 230, 50, 5, GRAY);  // x, y, width, height, r,color
    tft.drawRoundRect(45, 100, 230, 50, 5, WHITE);  // x, y, width, height, r,color
    text("Something", 60, 115,3, BLACK, WHITE );
    ///////////////// CONFIG
    tft.fillRoundRect(45+5, 160+5, 230, 50, 5, WHITE);
    tft.fillRoundRect(45, 160, 230, 50, 5, DARKGRAY);  // x, y, width, height, r,color
    tft.drawRoundRect(45, 160, 230, 50, 5, WHITE);  // x, y, width, height, r,color
    text("Config", 110, 175,3, BLACK, WHITE );
} 
void sensor_boxes(int startX, int startY, int boxWidth, int boxHeight, int gapX, int gapY) {
  for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++) {
          int x = startX + (col * (boxWidth + gapX));
          int y = startY + (row * (boxHeight + gapY));
          tft.drawRoundRect(x+2, y+2, boxWidth, boxHeight,5, WHITE);
          tft.fillRoundRect(x+2, y+2, boxWidth, boxHeight,5, WHITE);
          tft.fillRoundRect(x, y, boxWidth, boxHeight,5, BLACK);
          tft.drawRoundRect(x, y, boxWidth, boxHeight,5, WHITE);
          tft.setCursor(x+14 , y + boxHeight + 4);
          tft.setTextColor(WHITE);
          tft.setTextSize(1);
          tft.print(String(row * 4 + col + 1)+".");
      }
  }
}
void Sensor_Layout() {
  background();
  exit_button();
  int startX = 10;
  int startY = 10;
  int boxWidth = 40;
  int boxHeight = 40;
  int gapX = 22;
  int gapY = 14;
  sensor_boxes(startX,startY,boxWidth,boxHeight,gapX,gapY);
  text("MAX",250,20,3, WHITE, hot_color );
  number(hot,245,50,3, hot_color, WHITE );
  text("MIN",250,100,3, WHITE, freeze_color );
  number(freezing,245,130,3, freeze_color, WHITE );

}
void Color_Layout() {
    tft.fillRoundRect(5, 5, 280, 230, 5, DARKGRAY);
    tft.drawRoundRect(5, 5, 280, 230, 5, WHITE);

    int boxWidth = 40;
    int boxHeight = 40;
    int gapX = 15;
    int gapY = 15;
    int startX = 10;
    int startY = 10;
    int colorIndex = 0;

    const int colors[] = {BLACK, BLUE, RED, GREEN, CYAN, MAGENTA, YELLOW, WHITE,
                          ORANGE, PINK, PURPLE, BROWN, GOLD, SILVER, DARKRED,
                          DARKGREEN, DARKBLUE, DARKCYAN, DARKMAGENTA, DARKGRAY, GRAY};

    for (int i = 0; i < 20; i++) {
        int posX = startX + (i % 5) * (boxWidth + gapX);
        int posY = startY + (i / 5) * (boxHeight + gapY);
        
        tft.fillRoundRect(posX + 2, posY + 2, boxWidth, boxHeight, 5, WHITE);
        tft.fillRoundRect(posX, posY, boxWidth, boxHeight, 5, colors[colorIndex]);
        tft.drawRoundRect(posX, posY, boxWidth, boxHeight, 5, BLACK);

        colorIndex = (colorIndex + 1) % 20;
    }

    exit_button();
}
void Config_Layout() {
  background();
  ///// Øverste temperatur config 
  tft.fillRoundRect(1, 1, 319, 75,5, DARKGRAY);  // x, y, width, height, r,color
  tft.drawRoundRect(1, 1, 319, 75,5, WHITE);  // x, y, width, height, r,color
  text("MAX", 10, 10,3,WHITE,hot_color );
  text("MIN", 255, 10,3,WHITE,freeze_color);
  number(hot, 8, 40,3,hot_color,WHITE);
  tft.fillTriangle(80,30,95,5,110,30,WHITE);
  tft.fillTriangle(80,40,95,65,110,40,WHITE);
  number(freezing, 245, 40,3,freeze_color,WHITE);
  tft.fillTriangle(205,30,220,5,235,30,WHITE);
  tft.fillTriangle(205,40,220,65,235,40,WHITE);

  /// Midterste ting:
  tft.fillRoundRect(1, 76, 319, 75,5, DARKGRAY);  // x, y, width, height, r,color
  tft.drawRoundRect(1, 76, 319, 75,5, WHITE);  // x, y, width, height, r,color
  /// Nederste ting:
  tft.fillRoundRect(1, 151, 319, 80,5, DARKGRAY);  // x, y, width, height, r,color
  tft.drawRoundRect(1, 151, 319, 80,5, WHITE);  // x, y, width, height, r,color
  text("Define Colors", 50, 155,3,BLACK,WHITE );
  // HOT COLOR
  text("MAX",68,180,2,BLACK,hot_color);
  tft.fillRoundRect(70+2, 195+2, 30, 30,5, WHITE);
  tft.fillRoundRect(70, 195, 30, 30,5, hot_color);
  tft.drawRoundRect(70, 195, 30, 30,5, WHITE);

  // COLD COLOR
  text("MIN",118,180,2,BLACK,freeze_color);
  tft.fillRoundRect(120+2, 195+2, 30, 30,5, WHITE);
  tft.fillRoundRect(120, 195, 30, 30,5, freeze_color);
  tft.drawRoundRect(120, 195, 30, 30,5, WHITE);
  // NORMAL COLOR
  text("NOM",168,180,2,BLACK,normal_color);
  tft.fillRoundRect(170+2, 195+2, 30, 30,5, WHITE);
  tft.fillRoundRect(170, 195, 30, 30,5, normal_color);
  tft.drawRoundRect(170, 195, 30, 30,5, WHITE);
  //GRAPH COlor
  text("GRAPH",210,180,2,BLACK,graph_color);
  tft.fillRoundRect(220+2, 195+2, 30, 30,5, WHITE);
  tft.fillRoundRect(220, 195, 30, 30,5, graph_color);
  tft.drawRoundRect(220, 195, 30, 30,5, WHITE);


  exit_button();
}
void Graph_Layout() {
  background();
  exit_button();

  int startX = 100;
  int endX = 310;
  int startY = 10;
  int endY = 150;
  
  tft.setCursor(startX + 50, endY + 20);
  tft.setTextColor(WHITE);
  tft.print("Sensor " + String(sensor_ID));

  // Draw axes
  for (int i = 0; i < 7; i++) {
  tft.drawLine(startX+i, startY, startX+i, endY, WHITE);  // Y-axis
  tft.drawLine(startX, endY+i, endX, endY+i, WHITE);      // X-axis
  }
  tft.fillTriangle(startX-5, startY, startX+3, startY-10, startX+11, startY, WHITE);
  tft.fillTriangle(endX, endY-5, endX+10, endY+3, endX, endY+11, WHITE);
  // Draw labels
  tft.setRotation(0);
  tft.setTextSize(1);
  tft.setCursor(startX+50 , startY + 80);
  tft.setTextColor(WHITE);
  tft.print("Temp (C)");
  tft.setRotation(1);
  tft.setTextSize(1);
  tft.setCursor(startX + 100, endY + 8);
  tft.print("Time");
}
