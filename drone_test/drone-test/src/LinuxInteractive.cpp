/*! @file LinuxInteractive.cpp
 *  @version 3.1.8
 *  @date Aug 05 2016
 *
 *  @brief
 *  Barebones interactive UI for executing Onboard SDK commands.
 *  Calls functions from the new Linux example based on user input.
 *
 *  @copyright
 *  2016 DJI. All rights reserved.
 * */

#include "LinuxInteractive.h"
#include "DJI_VirtualRC.h"

using namespace std;

char userInput()
{
  cout << endl;
  cout << "|------------------DJI Onboard SDK Interactive Sample------------|" << endl;
  cout << "|                                                                |" << endl;
  cout << "| The interactive mode allows you to execute a few commands      |" << endl;
  cout << "| to help you get a feel of the DJI Onboard SDK. Try them out!   |" << endl;
  cout << "|                                                                |" << endl;
  cout << "| Standard DJI Onboard SDK Usage Flow:                           |" << endl;
  cout << "| 1. Activate (The sample has already done this for you)         |" << endl;
  cout << "| 2. Obtain Control (The sample has already done this for you)   |" << endl;
  cout << "| 3. Takeoff                                                     |" << endl;
  cout << "| 4. Execute Aircraft control (Movement control/Missions/Camera) |" << endl;
  cout << "| 5. Return to Home/Land                                         |" << endl;
  cout << "| 6. Release Control (The sample will do this for you on exit)   |" << endl;
  cout << "|                                                                |" << endl;
  cout << "| Available commands:                                            |" << endl;
  cout << "| [a] Request Control                                            |" << endl;
  cout << "| [b] Release Control                                            |" << endl;
  cout << "| [c] Arm the Drone                                              |" << endl;
  cout << "| [d] Disarm the Drone                                           |" << endl;
  cout << "| [e] Takeoff                                                    |" << endl;
  cout << "| [f] Waypoint Sample                                            |" << endl;
  cout << "| [g] Position Control Sample: Draw Square                       |" << endl;
  cout << "| [h] Landing                                                    |" << endl;
  cout << "| [i] Go Home                                                    |" << endl;
  cout << "| [j] Set Gimbal Angle                                           |" << endl;
  cout << "| [k] Set Gimbal Speed                                           |" << endl;
  cout << "| [l] Take Picture                                               |" << endl;
  cout << "| [m] Take Video                                                 |" << endl;
  cout << "| [n] Exit this sample                                           |" << endl;
  cout << "|                                                                |" << endl;
  cout << "| Type one of these letters and then press the enter key.        |" << endl;
  cout << "|                                                                |" << endl;
  cout << "| If you're new here, try following the usage flow shown above.  |" << endl;
  cout << "|                                                                |" << endl;
  cout << "| Visit developer.dji.com/onboard-sdk/documentation for more.    |" << endl;
  cout << "|                                                                |" << endl;
  cout << "|------------------DJI Onboard SDK Interactive Sample------------|" << endl;
#ifdef LIDAR_LOGGING
  cout << "                                                                  " << endl;
  cout << "                                                                  " << endl;
  cout << "|------------------LiDAR Logging Sample--------------------------|" << endl;
  cout << "|                                                                |" << endl;
  cout << "| [o] Start LiDAR Logging in pcap and LAS format                 |" << endl;
  cout << "| You would need a Velodyne PUCK or Simulator to run this sample |" << endl;
  cout << "|                                                                |" << endl;
  cout << "| [p] Stop LiDAR Logging                                         |" << endl;
  cout << "|                                                                |" << endl;
  cout << "|------------------LiDAR Logging Sample--------------------------|" << endl;
#endif
#ifdef USE_PRECISION_MISSIONS
  cout << "                                                                  " << endl;
  cout << "                                                                  " << endl;
  cout << "|------------------Precision Trajectories------------------------|" << endl;
  cout << "|                                                                |" << endl;
  cout << "| [z] Precision Mission Plan: Execute a pre-planned spiral       |" << endl;
  cout << "|                                                                |" << endl;
  cout << "|------------------Precision Trajectories------------------------|" << endl;
#endif
  char inputChar;
  cin >> inputChar;
  return inputChar;
}

void interactiveSpin(CoreAPI* api, Flight* flight, WayPoint* waypointObj, Camera* camera, std::string pathToSpiral, std::string paramTuningFile)
{
  bool userExitCommand = false;

  //@todo heartcraft add
  VirtualRC vrc(api);
  RadioData vrcdata;
  BroadcastData bcdata;
  CommonData comdata;
  CtrlInfoData cidata;\
  SDKFilter f;
  //end!

  ackReturnData takeControlStatus;
  ackReturnData releaseControlStatus;
  ackReturnData armStatus;
  ackReturnData disArmStatus;
  ackReturnData takeoffStatus;
  ackReturnData landingStatus;
  ackReturnData goHomeStatus;
  int drawSqrPosCtrlStatus;
  uint16_t trajectoryStatus;

#ifdef USE_PRECISION_MISSIONS
  //! Instantiate a local frame for trajectory following
  BroadcastData data = api->getBroadcastData();
  Eigen::Vector3d originLLA(data.pos.latitude, data.pos.longitude, data.pos.altitude);
  CartesianFrame localFrame(originLLA);
  TrajectoryFollower* follower;
  Trajectory* trajectory;

  //! Extract the drone version from the UserConfig params
  std::string hardwareVersion = std::string(api->getHwVersion());

  //! Set up the follower using the tuning parameters supplied
  if (!pathToSpiral.empty()) {
    TrajectoryInfrastructure::startStateBroadcast(api);
    follower = TrajectoryInfrastructure::setupFollower(api,
                                                       flight,
                                                       &localFrame,
                                                       camera,
                                                       hardwareVersion,
                                                       paramTuningFile);
  } else {
    follower = NULL;
    std::cout << "You have chosen to enable precision missions at compile time, but to run a precision mission, you need to supply a trajectory as a program argument.\n";
  }
  //! Set up the trajectory using the trajectory parameters supplied
  trajectory = TrajectoryInfrastructure::setupTrajectory(pathToSpiral);
#endif

  while (!userExitCommand)
  {

    //@todo heartcraft add code
    //gimbal ==> ping heng zhi jia
    //roll ==> gun dong cheng du
    //pitch ==> xiang qian qing xie cheng du
    //yaw ==> pian jiao
//    vrcdata = vrc.getRCData();
//    cout<<"gear= "<<vrcdata.gear<<(vrcdata.gear==-10000?" gear is up ":" gear is down")<<endl;
//    cout<<"roll= "<<vrcdata.roll<<(vrcdata.roll>0?" left handle to right":
//                                                  (vrcdata.roll==0?" left handle in mid ":" left handle to left"))<<endl;
//    cout<<"pitch= "<<vrcdata.pitch<<(vrcdata.pitch>0?" right handle to right":
//                                                  (vrcdata.pitch==0?" right handle in mid ":" right handle to left"))<<endl;
//    cout<<"yaw= "<<vrcdata.yaw<<(vrcdata.yaw>0?" right handle up":
//                                                 (vrcdata.yaw==0?" right handle in mid ":" right handle down"))<<endl;
    //cout<<"throtlle= "<<vrcdata.throttle<<endl;

    if(f.recvBuf[14]=='c')
        cout<<"take photo"<<endl;
    if(f.recvBuf[14]=='v')
        cout<<"take video"<<endl;
    if(f.recvBuf[14]=='l')
        cout<<"botton c1 is clicked"<<endl;
    if(f.recvBuf[14]=='r')
        cout<<"botton c2 is clicked"<<endl;

  }
  return;
}
