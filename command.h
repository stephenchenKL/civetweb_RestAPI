#pragma once


#include <string>

enum Axis {
    AXIS_ALL = 0,
    AXIS_X = 1,
    AXIS_Y = 2,
    AXIS_Z = 3,
};
enum RCmdId {
    HOME = 0,          //origin (0,0,0)
    PICKUP = 1,
    EJECT = 2,          //note: set (offs_um < 0) to eject to chute
    SAMPLE  = 3,        //plate#1
    SAMPLE_LAST  = 4,   //plate#1 last column
    SAMPLE2 = 5,        //second plate (if supported)
    SAMPLE2_LAST = 6,   //last column of 2nd plate
    WARMUP = 7,        //plate warmup location
    CHUTE = 8,
    PARK = 9,
    SHIP = 10,
    PRESENT = 11,       //robot present position
    UPGRADE = 12,       //Octet-R O-box upgrade location
};
enum ShakerId {
    //target shaker id
    ALL = 0, //all shakers
    SH1 = 1, //shaker #1
    SH2 = 2, //shaker #2
};
enum ShakerMode {
    STOP = 0,
    SHAKE = 1,
    ShakerHOME = 2,
    ShakerPARK = 3,
};
    
struct Command {
    std::string cmd;
    int para1;
    int para2;
    int para3;
    int para4;
    int para5;
    int para6;
};

struct ENGN_Info
{
   bool bCanAutoGain;                     // Spectrometer has adjustable integration time
   bool bHasVariableSpeed;                // Has more than one speed setting
   bool bHasDark;                         // Dark spectra has been saved
   bool bHasRef;                          // Reference spectra has been saved
   bool bMapOK;                           // Spectrometers map status
};

enum CmdType{ 
    Scan,
    Stop,
    Snap,
    SaveRef,
    SaveDark,
    AutoGain,
    LampOn,
    LampOff,
    Park,
    HomeXYZ,
    Eject,
    PickSensor,
    Sample,
    Shaker,
    SetSampleTemp,
    SetSpectTemp,
    RobotCmd,
    Unknown
};
static const CmdType AllCmdTypes[] = 
{ 
    Scan,
    Stop,
    Snap,
    SaveRef,
    SaveDark,
    AutoGain,
    LampOn,
    LampOff,
    Park,
    HomeXYZ,
    Eject,
    PickSensor,
    Sample,
    Shaker,
    SetSampleTemp,
    SetSpectTemp,
    RobotCmd,
    Unknown 
    
};


//==============================================================================================
// FUNCTION: cmdTypeToStr
// PURPOSE:  Maps a command enum value to a string.
//
inline std::string cmdTypeToStr( CmdType cmdType )
{
    switch (cmdType)
    {
        case Scan:              return "scan";
        case Stop:              return "stop";
        case Snap:              return "snap";
        case SaveRef:           return "saveRef";
        case SaveDark:          return "saveDark";
        case AutoGain:          return "autoGain";
        case LampOn:            return "lampOn";
        case LampOff:           return "lampOff";
        case Park:              return "park";
        case HomeXYZ:           return "homeXYZ";
        case Eject:             return "eject";
        case PickSensor:        return "pickSensor";
        case Sample:            return "sample";
        case Shaker:            return "shaker";
        case SetSampleTemp:     return "setSampleTemp";
        case SetSpectTemp:      return "setSpectTemp";
        case RobotCmd:          return "robotCmd";
        case Unknown:           return "unknown";
        
        default:                return "unknown";
        
    }
}

//std::map<std::string, CmdType> nodeMap;


            
