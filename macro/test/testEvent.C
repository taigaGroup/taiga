/* This is a test macro for testing and debug TAIGAEvent class.
*/

// Author: Satyshev Ilyas. JINR

void testEvent(Int_t rndIndex=0)
{
  std::vector<TAIGAEvent> vectOfEvents;

  ifstream fin("data/231119.out_005");
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
    vectOfEvents.push_back(curEvent);
  }

  cout << "NEvents is " << vectOfEvents.size() << endl;
  for (Int_t i=0; i<vectOfEvents.size(); i++) {
    vectOfEvents[i].Print();
  }
}
