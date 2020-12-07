// Test camera class
//Author is Maria L

#include <Riostream.h>
#include <TMath.h>
#include "TString.h"
#include <TMath.h>
#include "TString.h"
#include <TStyle.h>

using namespace std;
using namespace TMath;


void taigaTestCamera()  {     
     
   TString path = "/home/maria/TAIGA/xy_turn_2019s_EP.txt";  
   ifstream in(path.Data());
            
   string headinf[76];              // this massiv has no valuable information
   vector<int> vectofNcl;
   vector<int> vectofNFeu;
   vector<double> vectofLen;
   vector<double> vectofX;          //cm
   vector<double> vectofY;          //cm
   vector<double> vectofNan;
   vector<double> vectofNdir;
   vector<double> vectofh;
   vector <double> vectofcurX;
   vector <double> vectofcurY;
  
   for (Int_t i=0; i<76; i++) { 
         in>>headinf[i];
   }
  
  
   Double_t tmp1, tmp2,tmp3,tmp4, tmp5, tmp6, tmp7, tmp8;  
   
   while (in >> tmp1>>tmp2>>tmp3>>tmp4>>tmp5>>tmp6>>tmp7>>tmp8) {
       
          vectofNcl.push_back(tmp1);
          vectofNFeu.push_back(tmp2);
          vectofLen.push_back(tmp3);
          vectofX.push_back(tmp4);
          vectofY.push_back(tmp5);
          vectofNan.push_back(tmp6);
          vectofNdir.push_back(tmp7);
          vectofh.push_back(tmp8);
   }
    
   
   Double_t cuX, cuY;
   
   TAIGACamera *obj= new TAIGACamera;
      
    
   for (Int_t i=0; i<vectofh.size(); i++) {   
        
        obj->SetPixelXcor(vectofX[i], vectofNcl[i], vectofNFeu[i]);
        obj->SetPixelYcor(vectofY[i], vectofNcl[i], vectofNFeu[i]);
         
        cuX = obj->GetPixelXcor(vectofNcl[i], vectofNFeu[i]);
        cuY = obj->GetPixelYcor(vectofNcl[i], vectofNFeu[i]);
                 
        vectofcurX.push_back(cuX);
        vectofcurY.push_back(cuY); 
        
   }
    
      
   const int till= vectofh.size();
       
   for(Int_t i=0; i<till; i++)  { 
       for(Int_t j=0; j<till; j++)  {
           
           Double_t l;      //distance between 2 pixels
           
           if(i!=j) {
              l = sqrt(abs((vectofcurX[i]-vectofcurX[j])*(vectofcurX[i]-vectofcurX[j]) + (vectofcurY[i]-vectofcurY[j])*(vectofcurY[i]-vectofcurY[j])));
                
              if(l<MAX_DIST_BETWEEN_2_NEIGHBORS) {
                 obj->AddPixelNeighbor(vectofNcl[i], vectofNcl[j], vectofNFeu[i], vectofNFeu[j]);
              }
           }      
       }
   }
    
    
  //  obj->Print();                 //work
  //  obj->PrintNeighborsInfo();   //work
    
}
