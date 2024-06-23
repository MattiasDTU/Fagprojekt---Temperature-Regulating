#pragma once
#include "Lib.h"
ScreenState currentScreen = MENU;
MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);



void MenuControls() {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT); 
  if (p.z > ts.pressureThreshhold) {
    if (p.x > 232 && p.x < 829 && p.y > 620 && p.y < 771) {
        currentScreen = SENSORS;
    } else if (p.x > 232 && p.x < 829 && p.y > 206 && p.y < 357) {
        currentScreen = SETTINGS;
    } else if (p.x > 232 && p.x < 829 && p.y > 394 && p.y < 570) {
        currentScreen = SIMULATION;
    }
  }
}
void SettingControls() {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT); 
  if (p.z > ts.pressureThreshhold && p.x > 657 && p.x < 746) { 
    if (p.y > 820 && p.y < 895) {
      GlobalHot = GlobalHot +0.1;
      tft.fillRoundRect(8, 35, 70, 35,1, DARKGRAY);
      number(GlobalHot, 8, 40,3,HotColor,WHITE);
      delay(100);
      } else if (p.y > 696 && p.y < 775) {
      GlobalHot = GlobalHot - 0.1;
      tft.fillRoundRect(8, 35, 70, 35,1, DARKGRAY);
      number(GlobalHot, 8, 40,3,HotColor,WHITE);
      delay(100);
      }  
    } 
    else if (p.z > ts.pressureThreshhold && p.x > 328 && p.x < 420) { 
      if (p.y > 818 && p.y < 887) {
        GlobalCold = GlobalCold +0.1;
        tft.fillRoundRect(245, 35, 70, 35,1, DARKGRAY);
        number(GlobalCold, 245, 40,3,ColdColor,WHITE);
        delay(100);
      } else if (p.y > 689 && p.y < 770) {
        GlobalCold = GlobalCold - 0.1;
        tft.fillRoundRect(245, 35, 70, 35,1, DARKGRAY);
        number(GlobalCold, 245, 40,3,ColdColor,WHITE);
        delay(100);
      }
    }
    else if (p.z > ts.pressureThreshhold && p.x > 145 && p.x < 264 && p.y > 143 && p.y < 230) {
        currentScreen = MENU;
      }
    else if (p.z > ts.pressureThreshhold && p.y > 166 && p.y < 243) {
      if (p.x > 692 && p.x < 774) { //MAX
        currentScreen = HOTCOLOR;
      }
      else if (p.x > 569 && p.x < 625) { //MIN
        currentScreen = COLDCOLOR;
      }
      else if (p.x > 433 && p.x < 500) { //NOM
        currentScreen = NORMCOLOR;
      }
      else if (p.x > 306 && p.x < 366) { //GRAPH
        currentScreen = GRAPHCOLOR;
      }
    }
}

