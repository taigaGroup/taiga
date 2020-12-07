#include <iostream>
#include <fstream>
#include <string>

#include "TAIGACluster.h"
#include "TAIGACamera.h"
#include "TAIGAEvent.h"
#include "TAIGARun.h"

TAIGARun::TAIGARun()
  : TObject() {
  std::cout << "TAIGARun::TAIGARun()" << std::endl;
}

TAIGARun::~TAIGARun() {
}

void TAIGARun::readCamera(TAIGACamera *camera) {
	// Open input file with params of the camera
  std::ifstream inputDataIn(GetCameraFileName());
  if (!inputDataIn.is_open()) {
    std::cerr << "TAIGARun::readCamera [ERROR]: Can't read input file!" << std::endl;
    cameraReadStatus=kFALSE;
  }

  // Loop over the files head. To skip It.
  while (!inputDataIn.eof()) {
    std::string testStr;
    inputDataIn >> testStr;
    if (testStr == "h") break;
  }

  if (inputDataIn.eof()) {
    std::cerr << "TAIGARun::readCamera [ERROR]: End of the file, stop flag wasn't found!" << std::endl;
    cameraReadStatus=kFALSE;
  }

  UInt_t counter = 0;
  while(!inputDataIn.eof() && cameraReadStatus) {
    Int_t curNcl, curLen, curNFeu, curNan, curNdin, curH;
    Double_t curXcm, curYcm;
    inputDataIn >> curNcl >> curNFeu >> curLen >> curXcm >> curYcm >> curNan >> curNdin >> curH;
    /*std::cout << curNcl << " " << curNFeu << " " << curLen<< " " << curXcm << " " << curYcm << " " << curNan << " "
              << curNdin << " " << curH << std::endl;*/
    camera->SetPixelXcor(curXcm, curNcl, curNFeu); // Xcor, NClaster, NPixel
    camera->SetPixelYcor(curYcm, curNcl, curNFeu); // Ycor, NClaster, NPixel
    counter++;
  }
}

void TAIGARun::readEvents(std::vector<TAIGAEvent> *vectOfEvents) {
  std::ifstream fin(GetEventsFileName());
  if (!fin.is_open()) {
    std::cerr << "Can't read Input txt!" << std::endl;
    eventsReadStatus=kFALSE;
  }

  while (!fin.eof()) {
    Int_t curNum;
    fin >> curNum;
    Int_t NumberOfTriggClrs = curNum;
    TAIGAEvent curEvent;
    Int_t curNEvent;
    for (Int_t i=0; i<NumberOfTriggClrs; i++) {
      TAIGACluster curClr;
      fin >> curNum;
      Int_t curNClr = curNum;
      curClr.SetNCluster(curNClr);
      fin >> curNum;
      curNEvent = curNum;
      std::string timeStr;
      fin >> timeStr;

      for (Int_t j=0; j<NUMBER_OF_PIXELS; j++) {
        fin >> curNum;
        Double_t curAmp = (Double_t)curNum;
        curClr.SetPixelAmp(curAmp, j+1);
        curEvent.IterAmp(curAmp);
        fin >> curNum;
        Bool_t curTriggValue = (Bool_t)curNum;
        curClr.SetIsPixelTriggered(curTriggValue, j+1);
      }
      curEvent.AddCluster(curClr);
    }
    curEvent.SetNEvent(curNEvent);
    if (fin.eof()) break;
    vectOfEvents->push_back(curEvent);
  }
}
void TAIGARun::removePeds(std::vector<TAIGAEvent> *vectOfEvents) {

}

ClassImp(TAIGARun);
