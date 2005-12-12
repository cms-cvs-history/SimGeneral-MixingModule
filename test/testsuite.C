{
TFile f("histos.root");
int bcr;
for (bcr=-5;bcr<=3;bcr++)
{
  char name[20] ;
  sprintf(name,"Canvas_Bcr_%d",bcr);
  TCanvas *c = new TCanvas(name,name);
  gPad->Divide(3,3);
  // SimTracks
  gPad->cd(1);
  sprintf(name,"Tracks_%d",bcr);
  TH1I * hist = (TH1I*)f.Get(name);
  hist->Draw();
  c->cd(2);
  sprintf(name,"VtxPointers_signal_%d",bcr);
  TH1I * hist = (TH1I*)f.Get(name);
  hist->Draw();
  c->cd(3);
  sprintf(name,"VtxPointers_%d",bcr);
  TH1I * hist = (TH1I*)f.Get(name);
  hist->Draw();
  // SimVertices
  c->cd(4);
  sprintf(name,"Vertices_%d",bcr);
  TH1I * hist = (TH1I*)f.Get(name);
  hist->Draw();
  c->cd(5);
  sprintf(name,"TrackPointers_signal_%d",bcr);
  TH1I * hist = (TH1I*)f.Get(name);
  hist->Draw();
  c->cd(6);
  sprintf(name,"TrackPointers_%d",bcr);
  TH1I * hist = (TH1I*)f.Get(name);
  hist->Draw();
  c->cd(7);
  sprintf(name,"Tof_%d",bcr);
  TH1I * hist = (TH1I*)f.Get(name);
  hist->Draw();
  c->cd(8);
 
}
}
