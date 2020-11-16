
ofstream trashOut("trash.txt");
#define debug trashOut << "[DEBUG]: "

//#define debug cout << "[DEBUG]: "
#define info  cout << "[INFO]: "

void read_input_txt_v1(TAIGACamera* camera);
void read_input_txt_v2(TAIGACamera* camera);
void add_neighbors_info(TAIGACamera* camera);
// ----------------------------------------------------------------
void read_camera(Bool_t txtVersion = kTRUE)
{
  TAIGACamera camera;
  //txtVersion = kFALSE;
  (txtVersion) ? read_input_txt_v1(&camera) : read_input_txt_v2(&camera);

  camera.Print();
}

// ----------------------------------------------------------------
void read_input_txt_v1(TAIGACamera* camera)
{
  info << "Processing read_input_txt_v1(camera) ..." << endl;
  // Open input file with params of the camera
  ifstream inputDataIn("../test/data/xy_turn_2019s_EP.txt");
  if (!inputDataIn.is_open()) {
    cerr << "read_input_txt_v1()[ERROR]: Can't read input file!" << endl;
    return;
  }
  // Loop over the files head. To skip It.
  while (!inputDataIn.eof()) {
    string testStr;
    inputDataIn >> testStr;
    if (testStr == "h") break;
  }
  if (inputDataIn.eof()) {
    cerr << "read_input_txt_v1()[ERROR]: End of the file, stop flag wasn't found!" << endl;
    return;
  }
  UInt_t counter = 0;
  while(!inputDataIn.eof()) {
    Int_t curNcl, curLen, curNFeu, curNan, curNdin, curH;
    Double_t curXcm, curYcm;
    inputDataIn >> curNcl >> curNFeu >> curLen >> curXcm >> curYcm >> curNan >> curNdin >> curH;
    debug << curNcl << " " << curNFeu << " " << curLen<< " " << curXcm << " " << curYcm << " " << curNan << " "
          << curNdin << " " << curH << endl;
    camera->SetPixelXcor(curXcm, curNcl, curNFeu); // Xcor, NClaster, NPixel
    camera->SetPixelYcor(curYcm, curNcl, curNFeu); // Ycor, NClaster, NPixel
    counter++;
  }

  info << "Counts is " << counter << endl;
  info << "read_input_txt_v1 processing end!" << endl;
}
// ----------------------------------------------------------------
void read_input_txt_v2(TAIGACamera* camera)
{
  info << "Processing read_input_txt_v2(camera) ..." << endl;
  // Open input file with params of the camera
  ifstream inputDataIn("input_data/md1-250300-noi2-trigger6-no-cleaning.txt");
  if (!inputDataIn.is_open()) {
    cerr << "read_input_txt_v2()[ERROR]: Can't read input file!" << endl;
    return;
  }
  
  std::vector<Int_t> vOfNclId;
  // Loops over the file. To fill vOfNclId.
  while (!inputDataIn.eof()) {
    string testStr;
    inputDataIn >> testStr;
    //debug << testStr << endl;
    if (testStr == "id=1") break;
  } // End of the loop to skip the other info!
  // add It because cluster id=1 was skipped before
  vOfNclId.push_back(1);
  while (!inputDataIn.eof()) {
    string testStr;
    inputDataIn >> testStr;
    //debug << testStr << endl;
    if (testStr == "[events]") break;
    Int_t curPosInInputDataIn = (Int_t)testStr.length();
    inputDataIn.seekg(-curPosInInputDataIn, inputDataIn.cur);
    Int_t curNcl;
    inputDataIn >> curNcl;
    vOfNclId.push_back(curNcl);
  } // End of the vOfNclId filling loop 
  
  // Checking clusters is reading
  /*for (Int_t i=0; i<vOfNclId.size(); i++) {
    debug << i+1 << ": cid=" << vOfNclId[i] << endl;
  }*/

  inputDataIn.seekg(0, inputDataIn.beg); // set the cur in input file to the begin
  
  // Loop over the files head. To skip It.
  while (!inputDataIn.eof()) {
    string testStr;
    inputDataIn >> testStr;
    //debug << testStr << endl;
    if (testStr == "X[mm]=-15") break;
  }

  std::vector<Double_t> vOfXmm;
  // add It because X[mm]=-15 was skipped before
  vOfXmm.push_back(-15.);
  UInt_t curNcl=0;
  // Loop over the file. To read all Xmm
  while (!inputDataIn.eof()) {
    string testStr;
    inputDataIn >> testStr;
    if (testStr == "Y[mm]=-77.9422863405994803542853333055973052978515625") break;
    Int_t curPosInInputDataIn = (Int_t)testStr.length();
    inputDataIn.seekg(-curPosInInputDataIn, inputDataIn.cur);
    Double_t curXmm;
    inputDataIn >> curXmm;
    vOfXmm.push_back(curXmm);
  }

  std::vector<Double_t> vOfYmm;
  // add It because Y[mm]=-77.9423 was skipped before
  vOfYmm.push_back(-77.9423);
  curNcl=0;
  // Loop over the file. To read all Ymm
  while (!inputDataIn.eof()) {
    string testStr;
    inputDataIn >> testStr;
    if (testStr == "[clusters]") break;
    Int_t curPosInInputDataIn = (Int_t)testStr.length();
    inputDataIn.seekg(-curPosInInputDataIn, inputDataIn.cur);
    Double_t curYmm;
    inputDataIn >> curYmm;
    vOfYmm.push_back(curYmm);
  }
  
  info << "Nclid counts is " << vOfNclId.size() << endl;
  info << "Xmm counts is "   << vOfXmm.size()   << endl;
  info << "Ymm counts is "   << vOfYmm.size()   << endl;
  
  // Camera filling
  UInt_t curNFeu=0;
  UInt_t beforeNcl=vOfNclId[1];
  for (UInt_t i=0; i<vOfNclId.size(); i++) {
    (vOfNclId[i] == beforeNcl) ? curNFeu++ : curNFeu=1;
    Double_t curXcm = 0.1*vOfXmm[i];
    camera->SetPixelXcor(curXcm, vOfNclId[i], curNFeu); // Xcor, NClaster, NPixel 
    Double_t curYcm = 0.1*vOfYmm[i];
    camera->SetPixelYcor(curYcm, vOfNclId[i], curNFeu); // Xcor, NClaster, NPixel
    //debug << "cid: " << vOfNclId[i] << " nfeu: " << curNFeu << endl;
    beforeNcl=vOfNclId[i];
  }
  
  vOfNclId.clear();
  vOfXmm.clear();
  vOfYmm.clear();
  info << "read_input_txt_v2 processing end!" << endl;
}
