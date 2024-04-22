//////////////////////////////////////////////////////////////////////////////////////////                              _                            _   
//                        ____            _             _                               //
//                      / ___|___  _ __ | |_ _ __ ___ | |___                            //
//                      | |   / _ \| '_ \| __| '__/ _ \| / __|                          //
//                      | |__| (_) | | | | |_| | | (_) | \__ \                          //
//                      \____\___/|_| |_|\__|_|  \___/|_|___/                           //
//////////////////////////////////////////////////////////////////////////////////////////
//  In this file you can find the control functions for each window used on the arduino //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
#include <TouchScreen.h>
#include "Data.h"
#include "Layout.h"
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
int Update_window = 0;
char Screen = 'M';
int setting = "MAX";
void Menu_Controls() {
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);     //.kbv these pins are shared with TFT
    pinMode(XM, OUTPUT);     //.kbv these pins are shared with TFT
    if (p.z > ts.pressureThreshhold && p.x > 232 && p.x < 829 && p.y > 620 && p.y < 771) { 
      Update_window = 0;
      Screen = 'S';
    }
    if (p.z > ts.pressureThreshhold && p.x > 232 && p.x < 829 && p.y > 206 && p.y < 357) {
      Update_window = 0; 
      Screen = 'C';
    }
}
void readTemperature(float &temperature, int &boxIndex) {
  boxIndex = random(0, 16); 
  temperature = random(150, 360) / 10.0; 
}
void Graph_Control() {
  int startX = 10;
  int endX = 310;
  int startY = 10;
  int endY = 200;
  int interval = 300;
  int graphX = startX + 20;
  float temp;
  static float lastTemp = 0.0;
  tft.fillRect(107, 20, 204, 110, BLACK);
  for (int i = 0; i < 102-1; i++) {  
    for (int i = 0; i < numPoints - 1; i++) {
        temperatures[sensor_ID-1][i] = temperatures[sensor_ID-1][i + 1];
      }
      readMux(temperatures[sensor_ID-1][numPoints - 1], sensor_ID-1);
    temp = -temperatures[sensor_ID-1][101];
    if (temp <= 0 && i != 0) {
      float prev_temp = -temperatures[sensor_ID-1][100];
      float current_temp = -temperatures[sensor_ID-1][101];
      if (prev_temp <= 0 && current_temp <= 0) {
      tft.drawLine(106 + (i - 1)*2, prev_temp+120, 106 + i*2, current_temp+120, graph_color);
      tft.drawLine(106 + (i - 1)*2, prev_temp+119, 106 + i*2, current_temp+119, graph_color);
      tft.drawLine(106 + (i - 1)*2, prev_temp+118, 106 + i*2, current_temp+118, graph_color);
      tft.drawLine(106 + (i - 1)*2, prev_temp+117, 106 + i*2, current_temp+117, graph_color);
      }
    }
    temp = -temp;
    if (temp != lastTemp) {
    lastTemp = temp;
    if (temp > hot) {
      tft.fillRoundRect(10, 170, 100, 40,5, hot_color);
      tft.drawRoundRect(10, 170, 100, 40,5, WHITE);
      tft.setCursor(18, 180);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.print(String(round(temp * 10) / 10.0,1) + "C");
    } else if (temp < freezing) {
      tft.fillRoundRect(10, 170, 100, 40,5, freeze_color);
      tft.drawRoundRect(10, 170, 100, 40,5, WHITE);
      tft.setCursor(18, 180);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.print(String(round(temp * 10) / 10.0,1) + "C");
    } else {
      tft.fillRoundRect(10, 170, 100, 40,5, normal_color);
      tft.drawRoundRect(10, 170, 100, 40,5, WHITE);
      tft.setCursor(18, 180);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.print(String(round(temp * 10) / 10.0,1) + "C");
      }
    }
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);
    pinMode(XM, OUTPUT);
    if (p.z > ts.pressureThreshhold && p.x > 145 && p.x < 264 && p.y > 143 && p.y < 230) {
      Update_window = 0;
      Screen = 'S';
      break;
    }
    delay(interval);
  }
}

