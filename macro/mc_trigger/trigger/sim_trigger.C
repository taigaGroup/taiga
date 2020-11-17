Int_t nBins=10;
Double_t minBin=0.;
Double_t maxBin=2.;
struct headData
{
  Double_t evId, particle, Energy, Xc, Yc, Theta_tel, Phi_tel, Theta, Phi, h_1int, nshower, nscat, nc, bpe;
};
struct cameraEvData
{
  Double_t P, eid, nc, cid, sec, nsec, amp[28];
};
std::vector<headData> vOfHeadData;
std::vector<headData> vofTriggHeadData;
std::vector<cameraEvData> vOfCamEvData;

void read_head();
void read_events_in_camera();
void Logy(TH1D* hist);
void sim(Double_t thr, Int_t pix);
Int_t GetNumberOfEvents(std::vector<cameraEvData> v);
TH1D* Get_Energy_Histo(std::vector<headData> v, TString name);
TH1D* Get_Ratio(TH1D* h1, TH1D* h2);
// ---------------------------------------------------------
void sim_trigger()
{
  read_head();
  cout << "NEntries in HEAD is " << vOfHeadData.size() << endl;
  read_events_in_camera();
  cout << "NEntriesIn in Camera Events is " << vOfCamEvData.size() << endl;


  Double_t thr=20.;
  Int_t pix=10;
  sim(thr, pix);

  TCanvas* canv = new TCanvas("canv", "canv", 800, 1000);
  canv->Divide(1, 2);
  TH1D* baseEH = Get_Energy_Histo(vOfHeadData, "allE");
  Logy(baseEH);
  canv->cd(1);
  baseEH->Draw();
  baseEH->SetLineWidth(4);

  TH1D* triggEH = Get_Energy_Histo(vofTriggHeadData, "triggE");
  Logy(triggEH);
  canv->cd(2);
  triggEH->Draw();
  triggEH->SetLineWidth(4);

  TLegend* leg = new TLegend(1., 1., 0.80, 0.80);
  TH1D* ratio = Get_Ratio(baseEH, triggEH);
  //canv->cd(3);
  //ratio->Draw();
  ratio->SetLineWidth(4);
  ratio->SetLineColor(kRed);
  ratio->SetStats(kFALSE);
  TString legName;
  legName.Form("thr=%d,pix=%d", (Int_t)thr, pix);
  leg->AddEntry(ratio, legName, "l");
  //leg->Draw();

  TCanvas* canv2 = new TCanvas("canv2", "canv2", 800, 1000);
  canv2->cd(1);
  ratio->Draw();
  leg->Draw();
  /*
  TFile* file = new TFile("out.root", "UPDATE");
  canv->Write();*/
}

// ----------------------------------------------------------
void read_head()
{
  cout << "read_head() Processing..." << endl;
  ifstream fin("../input_data/mc_events_gamma_-1.csv");
  if (!fin.is_open()) {
    cerr << "Can't open input file!" << endl;
    return;
  }

  string str;
  fin >> str; // to skip head of the file
  //cout << str << endl;

  while (!fin.eof()) {
    fin >> str;
    istringstream strFin(str);
    string word;
    headData hData;
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
    vOfHeadData.push_back(hData);
  }
  cout << "The end of read_head()" << endl;
}
void read_events_in_camera()
{
  cout << "read_events_in_camera() Processing..." << endl;
  ifstream fin("../input_data/camera_events_gamma_-1.csv");
  if (!fin.is_open()) {
    cerr << "Can't open input file!" << endl;
    return;
  }

  cameraEvData evData;

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
    vOfCamEvData.push_back(evData);
  }
  cout << "The end of read_events_in_camera()" << endl;
}

void Logy(TH1D* hist)
{
  for (UInt_t i=0; i<=hist->GetNbinsX(); i++) {
    //cout << hist->GetName() << " " << i << ": " << hist->GetBinContent(i) << endl;
    Double_t curBinContent = hist->GetBinContent(i);
    Double_t newBinContent;
    if (curBinContent > 0.) newBinContent = log10(curBinContent);
    else                    newBinContent = curBinContent;
    hist->SetBinContent(i, newBinContent);
  }

}

Int_t GetNumberOfEvents(std::vector<cameraEvData> v)
{
  Double_t prevEvId=-1;
  Int_t counter=0;
  for (UInt_t iEv=0; iEv<v.size(); iEv++) {
    Double_t curEvId = v[iEv].eid;
    if (curEvId != prevEvId) counter++;
    prevEvId = curEvId;
  }
  return counter+1;
}

TH1D* Get_Energy_Histo(std::vector<headData> v, TString name)
{
  TH1D* histo = new TH1D(name, name, nBins, minBin, maxBin);
  for (UInt_t i=0; i<v.size(); i++) {
    Double_t curE = v[i].Energy;
    curE = log10(curE);
    histo->Fill(curE);
  }
  return histo;
}

void sim(Double_t thr, Int_t pix)
{
  cout << "Before trigger number of events: " << GetNumberOfEvents(vOfCamEvData) << endl;
  UInt_t evId=1;
  UInt_t curPix=0;
  for (UInt_t i=0; i<vOfCamEvData.size(); i++) {
    Int_t curEvId = vOfCamEvData[i].eid;
    if (curEvId != evId) {
      if (curPix > pix) {
        vofTriggHeadData.push_back(vOfHeadData[evId]);
      }
      evId++;
      curPix=0;
    }
    for (UInt_t iPix=0; iPix<28; iPix++) {
      Double_t curAmp = vOfCamEvData[i].amp[iPix];
      if (curAmp > thr) curPix++;
    }

    // Include last string
    if (i == vOfCamEvData.size()-1) {
      //cout << i  << ": ";
      if (curPix > pix) {
        //cout << "yes!";
        vofTriggHeadData.push_back(vOfHeadData[evId]);
      }
      //cout << endl;
    }
  }
}

TH1D* Get_Ratio(TH1D* h1, TH1D* h2)
{
  TString ratioTitle;
  ratioTitle.Form("ratio_of_%s_/_%s", TString(h2->GetName()).Data(), TString(h1->GetName()).Data());
  TH1D* ratio = new TH1D("ratio", ratioTitle, nBins, minBin, maxBin);
  for (Int_t i=0; i<=nBins; i++) {
    Double_t E1= h1->GetBinContent(i);
    Double_t E2= h2->GetBinContent(i);
    Double_t R;
    if (E1 != 0) R = E2 / E1;
    else R = 0.;
    ratio->SetBinContent(i, R);
    cout << "E1=" << E1 << ", E2=" << E2 << ", R=" << R << endl;
  }
  return ratio;
}
