/* This is a test macro for testing and debug TAIGACamera class.
*/

// Author: Satyshev Ilyas. JINR
void testCamera()
{
  TAIGACamera camera;
	Int_t nnei=1407;
	Double_t xc(0.), yc(0.);
  for (Int_t ii = 0; ii < NUMBER_OF_CLUSTERS; ii++) {
  	for (Int_t jj = 0; jj < NUMBER_OF_PIXELS; jj++) {
  		camera.SetPixelXcor(xc, ii, jj);
  		camera.SetPixelYcor(yc, ii, jj);
  		camera.SetPixelAmp(xc, ii, jj);
  		camera.SetIsPixelTriggered(kTRUE, ii, jj);
  		for (Int_t kk = 0; kk < nnei; kk++) {
        camera.AddPixelNeighbor(ii, 0, jj, 0);
  		}
  		xc+=1.; yc-=1.; nnei--;
  	}
  }
  camera.Print();
}