void Sensor_Controls() {
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);     //.kbv these pins are shared with TFT
    pinMode(XM, OUTPUT);     //.kbv these pins are shared with TFT
    int startX = 10;
    int startY = 10;
    int boxWidth = 40;
    int boxHeight = 40;
    int gapX = 22;
    int gapY = 14;
    float temp;
    int boxIndex;
    for (boxIndex = 0; boxIndex < numSensors; boxIndex++) {
    temp = temperatures[boxIndex][101];
    int x = startX + ((boxIndex % 4) * (boxWidth + gapX));
    int y = startY + ((boxIndex / 4) * (boxHeight + gapY));
    if (temp > hot) {
      tft.fillRoundRect(x, y, boxWidth, boxHeight,5, hot_color);
      tft.drawRoundRect(x, y, boxWidth, boxHeight,5, WHITE);
      tft.setCursor(x + 5, y + boxHeight / 2);
      tft.setTextColor(WHITE);
      tft.setTextSize(1);
      tft.print(String(round(temp * 10) / 10.0,1) + "C");
    } else if (temp < freezing) {
      tft.fillRoundRect(x, y, boxWidth, boxHeight,5, freeze_color);
      tft.drawRoundRect(x, y, boxWidth, boxHeight,5, WHITE);
      tft.setCursor(x + 5, y + boxHeight / 2);
      tft.setTextColor(WHITE);
      tft.setTextSize(1);
      tft.print(String(round(temp * 10) / 10.0,1) + "C");
    } else {
      tft.fillRoundRect(x, y, boxWidth, boxHeight,5, normal_color); 
      tft.drawRoundRect(x, y, boxWidth, boxHeight,5, WHITE);
      tft.setCursor(x + 5, y + boxHeight / 2);
      tft.setTextColor(BLACK);
      tft.setTextSize(1);
      tft.print(String(round(temp * 10) / 10.0,1) + "C");
    }
    if (p.z > ts.pressureThreshhold && p.x > 145 && p.x < 264 && p.y > 143 && p.y < 230) {
        Update_window = 0;
        Screen = 'M';
        break;
      }
    else if (p.z > ts.pressureThreshhold && p.x > 826 && p.x < 920) { //FØRSTE RÆKKE
      if (p.y > 752 && p.y < 874) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 1;
        break;
      }
      if (p.y > 553 && p.y < 689) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 5;
        break;
      }
      if (p.y > 401 && p.y < 514) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 9;
        break;
      }
      if (p.y > 208 && p.y < 331) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 13;
        break;
      }
    }
    else if (p.z > ts.pressureThreshhold && p.x > 675 && p.x < 766) {  /// ANDEN RÆKKE
      if (p.y > 752 && p.y < 874) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 2;
        break;
      }
      if (p.y > 553 && p.y < 689) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 6;
        break;
      }
      if (p.y > 401 && p.y < 514) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 10;
        break;
      }
      if (p.y > 208 && p.y < 331) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 14;
        break;
      }
    }
    else if (p.z > ts.pressureThreshhold && p.x > 512 && p.x < 607) { //TREDJE RÆKKE
      if (p.y > 752 && p.y < 874) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 3;
        break;
      }
      if (p.y > 553 && p.y < 689) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 7;
        break;
      }
      if (p.y > 401 && p.y < 514) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 11;
        break;
      }
      if (p.y > 208 && p.y < 331) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 15;
        break;
      }
    }
    else if (p.z > ts.pressureThreshhold && p.x > 353 && p.x < 454) { //FJERDE RÆKKE
      if (p.y > 752 && p.y < 874) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 4;
        break;
      }
      if (p.y > 553 && p.y < 689) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 8;
        break;
      }
      if (p.y > 401 && p.y < 514) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 12;
        break;
      }
      if (p.y > 208 && p.y < 331) {
        Screen = 'G';
        Update_window = 0;
        sensor_ID = 16;
        break;
      }
    }
    }
}

