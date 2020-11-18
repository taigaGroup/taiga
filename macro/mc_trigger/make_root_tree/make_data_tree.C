const Double_t XTel = 108.52; // [m]
const Double_t YTel = -91.3; // [m]
struct headData
{
  Double_t evId, particle, Energy, Xc, Yc, Theta_tel, Phi_tel, Theta, Phi, h_1int, nshower, nscat, nc, bpe;
};
struct cameraEvData
{
  Double_t P, eid, nc, cid, sec, nsec, amp[28];
};

void make_head(TTree* tree);
void make_camera_events(TTree* tree);

void make_data_tree()
{
  TTree* headT = new TTree("header", "header");
  make_head(headT);
  headT->StartViewer();

  TTree* cameraEvT = new TTree("events", "events");
  make_camera_events(cameraEvT);
  //cameraEvT->StartViewer();
/*
  TCanvas* canv = new TCanvas("canv", "canv", 1500, 1050);
  canv->Divide(7,4);
  for (UInt_t i=0; i<28; i++) {
    canv->cd(i+1);
    TString drawString;
    drawString.Form("evData.amp[%d]", i);
    cameraEvT->Draw(drawString);
    TH1* curH = (TH1*)gPad->FindObject("htemp");
    curH->SetStats(kFALSE);
    gPad->SetLogy();
  }*/
}

// ------------------------------------------------------------------------
void make_head(TTree* tree)
{
  cout << "Processing make_head()..." << endl;
  ifstream fin("../input_data/mc_events_gamma_-1.csv");
  if (!fin.is_open()) {
    cerr << "Can't open input file!" << endl;
    return;
  }

  headData hData;
  tree->Branch("HEAD", &hData);
  Double_t R;
  Double_t XcNorm;
  Double_t YcNorm;
  tree->Branch("R", &R, "R/D");
  tree->Branch("XcNorm", &XcNorm, "XcNorm/D");
  tree->Branch("YcNorm", &YcNorm, "YcNorm/D");

  string str;
  fin >> str; // to skip head of the file
  //cout << str << endl;

  while (!fin.eof()) {
    fin >> str;
    istringstream strFin(str);
    string word;
    for (UInt_t i=0; getline(strFin, word, ','); i++) {
      switch (i) {
        case  0 : hData.evId=stod(word); break;
        case  1 : hData.particle=1.; break;
        case  2 : hData.Energy=stod(word); break;
        case  3 : hData.Xc=stod(word); break;
        case  4 : hData.Yc=stod(word); break;
        case  5 : hData.Theta_tel=stod(word); break;
        case  6 : hData.Phi_tel=stod(word); break;
        case  7 : hData.Theta=stod(word); break;
        case  8 : hData.Phi=stod(word); break;
        case  9 : hData.h_1int=stod(word); break;
        case 10 : hData.nshower=stod(word); break;
        case 11 : hData.nscat=stod(word); break;
        case 12 : hData.nc=stod(word); break;
        case 13 : hData.bpe=stod(word); break;
        default : cerr << "[ERROR]: i can't be more than 13!" << endl; return;
      }
    }
    Double_t curXc = hData.Xc;
    Double_t curYc = hData.Yc;
    XcNorm = curXc-XTel;
    YcNorm = curYc-YTel;
    R = sqrt(XcNorm*XcNorm + YcNorm*YcNorm);

    tree->Fill();
  }
  cout << "The end of make_head()" << endl;
}
// -------------------------------------------------------------------
void make_camera_events(TTree* tree)
{
  cout << "make_camera_events() Processing..." << endl;
  ifstream fin("../input_data/camera_events_gamma_-1.csv");
  if (!fin.is_open()) {
    cerr << "Can't open input file!" << endl;
    return;
  }

  cameraEvData evData;
  tree->Branch("evData", &evData, "P/D:eid:nc:cid:sec:nsec:amp[28]");

  string str;
  fin >> str; // to skip head of the file
  //cout << str << endl;

  while (!fin.eof()) {
    fin >> str;
    istringstream strFin(str);
    string word;
    for (UInt_t i=0; getline(strFin, word, ','); i++) {
      switch (i) {
        case 0  : evData.P=stod(word); break;
        case 1  : evData.eid=stod(word); break;
        case 2  : evData.nc=stod(word); break;
        case 3  : evData.cid=stod(word); break;
        case 4  : evData.sec=stod(word); break;
        case 5  : evData.nsec=stod(word); break;
        default : evData.amp[i-6]=stod(word); break;
      }
    }
    tree->Fill();
  }
  cout << "The end of make_camera_events()" << endl;
}
