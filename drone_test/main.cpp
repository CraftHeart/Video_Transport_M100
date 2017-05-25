/*! @file main.cpp
 *  @version 3.1.8
 *  @date Aug 05 2016
 *
 *  @brief
 *  New Linux App for DJI Onboard SDK.
 *  Provides a number of convenient abstractions/wrappers around core API calls.
 *
 *  Calls are blocking; the calling thread will sleep until the
 *  call returns. Use Core API calls or another sample if you
 *  absolutely need non-blocking calls.
 *
 *  @copyright
 *  2016 DJI. All rights reserved.
 * */

//System Headers
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <Python.h>
#include "core.hpp"
#include "highgui.hpp"
#include "imgproc.hpp"
#include "videoio.hpp"

//DJI Linux Application Headers
#include "LinuxSerialDevice.h"
#include "LinuxThread.h"
#include "LinuxSetup.h"
#include "LinuxCleanup.h"
#include "ReadUserConfig.h"
#include "LinuxMobile.h"
#include "LinuxFlight.h"
#include "LinuxInteractive.h"
#include "LinuxWaypoint.h"
#include "LinuxCamera.h"

//DJI OSDK Library Headers
#include <DJI_Follow.h>
#include <DJI_Flight.h>
#include <DJI_Version.h>
#include <DJI_WayPoint.h>

//Wiring Pi


//Local Mission Planning Suite Headers
//#include <MissionplanHeaders.h>

using namespace cv;
using namespace std;
using namespace DJI;
using namespace DJI::onboardSDK;

//! Main function for the Linux sample. Lightweight. Users can call their own API calls inside the Programmatic Mode else on Line 68.
int main(int argc, char *argv[])
{
  //! Instantiate a serialDevice, an API object, flight and waypoint objects and a read thread.
  LinuxSerialDevice* serialDevice = new LinuxSerialDevice(UserConfig::deviceName, UserConfig::baudRate);
  CoreAPI* api = new CoreAPI(serialDevice);
  Flight* flight = new Flight(api);
  LinuxThread read(api, 2);

  //! Setup
  int setupStatus = setup(serialDevice, api, &read);
  if (setupStatus == -1)
  {
    std::cout << "This program will exit now. \n";
    return 0;
  }

    VideoCapture cap0(0);
    VideoCapture cap1(2);

    Mat frame0,frame1;
    bool show_0 = true;
    namedWindow("Video",CV_WINDOW_AUTOSIZE);
//    namedWindow("Video0",CV_WINDOW_AUTOSIZE);
//    namedWindow("Video1",CV_WINDOW_AUTOSIZE);
//    setWindowProperty("Video",CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
    while(1)
    {

        if(api->getFilter().recvBuf[14]=='c'||show_0)
         {
            show_0 = true;
            cap0>>frame0;
            cap1>>frame1;

            imshow("Video",frame0);
            waitKey(0);
         }
        if(api->getFilter().recvBuf[14]=='v'||!show_0)
        {
            cap0>>frame0;
            cap1>>frame1;
            show_0 = false;
            imshow("Video",frame1);
            waitKey(0);
        }
        if(api->getFilter().recvBuf[14]=='l')
        {
            cout<<"llllllllll"<<endl;
            usleep(1000);
            break;
        }
//        else
//        {
//            cap0>>frame0;
//            cap1>>frame1;

//            if(show_0)
//            {
//                imshow("Video",frame0);
//                waitKey(0);
//            }
//            else {
//                imshow("Video",frame1);
//                waitKey(0);
//            }

//        }

    }



//  while(1)
//  {
//      if(api->getFilter().recvBuf[14]=='c')
//      {
//          cout<<"take photo"<<endl;
//          usleep(1000);
//      }

//      if(api->getFilter().recvBuf[14]=='v')
//      {
//          cout<<"take video"<<endl;
//          usleep(1000);
//      }

//      if(api->getFilter().recvBuf[14]=='l')
//      {
//          cout<<"botton c1 is clicked"<<endl;
//          usleep(1000);
//      }
//      if(api->getFilter().recvBuf[14]=='r')
//      {
//          cout<<"botton c2 is clicked"<<endl;
//          usleep(1000);
//      }
//  }


  //! Cleanup
  int cleanupStatus = cleanup(serialDevice, api, flight, &read);
  if (cleanupStatus == -1)
  {
    std::cout << "Unable to cleanly destroy OSDK infrastructure. There may be residual objects in the system memory.\n";
    return 0;
  }
  std::cout << "Program exited successfully." << std::endl;

  return 0;
}