void SensorControls() {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT); 
  pinMode(XM, OUTPUT);

  int startX = 10;
  int startY = 10;
  int boxWidth = 40;
  int boxHeight = 40;
  int gapX = 22;
  int gapY = 14;
  float temp;

  for (int i = 0; i < numSensors; i++) {
    temp = temperatures[i][numPoints-1];
    int x = startX + ((i % 4) * (boxWidth + gapX));
    int y = startY + ((i / 4) * (boxHeight + gapY));
    if (temp > GlobalHot) {
          drawTemperatureBox(x, y, temp, HotColor, WHITE);
        } else if (temp < GlobalCold) {
          drawTemperatureBox(x, y, temp, ColdColor, WHITE);
        } else {
          drawTemperatureBox(x, y, temp, NormColor, BLACK);
        }
    if (p.z > ts.pressureThreshhold) {
      if (p.x > 145 && p.x < 264 && p.y > 143 && p.y < 230) {
          currentScreen = MENU;
          break;
        }
      else if (p.x > 826 && p.x < 920) { //FØRSTE RÆKKE
        if (p.y > 752 && p.y < 874) {
          currentScreen = GRAPH;
          GraphSensor = 1;
          break;
        }
        if (p.y > 553 && p.y < 689) {
          currentScreen = GRAPH;
          GraphSensor = 5;
          break;
        }
        if (p.y > 401 && p.y < 514) {
          currentScreen = GRAPH;
          GraphSensor = 9;
          break;
        }
        if (p.y > 208 && p.y < 331) {
          currentScreen = GRAPH;
          GraphSensor = 13;
          break;
        }
      }
      else if (p.x > 675 && p.x < 766) {  /// ANDEN RÆKKE
        if (p.y > 752 && p.y < 874) {
          currentScreen = GRAPH;
          GraphSensor = 2;
          break;
        }
        if (p.y > 553 && p.y < 689) {
          currentScreen = GRAPH;
          GraphSensor = 6;
          break;
        }
        if (p.y > 401 && p.y < 514) {
          currentScreen = GRAPH;
          GraphSensor = 10;
          break;
        }
        if (p.y > 208 && p.y < 331) {
          currentScreen = GRAPH;
          GraphSensor = 14;
          break;
        }
      }
      else if (p.x > 512 && p.x < 607) { //TREDJE RÆKKE
        if (p.y > 752 && p.y < 874) {
          currentScreen = GRAPH;
          GraphSensor = 13;
          break;
        }
        if (p.y > 553 && p.y < 689) {
          currentScreen = GRAPH;
          GraphSensor = 7;
          break;
        }
        if (p.y > 401 && p.y < 514) {
          currentScreen = GRAPH;
          GraphSensor = 11;
          break;
        }
        if (p.y > 208 && p.y < 331) {
          currentScreen = GRAPH;
          GraphSensor = 15;
          break;
        }
      }
      else if (p.x > 353 && p.x < 454) { //FJERDE RÆKKE
        if (p.y > 752 && p.y < 874) {
          currentScreen = GRAPH;
          GraphSensor = 4;
          break;
        }
        if (p.y > 553 && p.y < 689) {
          currentScreen = GRAPH;
          GraphSensor = 8;
          break;
        }
        if (p.y > 401 && p.y < 514) {
          currentScreen = GRAPH;
          GraphSensor = 12;
          break;
        }
        if (p.y > 208 && p.y < 331) {
          currentScreen = GRAPH;
          GraphSensor = 16;
          break;
        }
      }
    }
  }
}
void GraphControls() {
  int startX = 10;
  int endX = 310;
  int startY = 10;
  int endY = 200;
  int interval = 200;
  int graphX = startX + 20;
  float temprange1 = 0;
  float temprange2 = 0;
  if (GraphBegin == 101) {
    tft.fillRect(107, 20, 204, 130, BLACK);
    GraphBegin = 0;
  }
  float temperature = -temperatures[GraphSensor-1][numPoints-1];
  float prevTemperature = -temperatures[GraphSensor-1][numPoints-2];
  if (temperature <= 0) {
    if (prevTemperature <= 0 && temperature <= 0) {
      tft.drawLine(106 + (GraphBegin - 1)*2, (prevTemperature-10*round(prevTemperature/10.0))*10+100, 106 + GraphBegin*2,(temperature-10*round(temperature/10.0))*10+100, GraphColor);
      tft.drawLine(106 + (GraphBegin - 1)*2, (prevTemperature-10*round(prevTemperature/10.0))*10+99, 106 +  GraphBegin*2, (temperature-10*round(temperature/10.0))*10+99, GraphColor);
      tft.drawLine(106 + (GraphBegin - 1)*2, (prevTemperature-10*round(prevTemperature/10.0))*10+98, 106 +  GraphBegin*2, (temperature-10*round(temperature/10.0))*10+98, GraphColor);
      tft.drawLine(106 + (GraphBegin - 1)*2, (prevTemperature-10*round(prevTemperature/10.0))*10+97, 106 +  GraphBegin*2, (temperature-10*round(temperature/10.0))*10+97, GraphColor);
      }
  }
  GraphBegin++;
  temperature = -temperature;
  tft.setCursor(35, 20);
  tft.setCursor(35, 20);
  tft.setTextSize(1);
  temprange1 = round(temperature/10)*10-5;
  temprange2 = round(temperature/10)*10+5;
  if (prev_temprange != temprange1) {
    tft.fillRoundRect(30,30,69,30,1,BLACK);
    tft.setCursor(60, 40);
    tft.setTextSize(2);
    tft.print(String(round(temperature/10)*10+5) + "C");
    tft.fillRoundRect(30,140,69,30,1,BLACK);
    tft.setCursor(60, 140);
    tft.print(String(round(temperature/10)*10-5) + "C");
    prev_temprange=temprange1;
    tft.fillRect(107, 20, 204, 130, BLACK);
  }
  if (temperature > GlobalHot) {
    tft.fillRoundRect(10, 170, 100, 40,5, HotColor);
    tft.drawRoundRect(10, 170, 100, 40,5, WHITE);
    tft.setCursor(18, 180);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print(String(round(temperature * 10) / 10.0,1) + "C");
  } else if (temperature < GlobalCold) {
    tft.fillRoundRect(10, 170, 100, 40,5, ColdColor);
    tft.drawRoundRect(10, 170, 100, 40,5, WHITE);
    tft.setCursor(18, 180);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print(String(round(temperature * 10) / 10.0,1) + "C");
  } else {
    tft.fillRoundRect(10, 170, 100, 40,5, NormColor);
    tft.drawRoundRect(10, 170, 100, 40,5, WHITE);
    tft.setCursor(18, 180);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print(String(round(temperature * 10) / 10.0,1) + "C");
    }
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT);
  if (p.z > ts.pressureThreshhold && p.x > 145 && p.x < 264 && p.y > 143 && p.y < 230) {
    currentScreen = SENSORS;
    GraphBegin = 0;
  }
}

