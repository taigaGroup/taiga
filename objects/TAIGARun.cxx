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
    std::cerr << "read_input_txt_v1()[ERROR]: Can't read input file!" << std::endl;
    cameraReadStatus=kFALSE;
  }

  // Loop over the files head. To skip It.
  while (!inputDataIn.eof()) {
    std::string testStr;
    inputDataIn >> testStr;
    if (testStr == "h") break;
  }

  if (inputDataIn.eof()) {
    std::cerr << "read_input_txt_v1()[ERROR]: End of the file, stop flag wasn't found!" << std::endl;
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
    
  while (!fin.eof() && eventsReadStatus) {
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
      curEvent.SetTime(timeStr);

      for (Int_t j=0; j<NUMBER_OF_PIXELS; j++) {
        fin >> curNum;
        Double_t curAmp = (Double_t)curNum;
        curClr.SetPixelAmp(curAmp, j+1);
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
    
   TString path = GetPedsFileName();  
   
   ifstream in(path.Data());
  
    vector<double> vectofNc;
    vector<double> vectofNpix;
    vector<double> vectofPed;
    vector<double> vectofSigm;
    vector<double> vectofstat;
  
    double tmp1, tmp2, tmp3, tmp4, tmp5; 
    
     for(Int_t i=0; i<1408; i++) {
          
         in>>tmp1>>tmp2>>tmp3>>tmp4>>tmp5;
         vectofNc.push_back(tmp1);
         vectofNpix.push_back(tmp2);
         vectofPed.push_back(tmp3);
         vectofSigm.push_back(tmp4);
         vectofstat.push_back(tmp5);       
     }
 
    for (Int_t i=0; i<vectOfEvents->size(); i++) {
     
        int a = vectOfEvents[i].GetNumberOfTriggeredClusters(); 
         for(int k=0; k<a; k++) {
             TAIGACluster curClr;  
         
             curClr = vectOfEvents[i].GetCluster(k);
             int Ncl = vectOfEvents[i].GetCluster(k).GetNCluster(); // Ncl of this cluster
                    
             Double_t arrp[64], arrs[64];  // ped and sigma of ONE cluster with #Ncl
             const int n = (Ncl-1)*64;
 
             for(Int_t i=0; i<64; i++) {
                 arrp[i]=vectofPed[n+i]; //ped for this cluster
                 arrs[i]=vectofSigm[n+i]; // sigma for this cluster 
             }
     
             for (Int_t j=0; j<NUMBER_OF_PIXELS; j++) { 
                  double aa = curClr.GetPixelAmp(j+1) - arrp[j];       
                  curClr.SetPixelAmp(aa, j+1); 
             }
             vectOfEvents[i].AddCluster(curClr);
         }           
    }
     

 
}

ClassImp(TAIGARun);
