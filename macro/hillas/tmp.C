void ReadCamera();
void ReadEvents();
void Hillas();
TAIGACamera camera;
std::vector<TAIGAEvent> vectOfEvents;
// ----------------------------------------------
void tmp()
{
  ReadCamera();
  ReadEvents();
  Hillas();
}

// ----------------------------------------------
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
    alpha = asin(miss/distance);
    hillasTr->Fill();
  }
  hillasTr->StartViewer();
}

// ----------------------------------------------
void ReadCamera() {
  TString path = "../test/data/xy_turn_2019s_EP.txt";
  ifstream in(path.Data());
  if (!in.is_open()) {
    cerr << "Can't read camera!" << endl;
    return;
  }

  string a[76];
  vector<int> arrNcl;
  vector<int> arrNFeu;
  vector<double> arrLen;
  vector<double> arrX; //cm
  vector<double> arrY; //cm
  vector<double> arrNan;
  vector<double> arrNdir;
  vector<double> arrh;
  vector <double> arrcurX;
  vector <double> arrcurY;

  for (int i=0; i<76; i++) {
    in>>a[i];
    //cout << "a[" << i << "]=" << a[i] << endl;
  }

  double tmp1, tmp2,tmp3,tmp4, tmp5, tmp6, tmp7, tmp8;
  UInt_t counter=0;
  while (in >> tmp1>>tmp2>>tmp3>>tmp4>>tmp5>>tmp6>>tmp7>>tmp8) {
    counter++;
    arrNcl.push_back(tmp1);
    arrNFeu.push_back(tmp2);
    arrLen.push_back(tmp3);
    arrX.push_back(tmp4);
    arrY.push_back(tmp5);
    arrNan.push_back(tmp6);
    arrNdir.push_back(tmp7);
    arrh.push_back(tmp8);
  }

  Double_t curX, curY;
  for (int i=0; i<arrh.size(); i++) {
    camera.SetPixelXcor(arrX[i], arrNcl[i], arrNFeu[i]);
    camera.SetPixelYcor(arrY[i], arrNcl[i], arrNFeu[i]);

    curX = camera.GetPixelXcor(arrNcl[i], arrNFeu[i]);
    curY = camera.GetPixelYcor(arrNcl[i], arrNFeu[i]);

    arrcurX.push_back(curX);
    arrcurY.push_back(curY);
  }

  const int aa= arrcurX.size();

  for(int i=0; i<aa; i++)  {
    for(int j=0; j<aa; j++)  {
      double l; //distance between 2 pixels
      if(i!=j) {
        l = sqrt(abs((arrcurX[i]-arrcurX[j])*(arrcurX[i]-arrcurX[j]) + (arrcurY[i]-arrcurY[j])*(arrcurY[i]-arrcurY[j])));
        if(l<MAX_DIST_BETWEEN_2_NEIGHBORS) {
          camera.AddPixelNeighbor(arrNcl[i], arrNcl[j], arrNFeu[i], arrNFeu[j]);
        }
      }
    }
  }
  //camera.Print();
}

// ----------------------------------------------
void ReadEvents() {
  ifstream fin("../test/data/231119.out_005");
  if (!fin.is_open()) {
    cerr << "Can't read Input txt!" << endl;
    return;
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
      string timeStr;
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
    vectOfEvents.push_back(curEvent);
  }

  cout << "NEvents is " << vectOfEvents.size() << endl;
  /*
  for (Int_t i=0; i<vectOfEvents.size(); i++) {
    vectOfEvents[i].Print();
  }
  */
}