void SimulationControls() {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT); 
  pinMode(XM, OUTPUT);
  if (p.z > ts.pressureThreshhold && p.x > 145 && p.x < 264 && p.y > 143 && p.y < 230) {
      currentScreen = MENU;
      }
  UpdateSmallGrid();
  bilinearInterpolate(originalGrid, targetGrid);
  drawColormap(targetGrid, 60, 10);
}

void ControlSwitch(ScreenState currentScreen) {
  switch (currentScreen) {
    case MENU:      MenuControls();break;
    case SETTINGS:  SettingControls();break;
    case SENSORS:   SensorControls();break;
    case GRAPH:     GraphControls();break;
    case COLOR:     ColorControls();break;
    case SIMULATION:SimulationControls();break;
    case HOTCOLOR:  ColorControls();break;
    case COLDCOLOR: ColorControls();break;
    case GRAPHCOLOR:ColorControls();break;
    case NORMCOLOR: ColorControls();break;
  }
}

void ColorControls() {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT);
  if (p.z > ts.pressureThreshhold && p.x > 145 && p.x < 264 && p.y > 143 && p.y < 230) {
    currentScreen = SETTINGS;
  }
  ////////////////RÆKKE 1
  else if (p.z > ts.pressureThreshhold && p.x > 835	 && p.x < 914	) { //Række 1
    if (p.y > 748	 && p.y < 860	) { //COLUMN 1
      if (currentScreen == HOTCOLOR) {
        HotColor =BLACK ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =BLACK ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor =BLACK ;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = BLACK ;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 569	 && p.y < 680	) { //COLUMN 2
      if (currentScreen == HOTCOLOR) {
        HotColor =MAGENTA ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =MAGENTA ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor =MAGENTA ;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor =MAGENTA ;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 384 && p.y < 487	) { //COLUMN 3
      if (currentScreen == HOTCOLOR) {
        HotColor =PURPLE ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =PURPLE ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor =PURPLE ;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor =PURPLE ;
      }
      currentScreen = SETTINGS;
    }
  
    else if (p.y > 205	 && p.y < 306) { //COLUMN 4
      if (currentScreen == HOTCOLOR) {
        HotColor =DARKGREEN ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =DARKGREEN ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor = DARKGREEN;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = DARKGREEN;
      }
      currentScreen = SETTINGS;
    }
  }
  ////////////////RÆKKE 2
  else if (p.z > ts.pressureThreshhold && p.x > 680	 && p.x < 772	) { //Række 1
    if (p.y > 748	 && p.y < 860	) { //COLUMN 1
      if (currentScreen == HOTCOLOR) {
        HotColor =BLUE ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =BLUE ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor =BLUE ;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor =BLUE ;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 569	 && p.y < 680	) { //COLUMN 2
      if (currentScreen == HOTCOLOR) {
        HotColor = YELLOW;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =YELLOW ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor =YELLOW ;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = YELLOW;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 384 && p.y < 487	) { //COLUMN 3
      if (currentScreen == HOTCOLOR) {
        HotColor = BROWN ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =BROWN ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor =BROWN ;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor =BROWN ;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 205	 && p.y < 306) { //COLUMN 4
      if (currentScreen == HOTCOLOR) {
        HotColor =DARKBLUE ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =DARKBLUE ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor =DARKBLUE ;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = DARKBLUE;
      }
      currentScreen = SETTINGS;
    }
  }
  ////////////////RÆKKE 3
  else if (p.z > ts.pressureThreshhold && p.x > 552	 && p.x < 634	) { //Række 1
    if (p.y > 748	 && p.y < 860	) { //COLUMN 1
      if (currentScreen == HOTCOLOR) {
        HotColor =RED ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =RED ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor =RED ;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor =RED ;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 569	 && p.y < 680	) { //COLUMN 2
      if (currentScreen == HOTCOLOR) {
        HotColor = WHITE ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =WHITE ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor = WHITE;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor =WHITE ;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 384 && p.y < 487	) { //COLUMN 3
      if (currentScreen == HOTCOLOR) {
        HotColor = GOLD;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =GOLD ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor = GOLD;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = GOLD;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 205	 && p.y < 306) { //COLUMN 4
      if (currentScreen == HOTCOLOR) {
        HotColor =DARKCYAN ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor = DARKCYAN;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor =DARKCYAN ;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = DARKCYAN;
      }
      currentScreen = SETTINGS;
    }
  }
  ////////////////RÆKKE 4
  else if (p.z > ts.pressureThreshhold && p.x > 400	 && p.x < 490	) { //Række 1
    if (p.y > 748	 && p.y < 860	) { //COLUMN 1
      if (currentScreen == HOTCOLOR) {
        HotColor =GREEN ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =GREEN ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor = GREEN;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = GREEN;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 569	 && p.y < 680	) { //COLUMN 2
      if (currentScreen == HOTCOLOR) {
        HotColor = ORANGE;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor = ORANGE;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor =ORANGE ;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = ORANGE;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 384 && p.y < 487	) { //COLUMN 3
      if (currentScreen == HOTCOLOR) {
        HotColor = SILVER;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =SILVER ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor = SILVER;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = SILVER;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 205	 && p.y < 306) { //COLUMN 4
      if (currentScreen == HOTCOLOR) {
        HotColor =DARKMAGENTA ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =DARKMAGENTA ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor = DARKMAGENTA;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor =DARKMAGENTA ;
      }
      currentScreen = SETTINGS;
    }
  }
  ////////////////RÆKKE 5
  else if (p.z > ts.pressureThreshhold && p.x > 256	&& p.x < 347	) { //Række 1
    if (p.y > 748	 && p.y < 860	) { //COLUMN 1
      if (currentScreen == HOTCOLOR) {
        HotColor =CYAN ;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor = CYAN;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor = CYAN;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = CYAN;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 569	 && p.y < 680	) { //COLUMN 2
      if (currentScreen == HOTCOLOR) {
        HotColor = PINKPINK;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor = PINKPINK;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor = PINKPINK;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = PINKPINK;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 384 && p.y < 487	) { //COLUMN 3
      if (currentScreen == HOTCOLOR) {
        HotColor = DARKRED;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =DARKRED ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor =DARKRED ;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor =DARKRED ;
      }
      currentScreen = SETTINGS;
    }
    else if (p.y > 205	 && p.y < 306) { //COLUMN 4
      if (currentScreen == HOTCOLOR ) {
        HotColor = DARKGRAY;
      }
      else if (currentScreen == COLDCOLOR) {
        ColdColor =DARKGRAY ;
      }
      else if (currentScreen == GRAPHCOLOR) {
        GraphColor = DARKGRAY;
      }
      else if (currentScreen == NORMCOLOR) {
        NormColor = DARKGRAY;
      }
      currentScreen = SETTINGS;
    }
  }
}
