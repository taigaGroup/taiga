void Hillas();
TAIGACamera camera;
std::vector<TAIGAEvent> vectOfEvents;
void testRun()
{
	TAIGARun run;
	run.SetCameraFileName("/home/ilyas/soft/taigaRoot/taiga/macro/test/data/xy_turn_2019s_EP.txt");
	cout << run.GetCameraFileName() << endl;
	run.readCamera(&camera);
	//camera.Print();
  
  run.SetEventsFileName("/home/ilyas/soft/taigaRoot/taiga/macro/test/data/231119.out_005");
  run.readEvents(&vectOfEvents);

  cout << "NEvents is " << vectOfEvents.size() << endl;
/*  for (Int_t i=0; i<vectOfEvents.size(); i++) {
    vectOfEvents[i].Print();
  }*/
  Hillas();
}

void Hillas() {
  TTree* hillasTr = new TTree("hillas", "hillas");
  Double_t size;
  Double_t width;
  Double_t length;
  Double_t distance;
  Double_t azwidth;
  Double_t miss;
  Double_t alpha;
  hillasTr->Branch("size", &size, "size/D");
  hillasTr->Branch("width", &width, "width/D");
  hillasTr->Branch("length", &length, "length/D");
  hillasTr->Branch("distance", &distance, "distance/D");
  hillasTr->Branch("azwidth", &azwidth, "azwidth/D");
  hillasTr->Branch("miss", &miss, "miss/D");
  hillasTr->Branch("alpha", &alpha, "alpha/D");

  for (Int_t i=0; i<vectOfEvents.size(); i++) {
    Int_t NTriggClrs = vectOfEvents[i].GetNumberOfTriggeredClusters();
    Double_t mX=0.; Double_t mY=0.;
    Double_t mXX=0.; Double_t mYY=0.; Double_t mXY=0.;
    for (Int_t ii=0; ii <NTriggClrs; ii++) {
      TAIGACluster curClr = vectOfEvents[i].GetCluster(ii);
      for (Int_t iii=0; iii<NUMBER_OF_PIXELS; iii++) {
        Double_t curX = camera.GetPixelXcor(curClr.GetNCluster(), iii+1);
        Double_t curY = camera.GetPixelYcor(curClr.GetNCluster(), iii+1);
        Double_t curAmp = curClr.GetPixelAmp(iii+1);
        mX += curAmp*curX; mY += curAmp*curY;
        mXX += curAmp*curX*curX; mYY += curAmp*curY*curY; mXY += curAmp*curX*curY;
      }
    }
    Double_t curIntegral = vectOfEvents[i].GetIntegralofAmp();
    mX /= curIntegral; mY /= curIntegral;
    mXX /= curIntegral; mYY /= curIntegral; mXY /= curIntegral;
    Double_t sigmaXX = mXX-mX*mX;
    Double_t sigmaYY = mYY-mY*mY;
    Double_t sigmaXY = mXY-mX*mY;
    Double_t d = sigmaYY-sigmaXX;
    Double_t z = sqrt(d*d + 4.*sigmaXY*sigmaXY);
    size=curIntegral;
    length = sqrt(0.5*(sigmaXX+sigmaYY+z));
    width = sqrt(0.5*(sigmaXX+sigmaYY-z));
    distance = sqrt(mX*mX+mY*mY);
    azwidth = sqrt( (mX*mX*mYY-2.*mX*mY*mXY+mXX*mY*mY)/(distance*distance) );
    Double_t u =1.+d/z;
    Double_t v = 2.-u;
    miss = sqrt(0.5*(u*mX*mX+v*mY*mY) - (2.*sigmaXY*mX*mY)/z );
    alpha = asin(miss/distance)*TMath::RadToDeg();
    hillasTr->Fill();
  }
  hillasTr->StartViewer();
}