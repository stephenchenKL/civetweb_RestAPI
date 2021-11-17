#pragma once

enum Axis {
    AXIS_ALL = 0;
    AXIS_X = 1;
    AXIS_Y = 2;
    AXIS_Z = 3;
}
enum RCmdId {
    HOME = 0;           //origin (0,0,0)
    PICKUP = 1;
    EJECT = 2;          //note: set (offs_um < 0) to eject to chute
    SAMPLE  = 3;        //plate#1
    SAMPLE_LAST  = 4;   //plate#1 last column
    SAMPLE2 = 5;        //second plate (if supported)
    SAMPLE2_LAST = 6;   //last column of 2nd plate
    WARMUP = 7;        //plate warmup location
    CHUTE = 8;
    PARK = 9;
    SHIP = 10;
    PRESENT = 11;       //robot present position
    UPGRADE = 12;       //Octet-R O-box upgrade location
}
enum ShakerId {
    //target shaker id
    ALL = 0; //all shakers
    SH1 = 1; //shaker #1
    SH2 = 2; //shaker #2
}
enum ShakerMode {
    STOP = 0;
    SHAKE = 1;
    HOME = 2;
    PARK = 3;
}
    
struct Command {
    std::string cmd;
    int para1;
    int para2;
    int para3;
    int para4;
    int para5;
    int para6;
};