void Color_Controls() {

  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);     //.kbv these pins are shared with TFT
  pinMode(XM, OUTPUT);     //.kbv these pins are shared with TFT
  if (p.z > ts.pressureThreshhold && p.x > 145 && p.x < 264 && p.y > 143 && p.y < 230) {
    Screen = 'C';
    Update_window = 0;
  }
  ////////////////RÆKKE 1
  else if (p.z > ts.pressureThreshhold && p.x > 835	 && p.x < 914	) { //Række 1
    if (p.y > 748	 && p.y < 860	) { //COLUMN 1
      if (setting == "MAX") {
        hot_color =BLACK ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =BLACK ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color =BLACK ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = BLACK ;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 569	 && p.y < 680	) { //COLUMN 2
      if (setting == "MAX") {
        hot_color =MAGENTA ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =MAGENTA ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color =MAGENTA ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color =MAGENTA ;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 384 && p.y < 487	) { //COLUMN 3
      if (setting == "MAX") {
        hot_color =PURPLE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =PURPLE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color =PURPLE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color =PURPLE ;
        Screen = 'C';
        Update_window = 0;
      }
    }
  
    else if (p.y > 205	 && p.y < 306) { //COLUMN 4
      if (setting == "MAX") {
        hot_color =DARKGREEN ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =DARKGREEN ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color = DARKGREEN;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = DARKGREEN;
        Screen = 'C';
        Update_window = 0;
      }
    }
  }
  ////////////////RÆKKE 2
  else if (p.z > ts.pressureThreshhold && p.x > 680	 && p.x < 772	) { //Række 1
    if (p.y > 748	 && p.y < 860	) { //COLUMN 1
      if (setting == "MAX") {
        hot_color =BLUE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =BLUE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color =BLUE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color =BLUE ;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 569	 && p.y < 680	) { //COLUMN 2
      if (setting == "MAX") {
        hot_color = YELLOW;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =YELLOW ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color =YELLOW ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = YELLOW;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 384 && p.y < 487	) { //COLUMN 3
      if (setting == "MAX") {
        hot_color = BROWN ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =BROWN ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color =BROWN ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color =BROWN ;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 205	 && p.y < 306) { //COLUMN 4
      if (setting == "MAX") {
        hot_color =DARKBLUE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =DARKBLUE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color =DARKBLUE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = DARKBLUE;
        Screen = 'C';
        Update_window = 0;
      }
    }
  }
  ////////////////RÆKKE 3
  else if (p.z > ts.pressureThreshhold && p.x > 552	 && p.x < 634	) { //Række 1
    if (p.y > 748	 && p.y < 860	) { //COLUMN 1
      if (setting == "MAX") {
        hot_color =RED ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =RED ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color =RED ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color =RED ;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 569	 && p.y < 680	) { //COLUMN 2
      if (setting == "MAX") {
        hot_color = WHITE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =WHITE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color = WHITE;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color =WHITE ;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 384 && p.y < 487	) { //COLUMN 3
      if (setting == "MAX") {
        hot_color = GOLD;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =GOLD ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color = GOLD;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = GOLD;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 205	 && p.y < 306) { //COLUMN 4
      if (setting == "MAX") {
        hot_color =DARKCYAN ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color = DARKCYAN;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color =DARKCYAN ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = DARKCYAN;
        Screen = 'C';
        Update_window = 0;
      }
    }
  }
  ////////////////RÆKKE 4
  else if (p.z > ts.pressureThreshhold && p.x > 400	 && p.x < 490	) { //Række 1
    if (p.y > 748	 && p.y < 860	) { //COLUMN 1
      if (setting == "MAX") {
        hot_color =GREEN ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =GREEN ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color = GREEN;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = GREEN;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 569	 && p.y < 680	) { //COLUMN 2
      if (setting == "MAX") {
        hot_color = ORANGE;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color = ORANGE;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color =ORANGE ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = ORANGE;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 384 && p.y < 487	) { //COLUMN 3
      if (setting == "MAX") {
        hot_color = SILVER;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =SILVER ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color = SILVER;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = SILVER;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 205	 && p.y < 306) { //COLUMN 4
      if (setting == "MAX") {
        hot_color =DARKMAGENTA ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =DARKMAGENTA ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color = DARKMAGENTA;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color =DARKMAGENTA ;
        Screen = 'C';
        Update_window = 0;
      }
    }
  }
  ////////////////RÆKKE 5
  else if (p.z > ts.pressureThreshhold && p.x > 256	&& p.x < 347	) { //Række 1
    if (p.y > 748	 && p.y < 860	) { //COLUMN 1
      if (setting == "MAX") {
        hot_color =CYAN ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color = CYAN;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color = CYAN;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = CYAN;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 569	 && p.y < 680	) { //COLUMN 2
      if (setting == "MAX") {
        hot_color = PINK;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color = PINK;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color = PINK;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = PINK;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 384 && p.y < 487	) { //COLUMN 3
      if (setting == "MAX") {
        hot_color = DARKRED;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =DARKRED ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color =DARKRED ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color =DARKRED ;
        Screen = 'C';
        Update_window = 0;
      }
    }
    else if (p.y > 205	 && p.y < 306) { //COLUMN 4
      if (setting == "MAX") {
        hot_color = DARKGRAY;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "MIN") {
        freeze_color =DARKGRAY ;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "GRAPH") {
        graph_color = DARKGRAY;
        Screen = 'C';
        Update_window = 0;
      }
      else if (setting == "NOM") {
        normal_color = DARKGRAY;
        Screen = 'C';
        Update_window = 0;
      }
    }
  }
}

void Config_Controls() {
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);     //.kbv these pins are shared with TFT
    pinMode(XM, OUTPUT);     //.kbv these pins are shared with TFT
  if (p.z > ts.pressureThreshhold && p.x > 657 && p.x < 746) { 
    if (p.y > 820 && p.y < 895) {
      hot = hot +0.1;
      tft.fillRoundRect(8, 35, 70, 35,1, DARKGRAY);
      number(hot, 8, 40,3,hot_color,WHITE);
      delay(300);
      }
    else if (p.y > 696 && p.y < 775) {
      hot = hot - 0.1;
      tft.fillRoundRect(8, 35, 70, 35,1, DARKGRAY);
      number(hot, 8, 40,3,hot_color,WHITE);
      delay(300);
      }  
    }
    else if (p.z > ts.pressureThreshhold && p.x > 328 && p.x < 420) { 
      if (p.y > 818 && p.y < 887) {
        freezing = freezing +0.1;
        tft.fillRoundRect(245, 35, 70, 35,1, DARKGRAY);
        number(freezing, 245, 40,3,freeze_color,WHITE);
        delay(300);
      }
      else if (p.y > 689 && p.y < 770) {
        freezing = freezing - 0.1;
        tft.fillRoundRect(245, 35, 70, 35,1, DARKGRAY);
        number(freezing, 245, 40,3,freeze_color,WHITE);
        delay(300);
      }
    }
    else if (p.z > ts.pressureThreshhold && p.x > 145 && p.x < 264 && p.y > 143 && p.y < 230) {
        Update_window = 0;
        Screen = 'M';
      }
    else if (p.z > ts.pressureThreshhold && p.y > 166 && p.y < 243) {
      if (p.x > 692 && p.x < 774) { //MAX
        Update_window = 0;
        Screen = 'W';
        setting = "MAX";
      }
      else if (p.x > 569 && p.x < 625) { //MIN
        Update_window = 0;
        Screen = 'W';
        setting = "MIN";
      }
      else if (p.x > 433 && p.x < 500	) { //NOM
        Update_window = 0;
        Screen = 'W';
        setting = "NOM";
      }
      else if (p.x > 306 && p.x < 366		) { //GRAPH
        Update_window = 0;
        Screen = 'W';
        setting = "GRAPH";
      }
    }
}
