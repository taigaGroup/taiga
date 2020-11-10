
//ofstream trashOut("trash.txt");
//#define debug trashOut << "[DEBUG]: "

#define debug cout << "[DEBUG]: "

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
  debug << "Processing read_input_txt_v1(camera) ..." << endl;
  // Open input file with params of the camera
  ifstream inputDataIn("../test/data/xy_turn_2019s_EP.txt");
  if (!inputDataIn.is_open()) {
    cerr << "read_input_txt_v1()[ERROR]: Can't read input file!" << endl;
    return;
  }
  //Int_t counter = 0;
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
  while(!inputDataIn.eof()) {
    Int_t curNcl, curLen, curNFeu, curNan, curNdin, curH;
    Double_t curXcm, curYcm;
    inputDataIn >> curNcl >> curNFeu >> curLen >> curXcm >> curYcm >> curNan >> curNdin >> curH;
    debug << curNcl << " " << curNFeu << " " << curLen<< " " << curXcm << " " << curYcm << " " << curNan << " "
          << curNdin << " " << curH << endl;
    /*
    counter++;
    if (counter == 3) break;
    */

    camera->SetPixelXcor(curXcm, curNcl, curNFeu); // Xcor, NClaster, NPixel
    camera->SetPixelXcor(curYcm, curNcl, curNFeu); // Xcor, NClaster, NPixel
  }
}
// ----------------------------------------------------------------
void read_input_txt_v2(TAIGACamera* camera)
{
  debug << "Processing read_input_txt_v2(camera) ..." << endl;
  // Open input file with params of the camera
  ifstream inputDataIn("input_data/md1-250300-noi2-trigger6-no-cleaning.txt");
  if (!inputDataIn.is_open()) {
    cerr << "read_input_txt_v2()[ERROR]: Can't read input file!" << endl;
    return;
  }
  Int_t counter = 0;
  // Loop over the files head. To skip It.

}
